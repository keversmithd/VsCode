#pragma once
#include "NILProgram.h"
#include "NGL.h"

#define WS "X:\\1.4 C++\\Visual Studio Projects\\OpenGL\\OpenGL32\\OpenGL\\"
struct NILProgram : NGLProgram
{
    bool ProgramCreated = false;
    bool valid = false;
    int EssentialLink = 0;
    int TesselationLink = 0;
    bool hasLinked = false;
    bool LogEnabled = false;
    char* m_shader_sources[5];
    GLenum m_shadertypes[5]{ GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
    NGLShader m_shaders[5]{};
    bool m_activeShaders[5]{ false, false, false, false, false };
    bool varying;
    const GLchar** varyings;
    int varyingsCount;
    GLenum bufferMode;

    bool TesselationEnabled = false;
    bool GeometryEnabled = false;

    NILProgram()
    {
        const char* m_shader_def_name[5] = { WS "vertex.glsl", WS "tesscontrol.glsl", WS "tesseval.glsl", WS "geometry.glsl", WS "fragment.glsl" };
        valid = CreateProgram(); if (valid)
        {
            for (int i = 0; i < 5; i++)
            {
                m_shader_sources[i] = (char*)malloc(strlen(WS "tesscontrol.glsl")); strcpy(m_shader_sources[i], m_shader_def_name[i]);
            }
        }
        CreateDefaultShaders();
        int l = LinkShader(m_shader_sources[0], GL_VERTEX_SHADER);
        l = LinkShader(m_shader_sources[4], GL_FRAGMENT_SHADER);
        varying = false;
    }
    int SetTransformFeedbackMode(const GLchar** _varyings, int _varyingsCount, GLenum _bufferMode)
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
    int DisableTransformFeedback()
    {
        varying = false;
        return 1;
    }
    int CreateDefaultShaders()
    {
        int Index;
        for (int i = 0; i < 5; i++)
        {
            Index = ValidShaderType(i) - 1;
            m_shaders[i].CreateShader(m_shadertypes[i]);
        }


        return 1;
    }
    int LinkShader(const char* source, GLenum type) {
        if (valid == false) { return 0; }
        int ShaderTypeIndex = ValidShaderType(type);
        if (ShaderTypeIndex == 0) { return 0; }
        if (source == nullptr) { return 0; }
        char* m_shaderSource = NGLParseShader(source);
        if (m_shaderSource == nullptr) { return 0; }

        NGLShader m_shader;
        if (m_shader.CreateShader(type) == 0) { return 0; }
        if (m_shader.ShaderSource(1, (const char**)&m_shaderSource, NULL) == 0) { free(m_shaderSource); m_shader.DeleteShader(); return 0; }
        if (m_shader.CompileShader() == 0) { if (LogEnabled) { ExplainLog(); } free(m_shaderSource); m_shader.DeleteShader(); return 0; }
        int st = 0;
        int CompilationStatus = m_shader.GetShaderiv(GL_COMPILE_STATUS, &st); if (!CompilationStatus || !st) { m_shader.DeleteShader(); return 0; }
        if (m_shaders[ShaderTypeIndex - 1].ShaderSource(1, (const char**)&m_shaderSource, NULL) == 0) { free(m_shaderSource); return 0; }
        if (m_shaders[ShaderTypeIndex - 1].CompileShader() == 0) { if (LogEnabled) { ExplainLog(); } free(m_shaderSource); return 0; }
        free(m_shaderSource);
        int LocalSTIndex = ShaderTypeIndex - 1;
        if (strlen(source) > strlen(m_shader_sources[LocalSTIndex]))
        {
            void* BufferBlock = realloc(m_shader_sources[LocalSTIndex], strlen(source) + 1);
            if (BufferBlock == nullptr) { m_shader.DeleteShader(); return 0; }
            m_shader_sources[LocalSTIndex] = (char*)BufferBlock;
        }
        if (strcmp(m_shader_sources[LocalSTIndex], source)) { strcpy(m_shader_sources[LocalSTIndex], source); }

        m_activeShaders[LocalSTIndex] = true;

        if (EssentialLink != 2)
        {
            EssentialLink = ((m_shadertypes[LocalSTIndex] == GL_VERTEX_SHADER) || (m_shadertypes[LocalSTIndex] == GL_FRAGMENT_SHADER)) + (EssentialLink == 1);
        }
        if (TesselationLink != 2)
        {
            TesselationLink = ((m_shadertypes[LocalSTIndex] == GL_TESS_CONTROL_SHADER) || (m_shadertypes[LocalSTIndex] == GL_TESS_EVALUATION_SHADER)) + (TesselationLink == 1);
            TesselationEnabled = (TesselationLink > 0);
        }
        return 1;
    }
    int Link()
    {
        if (valid == false) { return 0; }
        if (EssentialLink != 2) { return 0; }
        if (!IsProgram()) { return 0; }
        for (int i = 0; i < 5; i++)
        {
            if (m_activeShaders[i] == true)
            {
                if ((m_shadertypes[i] == GL_TESS_CONTROL_SHADER || m_shadertypes[i] == GL_TESS_EVALUATION_SHADER) && (TesselationLink != 2 || TesselationEnabled == false))
                {

                }
                else
                {
                    int AttachmentStatus = AttachShader(m_shaders[i].ReturnShader());
                }

            }
        }
        if (varying)
        {
            int feedBackError = TransformFeedbackVaryings(varyingsCount, varyings, bufferMode);
            if (!feedBackError) { return 0; }
        }
        int LinkStatus = LinkProgram();
        if (hasLinked == false) { hasLinked = LinkStatus; }
        return LinkStatus;

    }
    int Recompile()
    {
        if (valid == false) { return 0; }

        for (int i = 0; i < 5; i++)
        {
            if (m_activeShaders[i])
            {
                RecompileShader(i);
            }
        }
    }
    int RecompileShader(int pos)
    {
        char* m_shaderSource = NGLParseShader(m_shader_sources[pos]);
        /*NGLShader ShaderBuffer; ShaderBuffer.CreateShader(m_shadertypes[pos]);


        int ShaderStatus = ShaderBuffer.ShaderSource(1, &m_shaderSource, NULL);
        if (!ShaderStatus) { return 0; }
        int CompileStatus = ShaderBuffer.CompileShader();
        if (!CompileStatus) { return 0; }

        ShaderBuffer.DeleteShader();
        free(m_shaderSource);

        m_shaders[pos].ShaderSource(1, &m_shaderSource, NULL);
        m_shaders[pos].CompileShader();*/

        if (m_shaderSource == nullptr)
        {
            return 0;
        }
        NGLShader m_shader;
        if (m_shader.CreateShader(m_shadertypes[pos]) == 0) { return 0; }
        int st = 0;
        int error = m_shader.ShaderSource(1, (const char**)&m_shaderSource, NULL);
        error = m_shader.CompileShader();
        int CompilationStatus = m_shader.GetShaderiv(GL_COMPILE_STATUS, &st); if (!CompilationStatus || !st) { return 0; }
        if (!st) { m_shader.DeleteShader(); return 0; }

        if (m_shaders[pos].ShaderSource(1, (const char**)&m_shaderSource, NULL) == 0) { free(m_shaderSource); return 0; }
        if (m_shaders[pos].CompileShader() == 0) { if (LogEnabled) { ExplainLog(); } free(m_shaderSource); return 0; }

        return error;
    }
    int RecompileProgram()
    {
        Recompile();
        return Link();
    }
    int ExplainLog()
    {
        return 0;
    }
    int ValidShaderType(GLenum Shadertype)
    {
        int i = (1 * (1 * (Shadertype == 0x8B31)) + (2 * (Shadertype == 0x8E88)) + (3 * (Shadertype == 0x8E87)) + (4 * (Shadertype == 0x8DD9)) + (5 * (Shadertype == 0x8B30)));
        return i;
    }
    void EnableTesselation() { TesselationEnabled = true; }
    void DisableTesselation() { TesselationEnabled = false; }
};