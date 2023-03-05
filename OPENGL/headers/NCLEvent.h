#ifndef NCLEVEN
#define NCLEVEN

#include "NCLDebug.h"

struct NCLEvent
{
private:
	cl_event m_event;
	bool active;
public:
	NCLEvent();

	int CreateUserEvent(cl_context context);
	int GetEventInfo(cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
	int ReleaseEvent();
	int RetainEvent();
	int SetEventCallback(cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void* user_data), void* user_data);
	int SetUserEventStatus(cl_int execution_status);
	int WaitForEvents();

	~NCLEvent();

};


#endif
