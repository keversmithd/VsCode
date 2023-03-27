#include "NGLSync.h"

NGLSync::NGLSync()
{
	m_sync = 0;
	deleted = true;
}
int NGLSync::FenceSync(GLenum condition, GLbitfield flags)
{
	if (deleted)
	{
		m_sync = glFenceSync(condition, flags);
		GetError
			if (Code) { return 0; }
		deleted = false;
		return 1;
	}
	
	printf("Fence is has been created, delete the sync to regenerate.\n"); Status
	return 0;
}
int NGLSync::WaitSync(GLbitfield flags, GLuint64 timeout) 
{
	if (deleted)
	{
		printf("Sync is deleted and cannot be edited, generate sync.\n"); Status
		return 0;
	}

	glWaitSync(m_sync, flags, timeout);
	GetError
		if (Code) { return 0; }
	return 1;

}
int NGLSync::ClientWaitSync(GLbitfield flags, GLuint64 timeout)
{
	if (deleted)
	{
		printf("Sync is deleted and cannot be edited, generate sync.\n"); Status
			return 0;
	}

	glClientWaitSync(m_sync, flags, timeout);
	GetError
		if (Code) { return 0; }
	return 1;
	
}
int NGLSync::TextureBarrier()
{
	glTextureBarrier();
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLSync::GetSynciv(GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)
{
	if (deleted)
	{
		printf("Sync is deleted and cannot be edited, generate sync.\n"); Status
			return 0;
	}

	glGetSynciv(m_sync, pname, bufSize, length, values);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLSync::DeleteSync()
{
	if (deleted)
	{
		printf("Sync is deleted and cannot be edited, generate sync.\n"); Status
			return 0;
	}

	glDeleteSync(m_sync);
	GetError
		if (Code) { return 0; }
	deleted = true;
	return 1;

}
bool NGLSync::IsSync()
{
	GLboolean issync = glIsSync(m_sync);
	return issync;
}
NGLSync::~NGLSync() 
{
	DeleteSync();
}