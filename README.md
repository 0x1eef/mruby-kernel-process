<p align="center">
  <a href="http://git.home.network/0x1eef/mruby-bsd-process">
    <img src="https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEi39c9ab6rTHulzqrvy45M_omMN8cUyRxfaAph0UhlpubhMxgnJVyOEarYGmHNZgt1uUZmO8cobmrloSiAfxUjgjNOVvRZrF9n9b5tO0S-sG7e9DHfalqyYQZm6aY1jV55IzPbGPA/s1600/freebsd_jail.png" width="200" height="200" border="0" alt="mruby-bsd-process">
  </a>
</p>
<p align="center">
  <a href="http://git.home.network/0x1eef/mruby-bsd-process">
    <img src="https://img.shields.io/badge/FreeBSD-native-blue.svg" alt="FreeBSD-native">
  </a>
  <a href="https://opensource.org/license/0bsd">
    <img src="https://img.shields.io/badge/License-0BSD-orange.svg" alt="License">
  </a>
</p>

## About

[mruby-bsd-process](https://github.com/0x1eef/mruby-bsd-process)
provides an object-oriented interface around processes on FreeBSD
systems. Unlike shelling out to ps(1), this library reads process
information through FreeBSD's native
[libutil(3)](https://man.freebsd.org/libutil) interfaces —
specifically [kinfo_getproc(3)](https://man.freebsd.org/kinfo_getproc)
and [kinfo_getallproc(3)](https://man.freebsd.org/kinfo_getallproc).

Exposes fields such as pid, ppid, pgid, sid, tpgid, uid, ruid, and
svuid.

## Quick start

#### BSD::Process.all

The `BSD::Process.all` method returns the processes visible to the
current user:

```ruby
BSD::Process.all.each do |process|
  print "pid=#{process.pid}", "ppid=#{process.ppid}",
        "uid=#{process.uid}", "\n\n"
end
```

Filtering is done on the Ruby side:

```ruby
root_procs = BSD::Process.all.select { |p| p.uid == 0 }
```

#### BSD::Process.find

The `BSD::Process.find` method can find a process by ID, and returns an
instance of `BSD::Process` or raises an error when a process by the given
ID cannot be found:

```ruby
process = BSD::Process.find(Process.pid)
print "pid " , "\t", process.pid  , "\n"  # => process ID
print "ppid ", "\t", process.ppid , "\n"  # => parent process ID
print "uid " , "\t", process.uid  , "\n"  # => effective user id
print "ruid ", "\t", process.ruid , "\n"  # => real user id
print "svuid", "\t", process.svuid, "\n"  # => saved user id
```

## Build

```ruby
MRuby::Build.new("app") do |conf|
  conf.toolchain
  conf.gembox "default"
  conf.gem github: "0x1eef/mruby-bsd-process", branch: "main"
end
```

## License

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/)
<br>
See [LICENSE](./LICENSE)
