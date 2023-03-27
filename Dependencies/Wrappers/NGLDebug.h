#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NGLDEBUG
#define NGLDEBUG

#include <GL/glew.h>
#ifdef _WIN32
#include <GL/wglew.h>
#else
#include <GL/glxew.h>
#endif


#include <stdio.h>


#include "NGLErrorLog.h"


#define GetError int Code = GLError();
/* if(Code){ fprintf(stderr, "Found in  %s \n at line :  %d \n", __FUNCTION__ __FILE__, __LINE__); */
#define Status printf(__FILE__ "\n" __FUNCTION__ "\n" "%d \n", __LINE__ );

const char* GLErrorString(GLenum Code);
int GLError();


#endif
