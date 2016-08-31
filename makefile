# SGS-SDL makefile


include sgscript/core.mk


# internal configuration
video = $(call fnIF_OS,windows,,nod3d)


# SGScript & XGMath FLAGS
SGS_CFLAGS = -Isgscript/src -Isgscript/ext
SGS_LIBS = -L$(OUTDIR) -lsgscript -lsgsxgmath

# SGS-SDL FLAGS
ifneq ($(os),windows)
	SDL2_CFLAGS = $(shell sdl2-config --cflags)
	SDL2_LIBS = $(shell sdl2-config --libs)
else
	SDL2_CFLAGS = -Iext/include/SDL2
	SDL2_LIBS = -Lext/lib-win32 -lSDL2main -lSDL2
endif

# FreeType FLAGS
FT2_CFLAGS = -Iext/include/freetype
FT2_LIBS = $(call fnIF_OS,windows,-Lext/lib-win32 -lOpenGL32 obj/freetype.a,-L$(OUTDIR) -lfreetype)

# Direct3D FLAGS
ifeq ($(video),nod3d)
	D3D9_CFLAGS =
	D3D9_LIBS =
else
	D3D9_CFLAGS = -DSGS_SDL_HAS_DIRECT3D -Wno-comment
	D3D9_LIBS = -Ld3dx -ld3dx9
endif


CFLAGS=-Wall -Wshadow -Wpointer-arith -Wcast-align \
	$(call fnIF_RELEASE,-O2,-D_DEBUG -g) $(call fnIF_COMPILER gcc,-static-libgcc,) \
	$(call fnIF_ARCH,x86,-m32,$(call fnIF_ARCH,x64,-m64,)) -Isrc \
	$(call fnIF_OS,windows,,-fPIC -D_FILE_OFFSET_BITS=64) \
	$(call fnIF_OS,android,-DSGS_PF_ANDROID,)
CXXFLAGS = -fno-exceptions -fno-rtti -static-libstdc++ -static-libgcc -fno-unwind-tables -fvisibility=hidden

BINFLAGS=-lm \
	$(call fnIF_OS,android,-ldl -Wl$(comma)-rpath$(comma)'$$ORIGIN' -Wl$(comma)-z$(comma)origin,) \
	$(call fnIF_OS,windows,-lkernel32,) \
	$(call fnIF_OS,osx,-framework OpenGL -ldl -Wl$(comma)-rpath$(comma)'@executable_path/.',) \
	$(call fnIF_OS,linux,-ldl -lrt -lGL -Wl$(comma)-rpath-link$(comma). \
		-Wl$(comma)-rpath-link$(comma)bin -Wl$(comma)-rpath$(comma)'$$ORIGIN' -Wl$(comma)-z$(comma)origin,)
LIBFLAGS=$(BINFLAGS) -shared -Wl,--no-undefined



# BUILD INFO
goals = $(or $(MAKECMDGOALS),<default>)
ifneq ($(filter clean clean_%,$(goals)),$(goals))
$(info -------------------)
$(info SGS-SDL build info )
$(info -------------------)
$(info PLATFORM - $(cOS)/$(cARCH))
$(info COMPILER - $(cCOMPILER))
$(info TARGET - $(os)/$(arch))
$(info MODE - $(call fnIF_RELEASE,Release,Debug))
$(info TODO - $(goals))
$(info -------------------)
endif


# PATHS
P_SGSVM = sgscript/bin/sgsvm$(BINEXT)
P_SGSCRIPT = $(OUTDIR)/$(LIBPFX)sgscript$(LIBEXT)
P_SGSXGMATH = $(OUTDIR)/$(LIBPFX)sgsxgmath$(LIBEXT)
P_SGSSDL = $(OUTDIR)/$(LIBPFX)sgs-sdl$(LIBEXT)
P_SS3D = $(OUTDIR)/$(LIBPFX)ss3d$(LIBEXT)
P_SS3DCULL = $(OUTDIR)/$(LIBPFX)ss3dcull$(LIBEXT)
P_SGSBOX2D = $(OUTDIR)/$(LIBPFX)sgsbox2d$(LIBEXT)
P_SGSBULLET = $(OUTDIR)/$(LIBPFX)sgsbullet$(LIBEXT)
P_SGSAUDIO = $(OUTDIR)/$(LIBPFX)sgsaudio$(LIBEXT)


