#ifndef VBA_VERSION_H
#define VBA_VERSION_H

#ifdef HAVE_GIT_VERSION_H
#include "git_version.h"
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRINGIZE_VALUE(X) _Py_STRINGIZE2(X)
#define _Py_STRINGIZE(X) _Py_STRINGIZE1((X))
#define _Py_STRINGIZE1(X) _Py_STRINGIZE2 ## X
#define _Py_STRINGIZE2(X) #X
//re: http://72.14.203.104/search?q=cache:HG-okth5NGkJ:mail.python.org/pipermail/python-checkins/2002-November/030704.html+_msc_ver+compiler+version+string&hl=en&gl=us&ct=clnk&cd=5

#if defined(_MSC_VER)
#	define VBA_COMPILER ""
#	define VBA_COMPILER_DETAIL " msvc " _Py_STRINGIZE(_MSC_VER)
#else
// TODO: make for others compilers
#	define VBA_COMPILER ""
#	define VBA_COMPILER_DETAIL ""
#endif

#define VBA_NAME "VisualBoyAdvance Rerecording"

// There used to be a check here for the version of the GBA core
// being used. This will no longer be used. If you are building
// a version using non V8-cores and want a different version number,
// please supply these parameters manually
//
// ALWAYS supply a meaningfull VBA_FEATURE_STRING when using
// non V8 cores
#ifndef VBA_RR_MAJOR_VERSION_NO
#	define VBA_RR_MAJOR_VERSION_NO 24
#	define VBA_RR_MINOR_VERSION_NO 4
// If necessary define an alpha, beta or rc version here
# define VBA_RR_ALPHA_VERSION 1
#endif

# ifdef VBA_RR_ALPHA_VERSION
#	 define VBA_RELEASE_TYPE "alpha" STRINGIZE_VALUE(VBA_RR_ALPHA_VERSION)
# elif defined(VBA_RR_BETA_VERSION)
#	 define VBA_RELEASE_TYPE "beta" STRINGIZE_VALUE(VBA_RR_BETA_VERSION)
# elif defined(VBA_RR_RC_VERSION)
#	 define VBA_RELEASE_TYPE "rc" STRINGIZE_VALUE(VBA_RR_RC_VERSION)
# else
// We made it to a final release! Hype!
#  define VBA_RELEASE_TYPE ""
# endif

// A git commit MAY be set for versioning and will be displayed
// if the version is not build from a tag or if the build
// is a debug build (Since that is actually valuable information
// when debugging).
// If the commit has a tag name, that MAY be used
// instead
//
// For cmake builds there is very little need to destinguish
// debug builds from interim builds. Indeed you can even
// build a debug version of the final version. Therefore
// we just use the final version flag and mark anything
// not final version as interim and don't mention
// the debug property in the subversion
#if defined(_DEBUG)
# ifdef GIT_COMMIT
#	 define VBA_SUBVERSION_STRING VBA_RELEASE_TYPE " DEBUG git@" GIT_COMMIT
# else
#	 define VBA_SUBVERSION_STRING VBA_RELEASE_TYPE " DEBUG"
# endif
#	define VBA_BUILDTYPE_STRING VBA_RELEASE_TYPE " Debug"
#elif defined(PUBLIC_RELEASE)
# define VBA_SUBVERSION_STRING VBA_RELEASE_TYPE
#	define VBA_BUILDTYPE_STRING  "Release"
#else // interim
#ifdef GIT_COMMIT
#	define VBA_SUBVERSION_STRING VBA_RELEASE_TYPE " git@" GIT_COMMIT
#else
#	define VBA_SUBVERSION_STRING VBA_RELEASE_TYPE " git"
#endif
#	define VBA_BUILDTYPE_STRING "Interim"
#endif

#ifndef VBA_FEATURE_STRING
# define VBA_FEATURE_STRING ""
#endif

#if VBA_RR_MINOR_VERSION_NO > 0
#	define VBA_RR_VERSION_NO VBA_RR_MAJOR_VERSION_NO ## . ## VBA_RR_MINOR_VERSION_NO
# define VBA_RR_VERSION_AS_STRING STRINGIZE_VALUE(VBA_RR_MAJOR_VERSION_NO) "." STRINGIZE_VALUE(VBA_RR_MINOR_VERSION_NO)
#else
# define VBA_RR_VERSION_NO VBA_RR_MAJOR_VERSION_NO
#	define VBA_RR_VERSION_AS_STRING STRINGIZE_VALUE(VBA_RR_MAJOR_VERSION_NO)
#endif

#define VBA_VERSION_STRING "v" VBA_RR_VERSION_AS_STRING VBA_SUBVERSION_STRING VBA_FEATURE_STRING
#define VBA_NAME_AND_VERSION VBA_NAME " - " VBA_VERSION_STRING
#define VBA_RR_SITE "https://github.com/sniperrifle2004/vba-rerecording"

#endif // !VBA_VERSION_H
