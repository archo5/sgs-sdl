# SGScript / SDL2 graphics framework: script-based foundation for GPU-accelerated graphics applications

## Overview

- The framework allows rendering basic 2D / 3D graphics and accept all kinds of input (keyboard, mouse, joystick, touch devices)
- SGScript is right at the core to provide a solid, standalone scripting solution that is easy to use and can be deployed anywhere.
- It's good for creating:
 - games
 - visually rich interactive / UI applications
 - quick visual prototypes
 - other technically complicated creations
- Things not available (yet):
 - browser support
 - advanced automatic text rendering (like HTML, to be handled by an external library)
 - advanced 3D graphics (support is on the way)

## Example Usage

    function initialize()
    {
    	global Window = SS_CreateWindow( "SGS-SDL Game Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 576, SDL_WINDOW_OPENGLMAYBE );
    	Window.initRenderer( SS_RENDERER_DONTCARE, SS_RENDERER_VSYNC );
    }
    function update()
    {
    	SS_Clear( color(0.1,0.2,0.4) );
    	SS_Present();
    }
    function on_event( e )
    {
    	if( e.type == SDL_QUIT )
    		global sys_exit = true;
    }

## Getting Started

- On Windows, `make` can be used in the root directory to fully build the library.
- Creating a new application is as simple as copying the following items from `bin` to a new directory:
 - `core` directory
 - `fonts` directory
 - `FreeImage.dll`
 - `libfreetype-6.dll`
 - `SDL2.dll`
 - `sgscript.dll`
 - `sgs-sdl.dll`
 - `sgs-sdl-debug.exe`
 - `sgs-sdl-release.exe`
- `sgsxgmath.dll`
- `/bin/tests/empty-template.sgs` is a good starting template for `main.sgs`

## Design Goals

- Main goal is for the framework to be portable. To be able to just download the data and keep working on it anywhere.
- Another goal is substantial coverage. Supporting most common formats and features for sufficient compatibility.
- Third goal is simplicity. It should be easy to infinitely expand on the foundations while building applications for maximum code effectivity.

## Detailed Usage

- See [a Ludum Dare game example](http://www.ludumdare.com/compo/ludum-dare-29/?action=preview&uid=34947) for more info on how it can be used.
- HTML/text documentation is under `/docs`.

## Comparable tools

None that I could approve of. The extensibility/development speed combo is rather unique.

## Developer info

Developed by Arvīds Kokins, the developer of [SGScript](http://www.sgscript.org/).

These libraries are included in the software:

- [SDL2](https://www.libsdl.org/index.php)
- [FreeType](http://www.freetype.org/)
- [libpng](http://www.libpng.org/pub/png/libpng.html)
- [libjpeg](http://www.ijg.org/)
- [zlib](http://www.zlib.net/)
