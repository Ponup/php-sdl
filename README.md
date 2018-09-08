
[![Build Status](https://travis-ci.org/Ponup/phpsdl.svg?branch=master)](https://travis-ci.org/Ponup/phpsdl)

PHP-SDL
=======

## Installation

### Requirements

* C compiler
* Automake tools
* PHP devel
* libSDL2 devel libraries and headers

### Via PECL (recommended)

```bash
pecl install sdl-beta
```

### Manual

Download the source code and within the main directory run these commands:

```bash
$ phpize --clean
$ phpize
$ ./configure --with-sdl (or --with-sdl=<PATH>)
$ make
$ make test
$ sudo make install
```

Then add

    extension=sdl.so

to your _php.ini_ file.

### Installing on Windows

We are working on the Windows build. Stay tuned.

## Documentation

The SDL extension mimics in almost every single aspect to the official C library, so until we write our own documentation, refer to the [C counterpart](https://wiki.libsdl.org/APIByCategory).

### Example

Standard SDL2 API is available in procedural style:

```php
    $w = SDL_CreateWindow( "Foo window", 500, 50, 350, 300, SDL_WINDOW_SHOWN+SDL_WINDOW_RESIZABLE);
    SDL_SetWindowTitle($w, "Some new title");
    SDL_DestroyWindow($w);
```

And is also available in object oriented style:

```php
    $w = new SDL_Window( "Foo window", 100, 50, 350, 300, SDL_Window::SHOWN|SDL_Window::RESIZABLE);
    $w->SetTitle("Some new title");
    unset($w); // will destroy the window
```

BUILDING ON UNIX etc.
=====================

To compile your new extension, you will have to execute the following steps:

```bash
$ ./phpize
$ ./configure [--enable--sdl] 
$ make
$ make test
$ [sudo] make install
```

BUILDING ON WINDOWS
===================

Not supported yet.

## Support / Feedback / Bugs / Feature Requests

Please submit anything that needs our attention to [issues section](https://github.com/phpsdl/extension/issues) on Github. We are commited to attend any request in a short timespan if it's a sensible matter.
