#ifndef VBA_GB_CPP_INCLUDED
#define VBA_GB_CPP_INCLUDED

#ifdef USE_GB_CORE_V7
#warning Using a V7 core. Please make sure you have supplied a meaningfull VBA_FEATURE_STRING to the build
#include "V7/GB.cpp"
#else
#include "V8/GB.cpp"
#endif

#endif
