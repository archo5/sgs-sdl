# SGS-SDL makefile


include sgscript/core.mk


# SGS-SDL FLAGS
ifneq ($(target_os),windows)
	video=nod3d
	SDL2_CFLAGS = $(shell sdl2-config --cflags)
	SDL2_LIBS = $(shell sdl2-config --libs)
	XGM_LIBS = -l:sgsxgmath.so
else
	SDL2_CFLAGS = -Iext/include/SDL2
	SDL2_LIBS = -lSDL2main -lSDL2
	XGM_LIBS = -lsgsxgmath
endif

SGS_SDL_INSTALL_TOOL = $(call fnIF_OS,osx,install_name_tool \
	-change $(OUTDIR)/libsgs-sdl.so @rpath/libsgs-sdl.so $1,)

SS_OUTFILE=$(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT)
SS_OUTFLAGS=-L$(OUTDIR) -lsgs-sdl
CFLAGS=-Wall -Wshadow -Wpointer-arith -Wcast-align \
	$(call fnIF_RELEASE,-O3,-D_DEBUG -g) $(call fnIF_COMPILER gcc,-static-libgcc,) \
	$(call fnIF_ARCH,x86,-m32,$(call fnIF_ARCH,x64,-m64,)) -Isrc \
	$(call fnIF_OS,windows,,-fPIC -D_FILE_OFFSET_BITS=64) \
	$(call fnIF_OS,android,-DSGS_PF_ANDROID,)
SS_CFLAGS=$(CFLAGS) -Isgscript/src -Isgscript/ext $(SDL2_CFLAGS) $(FT2_CFLAGS) -Iext/include/freetype -Wno-comment
BINFLAGS=$(CFLAGS) $(OUTFLAGS) -lm \
	$(call fnIF_OS,android,-ldl -Wl$(comma)-rpath$(comma)'$$ORIGIN' -Wl$(comma)-z$(comma)origin,) \
	$(call fnIF_OS,windows,-lkernel32,) \
	$(call fnIF_OS,osx,-framework OpenGL -ldl -Wl$(comma)-rpath$(comma)'@executable_path/.',) \
	$(call fnIF_OS,linux,-ldl -lrt -lGL -Wl$(comma)-rpath-link$(comma). \
		-Wl$(comma)-rpath-link$(comma)bin -Wl$(comma)-rpath$(comma)'$$ORIGIN' -Wl$(comma)-z$(comma)origin,)
MODULEFLAGS=$(BINFLAGS) -shared -Wl,--no-undefined
EXEFLAGS=$(BINFLAGS)

_DEPS = ss_main.h ss_cfg.h
_OBJ = ss_main.o ss_script.o ss_sdl.o ss_render.o ss_image.o ss_render_gl.o

_SS3D_DEPS = ss3d_engine.h lodepng.h dds.h
_SS3D_OBJ = ss3d_engine.o ss3d_render_gl.o lodepng.o dds.o

ifneq ($(video),nod3d)
	SS_CFLAGS += -DSGS_SDL_HAS_DIRECT3D
	MODULEFLAGS += -Ld3dx -ld3dx9
	_OBJ += ss_render_d3d9.o
	_SS3D_OBJ += ss3d_render_d3d9.o
endif

DEPS = $(patsubst %,src/%,$(_DEPS))
OBJ = $(patsubst %,obj/%,$(_OBJ))

SS3D_DEPS = $(patsubst %,src/%,$(_SS3D_DEPS))
SS3D_OBJ = $(patsubst %,obj/%,$(_SS3D_OBJ))

ifeq ($(target_os),windows)
	PF_LINK = -Lext/lib-win32 -lOpenGL32 obj/freetype.a
	PF_POST = $(fnCOPY_FILE) $(call fnFIX_PATH,ext/bin-win32/SDL2.dll bin) & \
	           $(fnCOPY_FILE) $(call fnFIX_PATH,sgscript/bin/sgscript.dll bin) & \
	           $(fnCOPY_FILE) $(call fnFIX_PATH,sgscript/bin/sgsxgmath.dll bin)
