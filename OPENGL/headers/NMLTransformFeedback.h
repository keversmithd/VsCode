#ifndef NMLTRANSFORMFEEDBACK
#define NMLTRANSFORMFEEDBACK

#include "NGL.h"
#include "NMLDebug.h"


struct NMLTransformFeedback : NGLBuffer
{
private:
	unsigned int xfb;
	bool m_data;
	size_t m_size;
	GLuint m_index;
public:
	NMLTransformFeedback();
	int CreateTransformFeedback();
	int BindTransformFeedback();
	int UnBindTransformFeedback();
	int TransformFeedbackData(GLsizeiptr size, const GLvoid* data, GLenum usage);
	int TransformFeedbackRange(GLuint index, GLintptr offset, GLsizeiptr size);
	int TransformFeedbackBase(GLuint index);
	int GetFeedbackData(GLsizei size, GLintptr offset,void* outData);
	~NMLTransformFeedback();


};

#endif