# TARGETS
## the library (default target)
.PHONY: tools make launchers ss3d ss3dcull sgs-sdl box2d bullet audio

tools: launchers box2d bullet audio
make: tools
launchers: $(OUTDIR)/sgs-sdl-release$(BINEXT) $(OUTDIR)/sgs-sdl-debug$(BINEXT)
sgs-sdl: $(P_SGSSDL)
ss3d: $(P_SS3D)
ss3dcull: $(P_SS3DCULL)
box2d: $(P_SGSBOX2D)
bullet: $(P_SGSBULLET)
audio: $(P_SGSAUDIO)


# SGScript
$(P_SGSXGMATH): sgscript/bin/$(LIBPFX)sgsxgmath$(LIBEXT) $(P_SGSCRIPT)
	$(fnCOPY_FILE) $(call fnFIX_PATH,sgscript/bin/$(LIBPFX)sgsxgmath$(LIBEXT) $(P_SGSXGMATH))
$(P_SGSCRIPT): sgscript/bin/$(LIBPFX)sgscript$(LIBEXT)
	$(fnCOPY_FILE) $(call fnFIX_PATH,sgscript/bin/$(LIBPFX)sgscript$(LIBEXT) $(P_SGSCRIPT))

$(P_SGSVM):
	$(MAKE) -C sgscript vm
sgscript/bin/$(LIBPFX)sgsxgmath$(LIBEXT):
	$(MAKE) -C sgscript xgmath
sgscript/bin/$(LIBPFX)sgscript$(LIBEXT):
	$(MAKE) -C sgscript
sgscript/bin/sgstest$(BINEXT):
	$(MAKE) -C sgscript build_test

# INPUT LIBRARIES
# - FreeType
ifeq ($(os),windows)
SGS_SDL_DEPS = obj/freetype.a
obj/freetype.a:
	$(CC) -o obj/freetype1.o -c $(CFLAGS) ext/src/freetype1.c $(FT2_CFLAGS)
	ar -rcs obj/freetype.a obj/freetype1.o
else
SGS_SDL_DEPS = $(OUTDIR)/$(LIBPFX)freetype$(LIBEXT)
$(OUTDIR)/$(LIBPFX)freetype$(LIBEXT):
	$(CC) -o $@ $(CFLAGS) -shared ext/src/freetype1.c $(FT2_CFLAGS)
endif
# - Box2D
obj/libbox2d.a:
	$(CXX) -o obj/libbox2d.o -c $(CFLAGS) $(CXXFLAGS) -Wno-shadow ext/src/box2d1.cpp -Iext/src/box2d/Box2D
	ar -rcs $@ obj/libbox2d.o
# - Bullet
_BLTOBJ = bullet_LinearMath.o bullet_BulletCollision.o bullet_BulletDynamics.o
BLTOBJ = $(patsubst %,obj/%,$(_BLTOBJ))
obj/bullet_%.o: ext/src/bullet_%.cpp
	$(CXX) -o $@ -c $(CFLAGS) $(CXXFLAGS) -Iext/src/bullet/src -Wno-unused-variable -Wno-unused-but-set-variable -Wno-reorder -Wno-shadow $<
obj/libbullet.a: $(BLTOBJ)
	ar -rcs $@ $^
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
# - Launcher
SGS_SDL_LAUNCHER_FLAGS = $(CFLAGS) $(BINFLAGS) -L$(OUTDIR) -lsgs-sdl $(SDL2_CFLAGS) $(SGS_CFLAGS)
SGS_SDL_INSTALL_TOOL = $(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/libsgs-sdl.so @rpath/libsgs-sdl.so $1,)
$(OUTDIR)/sgs-sdl-release$(BINEXT): $(P_SGSSDL) src/ss_launcher.c
	$(CC) -o $@ src/ss_launcher.c $(SGS_SDL_LAUNCHER_FLAGS) -s -DSS_RELEASE $(call fnIF_OS,windows,-mwindows,)
	$(call SGS_SDL_INSTALL_TOOL,$@)
