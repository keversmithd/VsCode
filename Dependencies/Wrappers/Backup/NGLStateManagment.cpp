#include "NGLStateManagment.h"

NGLStateManagement::NGLStateManagement()
{
	
}
int NGLStateManagement::SelectBuffer(GLsizei size, GLuint* buffer)
{
	glSelectBuffer(size, buffer);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::FeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer)
{
	glFeedbackBuffer(size, type, buffer);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::RenderMode(GLenum mode) 
{
	glRenderMode(mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glBlendColor(red, green, blue, alpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendEquation(GLenum mode)
{
	glBlendEquation(mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendEquationi(GLuint buf, GLenum mode)
{
	glBlendEquationi(buf, mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	glBlendEquationSeparate(modeRGB, modeAlpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ClampColor(GLenum target, GLenum clamp)
{
	glClampColor(target, clamp);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ClipControl(GLenum origin, GLenum depth)
{
	glClipControl(origin, depth);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ColorMaski(GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMaski(buf, red, green, blue, alpha);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::CullFace(GLenum mode)
{
	glCullFace(mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::DepthFunc(GLenum func)
{
	glDepthFunc(func);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::DepthMask(GLboolean flag)
{
	glDepthMask(flag);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::DepthRange(GLdouble nearVal, GLdouble farVal)
{
	glDepthRange(nearVal, farVal);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::DepthRangef(GLfloat nearVal, GLfloat farVal)
{
	glDepthRangef(nearVal, farVal);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v)
{
	glDepthRangeArrayv(first, count, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::DepthRangeIndexed(GLuint index, GLdouble nearVal, GLdouble farVal)
{
	glDepthRangeIndexed(index, nearVal, farVal);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Enable(GLenum cap)
{
	glEnable(cap);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Disable(GLenum cap)
{
	glDisable(cap);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Enablei(GLenum cap, GLuint index)
{
	glEnablei(cap, index);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Disablei(GLenum cap, GLuint index)
{
	glDisablei(cap, index);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::FrontFace(GLenum mode)
{
	glFrontFace(mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetBooleanv(GLenum pname, GLboolean* data)
{
	glGetBooleanv(pname, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetDoublev(GLenum pname, GLdouble* data)
{
	glGetDoublev(pname, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetFloatv(GLenum pname, GLfloat* data)
{
	glGetFloatv(pname, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetIntegerv(GLenum pname, GLint* data)
{
	glGetIntegerv(pname, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetInteger64v(GLenum pname, GLint64* data)
{
	glGetInteger64v(pname, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetBooleani_v(GLenum target, GLuint index, GLboolean* data)
{
	glGetBooleani_v(target, index, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetIntegeri_v(GLenum target, GLuint index, GLint* data)
{
	glGetIntegeri_v(target, index, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetFloati_v(GLenum target, GLuint index, GLfloat* data)
{
	glGetFloati_v(target, index, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetDoublei_v(GLenum target, GLuint index, GLdouble* data)
{
	glGetDoublei_v(target, index, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::GetInteger64i_v(GLenum target, GLuint index, GLint64* data)
{
	glGetInteger64i_v(target, index, data);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Hint(GLenum target, GLenum mode)
{
	glHint(target, mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
GLboolean NGLStateManagement::IsEnabled(GLenum cap)
{
	GLboolean isEnabled = glIsEnabled(cap);
	return isEnabled;
}
GLboolean NGLStateManagement::IsEnabledi(GLenum cap, GLuint index)
{
	GLboolean isEnabled = glIsEnabledi(cap, index);
	return isEnabled;
}
int NGLStateManagement::LineWidth(GLfloat width)
{
	glLineWidth(width);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::LogicOp(GLenum opcode)
{
	glLogicOp(opcode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PixelStoref(GLenum pname, GLfloat param)
{
	glPixelStoref(pname, param);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PixelStorei(GLenum pname, GLint param)
{
	glPixelStorei(pname, param);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PointParameterf(GLenum pname, GLfloat param)
{
	glPointParameterf(pname, param);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PointParameteri(GLenum pname, GLint param)
{
	glPointParameteri(pname, param);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PointParameterfv(GLenum pname, const GLfloat* params)
{
	glPointParameterfv(pname, params);
	GetError
		if (Code) { return 0; }
	return 1;

}
int NGLStateManagement::PointParameteriv(GLenum pname, const GLint* params)
{
	glPointParameteriv(pname, params);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PointSize(GLfloat size)
{
	glPointSize(size);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PolygonMode(GLenum face, GLenum mode)
{
	glPolygonMode(face, mode);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::PolygonOffset(GLfloat factor, GLfloat units)
{
	glPolygonOffset(factor, units);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::SampleCoverage(GLfloat value, GLboolean invert)
{
	glSampleCoverage(value, invert);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor(x, y, width, height);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ScissorArrayv(GLuint first, GLsizei count, const GLint* v)
{
	glScissorArrayv(first, count, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
	glScissorIndexed(index, left, bottom, width, height);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ScissorIndexedv(GLuint index, const GLint* v)
{
	glScissorIndexedv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::StencilFunc(GLenum func, GLint ref, GLuint mask)
{
	glStencilFunc(func, ref, mask);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	glStencilFuncSeparate(face, func, ref, mask);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::StencilMask(GLuint mask)
{
	glStencilMask(mask);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::StencilMaskSeparate(GLenum face, GLuint mask)
{
	glStencilMaskSeparate(face, mask);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::StencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
{
	glStencilOp(sfail, dpfail, dppass);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	glStencilOpSeparate(face, sfail, dpfail, dppass);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ViewportArrayv(GLuint first, GLsizei count, const GLfloat* v)
{
	glViewportArrayv(first, count, v);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	glViewportIndexedf(index, x, y, w, h);
	GetError
		if (Code) { return 0; }
	return 1;
}
int NGLStateManagement::ViewportIndexedfv(GLuint index, const GLfloat* v)
{
	glViewportIndexedfv(index, v);
	GetError
		if (Code) { return 0; }
	return 1;
}

NGLStateManagement::~NGLStateManagement(){}