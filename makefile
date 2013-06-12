
ifdef SystemRoot
	RM = del /Q
	CP = copy
	FixPath = $(subst /,\,$1)
	PLATFLAGS = -lkernel32 -lOpenGL32 -lmingw32 -lfreetype.dll
	LINKPATHS = -Lsdl-win/lib -Lfreeimage -Lfreetype
	COMPATHS = -Isdl-win/include -Ifreetype/include
	PLATPOST = $(CP) $(call FixPath,sdl-win/bin/SDL.dll bin) & \
	           $(CP) $(call FixPath,freeimage/FreeImage.dll bin) & \
	           $(CP) $(call FixPath,freetype/libfreetype-6.dll bin)
	BINEXT=.exe
else
	RM = rm -f
	CP = cp
	FixPath = $1
	PLATFLAGS = -lGL -lfreetype
	LINKPATHS = 
	COMPATHS = -I/usr/include/freetype2
	PLATPOST = 
	BINEXT=
endif

SRCDIR=src
LIBDIR=lib
EXTDIR=ext
OUTDIR=bin
OBJDIR=obj

CC=gcc
ifeq ($(mode),release)
	CFLAGS = -O3 -Wall
else
	mode = debug
	CFLAGS = -D_DEBUG -g -Wall
endif

_DEPS = ss_main.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = ss_main.o ss_script.o ss_sdl.o ss_render.o ss_image.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OUTDIR)/sgs-sdl$(BINEXT): $(OBJ)
	$(MAKE) -C sgscript static=1
	gcc -Wall -o $@ $(OBJ) -Lsgscript/lib $(LINKPATHS) $(PLATFLAGS) \
		-lSDLmain -lSDL -lsgscript -lfreeimage
	$(PLATPOST)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(COMPATHS) -Isgscript/src $(CFLAGS)

.PHONY: clean
clean:
	$(MAKE) -C sgscript clean
	$(RM) $(call FixPath,$(OBJDIR)/*.o $(OUTDIR)/sgs*)
