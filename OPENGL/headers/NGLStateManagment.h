#ifndef NGLSTATEMANAGEMENT
#define NGLSTATEMANAGEMENT

#include "NGLDebug.h"

struct NGLStateManagement
{
	NGLStateManagement();
	int SelectBuffer(GLsizei size, GLuint* buffer);
	int FeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer);
	int RenderMode(GLenum mode);
	int BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	int BlendEquation(GLenum mode);
	int BlendEquationi(GLuint buf, GLenum mode);
	int BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	int BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
	int BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	int BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	int ClampColor(GLenum target, GLenum clamp);
	int ClipControl(GLenum origin, GLenum depth);
	int ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	int ColorMaski(GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	int CullFace(GLenum mode);
	int DepthFunc(GLenum func);
	int DepthMask(GLboolean flag);
	int DepthRange(GLdouble nearVal, GLdouble farVal);
	int DepthRangef(GLfloat nearVal, GLfloat farVal);
	int DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble* v);
	int DepthRangeIndexed(GLuint index, GLdouble nearVal, GLdouble farVal);
	int Enable(GLenum cap);
	int Disable(GLenum cap);
	int Enablei(GLenum cap, GLuint index);
	int Disablei(GLenum cap, GLuint index);
	int FrontFace(GLenum mode);
	int GetBooleanv(GLenum pname, GLboolean* data);
	int GetDoublev(GLenum pname, GLdouble* data);
	int GetFloatv(GLenum pname, GLfloat* data);
	int GetIntegerv(GLenum pname, GLint* data);
	int GetInteger64v(GLenum pname, GLint64* data);
	int GetBooleani_v(GLenum target, GLuint index, GLboolean* data);
	int GetIntegeri_v(GLenum target, GLuint index, GLint* data);
	int GetFloati_v(GLenum target, GLuint index, GLfloat* data);
	int GetDoublei_v(GLenum target, GLuint index, GLdouble* data);
	int GetInteger64i_v(GLenum target, GLuint index, GLint64* data);
	int Hint(GLenum target, GLenum mode);
	GLboolean IsEnabled(GLenum cap);
	GLboolean IsEnabledi(GLenum cap, GLuint index);
	int LineWidth(GLfloat width);
	int LogicOp(GLenum opcode);
	int PixelStoref(GLenum pname, GLfloat param);
	int PixelStorei(GLenum pname, GLint param);
	int PointParameterf(GLenum pname, GLfloat param);
	int PointParameteri(GLenum pname, GLint param);
	int PointParameterfv(GLenum pname, const GLfloat* params);
	int PointParameteriv(GLenum pname, const GLint* params);
	int PointSize(GLfloat size);
	int PolygonMode(GLenum face, GLenum mode);
	int PolygonOffset(GLfloat factor, GLfloat units);
	int SampleCoverage(GLfloat value, GLboolean invert);
	int Scissor(GLint x, GLint y, GLsizei width, GLsizei height);
	int ScissorArrayv(GLuint first, GLsizei count, const GLint* v);
	int ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
	int ScissorIndexedv(GLuint index, const GLint* v);
	int StencilFunc(GLenum func, GLint ref, GLuint mask);
	int StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
	int StencilMask(GLuint mask);
	int StencilMaskSeparate(GLenum face, GLuint mask);
	int StencilOp(GLenum sfail, GLenum dpfail, GLenum dppass);
	int StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
	int Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	int ViewportArrayv(GLuint first, GLsizei count, const GLfloat* v);
	int ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	int ViewportIndexedfv(GLuint index, const GLfloat* v);

	~NGLStateManagement();
};

#endif