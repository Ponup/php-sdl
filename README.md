PHP-SDL
=======

## Installation

### Requirements

* C compiler
* Automake tools
* PHP devel
* libSDL v1.2.* devel libraries and headers

### Via PECL (recommended)

  pecl install sdl

### Manual

Download the source code and within the main directory run these commands:

  phpize
  ./configure --with-sdl (or --with-sdl=<PATH>)
  make
  make test
  sudo make install

Then add

    extension=sdl.so

to your _php.ini_ file.

### Installing on Windows

We are working on the Windows build. Stay tuned.

## Documentation

The SDL extension mimics in almost  every single aspect to the official C library, so until we write our own documentation, refer to the [http://www.libsdl.org/release/SDL-1.2.15/docs/index.html](C counterpart).

## Support / Feedback / Bugs / Feature Requests

Please submit anything that needs our attention to [https://github.com/phpsdl/extension/issues](issues section) on Github. We are commited to attend any request in a short timespan if it's a sensible matter.
