
CC=gcc
SRCDIR=src
LIBDIR=lib
EXTDIR=ext
OUTDIR=bin
OBJDIR=obj

ifdef SystemRoot
	RM = del /Q
	CP = copy
	FixPath = $(subst /,\,$1)
	PLATFLAGS = -lkernel32 -lOpenGL32 -ld3d9 -lmingw32 -lfreetype-6
	LINKPATHS = -Lsdl-win/lib -Lfreeimage -Lfreetype
	COMPATHS = -Isdl-win/include -Ifreetype/include
	PLATPOST = $(CP) $(call FixPath,sdl-win/bin/SDL.dll bin) & \
	           $(CP) $(call FixPath,freeimage/FreeImage.dll bin) & \
	           $(CP) $(call FixPath,freetype/libfreetype-6.dll bin) & \
	           $(CP) $(call FixPath,sgscript/bin/sgscript.dll bin) & \
	           $(CP) $(call FixPath,sgscript/bin/sgsxgmath.dll bin)
	BINEXT=.exe
	LIBPFX=
	LIBEXT=.dll
else
	RM = rm -f
	CP = cp
	FixPath = $1
	PLATFLAGS = -lGL -lfreetype -lm -Wl,-rpath,'$$ORIGIN' -Wl,-z,origin
	LINKPATHS = 
	COMPATHS = -I/usr/include/freetype2
	PLATPOST = $(CP) $(call FixPath,sgscript/bin/libsgscript.so bin) & \
	           $(CP) $(call FixPath,sgscript/bin/libsgsxgmath.so bin)
	BINEXT=
	LIBPFX=lib
	LIBEXT=.so
endif

ifeq ($(arch),64)
	ARCHFLAGS= -m64
else
	ifeq ($(arch),32)
		ARCHFLAGS= -m32
	else
		ARCHFLAGS=
	endif
endif

ifeq ($(mode),release)
	CFLAGS = -O3 -Wall $(ARCHFLAGS)
else
	mode = debug
	CFLAGS = -D_DEBUG -g -Wall $(ARCHFLAGS)
endif

ifeq ($(video),gl)
	VIDEOFLAGS = -DSGS_SDL_RENDERER_OPENGL
else
	VIDEOFLAGS = -DSGS_SDL_RENDERER_DIRECT3D
endif

C2FLAGS = $(CFLAGS) $(VIDEOFLAGS) -DBUILDING_SGS_SDL

_DEPS = ss_main.h ss_api.h ss_cfg.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = ss_main.o ss_script.o ss_sdl.o ss_render.o ss_image.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OUTDIR)/sgs-sdl$(BINEXT): $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT) src/ss_launcher.c
	gcc -o $@ src/ss_launcher.c $(COMPATHS) -Isgscript/src $(C2FLAGS) -Lbin -lsgs-sdl -s

$(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT): $(OBJ)
	$(MAKE) -C sgscript xgmath
	gcc -o $@ $(OBJ) $(C2FLAGS) -Lsgscript/bin $(LINKPATHS) $(PLATFLAGS) \
		-lSDLmain -lSDL -lsgscript -lsgsxgmath -lfreeimage -shared
	$(PLATPOST)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(COMPATHS) -Isgscript/src $(C2FLAGS)

.PHONY: clean
clean:
	$(RM) $(call FixPath,$(OBJDIR)/*.o $(OUTDIR)/sgs*)

.PHONY: clean_all
clean_all: clean
	$(MAKE) -C sgscript clean
