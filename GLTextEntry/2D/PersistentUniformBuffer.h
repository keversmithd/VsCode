#ifndef PERSISTENT_UNIFORM_BUFFER
#define PERSISTENT_UNIFORM_BUFFER

#include "LearnOpenglHelper.h"

struct MappedUniformBuffer
{
    unsigned int UniformBuffer;
    int reservedSize;

    float* mappedData;

    MappedUniformBuffer() :  reservedSize(0)
    {
        glGenBuffers(1, &UniformBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER, UniformBuffer);
        glBufferStorage(GL_UNIFORM_BUFFER, (512)*sizeof(float), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
        mappedData = (float*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, (512)*sizeof(float), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void ResizeMappedBuffer()
    {
        // Unmap the buffer first
        glUnmapNamedBuffer(UniformBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER, UniformBuffer);

        // Generate a new buffer
        GLuint newUniformBuffer;
        glGenBuffers(1, &newUniformBuffer);
        glBindBuffer(GL_UNIFORM_BUFFER, newUniformBuffer);
        glBufferStorage(GL_UNIFORM_BUFFER, (reservedSize)*2*sizeof(float), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
        float* newMappedData = (float*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, (reservedSize)*2*sizeof(float), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
        
        memcpy(newMappedData, mappedData, reservedSize);
        reservedSize = (reservedSize)*2;
        // Copy data from the old buffer to the new buffer
       
        // Unmap the new buffer
        glUnmapBuffer(GL_UNIFORM_BUFFER);

        // Delete the old buffer
        glDeleteBuffers(1, &UniformBuffer);

        // Update the UniformBuffer variable to point to the new buffer
        UniformBuffer = newUniformBuffer;
        mappedData = newMappedData;
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void BindBase(int Base)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, Base, UniformBuffer);
    }

    float& operator[](int index)
    {
        if(mappedData == nullptr)
        {
            return (float&)reservedSize;
        }
        if(index < 0)
        {
            return mappedData[0];
        }
        if(index > reservedSize)
        {
            ResizeMappedBuffer();
        }

        return mappedData[index];

    }

    ~MappedUniformBuffer()
    {

    }
};


#endif