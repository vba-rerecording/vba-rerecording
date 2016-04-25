# CMake build file. Based on the file used by vba-m
PROJECT(VBA-ReRecording C CXX)
# No need to check for ASM until MMX support
# PROJECT(VBA-ReRecording ASM C CXX)

# List of todo's of functionality provided by the autotools chain this
# cmake script does not yet provided
# TODO: Implement c vs. mmx core choice (-DMMX plus build mmx asm filter)
# TODO: Fix and allow enabling of profiling (-DPROFILING and build prof)
# TODO: Allow development features toggle (-DDEV_VERSION)
# TODO: BKPT_SUPPORT?
# TODO: Win32 mingw/cygwin based support

# This is the version needed for nativednasm support
cmake_minimum_required( VERSION 2.8.4 )
# This only has to be enabled with mmx support
# enable_language(ASM_NASM)

find_package ( ZLIB REQUIRED )
find_package ( PNG REQUIRED )
find_package ( SDL REQUIRED )
find_package ( BISON REQUIRED )
find_package ( FLEX REQUIRED )
find_package ( Gettext REQUIRED )
find_package ( Lua51  REQUIRED )

# Version number
IF( NOT VERSION )
    SET( VERSION "v24-git" )
ENDIF( NOT VERSION )

# This is taken from vba-m's file
# TODO: Figure out why SDLMain.m is a problem.
# Fill in SDLMAIN_LIBRARY on OS X manually to avoid using SDLMain.m
# OS X users will have to compile and install SDL from source.
if( APPLE )
	SET(SDLMAIN_LIBRARY "-lSDLmain")
endif( APPLE )

# GTK is disabled by default since the build is currently very
# bitrotted
IF( GTK )
  FIND_PACKAGE ( PkgConfig REQUIRED )

  # These dependencies require pkg-config to be found
  PKG_CHECK_MODULES ( GTKMM gtkmm-2.4 )
  PKG_CHECK_MODULES ( GLIBMM glibmm-2.4 )
  PKG_CHECK_MODULES ( GIOMM giomm-2.4 )
  PKG_CHECK_MODULES ( GLADEMM libglademm-2.4 )
ENDIF( GTK )

IF( NOT NO_SDL )
    IF( SDL_FOUND AND LUA51_FOUND )
        SET( CAN_BUILD_VBARR 1 )
    ENDIF( SDL_FOUND AND LUA51_FOUND )
ENDIF( NOT NO_SDL )

# Check that the dependencies are met to build the GTK frontend
IF( GTK )
    IF( GLIBMM_FOUND AND GTKMM_FOUND AND GLADEMM_FOUND AND SDL_FOUND AND GETTEXT_FOUND AND LUA51_FOUND )
        SET( CAN_BUILD_GVBARR 1 )
    ENDIF( GLIBMM_FOUND AND GTKMM_FOUND AND GLADEMM_FOUND AND SDL_FOUND AND GETTEXT_FOUND AND LUA51_FOUND )
ENDIF( GTK )

# Set the default install dir
IF( NOT DATA_INSTALL_DIR )
    SET( DATA_INSTALL_DIR "share/vba-rerecording" )
ENDIF( NOT DATA_INSTALL_DIR )

SET( PKGDATADIR ${CMAKE_INSTALL_PREFIX}/${DATA_INSTALL_DIR} )

# Set the configuration file location
IF( NOT SYSCONFDIR )
    SET( SYSCONFDIR "/etc" )
ENDIF( NOT SYSCONFDIR )

# C defines
ADD_DEFINITIONS (-DHAVE_NETINET_IN_H -DHAVE_ARPA_INET_H -DHAVE_ZLIB_H -DFINAL_VERSION -DSDL -DSYSCONFDIR="${SYSCONFDIR}")

ADD_DEFINITIONS (-DVERSION="${VERSION}" -DPKGDATADIR="${PKGDATADIR}" -DPACKAGE="vba-rerecording" -DUSE_EXTERNAL_LUA)

# The ASM core is disabled by default because we don't know on which platform we are
IF( NOT USE_ASM_CORE )
    ADD_DEFINITIONS (-DC_CORE)
ENDIF( NOT USE_ASM_CORE )

SET( CMAKE_C_FLAGS "-O3 -Wall")
SET( CMAKE_CXX_FLAGS "-O3 -Wall")

SET(SRC_COMMON
    src/common/lua-engine.cpp
    src/common/memgzio.c
    src/common/movie.cpp
    src/common/System.cpp
    src/common/SystemGlobals.cpp
    src/common/Text.cpp
    src/common/unzip.cpp
    src/common/Util.cpp
)

SET(SRC_GBA
	src/gba/agbprint.cpp
	src/gba/armdis.cpp
	src/gba/bios.cpp
	src/gba/elf.cpp
	src/gba/GBACheats.cpp
	src/gba/EEprom.cpp
	src/gba/Flash.cpp
	src/gba/GBA.cpp
	src/gba/GBA-arm.cpp
	src/gba/GBA-thumb.cpp
	src/gba/GBAGfx.cpp
	src/gba/GBAGlobals.cpp
	src/gba/GBAMemory.cpp
	src/gba/GBASound.cpp
	src/gba/Mode0.cpp
	src/gba/Mode1.cpp
	src/gba/Mode2.cpp
	src/gba/Mode3.cpp
	src/gba/Mode4.cpp
	src/gba/Mode5.cpp
	src/gba/remote.cpp
	src/gba/RTC.cpp
	src/gba/Sram.cpp
)

