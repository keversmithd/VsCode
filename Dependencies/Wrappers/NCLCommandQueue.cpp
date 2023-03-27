#include "NCLCommandQueue.h"

NCLCommandQueue::NCLCommandQueue()
{
	commandqueue = 0;
	incomplete = false;
	active = false;
	released = true;
}
int NCLCommandQueue::CreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties)
{
	cl_int Error = 0;
	if (active == true && released == false)
	{
		printf("Command queue already active: Releasing object. \n");
		Error = clReleaseCommandQueue(commandqueue);
		if (CLerr(Error) == false)
		{
			printf("Failure to release command queue. \n: " __FUNCTION__ "%d\n", __LINE__);
			incomplete = true;
			return 0;
		}
	}
	commandqueue = clCreateCommandQueue(context, device, properties, &Error);
	if (Error == -1) {
		printf("Unable to create command queue: \n: " __FUNCTION__ "%d\n", __LINE__); incomplete = true; if (CLerr(Error) == false) { return 0; }
	}
	active = true;
	released = false;
	return 1;
}
int NCLCommandQueue::RetainCommandQueue()
{
	cl_int Error = 0;
	if (active == true && released == false)
	{
		Error = clRetainCommandQueue(commandqueue);
		if (CLerr(Error) == false)
		{
			printf("Failure to retain command queue. \n: " __FUNCTION__ "%d\n", __LINE__);
			incomplete = true;
			return 0;
		}

		return 1;

	}
	else
	{
		printf("Not active and possibly released.. \n: " __FUNCTION__ "%d\n", __LINE__);
		
		return 0;
	}
	
	return 0;

}
int NCLCommandQueue::ReleaseCommandQueue()
{
	cl_int Error = 0;
	if (active == true && released == false)
	{
		printf("Command queue already active: Releasing object. \n");
		Error = clReleaseCommandQueue(commandqueue);
		if (CLerr(Error) == false)
		{
			printf("Failure to release command queue. \n: " __FUNCTION__ "%d\n", __LINE__);
			incomplete = true;
			return 0;
		}
	}
	active = false;
	released = true;
	return 1;
}
int NCLCommandQueue::EnqueueBarrier()
{
	if (active)
	{
		cl_int Error = 0;

		//Error = clEnqueueBarrier(commandqueue);
		if (Error == -1)
		{
			printf("Unable to enqueue command queue with barrier.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;

	}
	return 0;
}
int NCLCommandQueue::EnqueueBarrierWithWaitList(cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	if (active)
	{
		cl_int Error = 0;

		Error = clEnqueueBarrierWithWaitList(commandqueue, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1)
		{
			printf("Unable to enqueue barrier with wait list.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;

	}
	return 0;
}
int NCLCommandQueue::EnqueueMarkerWithWaitList(cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event)
{
	if (active)
	{
		cl_int Error = 0;

		Error = clEnqueueMarkerWithWaitList(commandqueue, num_events_in_wait_list, event_wait_list, event);
		if (Error == -1)
		{
			printf("Unable to enqueue barrier with wait list.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		return 1;

	}
	return 0;
}
int NCLCommandQueue::Flush()
{
	if (active)
	{
		clFlush(commandqueue);
		return 1;
	}
	return 0;
}
int NCLCommandQueue::Finish()
{
	if (active)
	{
		clFinish(commandqueue);
		return 1;
	}
	return 0;
}
cl_command_queue NCLCommandQueue::ReturnCommandQueue()
{
	return commandqueue;
}
bool NCLCommandQueue::Completeness()
{
	bool Flip = !incomplete;
	return Flip;
}
NCLCommandQueue::~NCLCommandQueue()
{
	ReleaseCommandQueue();
}