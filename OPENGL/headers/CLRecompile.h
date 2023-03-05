#ifndef __FUNCTION__
#define __FUNCTION__
#endif
#ifndef CLREC
#define CLREC

#include <CL/cl.h>
#include <stdio.h>
#include <initializer_list>
#include <memory>
#include "NCLDebug.h"

char* CLParse(const char* path);


struct DynamicCLBufferInitData
{
	size_t size;
	cl_mem_flags flags;
	cl_context* context;
};

struct DynamicCLBuffer
{
	cl_context* Context;
	cl_command_queue* Queue;
	cl_mem_flags Flags;
	size_t Size;
	cl_mem bufferunit;
	bool incomplete = false;
	cl_int ERR;
	cl_event* writeEvent;
	cl_event* readEvent;
	DynamicCLBuffer(DynamicCLBufferInitData data);
	int InitialCreationBuffer();
	int UpdateBufferCapacity(size_t size);
	int WriteToBuffer(const void* data);
	int ReadFromBuffer(void* dataout);
};

class CLRecompile
{
	cl_platform_id platform;
	cl_device_id gpu;
	cl_context context;
	cl_program program;
	cl_program testProgram;
	cl_command_queue queue;
	cl_kernel kernel;
	bool incomplete = false;
	const char* defaultsource;
	const char* experimentalsource;
public:
	CLRecompile(const char* src);
	int  CLRContext();
	int  CLRQueue();
	int  CLRTestCompile(const char* source);
	int  CLRInitializeProgram();
	void ResetKernel(const char* src, std::initializer_list<cl_mem> args);
	void CLRBindCompile();
	void CLRFileSizeUpdate();
	~CLRecompile();
};

#endif