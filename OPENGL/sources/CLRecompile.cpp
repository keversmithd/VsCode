#include "CLRecompile.h"


char* CLParse(const char* path)
{
	FILE* ParseFile;
	fopen_s(&ParseFile, path, "rb");
	fpos_t extractionByteTotal;
	if (ParseFile != NULL)
	{
		fseek(ParseFile, 0, SEEK_END);
		fgetpos(ParseFile, &extractionByteTotal);
		fseek(ParseFile, 0, SEEK_SET);
		char* ParseBuffer = (char*)malloc(static_cast<size_t>(extractionByteTotal + 1));
		if (ParseBuffer != nullptr)
		{
			fread(ParseBuffer, extractionByteTotal, 1, ParseFile);
			ParseBuffer[extractionByteTotal] = '\0';
		}
		return ParseBuffer;
	}
	return nullptr;
}



DynamicCLBuffer::DynamicCLBuffer(DynamicCLBufferInitData data){
	Size = data.size;
	Context = data.context;
	Flags = data.flags;
}
int DynamicCLBuffer::InitialCreationBuffer()
{
	bufferunit = clCreateBuffer(*Context, Flags, Size, 0, &ERR);
	if (ERR == -1) {
		printf("Unable to create buffer\n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(ERR) == false) { return -1; }
	}
}

int DynamicCLBuffer::UpdateBufferCapacity(size_t size)
{
	bufferunit = nullptr;
	Size = size;
	bufferunit = clCreateBuffer(*Context, Flags, Size, 0, &ERR);
	if (ERR == -1) { printf("Unable to create buffer\n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(ERR) == false) { return -1; }
	}
}

int DynamicCLBuffer::WriteToBuffer(const void* data)
{
	clEnqueueWriteBuffer(*Queue, bufferunit, CL_TRUE, 0, Size, data, 0, 0, writeEvent);
	return 1;
}

int DynamicCLBuffer::ReadFromBuffer(void* dataout)
{
	clEnqueueReadBuffer(*Queue, bufferunit, CL_TRUE, 0, Size, dataout, 0, 0, readEvent);
	return 1;
}

CLRecompile::CLRecompile(const char* src)
{
	cl_int ERR;
	ERR = CLRContext();
	if (ERR == -1) { printf("Incomplete corrupted program in\n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return; }
	ERR = CLRQueue();
	if (ERR == -1) { printf("Incomplete corrupted program in\n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return; }
	ERR = CLRInitializeProgram();
	if (ERR == -1) { printf("Incomplete corrupted program in\n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; return; }
}

int CLRecompile::CLRContext()
{
	cl_int ERR;
	ERR = clGetPlatformIDs(1, &platform, NULL);
	if (CLerr(ERR) == false) { return -1; }
	ERR = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &gpu, NULL);
	if (CLerr(ERR) == false) { return -1; }
	context = clCreateContext(0, 1, &gpu, NULL, nullptr, &ERR);
	if (CLerr(ERR) == false) { return -1; }
}


int CLRecompile::CLRQueue()
{
	cl_int ERR;
	queue = clCreateCommandQueue(context, gpu, 0, &ERR);
	if (CLerr(ERR) == false) { return -1; }
}

int CLRecompile::CLRInitializeProgram()
{
	cl_int ERR;
	char* defaultsrc = CLParse(defaultsource);
	if (defaultsrc == nullptr)
	{
		printf("%s\n", "Invalid file path while initializing program, incomplete program set to undefined mode.");
		return 0;
	}
	program = clCreateProgramWithSource(context, 1, (const char**)&defaultsrc, NULL, &ERR);
	if (CLerr(ERR) == false) { return -1; }
	free(defaultsrc);
	return 1;
}

int CLRecompile::CLRTestCompile(const char* source)
{
	cl_int ERR;
	char* expsource = CLParse(source);
	testProgram = clCreateProgramWithSource(context, 1, (const char**)&expsource, 0, &ERR);
	if (ERR != CL_SUCCESS) { return -1; }
	ERR = clBuildProgram(testProgram, 0, NULL, NULL, NULL, NULL);
	if (ERR != CL_SUCCESS)
	{ 
		
		size_t len;
		ERR = clGetProgramBuildInfo(testProgram, gpu, CL_PROGRAM_BUILD_LOG, NULL, NULL, &len);
		char* buffer = (char*)malloc(len);
		ERR = clGetProgramBuildInfo(testProgram, gpu, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
		printf("%s\n", buffer);
		free(buffer);
		return -1; 
	}


}

void CLRecompile::CLRBindCompile()
{

}

void CLRecompile::CLRFileSizeUpdate()
{

}

CLRecompile::~CLRecompile() {

}