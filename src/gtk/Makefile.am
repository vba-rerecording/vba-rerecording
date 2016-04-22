SUBDIRS = images

bin_PROGRAMS = gvbarr

noinst_LIBRARIES = libgvbarr.a

gvbarr_SOURCES = \
	configfile.cpp		\
	configfile.h		\
	filters.cpp		\
	filters.h		\
	input.cpp		\
	input.h			\
	intl.h			\
	joypadconfig.cpp	\
	joypadconfig.h		\
	main.cpp		\
	menuitem.h		\
	screenarea.cpp		\
	screenarea.h		\
	sigccompat.h		\
	system.cpp		\
	tools.cpp		\
	tools.h			\
	windowcallbacks.cpp	\
	window.cpp		\
	window.h

gvbarr_LDADD = libgvba.a @VBA_LIBS@ @GTKMM_LIBS@ @LIBINTL@ @SDL_LIBS@

gvbarr_DEPENDENCIES = libgvba.a @VBA_LIBS@

gvbarr_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-DPKGDATADIR=\"$(pkgdatadir)\"			\
	-DLOCALEDIR=\"$(datadir)/locale\"		\
	-DGETTEXT_PACKAGE=\"$(GETTEXT_PACKAGE)\"	\
	$(GTKMM_CPPFLAGS)

gvbarr_CXXFLAGS = @GTKMM_STD@ @GTKMM_CFLAGS@ @SDL_CFLAGS@

libgvbarr_a_SOURCES = \
	../AutoBuild.h		\
	../NLS.h		\
	../Port.h

libgvbarr_a_CPPFLAGS = -DSDL

libgvbarr_a_CXXFLAGS = -fno-exceptions

dist_pkgdata_DATA = vba.glade
