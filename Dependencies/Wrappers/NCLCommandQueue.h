#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NCLCOM
#define NCLCOM
#include <CL/cl.h>
#include <memory>
#include "NCLDebug.h"
struct NCLCommandQueue
{
private:
	cl_command_queue commandqueue;
	bool active;
	bool incomplete;
	bool released;
public:
	NCLCommandQueue();
	int CreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties);
	int RetainCommandQueue();
	int ReleaseCommandQueue();

	int EnqueueBarrier();
	int EnqueueBarrierWithWaitList(cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int EnqueueMarkerWithWaitList(cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
	int Flush();
	int Finish();

	cl_command_queue ReturnCommandQueue();
	bool Completeness();
	~NCLCommandQueue();
};


#endif
