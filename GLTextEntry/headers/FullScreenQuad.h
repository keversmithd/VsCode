#ifndef FULL_SCREEN_QUAD
#define FULL_SCREEN_QUAD
#include "LearnOpenglHelper.h"

struct FullQuadController
{
    unsigned int vertexBuffer, uvBuffer, FullScreenQuadVertexArray;
    unsigned int texture;
    NGLProgram program;

    FullQuadController() : vertexBuffer(-1), uvBuffer(-1), FullScreenQuadVertexArray(-1), texture(-1), program(CreateShader("shaders/FullScreenQuad.vs", "shaders/FullScreenQuad.fs"))
    {
        FullScreenQuad();
    }

    void Draw()
    {
        program.UseProgram();
        if(texture != -1)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            setInt(program, "atlas", 0);
        }
        glBindVertexArray(FullScreenQuadVertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
    }

    void FullScreenQuad()
    {

        float vertex[] =
        {
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,

            -1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,
            -1.0, 1.0, 0.0,

        };

        float uv[] = 
        {
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 0.0,
            1.0, 1.0,
            0.0, 1.0
        };

        glGenVertexArrays(1, &FullScreenQuadVertexArray);
        glBindVertexArray(FullScreenQuadVertexArray);

        unsigned int vertexBuffer, uvBuffer;
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &uvBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }

};

struct QuickRender
{
    unsigned int vertexBuffer, uvBuffer, FullScreenQuadVertexArray;
    unsigned int texture;
    NGLProgram program;

    QuickRender() : vertexBuffer(-1), uvBuffer(-1), FullScreenQuadVertexArray(-1), texture(-1), program(CreateShader("shaders/FullScreenQuad.vs", "shaders/FullScreenQuad.fs"))
    {
    }

    void Draw()
    {
        program.UseProgram();
        if(texture != -1)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            setInt(program, "atlas", 0);
        }
        glBindVertexArray(FullScreenQuadVertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
    }

    void SetUpBuffers(float* vertex, float* uv, int sizev, int sizeuv)
    {

        glGenVertexArrays(1, &FullScreenQuadVertexArray);
        glBindVertexArray(FullScreenQuadVertexArray);

        unsigned int vertexBuffer, uvBuffer;
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &uvBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizev, vertex, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeuv, uv, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    }
};



#endif