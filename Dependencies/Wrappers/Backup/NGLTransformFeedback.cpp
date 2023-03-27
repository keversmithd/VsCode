#ifndef NGLTRANSFEED
#define NGLTRANSFEED
#include "NGLTransformFeedback.h"
NGLTransformFeedback::NGLTransformFeedback()
{
	m_feedback = 0;
	created = false;
}
int NGLTransformFeedback::GenerateTransformFeedback()
{
	if (created)
	{
		NGLStateError("Feedback buffer currently active, delete in order to regenerate.\n");
		return 0;
	}
	glGenTransformFeedbacks(1, &m_feedback);
	GetError
		if (Code) { return 0; }
	created = true;
	return 1;

}
int NGLTransformFeedback::BindTransformFeedback()
{
	if (created)
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_feedback);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::BeginTransformFeedback(GLenum primitivemode)
{
	glBeginTransformFeedback(primitivemode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLTransformFeedback::PauseTransformFeedback()
{
	glPauseTransformFeedback();
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLTransformFeedback::ResumeTransformFeedback()
{
	glResumeTransformFeedback();
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLTransformFeedback::EndTransformFeedback()
{
	glEndTransformFeedback();
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLTransformFeedback::DrawTransformFeedback(GLenum mode)
{
	if (created)
	{
		glDrawTransformFeedback(mode, m_feedback);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
	
}
int NGLTransformFeedback::DrawTransformFeedbackInstanced(GLenum mode, GLsizei primcount)
{
	if (created)
	{
		glDrawTransformFeedbackInstanced(mode, m_feedback, primcount);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::DrawTransformFeedbackStream(GLenum mode, GLuint stream)
{
	if (created)
	{
		glDrawTransformFeedbackStream(mode, m_feedback, stream);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint stream, GLsizei primcount)
{
	if (created)
	{
		glDrawTransformFeedbackStreamInstanced(mode, m_feedback, stream, primcount);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::GetTransformFeedbackiv(GLenum pname, GLint* param)
{
	if (created)
	{
		glGetTransformFeedbackiv(m_feedback, pname, param);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::GetTransformFeedbacki_v(GLenum pname, GLuint index, GLint* param)
{
	if (created)
	{
		glGetTransformFeedbacki_v(m_feedback, pname, index, param);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::GetTransformFeedbacki64_v(GLenum pname, GLuint index, GLint64* param)
{
	if (created)
	{
		glGetTransformFeedbacki64_v(m_feedback, pname, index, param);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
bool NGLTransformFeedback::IsTransformFeedback()
{
	GLboolean isTransformFeedback = glIsTransformFeedback(m_feedback);
	return isTransformFeedback;
}
int NGLTransformFeedback::TransformFeedbackBufferBase(GLuint index, GLuint buffer)
{
	if (created)
	{
		glTransformFeedbackBufferBase(m_feedback, index, buffer);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::TransformFeedbackBufferRange(GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	if (created)
	{
		glTransformFeedbackBufferRange(m_feedback, index, buffer, offset, size);
		GetError
			if (Code) { return 0; }
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
int NGLTransformFeedback::DeleteTransformFeedback()
{
	if (created)
	{
		glDeleteTransformFeedbacks(1, &m_feedback);
		GetError
			if (Code) { return 0; }
		created = false;
		return 1;
	}
	NGLStateError("Feedback buffer has not been created and cannot be edited.\n");
	return 0;
}
NGLTransformFeedback::~NGLTransformFeedback()
{
	DeleteTransformFeedback();
}


#endif