else
	PF_LINK = -Lbin -lfreetype
	PF_POST = $(call fnIF_OS,osx,$(fnCOPY_FILE) /usr/local/lib/libSDL2.dylib bin &,) \
				$(fnCOPY_FILE) sgscript/bin/libsgscript.so bin & \
				$(fnCOPY_FILE) sgscript/bin/sgsxgmath.so bin
endif

SGS_SDL_FLAGS = $(SS_CFLAGS) $(MODULEFLAGS) $(PF_LINK) -Lsgscript/bin $(SDL2_LIBS) $(FT2_LIBS) -lsgscript $(XGM_LIBS) $(PF_DEPS)
SGS_SDL_LAUNCHER_FLAGS = $(SS_CFLAGS) $(BINFLAGS) -L$(OUTDIR) -lsgs-sdl

SGS_CXX_FLAGS = -fno-exceptions -fno-rtti -static-libstdc++ -static-libgcc -fno-unwind-tables -fvisibility=hidden


# BUILD INFO
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),clean_obj)
ifneq ($(MAKECMDGOALS),clean_objbin)
$(info -------------------)
$(info SGS-SDL build info )
$(info -------------------)
$(info OS - $(cOS))
$(info ARCH - $(cARCH))
$(info COMPILER - $(cCOMPILER))
$(info TARGET - $(target_os)/$(target_arch))
$(info MODE - $(call fnIF_RELEASE,release,debug))
$(info OUT.LIB. - $(OUTFILE))
$(info TODO - $(MAKECMDGOALS))
$(info -------------------)
endif
endif
endif


# TARGETS
## the library (default target)
.PHONY: tools make launchers ss3d ss3dcull sgs-sdl box2d bullet audio

tools: launchers box2d bullet audio
make: tools
launchers: $(OUTDIR)/sgs-sdl-release$(BINEXT) $(OUTDIR)/sgs-sdl-debug$(BINEXT)
sgs-sdl: $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT)
ss3d: $(OUTDIR)/$(LIBPFX)ss3d$(LIBEXT)
ss3dcull: $(OUTDIR)/$(LIBPFX)ss3dcull$(LIBEXT)
box2d: $(OUTDIR)/sgsbox2d$(LIBEXT)
bullet: $(OUTDIR)/sgsbullet$(LIBEXT)
audio: $(OUTDIR)/sgsaudio$(LIBEXT)


# SGScript
sgscript/bin/sgsvm$(BINEXT):
	$(MAKE) -C sgscript vm
sgscript/bin/sgsxgmath$(LIBEXT):
	$(MAKE) -C sgscript xgmath
sgscript/bin/sgstest$(BINEXT):
	$(MAKE) -C sgscript build_test

# INPUT LIBRARIES
.PHONY: sgs-sdl-deps
ifeq ($(target_os),windows)
SGS_SDL_DEPS = obj/freetype.a
obj/freetype.a:
	$(CC) -o obj/freetype1.o -c $(CFLAGS) ext/src/freetype1.c -Iext/include/freetype
	ar -rcs obj/freetype.a obj/freetype1.o
else
SGS_SDL_DEPS = $(OUTDIR)/$(LIBPFX)freetype$(LIBEXT)
$(OUTDIR)/$(LIBPFX)freetype$(LIBEXT):
	$(CC) -o $@ $(CFLAGS) -shared ext/src/freetype1.c -Iext/include/freetype
endif
# - Box2D
obj/libbox2d.a:
	$(CXX) -o obj/libbox2d.o -c $(CFLAGS) $(SGS_CXX_FLAGS) -Wno-shadow ext/src/box2d1.cpp -Iext/src/box2d/Box2D
	ar -rcs $@ obj/libbox2d.o
# - Bullet
_BLTOBJ = bullet_LinearMath.o bullet_BulletCollision.o bullet_BulletDynamics.o
BLTOBJ = $(patsubst %,obj/%,$(_BLTOBJ))
obj/bullet_%.o: ext/src/bullet_%.cpp
	$(CXX) -o $@ -c $(CFLAGS) $(SGS_CXX_FLAGS) -Iext/src/bullet/src -Wno-unused-variable $<
obj/libbullet.a: $(BLTOBJ)
	ar -rcs $@ $^
