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


## Quick start

#### BSD::Process

The BSD::Process singleton class is enumerable. It provides
access to all processes that are visible to a user. We can
use the `each` method to iterate over processes, we can use
the `select` method to filter, and we can use the `map` method
to trasform:

```ruby
##
# Iterate all
BSD::Process.each do |process|
  print "pid=#{process.pid}",
        "ppid=#{process.ppid}",
        "uid=#{process.uid}",
        "\n\n"
end

##
# Select root processes
BSD::Process.select do |process|
  process.uid == 0
end

##
# Transform processes
parents = BSD::Process.map(&:ppid)
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
