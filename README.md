<p align="center">
  <a href="http://git.home.network/0x1eef/mruby-kernel-process">
    <img src="https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEi39c9ab6rTHulzqrvy45M_omMN8cUyRxfaAph0UhlpubhMxgnJVyOEarYGmHNZgt1uUZmO8cobmrloSiAfxUjgjNOVvRZrF9n9b5tO0S-sG7e9DHfalqyYQZm6aY1jV55IzPbGPA/s1600/freebsd_jail.png" width="200" height="200" border="0" alt="mruby-kernel-process">
  </a>
</p>
<p align="center">
  <a href="http://git.home.network/0x1eef/mruby-kernel-process">
    <img src="https://img.shields.io/badge/FreeBSD-native-blue.svg" alt="FreeBSD-native">
  </a>
  <a href="https://opensource.org/license/0bsd">
    <img src="https://img.shields.io/badge/License-0BSD-orange.svg" alt="License">
  </a>
</p>

## About

[mruby-kernel-process](https://github.com/0x1eef/mruby-kernel-process)
provides an object-oriented interface around processes on FreeBSD
systems. Unlike shelling out to ps(1), this library reads process
information through FreeBSD's native libutil(3) interfaces &ndash;
in particular [kinfo_getproc(3)](https://man.freebsd.org/kinfo_getproc)
and [kinfo_getallproc(3)](https://man.freebsd.org/kinfo_getallproc).

## Why "Kernel" ?

The two functions that we use are implemented as easy-to-use wrappers
around [sysctl(3)](https://man.freebsd.org/sysctl) &ndash; which is used
to query kernel state, including information about active processes, hence
the name "Kernel Process". It also avoids confusion and conflict with
mruby-process.

## Quick start

#### Kernel::Process

The Kernel::Process singleton class is enumerable. It provides
access to all processes that are visible to a user. We can
use the `each` method to iterate over processes, we can use
the `select` method to filter, and we can use the `map` method
to trasform:

```ruby
##
# Iterate all
Kernel::Process.each do |process|
  print "pid=#{process.pid}",
        "ppid=#{process.ppid}",
        "uid=#{process.uid}",
        "\n\n"
end

##
# Select root processes
Kernel::Process.select do |process|
  process.uid == 0
end

##
# Transform processes
parents = Kernel::Process.map(&:ppid)
```

#### Kernel::Process.self

The `Kernel::Process.self` method returns an instance
of `Kernel::Process` that represents the current process:

```ruby
this = Process.self
print "pid = ", this.pid, "\n"
```

#### Kernel::Process.find_by

The `Kernel::Process.find_by` method can find a process by ID, and returns an
instance of `Kernel::Process` or raises an error when a process by the given
ID cannot be found:

```ruby
process = Kernel::Process.find_by(12345)
print "pid " , "\t", process.pid  , "\n"  # => process ID
print "ppid ", "\t", process.ppid , "\n"  # => parent process ID
print "uid " , "\t", process.uid  , "\n"  # => effective user id
print "ruid ", "\t", process.ruid , "\n"  # => real user id
print "svuid", "\t", process.svuid, "\n"  # => saved user id
```

#### Kernel::Process#reload

The `Kernel::Process` object represents a snapshot of a process
in a moment of time. Certain values, such as the process runtime
(`Kernel::Process#runtime`) are constantly changing but the process
snapshot does not capture the new state unless you run
`Kernel::Process#reload`:

```ruby
this = Kernel::Process.self
print "runtime = ", this.runtime
1.upto(100_000) { }
print "runtime = ", this.reload.runtime
```

## ABI

Supported:

| `struct kinfo_proc` member | Ruby API | Notes |
| --- | --- | --- |
| `ki_jid` | `#jid` | Process jail ID |
| `ki_pid` | `#pid` | Process ID |
| `ki_ppid` | `#ppid`, `#parent` | Parent process ID; `#parent` resolves the parent process object |
| `ki_pgid` | `#pgid` | Process group ID |
| `ki_sid` | `#sid` | Session ID |
| `ki_tpgid` | `#tpgid` | Terminal process group ID |
| `ki_uid` | `#uid` | Effective user ID |
| `ki_ruid` | `#ruid` | Real user ID |
| `ki_svuid` | `#svuid` | Saved effective user ID |
| `ki_login` | `#login` | Login name |
| `ki_loginclass` | `#login_class` | Login class |
| `ki_comm` | `#command` | Command name |
| `ki_start` | `#start_time`, `#starts_at` | Process start time |
| `ki_runtime` | `#runtime` | Runtime in microseconds |

Not supported... yet :)

| `struct kinfo_proc` member | Notes |
| --- | --- |
| `ki_structsize` | Size of this structure |
| `ki_layout` | Reserved layout identifier |
| `ki_args` | Address of command arguments |
| `ki_paddr` | Address of proc |
| `ki_addr` | Kernel virtual address of u-area |
| `ki_tracep` | Pointer to trace file |
| `ki_textvp` | Pointer to executable file |
| `ki_fd` | Pointer to open file info |
| `ki_vmspace` | Pointer to kernel vmspace struct |
| `ki_wchan` | Sleep address |
| `ki_tsid` | Terminal session ID |
| `ki_jobc` | Job control counter |
| `ki_spare_short1` | Unused alignment field |
| `ki_tdev_freebsd11` | Legacy controlling TTY device |
| `ki_siglist` | Signals arrived but not delivered |
| `ki_sigmask` | Current signal mask |
| `ki_sigignore` | Signals being ignored |
| `ki_sigcatch` | Signals being caught by user |
| `ki_rgid` | Real group ID |
| `ki_svgid` | Saved effective group ID |
| `ki_ngroups` | Number of groups |
| `ki_spare_short2` | Unused alignment field |
| `ki_groups` | Groups |
| `ki_size` | Virtual size |
| `ki_rssize` | Current resident set size in pages |
| `ki_swrss` | Resident set size before last swap |
| `ki_tsize` | Text size in pages |
| `ki_dsize` | Data size in pages |
| `ki_ssize` | Stack size in pages |
| `ki_xstat` | Exit status for wait and stop signal |
| `ki_acflag` | Accounting flags |
| `ki_pctcpu` | CPU percentage during `ki_swtime` |
| `ki_estcpu` | Time-averaged value of `ki_cpticks` |
| `ki_slptime` | Time since last blocked |
| `ki_swtime` | Time swapped in or out |
| `ki_cow` | Number of copy-on-write faults |
| `ki_childtime` | Time used by process children |
| `ki_flag` | `P_*` flags |
| `ki_kiflag` | `KI_*` flags |
| `ki_traceflag` | Kernel trace points |
| `ki_stat` | `S*` process status |
| `ki_nice` | Process nice value |
| `ki_lock` | Process lock count |
| `ki_rqindex` | Run queue index |
| `ki_oncpu_old` | Legacy current CPU |
| `ki_lastcpu_old` | Legacy last CPU |
| `ki_tdname` | Thread name |
| `ki_wmesg` | Wait channel message |
| `ki_lockname` | Lock name |
| `ki_emul` | Emulation name |
| `ki_moretdname` | Extended thread name |
| `ki_sparestrings` | Spare string space |
| `ki_spareints` | Spare integer space |
| `ki_reaper` | Reaper process PID |
| `ki_reapsubtree` | Reaper subtree ID |
| `ki_tdev` | Controlling TTY device |
| `ki_oncpu` | Current CPU |
| `ki_lastcpu` | Last CPU |
| `ki_tracer` | Tracing process PID |
| `ki_flag2` | `P2_*` flags |
| `ki_fibnum` | Default FIB number |
| `ki_cr_flags` | Credential flags |
| `ki_numthreads` | Total number of threads |
| `ki_tid` | Thread ID |
| `ki_pri` | Process priority |
| `ki_rusage` | Process resource usage statistics |
| `ki_rusage_ch` | Child process resource usage statistics |
| `ki_pcb` | Kernel virtual address of PCB |
| `ki_kstack` | Kernel virtual address of stack |
| `ki_udata` | User convenience pointer |
| `ki_tdaddr` | Address of thread |
| `ki_pd` | Pointer to process paths info |
| `ki_uerrmsg` | Address of extended error message storage |
| `ki_spareptrs` | Spare pointer space |
| `ki_sparelongs` | Spare long integer space |
| `ki_sflag` | `PS_*` flags |
| `ki_tdflags` | Kernel thread flags |


## Build

```ruby
MRuby::Build.new("app") do |conf|
  conf.toolchain
  conf.gembox "default"
  conf.gem github: "0x1eef/mruby-kernel-process", branch: "main"
end
```

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/)
<br>
See [LICENSE](./LICENSE)
