#ifndef NGLSYNC
#define NGLSYNC

#include "NGLDebug.h"

struct NGLSync
{
private:
	GLsync m_sync;
	bool deleted;
public:
	NGLSync();
	int FenceSync(GLenum condition, GLbitfield flags);
	int WaitSync(GLbitfield flags, GLuint64 timeout);
	int ClientWaitSync(GLbitfield flags, GLuint64 timeout);
	int TextureBarrier();
	int GetSynciv(GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values);
	int DeleteSync();
	bool IsSync();
	~NGLSync();

};

#endif
