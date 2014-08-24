runas - small program to run a program as another user

Usage:

    $ runas user program [args...]

This runs `program` as user `user`, setting the user ID, group ID,
supplementary groups, and `USER`, `UID`, `HOME`, and `SHELL` environment
variables.

This program is like [gosu][], but is in C instead of Go so it requires almost
no build system.  In general, rewriting programs just because of implementation
languages, especially when things like resource consumption aren't the crucial
matter, isn't a wise use of time.  But gosu's build system is pretty heavy, and
it requires libraries that aren't in Fedora.  This program requires nothing but
the Linux system libraries.

The privilege-dropping logic is inspired by [Privileges::Drop][].  It does not
yet do anything to handle SELinux transitions; that can be considered a bug.

[gosu]: https://github.com/tianon/gosu/
[Privileges::Drop]: https://metacpan.org/source/TLBDK/Privileges-Drop-1.03/lib/Privileges/Drop.pm

## Copyright

Copyright (c) 2014 Michael Ekstrand.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
