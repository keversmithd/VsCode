#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NGLINFO_H
#define NGLINFO_H

#include "NGLDebug.h"

struct NGLInformation
{
	NGLInformation();
	int MaximumVertexArraysBindings(GLint* param);
	
	~NGLInformation();
};

#endif