SET(SRC_GB
    src/gb/GB.cpp
    src/gb/gbCheats.cpp
    src/gb/gbDis.cpp
    src/gb/gbGfx.cpp
    src/gb/gbGlobals.cpp
    src/gb/gbMemory.cpp
    src/gb/gbPrinter.cpp
    src/gb/gbSGB.cpp
    src/gb/gbSound.cpp
)

SET(SRC_APU
    src/apu/Blip_Buffer.cpp
)

BISON_TARGET(EXPR_PARSER src/sdl/expr.ypp ${CMAKE_CURRENT_BINARY_DIR}/expr.cpp)
FLEX_TARGET(EXPR_LEXER src/sdl/expr-lex.lpp  ${CMAKE_CURRENT_BINARY_DIR}/expr-lex.cpp)
ADD_FLEX_BISON_DEPENDENCY(EXPR_LEXER EXPR_PARSER)

SET(SRC_SDL
    src/sdl/SDL.cpp
    src/sdl/debugger.cpp
    src/sdl/SoundSDL.cpp
    ${BISON_EXPR_PARSER_OUTPUTS}
    src/sdl/exprNode.cpp
    ${FLEX_EXPR_LEXER_OUTPUTS}
    src/sdl/getopt1.c
)

SET(SRC_FILTERS
    src/filters/2xSaI.cpp
    src/filters/admame.cpp
    src/filters/bilinear.cpp
    src/filters/hq2x.cpp
    src/filters/interframe
    src/filters/motionblur.cpp
    src/filters/pixel.cpp
    src/filters/scanline.cpp
    src/filters/simple2x.cpp
)

SET(SRC_GTK
	src/gtk/configfile.cpp
	src/gtk/filters.cpp
	src/gtk/input.cpp
	src/gtk/joypadconfig.cpp
	src/gtk/main.cpp
	src/gtk/screenarea.cpp
	src/gtk/system.cpp
	src/gtk/tools.cpp
	src/gtk/windowcallbacks.cpp
	src/gtk/window.cpp
)

INCLUDE_DIRECTORIES(
    src
    ${ZLIB_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
    ${SDL_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}
)

IF( CAN_BUILD_GVBARR )
    INCLUDE_DIRECTORIES(
        ${GLIBMM_INCLUDE_DIRS}
        ${GIOMM_INCLUDE_DIRS}
        ${GTKMM_INCLUDE_DIRS}
        ${GLADEMM_INCLUDE_DIRS}
    )

    LINK_DIRECTORIES(
        ${GLIBMM_LIBRARY_DIRS}
        ${GIOMM_LIBRARY_DIRS}
        ${GTKMM_LIBRARY_DIRS}
        ${GLADEMM_LIBRARY_DIRS}
        ${GLADEMM_LIBRARY_DIRS}
    )

    add_definitions(-DGETTEXT_PACKAGE=vba-1.7.2)
ENDIF( CAN_BUILD_GVBARR )

ADD_LIBRARY (
    libgbcom
    ${PROJECT_SRCS}
    ${SRC_COMMON}
)

add_library (
    libgb
    ${PROJECT_SRCS}
    ${SRC_GB}
)

add_library (
    libgba
    ${PROJECT_SRCS}
    ${SRC_GBA}
)

add_library (
    libfilter
    ${PROJECT_SRCS}
    ${SRC_FILTERS}
)

IF( NO_SDL AND NOT GTK )
message(WARNING "You have chosen not to build any frontend")
ENDIF( NO_SDL AND NOT GTK )

IF( CAN_BUILD_VBARR )
    ADD_EXECUTABLE (
        vba-rr
        ${SRC_SDL}
    )

    TARGET_LINK_LIBRARIES (
        vba-rr
        libfilter
        libgbcom
        libgb
        libgba
        ${SDL_LIBRARY}
        ${ZLIB_LIBRARY}
        ${PNG_LIBRARY}
        ${LUA_LIBRARIES}
    )

    INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/vba-rr DESTINATION bin)
ENDIF( CAN_BUILD_VBARR )

IF( CAN_BUILD_GVBARR )

    SET(VBA_WM_VARIABLES
      stock_vba_wm_16  ${CMAKE_CURRENT_SOURCE_DIR}/src/gtk/images/stock-vba-wm-16.png
      stock_vba_wm_32  ${CMAKE_CURRENT_SOURCE_DIR}/src/gtk/images/stock-vba-wm-32.png
      stock_vba_wm_48  ${CMAKE_CURRENT_SOURCE_DIR}/src/gtk/images/stock-vba-wm-48.png
      stock_vba_wm_64  ${CMAKE_CURRENT_SOURCE_DIR}/src/gtk/images/stock-vba-wm-64.png
    )

    add_custom_command(OUTPUT images/vba-wm-pixbufs.h
                   PRE_BUILD
                 COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/gen/images
                 COMMAND gdk-pixbuf-csource --raw --build-list ${VBA_WM_VARIABLES} > ${CMAKE_CURRENT_BINARY_DIR}/gen/images/vba-wm-pixbufs.h)

    ADD_EXECUTABLE (
        gvba-rr
        WIN32
        MACOSX_BUNDLE
        ${SRC_GTK}
        images/vba-wm-pixbufs.h
    )

    target_include_directories(
      gvba-rr
      PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/gen
    )

    set_property(
      TARGET
      gvba-rr
      PROPERTY
      CXX_STANDARD
      11
    )

    TARGET_LINK_LIBRARIES (
        gvba-rr
        libfilter
        libgbcom
        libgb
        libgba
        ${ZLIB_LIBRARY}
        ${PNG_LIBRARY}
        ${GLADEMM_LIBRARIES}
        ${SDL_LIBRARY}
        ${LUA_LIBRARIES}
    )


    INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/gvba-rr DESTINATION bin)

ENDIF( CAN_BUILD_GVBARR )