obj/bullet_%.o: ext/src/bullet_%.cpp $(DEPS)
# - Ogg
obj/libogg_bitwise.o:
	gcc -c -o $@ ext/src/libogg-1.3.1/src/bitwise.c -O3 -Iext/src/libogg-1.3.1/include $(CFLAGS)
obj/libogg_framing.o:
	gcc -c -o $@ ext/src/libogg-1.3.1/src/framing.c -O3 -Iext/src/libogg-1.3.1/include $(CFLAGS)
obj/libogg.a: obj/libogg_bitwise.o obj/libogg_framing.o
	ar rcs $@ $?
# - Vorbis
_OBJ_VORBIS = analysis.o bitrate.o block.o codebook.o envelope.o \
floor0.o floor1.o info.o lookup.o lpc.o lsp.o mapping0.o mdct.o psy.o \
registry.o res0.o sharedbook.o smallft.o synthesis.o vorbisenc.o vorbisfile.o window.o
OBJ_VORBIS = $(patsubst %,obj/%,$(_OBJ_VORBIS))
obj/libvorbis_%.o: ext/src/libvorbis-1.3.3/lib/%.c
	gcc -c -o $@ $< -Iext/src/libvorbis-1.3.3/include -Iext/src/libvorbis-1.3.3/lib -Iext/src/libogg-1.3.1/include $(CFLAGS)
obj/libvorbis.a: $(patsubst %,obj/libvorbis_%,$(_OBJ_VORBIS))
	ar rcs $@ $?


# MAIN LIBRARIES
$(OUTDIR)/sgs-sdl-release$(BINEXT): $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT) src/ss_launcher.c
	$(LINUXHACKPRE)
	$(CC) -o $@ src/ss_launcher.c $(call fnIF_OS,windows,-mwindows,) $(SGS_SDL_LAUNCHER_FLAGS) -DSS_RELEASE -s
	$(LINUXHACKPOST)
	$(call SGS_SDL_INSTALL_TOOL,$@)
$(OUTDIR)/sgs-sdl-debug$(BINEXT): $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT) src/ss_launcher.c
	$(LINUXHACKPRE)
	$(CC) -o $@ src/ss_launcher.c $(SGS_SDL_LAUNCHER_FLAGS) -s
	$(LINUXHACKPOST)
	$(call SGS_SDL_INSTALL_TOOL,$@)

$(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT): $(OBJ) $(SGS_SDL_DEPS) sgscript/bin/sgsxgmath$(LIBEXT)
	$(LINUXHACKPRE)
	$(PF_POST)
	$(CC) -o $@ $(OBJ) $(SGS_SDL_FLAGS)
	$(LINUXHACKPOST)
	$(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/libfreetype.so @rpath/libfreetype.so $@,)
	$(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/libsgscript.so @rpath/libsgscript.so $@,)
	$(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/sgsxgmath.so @rpath/sgsxgmath.so $@,)

$(OUTDIR)/ss3d$(LIBEXT): $(SS3D_OBJ) $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT) sgscript/bin/sgsxgmath$(LIBEXT)
	$(LINUXHACKPRE)
	$(CC) -o $@ $(SS3D_OBJ) $(SGS_SDL_FLAGS)
	$(LINUXHACKPOST)
	$(PF_POST)

$(OUTDIR)/ss3dcull$(LIBEXT): src/ss3dcull.cpp src/ss3dcull.hpp src/cppbc_ss3dcull.cpp $(OUTDIR)/ss3d$(LIBEXT) sgscript/bin/sgsxgmath$(LIBEXT)
	$(LINUXHACKPRE)
	$(CXX) -o $@ src/ss3dcull.cpp src/cppbc_ss3dcull.cpp $(SGS_SDL_FLAGS) -msse2 $(SGS_CXX_FLAGS) -I. $(OUTDIR)/ss3d$(LIBEXT)
	$(LINUXHACKPOST)

