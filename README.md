<p align="center">
  <a href="http://git.home.network/0x1eef/mruby-bsd-process">
    <img src="https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEi39c9ab6rTHulzqrvy45M_omMN8cUyRxfaAph0UhlpubhMxgnJVyOEarYGmHNZgt1uUZmO8cobmrloSiAfxUjgjNOVvRZrF9n9b5tO0S-sG7e9DHfalqyYQZm6aY1jV55IzPbGPA/s1600/freebsd_jail.png" width="200" height="200" border="0" alt="mruby-bsd-process">
  </a>
</p>
<p align="center">
  <a href="http://git.home.network/0x1eef/mruby-bsd-process">
    <img src="https://img.shields.io/badge/FreeBSD-Process-blue.svg" alt="FreeBSD Process">
  </a>
  <a href="https://opensource.org/license/0bsd">
    <img src="https://img.shields.io/badge/License-0BSD-orange.svg" alt="License">
  </a>
</p>

## About

[mruby-bsd-process](https://github.com/0x1eef/mruby-bsd-process) provides an object-oriented
interface around processes on FreeBSD systems. Both the [kinfo_getproc(3)](https://man.freebsd.org/kinfo_getproc)
and [kinfo_getallproc(3)](https://man.freebsd.org/kinfo_getallproc) library routines
provide deep, insightful information about running processes, and this library exposes
that information to the mruby runtime.

## Quick start

#### BSD::Process.all

The `BSD::Process.all` method returns all processes that a user
can retrieve from the kernel. For the root user, it provides access
to all running processes on the system:

```ruby
BSD::Process.all.each do |process|
  print "pid=#{process.pid}", "ppid=#{process.ppid}", "uid=#{process.uid}", "\n\n"
end
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
# and much more...
```

## License

0BSDL. <br>
See LICENSE.

