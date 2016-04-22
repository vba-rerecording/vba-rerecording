bin_PROGRAMS = vbarr

# noinst_PROGRAMS = TestEmu

vbarr_SOURCES = \
	SDL.cpp			\
	SoundSDL.cpp \
	SoundSDL.h \
	debugger.cpp		\
	debugger.h		\
	expr-lex.lpp	\
	expr.ypp		\
	expr.cpp.h		\
	exprNode.cpp		\
	exprNode.h		\
	getopt.c		\
	getopt.h		\
	getopt1.c		\
	../AutoBuild.h		\
	../NLS.h		\
	../Port.h

vbarr_LDADD = @VBA_LIBS@ @SDL_LIBS@

vbarr_DEPENDENCIES = @VBA_LIBS@

# TestEmu_SOURCES = \
# 	TestEmu.cpp		\
# 	debugger.cpp		\
# 	debugger.h		\
# 	expr-lex.lpp		\
# 	expr.ypp		\
# 	expr.cpp.h		\
# 	exprNode.cpp		\
# 	exprNode.h		\
# 	../AutoBuild.h		\
# 	../NLS.h		\
# 	../Port.h
#
# TestEmu_LDADD = @VBA_LIBS@ @SDL_LIBS@
#
# TestEmu_DEPENDENCIES = @VBA_LIBS@

AM_CPPFLAGS = \
	-I$(top_srcdir)/src		\
	-DSDL				\
	-DSYSCONFDIR=\"$(sysconfdir)\"

AM_CXXFLAGS = -fno-exceptions @SDL_CFLAGS@
