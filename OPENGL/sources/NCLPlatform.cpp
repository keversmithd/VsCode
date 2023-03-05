#include "NCLPlatform.h"


NCLPlatform::NCLPlatform()
{
	 platform = 0;
	 platforms = nullptr;
	 num_platforms = 0;
	 incomplete = false;
}

int NCLPlatform::GetPlatforms()
{
	cl_int Error;
	Error = clGetPlatformIDs(NULL, NULL, &num_platforms);
	if (Error == -1) {
		printf("Unable to get platform count. : \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}
	if (platforms != nullptr)
	{
		free(platforms);
	}
	platforms = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id));
	if (platforms == nullptr)
	{
		printf("Platforms allocation failue. : \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return 0;
	}
	Error = clGetPlatformIDs(num_platforms, platforms, NULL);
	if (Error == -1) {
		printf("Unable to get platform ids. : \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}

	return 1;


}
int NCLPlatform::SelectDefaultPlatform(cl_uint platformindex)
{
	if (platformindex > (num_platforms - 1))
	{
		printf("Platform index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (platforms == nullptr)
	{
		printf("platforms are null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (platforms[platformindex] == nullptr)
	{
		printf("Platform at index is null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	platform = platforms[platformindex];
	return 1;
}
int NCLPlatform::FreePlatforms()
{
	if (platforms != nullptr)
	{
		free(platforms);
	}
	return 1;
}
cl_platform_id NCLPlatform::ReturnPlatform()
{
	return platform;
	
}
cl_platform_id& NCLPlatform::ReferencePlatform()
{
	return platform;
}


cl_platform_id NCLPlatform::ArrayReturnPlatform(cl_uint platformindex)
{
	if (platformindex > (num_platforms - 1))
	{
		printf("Platform index out of bounds, incomplete: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (platforms == nullptr)
	{
		printf("Platforms are null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	if (platforms[platformindex] == nullptr)
	{
		printf("Platform at index is null: \n: " __FUNCTION__ "%d\n", __LINE__);
		incomplete = true;
		return 0;
	}

	return platforms[platformindex];
}
bool NCLPlatform::Completeness()
{
	bool Flip = !incomplete;
	return Flip;
}
NCLPlatform::~NCLPlatform()
{
	if (platforms != nullptr)
	{
		free(platforms);
	}

}