$(OUTDIR)/sgs-sdl-debug$(BINEXT): $(P_SGSSDL) src/ss_launcher.c
	$(CC) -o $@ src/ss_launcher.c $(SGS_SDL_LAUNCHER_FLAGS)
	$(call SGS_SDL_INSTALL_TOOL,$@)


# - SGS-SDL
_SS_DEPS = ss_main.h ss_cfg.h
_SS_OBJ = ss_main.o ss_script.o ss_sdl.o ss_render.o ss_image.o ss_render_gl.o
ifneq ($(video),nod3d)
	_SS_OBJ += ss_render_d3d9.o
endif
SS_DEPS = $(patsubst %,src/%,$(_SS_DEPS))
SS_OBJ = $(patsubst %,obj/%,$(_SS_OBJ))

$(P_SGSSDL): $(SS_OBJ) $(SGS_SDL_DEPS) $(P_SGSXGMATH)
# copy SDL2
	$(call fnIF_OS,windows,$(fnCOPY_FILE) $(call fnFIX_PATH,ext/bin-win32/SDL2.dll bin),)
	$(call fnIF_OS,osx,$(fnCOPY_FILE) /usr/local/lib/libSDL2.dylib bin,)
# build
	$(CC) -o $@ $(SS_OBJ) $(CFLAGS) $(SGS_LIBS) $(SDL2_LIBS) $(D3D9_LIBS) $(FT2_LIBS) $(LIBFLAGS)
# adjust built projects
	$(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/libfreetype.so @rpath/libfreetype.so $@,)
	$(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/libsgscript.so @rpath/libsgscript.so $@,)
	$(call fnIF_OS,osx,install_name_tool -change $(OUTDIR)/libsgsxgmath.so @rpath/libsgsxgmath.so $@,)
obj/ss_%.o: src/ss_%.c $(SS_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SGS_CFLAGS) $(SDL2_CFLAGS) $(D3D9_CFLAGS) $(FT2_CFLAGS)


# - SS3D
SS3D_CFLAGS = $(CFLAGS) $(SGS_CFLAGS) $(D3D9_CFLAGS) $(SDL2_CFLAGS)
_SS3D_DEPS = ss3d_engine.h lodepng.h dds.h
_SS3D_OBJ = ss3d_engine.o ss3d_render_gl.o lodepng.o dds.o
ifneq ($(video),nod3d)
	_SS3D_OBJ += ss3d_render_d3d9.o
endif
SS3D_DEPS = $(patsubst %,src/%,$(_SS3D_DEPS))
SS3D_OBJ = $(patsubst %,obj/%,$(_SS3D_OBJ))

$(P_SS3D): $(SS3D_OBJ) $(P_SGSSDL) $(P_SGSXGMATH)
	$(CC) -o $@ $(SS3D_OBJ) $(CFLAGS) -lsgs-sdl $(SGS_LIBS) $(SDL2_LIBS) $(D3D9_LIBS) $(LIBFLAGS)
obj/ss3d_%.o: src/ss3d_%.c $(SS3D_DEPS)
	$(CC) -c -o $@ $< $(SS3D_CFLAGS)
obj/lodepng.o: src/lodepng.c src/lodepng.h
	$(CC) -c -o $@ $< $(SS3D_CFLAGS)
obj/dds.o: src/dds.c src/dds.h
	$(CC) -c -o $@ $< $(SS3D_CFLAGS)


# - SS3DCull
$(P_SS3DCULL): src/ss3dcull.cpp src/ss3dcull.hpp src/cppbc_ss3dcull.cpp $(P_SS3D) $(P_SGSXGMATH)
	$(CXX) -o $@ src/ss3dcull.cpp src/cppbc_ss3dcull.cpp $(CFLAGS) $(SGS_CFLAGS) -msse2 $(CXXFLAGS) -lss3d $(LIBFLAGS) $(SGS_LIBS)
