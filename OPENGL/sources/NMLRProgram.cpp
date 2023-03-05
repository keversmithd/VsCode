#include "NMLRProgram.h"



NMLRProgram::NMLRProgram()
{
	defaultGood = false;
	varying = false;
	const GLchar** varyings = nullptr;
	varyingsCount = 0;
	bufferMode = GL_NONE;
}

int NMLRProgram::SetTransformFeedbackMode(const GLchar** _varyings, int _varyingsCount, GLenum _bufferMode)
{
	if (_bufferMode != GL_INTERLEAVED_ATTRIBS && _bufferMode != GL_SEPARATE_ATTRIBS)
	{
		return 0;
	}
	if (!varying)
	{
		varying = true;
	}
	varyings = _varyings;
	varyingsCount = _varyingsCount;
	bufferMode = _bufferMode;
	return 1;
}

int NMLRProgram::DisableTransformFeedback()
{
	varying = false;
	return 1;
}

int NMLRProgram::Start()
{
	defaultGood = false;
	int ProgramCreationStatus = CreateDefaultProgram();
	if (ProgramCreationStatus)
	{
			int ShaderLoadStatus = LoadDefaultShaders();
			if (ShaderLoadStatus)
			{
				int AttachStatus = AttachDefaultShaders();
				if (AttachStatus)
				{
					int LinkStatus = LinkMainProgram();
					if (LinkStatus)
					{
						defaultGood = true;
					}
				}
				DetachDefaultShaders();

			}


	}
	return defaultGood;
}

int NMLRProgram::CreateDefaultProgram()
{
	return CreateProgram();
}

int NMLRProgram::LoadDefaultShaders()
{
	int error = 1;
	int ferror = 1;
	for (int i = 0; i < 5; i++)
	{
		const char* src = NGLParseShader(m_src_loc_def[i]);
		if (!src)
		{
			ferror = 0;
		}
		error = m_shaders[i].CreateShader(m_shadertypes[i]);
		if (!error)
		{
			ferror = 0;
		}
		error = m_shaders[i].ShaderSource(1, &src, NULL);
		if (!error)
		{
			ferror = 0;
		}
		error = m_shaders[i].CompileShader();
		if (!error)
		{
			ferror = 0;
		}
		free((char*)src);
	}

	return ferror;
}

int NMLRProgram::AttachDefaultShaders()
{
	int ferror = 1;
	int attachmentStatus = AttachShader(m_shaders[0].ReturnShader());
	if (attachmentStatus)
	{
		m_activeShaders[0] = true;
		
	}
	else
	{
		ferror = 0;
	}
	
	attachmentStatus = AttachShader(m_shaders[4].ReturnShader());
	if (attachmentStatus)
	{
		m_activeShaders[4] = true;
		
	}
	else
	{
		ferror = 0;
	}
	return ferror;

}
int NMLRProgram::DetachDefaultShaders()
{
	int ferror = 1;
	int DetachmentStatus = DetachShader(m_shaders[0].ReturnShader());
	if (!DetachmentStatus)
	{
		ferror = 0;
	}
	DetachmentStatus = DetachShader(m_shaders[4].ReturnShader());
	if (!DetachmentStatus)
	{
		ferror = 0;
	}
	return ferror;

}
int NMLRProgram::LoadActiveShaders()
{
	int error = 1;
	int ferror = 1;
	for (int i = 0; i < 5; i++)
	{
		if (m_activeShaders[i])
		{
			const char* src = NGLParseShader(m_src_loc_def[i]);
			if (!src)
			{
				ferror = 0;
			}
			error = m_shaders[i].ShaderSource(1, &src, NULL);
			if (!error)
			{
				ferror = 0;
			}
			error = m_shaders[i].CompileShader();
			if (!error)
			{
				ferror = 0;
			}
			free((char*)src);
		}
	}

	return ferror;
}
int NMLRProgram::ActiveShaderLoadStatus()
{
	int error = 1;
	int ferror = 1;
	GLint param = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_activeShaders[i])
		{
			m_shaders[i].GetShaderiv(GL_COMPILE_STATUS, &param);
			if (!param)
			{
				ferror = 0;
			}
		}
	}

	return ferror;
}
int NMLRProgram::AttachActiveShaders()
{
	int attachmentStatus = 1;
	int ferror = 1;
	for (int i = 0; i < 5; i++)
	{
		if (m_activeShaders[i])
		{
			attachmentStatus = AttachShader(m_shaders[i].ReturnShader());
			if (!attachmentStatus) { ferror = attachmentStatus; }
		}
	}
	return ferror;
}
int NMLRProgram::DetachActiveShaders()
{
	int detachmentStatus = 1;
	int ferror = 1;
	for (int i = 0; i < 5; i++)
	{
		if (m_activeShaders[i])
		{
			detachmentStatus = DetachShader(m_shaders[i].ReturnShader());
			if (!detachmentStatus) { ferror = detachmentStatus; }
		}
	}
	return ferror;
}
int NMLRProgram::LinkMainProgram()
{
	if (varying)
	{
		int feedBackError = TransformFeedbackVaryings(varyingsCount, varyings, bufferMode);
		if (!feedBackError) { return 0; }
	}
	return LinkProgram();
}

