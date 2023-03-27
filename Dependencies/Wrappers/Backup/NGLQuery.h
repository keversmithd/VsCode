#ifndef NGLQUERY
#define NGLQUERY

#include "NGLDebug.h"

struct NGLQuery
{
private:
	unsigned int m_query;
	bool generated;
public:
	NGLQuery();
	int GenerateQuery();
	int BeginQuery(GLenum target);
	int EndQuery(GLenum target);
	int BeginQueryIndexed(GLenum target, GLuint index);
	int EndQueryIndexed(GLenum target, GLuint index);
	int BeginConditionalRender(GLenum mode);
	int EndConditionalRender();
	int GetQueryIndexed(GLenum target, GLuint index, GLenum pname, GLint* params);
	int GetQueryObjectiv(GLenum pname, GLint* params);
	int GetQueryObjectuiv(GLenum pname, GLuint* params);
	int GetQueryObjecti64v(GLenum pname, GLint64* params);
	int GetQueryObjecti64v(GLenum pname, GLuint64* params);
	int GetQueryiv(GLenum target, GLenum pname, GLint* params);
	bool IsQuery();
	int QueryCounter(GLenum target);
	int DeleteQuery();
	bool Generated();
	unsigned int GetQuery();
	~NGLQuery();



};

#endif
