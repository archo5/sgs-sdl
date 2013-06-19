
ifdef SystemRoot
	RM = del /Q
	CP = copy
	FixPath = $(subst /,\,$1)
	PLATFLAGS = -lkernel32 -lOpenGL32 -lmingw32 -lfreetype.dll
	LINKPATHS = -Lsdl-win/lib -Lfreeimage -Lfreetype
	COMPATHS = -Isdl-win/include -Ifreetype/include
	PLATPOST = $(CP) $(call FixPath,sdl-win/bin/SDL.dll bin) & \
	           $(CP) $(call FixPath,freeimage/FreeImage.dll bin) & \
	           $(CP) $(call FixPath,freetype/libfreetype-6.dll bin) & \
	           $(CP) $(call FixPath,sgscript/bin/sgscript.dll bin)
	BINEXT=.exe
	LIBEXT=.dll
else
	RM = rm -f
	CP = cp
	FixPath = $1
	PLATFLAGS = -lGL -lfreetype
	LINKPATHS = 
	COMPATHS = -I/usr/include/freetype2
	PLATPOST = $(CP) $(call FixPath,sgscript/bin/sgscript.dll bin)
	BINEXT=
	LIBEXT=.so
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

C2FLAGS = $(CFLAGS) -DBUILDING_SGS_SDL

_DEPS = ss_main.h ss_api.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = ss_main.o ss_script.o ss_sdl.o ss_render.o ss_image.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OUTDIR)/sgs-sdl$(BINEXT): $(OBJ)
	$(MAKE) -C sgscript
	gcc -Wall -o $@ $(OBJ) -Lsgscript/lib $(LINKPATHS) $(PLATFLAGS) \
		-lSDLmain -lSDL sgscript/bin/sgscript$(LIBEXT) -lfreeimage
	$(PLATPOST)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(COMPATHS) -Isgscript/src $(C2FLAGS)

.PHONY: clean
clean:
	$(MAKE) -C sgscript clean
	$(RM) $(call FixPath,$(OBJDIR)/*.o $(OUTDIR)/sgs*)