int	NMLRProgram::SubmitVertexShaderSource(const char* m_src_loc)
{
	m_src_loc_def[0] = m_src_loc;
	return 1;
}
int NMLRProgram::SubmitFragmentShaderSource(const char* m_src_loc)
{
	m_src_loc_def[4] = m_src_loc;
	return 1;
}
int NMLRProgram::SubmitTesselationControlShaderSource(const char* m_src_loc)
{
	m_src_loc_def[1] = m_src_loc;
	return 1;
}
int NMLRProgram::SubmitTesselationEvaluationShaderSource(const char* m_src_loc)
{
	m_src_loc_def[2] = m_src_loc;
	return 1;
}
int NMLRProgram::SubmitGeometryShaderSource(const char* m_src_loc)
{
	m_src_loc_def[3] = m_src_loc;
	return 1;
}
int NMLRProgram::SubmitShaderRange(GLenum* m_types, const char** m_src_loc, int n)
{
	if (n > 5) { return 0; }
	for (int i = 0; i < n; i++)
	{
		int Index = GetIndexByEnum(m_types[i]);
		m_src_loc_def[Index] = m_src_loc[i];
	}
	return 1;
}
int NMLRProgram::EngageTesselationShader()
{
	m_activeShaders[1] = true;
	m_activeShaders[2] = true;
	return 1;
}
int NMLRProgram::EngageGeometryShader()
{
	m_activeShaders[3] = true;
	return 1;
}
bool NMLRProgram::TesselationEngaged()
{
	return (m_activeShaders[1] && m_activeShaders[2]);
}
bool NMLRProgram::GeometryEngaged()
{
	return (m_activeShaders[3]);
}

int NMLRProgram::RecompileProgram()
{
	
	int LoadStatus = LoadActiveShaders();
	if (!LoadStatus) { return 0; }
	int CompilationStatus = ActiveShaderLoadStatus();
	if (!CompilationStatus) { return 0; }
	int AttachStatus = AttachActiveShaders();
	if (!AttachStatus) { return 0; }
	int LinkStatus = LinkMainProgram();
	int ProgramUseage = UseProgram();
	int Detachment = DetachActiveShaders();
	return 1;
}
int NMLRProgram::ExchangeValidProgram()
{
	return 1;
}
int NMLRProgram::GetIndexByEnum(GLenum Shadertype)
{
	int i = (1 * (Shadertype == 0x8B31) + 2 * (Shadertype == 0x8E88) + 3 * (Shadertype == 0x8E87) + 4 * (Shadertype == 0x8DD9) + 5 * (Shadertype == 0x8B30));

	return i - (1 * (i != 0));
}
bool NMLRProgram::CheckCompilationStatus(GLenum ShaderType) { return false; }
bool NMLRProgram::CheckCompilationStatus(int index) { return false; }
NMLRProgram::~NMLRProgram(){}

