#ifndef VBA_VERSIONINFO_H
#define VBA_VERSIONINFO_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../version.h"

#if SVN_REV > 65535
#	define VBA_RR_BUILD_NO 0
#else
#	ifdef GIT_COMMIT
#		define VBA_RR_BUILD_NO GIT_COMMIT
#	else
#		define VBA_RR_BUILD_NO 0
#	endif
#endif

// diaplayed in the file attribute dialog
// TODO: Figure out if having different versions here is actually useful
// in some way. I cannot imagine what for at the moment
#define VBA_VERSIONINFO_FILEVER		   VBA_RR_MAJOR_VERSION_NO, VBA_RR_MINOR_VERSION_NO, VBA_RR_BUILD_NO
#define VBA_VERSIONINFO_STRFILEVER     STRINGIZE_VALUE(VBA_VERSIONINFO_FILEVER) "\0"

#define VBA_VERSIONINFO_PRODUCTVER     VBA_VERSIONINFO_FILEVER
#define VBA_VERSIONINFO_STRPRODUCTVER  VBA_VERSIONINFO_STRFILEVER
// FIXME: Fix this up to properly reflect the history and the current situation
#define VBA_VERSIONINFO_STRCOPYRIGHT   "Copyright (C) 2005-2012 VBA-RR Development Team"
#define VBA_VERSIONINFO_ORGANIZATION   VBA_RR_SITE

// So this is where the debug and interim values actually make a difference
#ifdef _DEBUG
#	define VBA_VERSIONINFO_FILEFLAGS   VS_FF_DEBUG
#elif defined(PUBLIC_RELEASE)
#	define VBA_VERSIONINFO_FILEFLAGS   0
#else
#	define VBA_VERSIONINFO_FILEFLAGS   VS_FF_PRERELEASE
#endif

#endif // VBA_VERSIONINFO_H
