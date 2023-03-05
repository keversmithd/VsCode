#include "NGLInformation.h"
NGLInformation::NGLInformation(){}
int NGLInformation::MaximumVertexArraysBindings(GLint* param)
{
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, param);
	GetError
		if (Code) { NGLStateError("Information Error: "); return 0; }
	return 1;
}
NGLInformation::~NGLInformation() {}