# Description

While developping in node.js (http://nodejs.org) I often need to re-run a script (in the Terminal) and check it's output almost like TTD but more like experimenting.

*node-watch* watches a list of files or folders and runs a particular script in node when any of the files or script have changed.


# Install

## Requirements: OSX ONLY! :(

The node-watch script is using a little binary executable (source included in src/) that makes use of kqueue in OSX to register for file descriptors changes which is a lot better than polling the filesystem every 500 ms or whatever.
Since my development plateform is a mac laptop and because I didn't have the time (yet) to investigate on how to do the very same on GNU/Linux and other OSes it will only work on OSX.

## Installation

Make a link in one of you binary search PATH directory to the node-watch script

	  $ cd ~/bin
	  $ ln -s path-to-node-watch/node-watch

## Usage

    $ node-watch
    Usage: /Users/orion/bin/node-watch [<filename> [<filename> ...]] <script-to-run.js>

Remark: the *script-to-run.js* is implicitly watched

Now, open a new Terminal and change the directory to your current development path

    $ cd my-dev
	  $ ls
	  my-class.js my-tests.js README.md foo.js

Start the node-watch for two of the files I am currently working on

	  $ node-watch my-class.js my-test.js

Then for example, edit my-test.js or my-class.js in you favorite editor. (The best result is obtained when you can see the terminal while editing the files in you editor).

When you save any of these two files the script _my-test.js_ will be re-run in node and you will see it's new output in the Terminal.

## Extra

As an extra benefit, you can re-use the watchfiles binary for many other things, it's simple as possible.

    Usage: watchfiles <file-path> [<file-path> ...]

*watchfiles* watches for changes for a list of files or folders and exits when a change occurs. It is very efficient and uses 0% CPU :) because of the kqueue usage.

## Other

If you want to contribute and make a watchfiles for other OSes please let me know.

## License terms

Copyright (c), 2012 Thierry Passeron

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
