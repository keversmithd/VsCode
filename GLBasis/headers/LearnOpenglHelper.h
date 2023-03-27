#ifndef EXPERIMENT_1_H
#define EXPERIMENT_1_H

#include "NGL.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



NGLProgram CreateShader(const char* vs, const char* fs)
{
    int error = 0;
    NGLProgram nglProgram;
    error = nglProgram.CreateProgram();
    NGLShader nglVertexShader; error = nglVertexShader.CreateShader(GL_VERTEX_SHADER);
    NGLShader nglFragmentShader; error = nglFragmentShader.CreateShader(GL_FRAGMENT_SHADER);
    char* vertexSource = NGLParseShader(vs);
    char* fragmentSource = NGLParseShader(fs);
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

void setMat4(NGLProgram& program, const char* name, glm::mat4 mat)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void setVec3(NGLProgram& program, const char* name, glm::vec3 vec)
{
    int modelLoc;
    program.GetUniformLocation(name, &modelLoc);
    program.ProgramUniform3f(modelLoc, vec.x, vec.y, vec.z);
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

#endif