src/cppbc_ss3dcull.cpp: src/ss3dcull.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/ss3dcull.hpp -o $@ -iname ss3dcull.hpp


# - sgs-Box2D
$(P_SGSBOX2D): src/box2d.cpp src/box2d.hpp src/cppbc_box2d.cpp $(P_SGSXGMATH) obj/libbox2d.a
	$(CXX) -o $@ src/box2d.cpp src/cppbc_box2d.cpp $(CFLAGS) $(CXXFLAGS) $(SGS_CFLAGS) $(SGS_LIBS) $(LIBFLAGS) -Wno-shadow -Iext/src/box2d/Box2D -Lobj -lbox2d
src/cppbc_box2d.cpp: src/box2d.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/box2d.hpp -o $@ -iname box2d.hpp


# - sgs-Bullet
$(P_SGSBULLET): src/bullet.cpp src/bullet.hpp src/cppbc_bullet.cpp $(OUTDIR)/$(LIBPFX)sgscript$(LIBEXT) $(OUTDIR)/$(LIBPFX)sgsxgmath$(LIBEXT) obj/libbullet.a
	$(CXX) -o $@ src/bullet.cpp src/cppbc_bullet.cpp $(CFLAGS) $(CXXFLAGS) $(SGS_CFLAGS) $(SGS_LIBS) $(LIBFLAGS) -Iext/src/bullet/src -Lobj -lbullet -Wno-unused-variable
src/cppbc_bullet.cpp: src/bullet.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/bullet.hpp -o $@ -iname bullet.hpp


# - sgs-Audio
$(P_SGSAUDIO): src/sa_main.cpp src/sa_main.hpp src/cppbc_sa_main.cpp src/sa_sound.cpp src/sa_sound.hpp obj/libogg.a obj/libvorbis.a
	$(CXX) -o $@ src/sa_main.cpp src/cppbc_sa_main.cpp src/sa_sound.cpp \
		$(CFLAGS) $(CXXFLAGS) $(SGS_CFLAGS) $(SGS_LIBS) $(LIBFLAGS) -Iext/include -Iext/src/libogg-1.3.1/include -Iext/src/libvorbis-1.3.3/include -Lobj -lvorbis -logg \
		$(call fnIF_OS,windows,ext/bin-win32/OpenAL32.dll,) \
		$(call fnIF_OS,linux,-lopenal -lpthread,)
	$(call fnIF_OS,windows,$(fnCOPY_FILE) $(call fnFIX_PATH,ext/bin-win32/OpenAL32.dll $(OUTDIR)/),)
	$(call fnIF_OS,windows,$(fnCOPY_FILE) $(call fnFIX_PATH,ext/bin-win32/wrap_oal.dll $(OUTDIR)/),)
src/cppbc_sa_main.cpp: src/sa_main.hpp sgscript/bin/sgsvm$(BINEXT)
	sgscript/bin/sgsvm -p sgscript/ext/cppbc.sgs src/sa_main.hpp -o $@ -iname sa_main.hpp


# UTILITY TARGETS
.PHONY: clean clean_deps clean_all test binarch
clean:
	-$(fnREMOVE_ALL) $(call fnFIX_PATH,obj/ss*.o bin/sgs*)
clean_deps:
	-$(fnREMOVE_ALL) $(call fnFIX_PATH,obj/*lib*.o bin/*.dylib bin/*.so bin/*.so.dSYM obj/*lib*.a obj/freetype*.o obj/freetype*.a obj/bullet_* obj/dds.o obj/lodepng.o)
clean_all: clean clean_deps
	$(MAKE) -C sgscript clean
test: sgscript/bin/sgstest$(BINEXT) $(P_SGSBOX2D) $(P_SGSBULLET)
	sgscript/bin/sgstest
binarch: sgscript/bin/sgsvm$(BINEXT)
	sgsvm build/prep.sgs


