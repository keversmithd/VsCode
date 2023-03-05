#ifndef RPROGRAM
#define RPOGRAM
#include "GL/glew.h"
#include <stdio.h>
#include <malloc.h>
#include <initializer_list>


char* RParse(const char* file);


template<int X>
struct RProgram
{
    unsigned int finalProgram;
    unsigned int testProgram;
    const char* sources_m[X];
    GLenum shadertypes_m[X];
    unsigned int shaderbuffer[X];
    int fileSizes[2];
    RProgram(std::initializer_list<const char*> sources, std::initializer_list<GLenum> shadertypes) {

        for (int i = 0; i < X; i++)
        {
            sources_m[i] = *(sources.begin() + i);
            shadertypes_m[i] = *(shadertypes.begin() + i);
            fileSizes[i] = GetFileSize(sources_m[i]);
        }
        CompileDefaultProgram();
    }
int TestCompile()
{
    int InitialCompileTest = 0;
    for(int i = 0; i < X; i++)
    {
        shaderbuffer[i] = glCreateShader(shadertypes_m[i]);
        const char* source_mem = RParse(sources_m[i]);
        if(source_mem != nullptr)
        {
        glShaderSource(shaderbuffer[i], 1, &source_mem, NULL);
        glCompileShader(shaderbuffer[i]);
        free((char*)source_mem);
        int CompileSuccess = 0;
        glGetShaderiv(shaderbuffer[i],GL_COMPILE_STATUS, &CompileSuccess);
        if(CompileSuccess != GL_TRUE)
        {
            int tempSize = 0;
            glGetShaderiv(shaderbuffer[i], GL_INFO_LOG_LENGTH, &tempSize);
            //printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));
            char* tempLog = (char*)malloc(tempSize);
            glGetShaderInfoLog(shaderbuffer[i], tempSize, &tempSize, tempLog);
            printf("%s\n%", tempLog);
            InitialCompileTest = -1;
            glDeleteShader(shaderbuffer[i]);
            free(tempLog);
        }
        }
        else
    {
        InitialCompileTest = -1;
    }
        
        
    }
    
    return InitialCompileTest;
}


void CompileAndLinkProgram()
{
    
    glDeleteProgram(finalProgram);
    finalProgram = glCreateProgram();

    for(int i = 0; i < X; i++)
        {
            shaderbuffer[i] = glCreateShader(shadertypes_m[i]);
            const char* source_mem = RParse(sources_m[i]);
            glShaderSource(shaderbuffer[i], 1, &source_mem, NULL);
            glCompileShader(shaderbuffer[i]);
            free((char*)source_mem);
            int CompSucc = 0;
            glGetShaderiv(shaderbuffer[i], GL_COMPILE_STATUS, &CompSucc);
            if(CompSucc != GL_TRUE)
            {
                printf("Fatal error in compile status checking. \n");
            }
            glAttachShader(finalProgram, shaderbuffer[i]);
        }
        glLinkProgram(finalProgram);
        glUseProgram(finalProgram);
        glUseProgram(0);
        for(int i = 0; i < 2; i++)
        {
            glDetachShader(finalProgram, shaderbuffer[i]);
            glDeleteShader(shaderbuffer[i]);
        }
}

void CompileDefaultProgram()
{
    const char* DefaultSources[] = {"C:\\Projects\\C++\\Hello\\FontParser\\DefaultShader.vs", "C:\\Projects\\C++\\Hello\\FontParser\\DefaultShader.fs"};
    GLenum DefaultTypes[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    int ProgrammedSourceResult = TestCompile();

    if(ProgrammedSourceResult == -1)
    {
        finalProgram = glCreateProgram();
        for(int i = 0; i < 2; i++)
        {
            shaderbuffer[i] = glCreateShader(DefaultTypes[i]);
            const char* source_mem = RParse(DefaultSources[i]);
            glShaderSource(shaderbuffer[i], 1, &source_mem, NULL);
            glCompileShader(shaderbuffer[i]);
            free((char*)source_mem);
            int CompSucc = 0;
            glGetShaderiv(shaderbuffer[i], GL_COMPILE_STATUS, &CompSucc);
            if(CompSucc != GL_TRUE)
            {
                printf("%s\n", "Fatal error in recompiling program. Fatal period, restore values compiled correctly in alternative compiler.");
                for(int j = 0; j < i; j++)
                {
                    glDeleteShader(shaderbuffer[i]);
                }
                return;
            }
            glAttachShader(finalProgram, shaderbuffer[i]);
        }
        glLinkProgram(finalProgram);
        glUseProgram(finalProgram);
        glUseProgram(0);
        for(int i = 0; i < 2; i++)
        {
            glDetachShader(finalProgram, shaderbuffer[i]);
            glDeleteShader(shaderbuffer[i]);
        }
        return;
    }
    
    CompileAndLinkProgram();



}


int GetFileSize(const char* source)
{
    FILE*  f = NULL;
    fopen_s(&f, source, "rb");
    if(f == NULL)
    {
        return -1;
    }
    fpos_t end;
    fseek(f, 0, SEEK_END);
    fgetpos(f, &end);
    fclose(f);
    return (int)end;
}

bool FileSizesChanged()
{
    for(int i = 0; i < X; i++)
    {
        if(GetFileSize(sources_m[i]) != fileSizes[i])
        {
            return true;
        }
    }
    return false;
}

void FileSizeUpdate()
{
   if(FileSizesChanged() == true)
   {
        if(TestCompile() == true)
        {
            CompileAndLinkProgram();
        }
   }
}

    //use case "include RProgram"
    //RProgram.Update();
    
};

#endif