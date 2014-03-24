// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN



#if defined DLL_EXPORT
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#define ALIGNED16 __declspec( align( 16 ) )
#define EXTERN_C extern "C"

#include <cassert>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <exception>

#include <cfloat>
#include <stdexcept>
#include <memory>
#include <set>
#include <utility>
#include <hash_set>

#include <omp.h>
