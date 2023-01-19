#ifndef ADPASIODEBUG
#define ADPASIODEBUG
#include <stdio.h>
#include <string.h>
#include "asiosys.h"
#include "asio.h"
#include "asiodrivers.h"
#include <tchar.h>


constexpr long adp_MaxInputChannels = 32;
constexpr long adp_MaxOutputChannels = 32;


#if NATIVE_INT64
	#define ASIO64toDouble(a)  (a)
#else
	#define ASIO64toDouble(a)  ((a).lo + (a).hi * 4294967296.)
#endif

#endif