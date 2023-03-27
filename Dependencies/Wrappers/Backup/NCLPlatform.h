#ifndef NCLPLAT
#define NCLPLAT
#include <CL/cl.h>
#include <stdio.h>
#include "NCLDebug.h"
#include <memory>
struct NCLPlatform
{
protected:
	cl_platform_id platform;
	cl_platform_id* platforms;
	cl_uint num_platforms;
	bool incomplete;
public:
	NCLPlatform();
	int GetPlatforms();
	int SelectDefaultPlatform(cl_uint platformindex);
	int FreePlatforms();
	cl_platform_id ReturnPlatform();
	cl_platform_id& ReferencePlatform();
	cl_platform_id ArrayReturnPlatform(cl_uint platformindex);
	bool Completeness();
	cl_platform_id* get_platforms();

	~NCLPlatform();




};




#endif
