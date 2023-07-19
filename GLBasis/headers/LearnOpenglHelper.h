#ifndef EXPERIMENT_1_H
#define EXPERIMENT_1_H

#include "NGL.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDFArchive.h>
#include <filesystem>



struct vec4
{
    float x,y,z,w;
};

struct vec2
{
    float x, y;
};
struct vec3
{
    float x,y,z;
};

NGLProgram CreateShader(std::string vs, std::string fs)
{
    std::filesystem::path systemPath = std::filesystem::current_path();
    vs = systemPath.string() + '\\' + vs;
    fs = systemPath.string() + '\\' + fs;
    int error = 0;
    NGLProgram nglProgram;
    error = nglProgram.CreateProgram();
    NGLShader nglVertexShader; error = nglVertexShader.CreateShader(GL_VERTEX_SHADER);
    NGLShader nglFragmentShader; error = nglFragmentShader.CreateShader(GL_FRAGMENT_SHADER);
    char* vertexSource = NGLParseShader(vs.c_str());
    char* fragmentSource = NGLParseShader(fs.c_str());
    error = nglVertexShader.ShaderSource(1, (const char**)&vertexSource, NULL);
    error = nglFragmentShader.ShaderSource(1, (const char**)&fragmentSource, NULL);
    error = nglVertexShader.CompileShader();
    error = nglFragmentShader.CompileShader();
    GLsizei LogLength = 0;
    error = nglVertexShader.GetInfoLog(NULL, &LogLength, NULL);
    GLint isCompiled = 0;
    error = nglVertexShader.GetShaderiv(GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        char* VertexLog = (char*)malloc(LogLength);
        error = nglVertexShader.GetInfoLog(LogLength, NULL, VertexLog);
        printf("%s\n", VertexLog);
        free(VertexLog);
    }
    error = nglFragmentShader.GetShaderiv(GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        error = nglFragmentShader.GetInfoLog(NULL, &LogLength, NULL);
        char* FragmentLog = (char*)malloc(LogLength);
        error = nglFragmentShader.GetInfoLog(LogLength, NULL, FragmentLog);
        printf("%s\n", FragmentLog);
        free(FragmentLog);
    }
    error = nglProgram.AttachShader(nglVertexShader.ReturnShader());
    error = nglProgram.AttachShader(nglFragmentShader.ReturnShader());
    error = nglProgram.LinkProgram();
    //error = nglProgram.UseProgram();

    //nglProgram.DetachShader(nglVertexShader.ReturnShader());
    //nglProgram.DetachShader(nglFragmentShader.ReturnShader());
    nglVertexShader.DeleteShader();
    nglFragmentShader.DeleteShader();
    GLint  linkStatus = 0;
    error = nglProgram.GetProgramiv(GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE){ throw("fuck"); }

    return nglProgram;
}

NGLBuffer CreateUniformBuffer(int size, void* data, int index)
{
    NGLBuffer waveInformation;
    waveInformation.GenerateBuffer();
    waveInformation.BindBuffer(GL_UNIFORM_BUFFER);
    waveInformation.BufferData(size, data, GL_STATIC_DRAW);
    waveInformation.Unbind(GL_UNIFORM_BUFFER);
    waveInformation.BindBufferBase(GL_UNIFORM_BUFFER, 0);
    return waveInformation;
}

void setMat4(NGLProgram& program, const char* name, glm::mat4 mat)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void setVec2(NGLProgram& program, const char* name, glm::vec2 vec)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform2f(modelLoc, vec.x, vec.y);
}

void setVec3(NGLProgram& program, const char* name, float* a)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform3f(modelLoc, a[0], a[1], a[2]);

}

void setVec3(NGLProgram& program, const char* name, glm::vec3 X)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform3f(modelLoc, X.x, X.y, X.z);

}

void set2Vec3Array(NGLProgram& program, const char* name, float* array)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform3fv(modelLoc, 2, array);
}

void setVec4(NGLProgram& program, const char* name, glm::vec4 vec)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform4f(modelLoc, vec.x, vec.y, vec.z, vec.w);
}

void setFloat(NGLProgram& program, const char* name, float value)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform1f(modelLoc, value);
}



void setInt(NGLProgram& program, const char* name, GLint value)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform1i(modelLoc, value);
}

void setUniformBlock(NGLProgram& program, const char* name, int binding)
{
    GLuint index;
    program.GetUniformBlockIndex(name, &index);
    program.UniformBlockBinding(index, binding);
}
#endif

