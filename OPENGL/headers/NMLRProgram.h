#ifndef NMLRPROG
#define NMLRPROG

#include "NGLProgram.h"
#include "NGLShader.h"

#include <vector>

#define WS2 "X:\\1.4 C++\\Visual Studio Projects\\OpenGL\\OpenGL32\\OpenGL\\"

struct NMLRProgram : NGLProgram
{
private:
	const char* m_src_loc_def[5]{ WS2 "vertex.glsl", WS2 "tesscontrol.glsl", WS2 "tesseval.glsl", WS2 "geometry.glsl", WS2 "fragment.glsl" };
	GLenum m_shadertypes[5]{ GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
	NGLShader m_shaders[5]{};
	bool m_activeShaders[5]{ false, false, false, false, false };
	bool defaultGood;
	
	bool varying;
	const GLchar** varyings;
	int varyingsCount;
	GLenum bufferMode;
public:
	NMLRProgram();
	int SetTransformFeedbackMode(const GLchar** varyings, int varyingsCount, GLenum _bufferMode);
	int DisableTransformFeedback();
	int Start();
	int CreateDefaultProgram();
	int LoadDefaultShaders();
	int AttachDefaultShaders();
	int DetachDefaultShaders();


	int LoadActiveShaders();
	int ActiveShaderLoadStatus();
	int AttachActiveShaders();
	

	int DetachActiveShaders();
	int LinkMainProgram();

	int	SubmitVertexShaderSource(const char* m_src_loc);
	int SubmitFragmentShaderSource(const char* m_src_loc);
	int SubmitTesselationControlShaderSource(const char* m_src_loc);
	int SubmitTesselationEvaluationShaderSource(const char* m_src_loc);
	int SubmitGeometryShaderSource(const char* m_src_loc);
	int SubmitShaderRange(GLenum* m_types, const char** m_src_loc, int n);
	int EngageTesselationShader();
	int EngageGeometryShader();
	bool TesselationEngaged();
	
	bool GeometryEngaged();
	int RecompileProgram();
	int ExchangeValidProgram();
	int GetIndexByEnum(GLenum Shadertype);
	bool CheckCompilationStatus(GLenum ShaderType);
	bool CheckCompilationStatus(int index);
	~NMLRProgram();

};


#endif