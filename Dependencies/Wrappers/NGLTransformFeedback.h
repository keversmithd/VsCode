#ifndef __FUNCTION__ 
 #define __FUNCTION__ 
 #endif
#ifndef NGLTRANSFORMFEEDBACK
#define NGLTRANSFORMFEEDBACK

#include "NGLDebug.h"

struct NGLTransformFeedback
{
private:
	unsigned int m_feedback;
	bool created;
public:
	NGLTransformFeedback();
	int GenerateTransformFeedback();
	int BindTransformFeedback();
	int BeginTransformFeedback(GLenum primitiveMode);
	int PauseTransformFeedback();
	int ResumeTransformFeedback();
	int EndTransformFeedback();
	int DrawTransformFeedback(GLenum mode);
	int DrawTransformFeedbackInstanced(GLenum mode, GLsizei primcount);
	int DrawTransformFeedbackStream(GLenum mode, GLuint stream);
	int DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint stream, GLsizei primcount);
	int GetTransformFeedbackiv(GLenum pname, GLint* param);
	int GetTransformFeedbacki_v(GLenum pname, GLuint index, GLint* param);
	int GetTransformFeedbacki64_v(GLenum pname, GLuint index, GLint64* param);
	bool IsTransformFeedback();
	int TransformFeedbackBufferBase(GLuint index, GLuint buffer);
	int TransformFeedbackBufferRange(GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
	int DeleteTransformFeedback();
	~NGLTransformFeedback();
};

#endif