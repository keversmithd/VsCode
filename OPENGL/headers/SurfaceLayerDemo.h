#ifndef SURFACELAYERDEMO
#define SURFACELAYERDEMO

#include "NCL.h"
#define WS "Workspace"

void SFLDemo()
{
    int Error;
    NCLPlatform Platform;
    Error = Platform.GetPlatforms();
    Error = Platform.SelectDefaultPlatform(0);
    Error = Platform.FreePlatforms();
    NCLDevice Device;
    Device.GetDevices(Platform.ReturnPlatform(), CL_DEVICE_TYPE_GPU);
    Device.SelectDefaultDevice(0);
    NCLContext Context;
    cl_device_id Id = Device.ReturnDevice();
    Context.CreateContext(NULL, 1, &Id, NULL, NULL);

    NCLCommandQueue qu;
    qu.CreateCommandQueue(Context.ReturnContext(), Device.ReturnDevice(), NULL);
    NCLBuffer b;
    int p[100];
    for (int i = 0; i < 100; i++)
    {
        p[i] = i;
    }
    int k[100] = { 0 };
    b.CreateBuffer(Context.ReturnContext(), CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, 100 * sizeof(int), p);
    NCLBuffer c;
    c.CreateBuffer(Context.ReturnContext(), CL_MEM_WRITE_ONLY, 100 * sizeof(int), NULL);
    const char* clFile = CLParser(WS "\\test.cl");
    NCLProgram prog;

    prog.CreateProgramWithSource(Context.ReturnContext(), 1, &clFile, NULL);
    prog.BuildProgram(1, &Id, NULL, NULL, NULL);
    int st = 0;
    prog.GetProgramBuildInfo(Id, CL_PROGRAM_BUILD_STATUS, sizeof(int), &st, NULL);
    size_t buildloglength = 0;
    prog.GetProgramBuildInfo(Id, CL_PROGRAM_BUILD_LOG, NULL, NULL, &buildloglength);
    char* buildlog = (char*)malloc(buildloglength);
    prog.GetProgramBuildInfo(Id, CL_PROGRAM_BUILD_LOG, buildloglength, buildlog, NULL);

    cl_mem bufferb = b.ReturnBuffer();
    cl_mem bufferc = c.ReturnBuffer();
    int RequiredPasses = log2(100);
    NCLKernel NaivePrefixSum;
    NaivePrefixSum.CreateKernel(prog.ReturnProgram(), "NPrefix");

    NCLBuffer IntegerBuffer;
    int* IntegerTrack = (int*)malloc(sizeof(int));
    IntegerTrack[0] = 0;
    IntegerBuffer.CreateBuffer(Context.ReturnContext(), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int), IntegerTrack);

    NCLBuffer SharedBuffer;
    SharedBuffer.CreateBuffer(Context.ReturnContext(), CL_MEM_READ_WRITE, sizeof(int) * 100, NULL);
    cl_mem Shared = SharedBuffer.ReturnBuffer();

    NaivePrefixSum.SetKernelArg(0, sizeof(cl_mem), &b);
    NaivePrefixSum.SetKernelArg(1, sizeof(cl_mem), &c);
    NaivePrefixSum.SetKernelArg(2, sizeof(cl_mem), &Shared);
    NaivePrefixSum.SetKernelArg(3, sizeof(cl_mem), &IntegerBuffer);

    const size_t workGroupSize = 100;
    for (int i = 1; i < 4; i++)
    {
        NaivePrefixSum.EnqueueNDRangeKernel(qu.ReturnCommandQueue(), 1, NULL, &workGroupSize, &workGroupSize, NULL, NULL, NULL);
        b.EnqueueReadBuffer(qu.ReturnCommandQueue(), CL_TRUE, 0, 100 * sizeof(int), k, NULL, NULL, NULL);
        IntegerTrack[0] += 1;
    }

    NCLKernel kernel;
    kernel.CreateKernel(prog.ReturnProgram(), "add");

    kernel.SetKernelArg(0, sizeof(cl_mem), &bufferb);
    kernel.SetKernelArg(1, sizeof(cl_mem), &bufferc);

    kernel.EnqueueNDRangeKernel(qu.ReturnCommandQueue(), 1, NULL, &workGroupSize, &workGroupSize, NULL, NULL, NULL);
    kernel.EnqueueNDRangeKernel()
    c.EnqueueReadBuffer(qu.ReturnCommandQueue(), CL_TRUE, 0, 100 * sizeof(int), k, NULL, NULL, NULL);
    qu.Finish();
}

#endif
