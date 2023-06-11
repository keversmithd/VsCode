#ifndef FON_H
#define FON_H
#include <iostream>
#include <map>
#include <ft2build.h>
#include <GL/glew.h>
#include <vector>
#include FT_FREETYPE_H

struct ivec2
{
    int x,y;
};

struct AtlasVec2
{
    float x,y;
};

struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        ivec2   Size;       // Size of glyph
        ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
};

struct AtlasCharacter
{
    AtlasVec2 BottomLeft;
    AtlasVec2 TopRight;
    ivec2 Size;
    ivec2 Bearing;
    unsigned int Advance;
};

unsigned int CharacterAtlas;
std::map<char, AtlasCharacter> AtlasCharacters;

std::map<char, Character> Characters;



inline bool loadFont(const char* file)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, file, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 24);  


    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;  
        return -1;
    }

    

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            {face->glyph->bitmap.width, face->glyph->bitmap.rows},
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

}


inline bool LoadCharacterAtlas(const char* file)
{
    int FontHeight = 120;
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, file, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, FontHeight);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;  
        return false;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Texture Definitions
    int TextureDimension = 1024;

    //Over all data meant to be extracted to gl texture.
    unsigned char* TextureData = new unsigned char[(TextureDimension*TextureDimension)];
    memset(TextureData,0,(TextureDimension*TextureDimension) );

    
    int CharactersToLoad = 40;

    AtlasVec2 CurrentLocation = {0,0}; //Starting At the Bottom Of the Texture
    AtlasVec2 DeltaLocation = CurrentLocation;

    int CharactersProccessed = 0;

    //Character Metrics
    int CWidth = 0;
    int CHeight = 0;
    unsigned char* CBuffer = nullptr;


    
    int StartChar = 32;
    for (unsigned char c = StartChar; c < (StartChar+CharactersToLoad); c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        CWidth = face->glyph->bitmap.width;
        CHeight = face->glyph->bitmap.rows;
        CBuffer = face->glyph->bitmap.buffer;

        //Calculate The Texture Coordinates Of This Locations that is being Inserted.
        AtlasCharacter CharacterInfo;
        CharacterInfo.BottomLeft.x = CurrentLocation.x / TextureDimension;
        CharacterInfo.BottomLeft.y = CurrentLocation.y / TextureDimension;
        CharacterInfo.TopRight.x = (CurrentLocation.x + CWidth) / TextureDimension;
        CharacterInfo.TopRight.y = (CurrentLocation.y + CHeight) / TextureDimension;

        CharacterInfo.Advance = face->glyph->advance.x;
        CharacterInfo.Bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top};
        CharacterInfo.Size = {CWidth, CHeight};

        AtlasCharacters.insert({c, CharacterInfo});

        //Setting Temporary Location Identifier
        DeltaLocation = CurrentLocation;
        DeltaLocation.y += CHeight;
        for(int C = 0; C < CHeight; C++)
        {
            for(int J = 0; J < CWidth; J++)
            {
                int GlyphIndex = J + (C*CWidth);
                int TextureIndex = (DeltaLocation.x+J+(J==(CWidth-1)))+(DeltaLocation.y*TextureDimension);

                if(TextureIndex >= (TextureDimension*TextureDimension)-1)
                {
                    printf("Overloaded Texture Atlas");
                    abort();
                }else
                {
                    TextureData[TextureIndex] = CBuffer[GlyphIndex];
                }

                
            }
            DeltaLocation.y--;
        }

        float DistanceFromRightEdge = (TextureDimension - (CurrentLocation.x+CWidth));

        if(DistanceFromRightEdge < 48)
        {
            CurrentLocation.x = 0;
            CurrentLocation.y+=FontHeight;
        }else
        {
            CurrentLocation.x += CWidth;
        }

        CharactersProccessed++;
    }

    glGenTextures(1, &CharacterAtlas);
    glBindTexture(GL_TEXTURE_2D, CharacterAtlas);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, TextureDimension,  TextureDimension, 0, GL_RED, GL_UNSIGNED_BYTE, TextureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;

}




#endif