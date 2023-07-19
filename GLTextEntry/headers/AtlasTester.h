#ifndef ATLAS_TESTER_H
#define ATLAS_TESTER_H
#include "LearnOpenglHelper.h"
#include "fon.h"
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


#endif