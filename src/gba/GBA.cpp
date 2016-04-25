#ifndef VBA_GBA_CPP_INCLUDED
#define VBA_GBA_CPP_INCLUDED

#ifdef USE_GBA_CORE_V7
#warning Using a V7 core. Please make sure you have supplied a meaningfull VBA_FEATURE_STRING to the build
#include "V7/GBA.cpp"
#else
#include "V8/GBA.cpp"
#endif

#endif