$(OUTDIR)/sgsbox2d$(LIBEXT): src/box2d.cpp src/box2d.hpp src/cppbc_box2d.cpp sgscript/bin/sgsxgmath$(LIBEXT) obj/libbox2d.a
	$(LINUXHACKPRE)
	$(CXX) -o $@ src/box2d.cpp src/cppbc_box2d.cpp $(SGS_SDL_FLAGS) $(SGS_CXX_FLAGS) -Wno-shadow -Iext/src/box2d/Box2D -Lobj -lbox2d
	$(LINUXHACKPOST)

$(OUTDIR)/sgsbullet$(LIBEXT): src/bullet.cpp src/bullet.hpp src/cppbc_bullet.cpp $(OUTDIR)/$(LIBPFX)sgscript$(LIBEXT) $(OUTDIR)/sgsxgmath$(LIBEXT) obj/libbullet.a
	$(LINUXHACKPRE)
	$(CXX) -o $@ src/bullet.cpp src/cppbc_bullet.cpp $(SGS_SDL_FLAGS) $(SGS_CXX_FLAGS) -Iext/src/bullet/src -Lobj -lbullet -Wno-unused-variable
	$(LINUXHACKPOST)

$(OUTDIR)/sgsaudio$(LIBEXT): src/sa_main.cpp src/sa_main.hpp src/cppbc_sa_main.cpp src/sa_sound.cpp src/sa_sound.hpp obj/libogg.a obj/libvorbis.a
	$(LINUXHACKPRE)
	$(CXX) -o $@ src/sa_main.cpp src/cppbc_sa_main.cpp src/sa_sound.cpp \
		$(SGS_SDL_FLAGS) $(SGS_CXX_FLAGS) -Iext/include -Iext/src/libogg-1.3.1/include -Iext/src/libvorbis-1.3.3/include -Lobj -lvorbis -logg \
		$(call fnIF_OS,windows,ext/bin-win32/OpenAL32.dll,) \
		$(call fnIF_OS,linux,-lopenal -lpthread,)
	$(call fnIF_OS,windows,$(fnCOPY_FILE) $(call fnFIX_PATH,ext/bin-win32/OpenAL32.dll) $(OUTDIR)/,)
	$(call fnIF_OS,windows,$(fnCOPY_FILE) $(call fnFIX_PATH,ext/bin-win32/wrap_oal.dll) $(OUTDIR)/,)
	$(LINUXHACKPOST)

obj/ss_%.o: src/ss_%.c $(DEPS)
	$(CC) -c -o $@ $< $(SS_CFLAGS)

obj/ss3d_%.o: src/ss3d_%.c $(SS3D_DEPS)
	$(CC) -c -o $@ $< $(SS_CFLAGS)
obj/lodepng.o: src/lodepng.c src/lodepng.h
	$(CC) -c -o $@ $< $(SS_CFLAGS)
obj/dds.o: src/dds.c src/dds.h
	$(CC) -c -o $@ $< $(SS_CFLAGS)

src/cppbc_ss3dcull.cpp: src/ss3dcull.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/ss3dcull.hpp -o $@ -iname ss3dcull.hpp
src/cppbc_box2d.cpp: src/box2d.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/box2d.hpp -o $@ -iname box2d.hpp
src/cppbc_bullet.cpp: src/bullet.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/bullet.hpp -o $@ -iname bullet.hpp
src/cppbc_sa_main.cpp: src/sa_main.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/sa_main.hpp -o $@ -iname sa_main.hpp

# UTILITY TARGETS
.PHONY: clean clean_deps clean_all, test, binarch
clean:
	-$(fnREMOVE_ALL) $(call fnFIX_PATH,obj/ss*.o bin/sgs*)
clean_deps:
	-$(fnREMOVE_ALL) $(call fnFIX_PATH,obj/*lib*.o bin/*.dylib bin/*.so bin/*.so.dSYM obj/*lib*.a obj/freetype*.o obj/freetype*.a)
clean_all: clean clean_deps
	$(MAKE) -C sgscript clean
test: sgscript/bin/sgstest$(BINEXT) $(OUTDIR)/sgsbox2d$(LIBEXT) $(OUTDIR)/sgsbullet$(LIBEXT)
	sgscript/bin/sgstest
binarch: sgscript/bin/sgsvm$(BINEXT)
	sgsvm build/prep.sgs


