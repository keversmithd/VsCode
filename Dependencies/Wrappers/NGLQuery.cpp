#include "NGLQuery.h"
NGLQuery::NGLQuery()
{
	m_query = 0;
	generated = false;
}
int NGLQuery::GenerateQuery()
{
	if (generated)
	{
		printf("Query object already generated, delete before generating again.\n");
		return 0;
	}
	glGenQueries(1, &m_query);
	GetError
		if (Code) { return 0; }
	generated = true;
	return 1;
}
int NGLQuery::BeginQuery(GLenum target)
{
	if (generated)
	{
		glBeginQuery(target, m_query);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::EndQuery(GLenum target)
{
	if (generated)
	{
		glEndQuery(target);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
	
}
int NGLQuery::BeginQueryIndexed(GLenum target, GLuint index) 
{
	if (generated)
	{
		glBeginQueryIndexed(target, index, m_query);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;

}
int NGLQuery::EndQueryIndexed(GLenum target, GLuint index)
{
	if (generated)
	{
		glEndQueryIndexed(target, index);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::BeginConditionalRender(GLenum mode)
{
	if (generated)
	{
		glBeginConditionalRender(m_query, mode);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::EndConditionalRender()
{
	if (generated)
	{
		glEndConditionalRender();
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::GetQueryIndexed(GLenum target, GLuint index, GLenum pname, GLint* params)
{
	if (generated)
	{
		glGetQueryIndexediv(target, index, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::GetQueryObjectiv(GLenum pname, GLint* params)
{

	if (generated)
	{
		glGetQueryObjectiv(m_query, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::GetQueryObjectuiv(GLenum pname, GLuint* params)
{

	if (generated)
	{
		glGetQueryObjectuiv(m_query, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::GetQueryObjecti64v(GLenum pname, GLint64* params)
{

	if (generated)
	{
		glGetQueryObjecti64v(m_query, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::GetQueryObjecti64v(GLenum pname, GLuint64* params)
{

	if (generated)
	{
		glGetQueryObjectui64v(m_query, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::GetQueryiv(GLenum target, GLenum pname, GLint* params)
{
	if (generated)
	{
		glGetQueryiv(target, pname, params);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
bool NGLQuery::IsQuery()
{
	GLboolean isQry = glIsQuery(m_query);
	return isQry;
}
int NGLQuery::QueryCounter(GLenum target)
{
	if (generated)
	{
		glQueryCounter(m_query, target);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, generate before altering object.\n");
	return 0;
}
int NGLQuery::DeleteQuery()
{
	if (generated)
	{
		glDeleteQueries(1, &m_query);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	printf("Query object is not generated, and cannot be deleted.\n");
	return 0;
}
bool NGLQuery::Generated()
{
	return generated;
}
unsigned int NGLQuery::GetQuery()
{
	return m_query;
}
NGLQuery::~NGLQuery()
{
	DeleteQuery();
}