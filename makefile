
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
	LIBFLAGS = 
	PLATFLAGS = -lkernel32 -lOpenGL32 -ld3d9 -lmingw32 -lfreetype-6 -lsgsxgmath
	LINKPATHS = -Lsdl-win/lib -Lfreeimage -Lfreetype
	COMPATHS = -Isdl-win/include -Ifreetype/include
	LINUXHACKPRE =
	LINUXHACKPOST =
	PLATPOST = $(CP) $(call FixPath,sdl-win/bin/SDL2.dll bin) & \
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
	LIBFLAGS = -Wl,-rpath,'$$ORIGIN' -Wl,-z,origin -Wl,-rpath-link,bin
	PLATFLAGS = -lGL -lfreetype -lm -Wl,-rpath,'$$ORIGIN' -Wl,-z,origin -l:sgsxgmath.so
	LINKPATHS = 
	COMPATHS = -I/usr/include/freetype2
	LINUXHACKPRE = -ln -s sgscript/bin/sgsxgmath.so sgsxgmath.so
	LINUXHACKPOST = -unlink sgsxgmath.so
	PLATPOST = $(CP) $(call FixPath,sgscript/bin/libsgscript.so bin) & \
	           $(CP) $(call FixPath,sgscript/bin/sgsxgmath.so bin)
	BINEXT=
	LIBPFX=lib
	LIBEXT=.so
	video=nod3d
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

C2FLAGS = $(CFLAGS) $(VIDEOFLAGS) -DBUILDING_SGS_SDL

_DEPS = ss_main.h ss_cfg.h
_OBJ = ss_main.o ss_script.o ss_sdl.o ss_render.o ss_image.o ss_render_gl.o

ifneq ($(video),nod3d)
	VIDEOFLAGS = -DSGS_SDL_HAS_DIRECT3D
	_OBJ += ss_render_d3d9.o
endif


DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

.PHONY: bothlaunchers
bothlaunchers: $(OUTDIR)/sgs-sdl-release$(BINEXT) $(OUTDIR)/sgs-sdl-debug$(BINEXT)

$(OUTDIR)/sgs-sdl-release$(BINEXT): $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT) src/ss_launcher.c
	$(LINUXHACKPRE)
	gcc -o $@ src/ss_launcher.c -mwindows $(COMPATHS) $(LIBFLAGS) -Isgscript/src $(C2FLAGS) -DSS_RELEASE -Lbin -lsgs-sdl -s
	$(LINUXHACKPOST)
$(OUTDIR)/sgs-sdl-debug$(BINEXT): $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT) src/ss_launcher.c
	$(LINUXHACKPRE)
	gcc -o $@ src/ss_launcher.c $(COMPATHS) $(LIBFLAGS) -Isgscript/src $(C2FLAGS) -Lbin -lsgs-sdl -s
	$(LINUXHACKPOST)

$(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT): $(OBJ)
	$(MAKE) -C sgscript xgmath
	$(LINUXHACKPRE)
	gcc -o $@ $(OBJ) $(C2FLAGS) -Lsgscript/bin $(LINKPATHS) $(PLATFLAGS) \
		-lSDL2main -lSDL2 -lsgscript -lfreeimage -shared
	$(LINUXHACKPOST)
	$(PLATPOST)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(COMPATHS) -Isgscript/src $(C2FLAGS)

.PHONY: clean
clean:
	$(RM) $(call FixPath,$(OBJDIR)/*.o $(OUTDIR)/sgs*)

.PHONY: clean_all
clean_all: clean
	$(MAKE) -C sgscript clean
