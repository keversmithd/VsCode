#include "NCLEvent.h"

NCLEvent::NCLEvent()
{
	m_event = 0;
	active = false;
}

int NCLEvent::CreateUserEvent(cl_context context)
{
	cl_int Error = 0;
	if (active)
	{
		int ReleaseStatus = ReleaseEvent();
		if (!ReleaseStatus)
		{
			printf("Unable to release previous event object: Memory leak\n");
		}
		else
		{
			printf("Released previous event object: Memory leak\n");
		}
	}

	m_event = clCreateUserEvent(context, &Error);

	if (Error == -1)
	{
		printf("Creating the user event failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
	}

	active = true;
	return 1;

}
int NCLEvent::GetEventInfo(cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clGetEventInfo(m_event,param_name, param_value_size, param_value, param_value_size_ret);
		if (Error == -1)
		{
			printf("Creating the event info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}

		return 1;

	}

	return 0;
}
int NCLEvent::ReleaseEvent()
{
	if (active)
	{
		cl_int Error = 0;
		Error = clReleaseEvent(m_event);
		if (Error == -1)
		{
			printf("Unalbe to release event.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		active = false;
		return 1;
	}
	return 1;
}
int NCLEvent::RetainEvent()
{
	if (active)
	{
		cl_int Error = 0;
		Error = clRetainEvent(m_event);
		if (Error == -1)
		{
			printf("Retaining the event info failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}

		return 1;

	}

	return 0;
}
int NCLEvent::SetEventCallback(cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void* user_data), void* user_data)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clSetEventCallback(m_event, command_exec_callback_type, pfn_notify , user_data);
		if (Error == -1)
		{
			printf("Unable to set callback on event.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		active = false;
		return 1;
	}
	return 1;
	
}
int NCLEvent::SetUserEventStatus(cl_int execution_status)
{
	if (active)
	{
		cl_int Error = 0;
		Error = clSetUserEventStatus(m_event, execution_status);
		if (Error == -1)
		{
			printf("Setting user event stauts failed.: \n: " __FUNCTION__ " %d\n", __LINE__); if (CLerr(Error) == false) { return 0; }
		}
		active = false;
		return 1;
	}
	return 1;
}

NCLEvent::~NCLEvent() 
{
	ReleaseEvent();
}