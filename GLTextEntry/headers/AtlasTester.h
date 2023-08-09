#ifndef ATLAS_TESTER_H
#define ATLAS_TESTER_H
#include "LearnOpenglHelper.h"
#include "fon.h"
#include "Camera.h"
#include "FGeom.h"
#include <string>

struct AtlasText
{
    NGLProgram program;
    unsigned int vbo;
    unsigned int vuv;
    unsigned int vao;

    std::vector<vec3> Vertexes;
    std::vector<vec2> Uvs;

    int vertexes;

    AtlasText() : vbo(-1), vuv(-1), vao(-1), program(CreateShader("shaders/AtlasTester.vs", "shaders/AtlasTester.fs")), vertexes(0)
    {

    }

    void AddText(float x, float y, float z, float scale, std::string text)
    {
        for(int i = 0; i < text.size(); i++)
        {

            if(AtlasCharacters.find(text[i]) != AtlasCharacters.end())
            {
                AtlasCharacter ch = AtlasCharacters[text[i]];

                float xpos = x + ch.Bearing.x * scale;
                float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
                float w = ch.Size.x * scale;
                float h = ch.Size.y * scale;
                

                Vertexes.push_back({ xpos,     ypos,   z});
                Vertexes.push_back({ xpos+w,     ypos,       z});
                Vertexes.push_back({ xpos + w, ypos+h,   z});

                Vertexes.push_back({ xpos,     ypos,   z});
                Vertexes.push_back({ xpos + w, ypos + h,   z});
                Vertexes.push_back({ xpos, ypos + h,   z});


                Uvs.push_back({ch.BottomLeft.x, ch.BottomLeft.y});
                Uvs.push_back({ch.TopRight.x, ch.BottomLeft.y});
                Uvs.push_back({ch.TopRight.x, ch.TopRight.y});

                Uvs.push_back({ch.BottomLeft.x, ch.BottomLeft.y});
                Uvs.push_back({ch.TopRight.x, ch.TopRight.y});
                Uvs.push_back({ch.BottomLeft.x, ch.TopRight.y});

                vertexes += 6;
                x += (ch.Advance >> 6) * scale;
            }
            
        }



    }

    void SetupBuffers()
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &vuv);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*Vertexes.size(), Vertexes.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, vuv);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*Uvs.size(), Uvs.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Draw()
    {
        program.UseProgram();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, CharacterAtlas);
        setInt(program, "atlas", 0);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertexes);
    }

};

struct AtlasAlignedText
{
    NGLProgram program;
    unsigned int vbo;
    unsigned int vao;
    unsigned int ibo;

    float* vertexBuffer;
    int vertexes;

    unsigned int* indexBuffer;
    int indices;

    AtlasAlignedText() : vbo(-1), vao(-1), program(CreateShader("shaders/AtlasTester.vs", "shaders/AtlasTester.fs")), vertexes(0), indices(0), vertexBuffer(nullptr), indexBuffer(nullptr)
    {

    }

    // void AddText(float x, float y, float z, float scale, std::string text)
    // {
    //     for(int i = 0; i < text.size(); i++)
    //     {
    //         if(AtlasCharacters.find(text[i]) != AtlasCharacters.end())
    //         {
    //             AtlasCharacter ch = AtlasCharacters[text[i]];

    //             float xpos = x + ch.Bearing.x * scale;
    //             float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
    //             float w = ch.Size.x * scale;
    //             float h = ch.Size.y * scale;
                
    //             Vertexes.push_back({ xpos,     ypos,   z});
    //             Vertexes.push_back({ xpos+w,     ypos,       z});
    //             Vertexes.push_back({ xpos + w, ypos+h,   z});

    //             Vertexes.push_back({ xpos,     ypos,   z});
    //             Vertexes.push_back({ xpos + w, ypos + h,   z});
    //             Vertexes.push_back({ xpos, ypos + h,   z});


    //             Uvs.push_back({ch.BottomLeft.x, ch.BottomLeft.y});
    //             Uvs.push_back({ch.TopRight.x, ch.BottomLeft.y});
    //             Uvs.push_back({ch.TopRight.x, ch.TopRight.y});

    //             Uvs.push_back({ch.BottomLeft.x, ch.BottomLeft.y});
    //             Uvs.push_back({ch.TopRight.x, ch.TopRight.y});
    //             Uvs.push_back({ch.BottomLeft.x, ch.TopRight.y});

    //             vertexes += 6;
    //             x += (ch.Advance >> 6) * scale;
    //         }
            
    //     }



    // }

    void AddAlignedText(SDFVec3 Origin, SDFVec3 Normal, SDFVec3 Binormal, std::string text, float height, float width)
    {
        // Normal.normalize();
        // Binormal.normalize();

        SDFVec3 A,B,C,D;
        float verticalPadding = 0.1;
        float horizontalPadding = 0.1;

        vertexBuffer = new float[8*7*text.size()];
        indexBuffer = new unsigned int[9*text.size()];

        for(int i = 0; i < text.size(); i++)
        {
            if(AtlasCharacters.find(text[i]) != AtlasCharacters.end())
            {
                AtlasCharacter ch = AtlasCharacters[text[i]];

                A = Origin - Binormal*(height + verticalPadding);
                B = Origin + Normal*(width);
                C = B + Binormal*(height);
                A = Origin + Binormal*(height);
                
                Origin.x += (ch.Advance >> 6) * (height/width);

                NHolder = Cross(Subtract(B, A), Subtract(D,A));
                fPoint(A, ch.BottomLeft.x, ch.BottomLeft.y, vertexBuffer, vertexes);
                fPoint(B, ch.TopRight.x, ch.BottomLeft.y, vertexBuffer, vertexes);
                fPoint(C, ch.TopRight.x, ch.TopRight.y, vertexBuffer, vertexes);
                fPoint(D, ch.BottomLeft.x, ch.TopRight.y, vertexBuffer, vertexes);
                
                indexBuffer[indices++] = indices;
                indexBuffer[indices++] = indices+1;
                indexBuffer[indices++] = indices+2;

                indexBuffer[indices++] = indices;
                indexBuffer[indices++] = indices+2;
                indexBuffer[indices++] = indices+3;

                indices+=4;
            }
        }

        SetupBuffers();
    }


    void SetupBuffers()
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float)*vertexes+1, vertexBuffer, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*8, (GLvoid*)(sizeof(float) * 5));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices, indexBuffer, GL_STATIC_DRAW);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Draw(Camera& MainCamera)
    {
        program.UseProgram();

        setMat4(program, "projection", MainCamera.projection);
        setMat4(program, "view", MainCamera.view);

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, CharacterAtlas);
        setInt(program, "atlas", 0);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertexes);
    }

    ~AtlasAlignedText()
    {
        if(vertexBuffer != nullptr)
        {
            delete[] vertexBuffer;
        }
        if(indexBuffer != nullptr)
        {
            delete[] indexBuffer;
        }
        
    }

};


#endif