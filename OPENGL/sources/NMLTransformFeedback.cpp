#include "NMLTransformFeedback.h"

NMLTransformFeedback::NMLTransformFeedback()
{
	xfb = 0;
	m_data = false;
	m_size = 0;
	m_index = 0;
}
int NMLTransformFeedback::CreateTransformFeedback()
{
	glGenTransformFeedbacks(1, &xfb);
	GetError
		if (Code) { return 0; }
	int GenerationStatus = GenerateBuffer();
	if (!GenerationStatus) { return 0; }
	SetDeleted(false);
	return 1;
}
int NMLTransformFeedback::BindTransformFeedback()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, xfb);
	GetError
		if (Code) { return 0; }
	BindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
	return 1;
}
int NMLTransformFeedback::UnBindTransformFeedback()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	GetError
		if (Code) { return 0; }
	return Unbind(GL_TRANSFORM_FEEDBACK_BUFFER);
}
int NMLTransformFeedback::TransformFeedbackData(GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	if (m_data) { if (!InvalidateBufferData()) { return 0; } }
	if (Deleted()){return 0;}
	int BufferStatus = BufferData(size, data, usage);
	if (!BufferStatus) { return 0; }
	m_data = true;
	m_size = size;
	return 1;

}
int NMLTransformFeedback::TransformFeedbackBase(GLuint index)
{
	if (Deleted()) { return 0; }
	if (!m_data) { return 0; }
	glTransformFeedbackBufferBase(xfb, index, ReferenceBuffer());
	GetError
		if (Code) { return 0; }
	return 1;
}
int NMLTransformFeedback::TransformFeedbackRange(GLuint index, GLintptr offset, GLsizeiptr size)
{
	if (Deleted()) { return 0; }
	if (!m_data) { return 0; }
	glTransformFeedbackBufferRange(xfb, index, ReferenceBuffer(), offset, size);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NMLTransformFeedback::GetFeedbackData(GLsizei size, GLintptr offset, void* outData)
{
	if (offset < 1 || offset+size > m_size) { return 0; }
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, offset, size, outData);
	GetError
		if (Code) { return 0; }

}
NMLTransformFeedback::~NMLTransformFeedback()
{
	DeleteBuffer();
}