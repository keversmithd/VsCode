#ifndef INSTANCE_UNIFORM
#define INSTANCE_UNIFORM

#include "OpenGLObjectTools.h"

struct UniformInstanceDetails{
    int index;
};

struct InstanceUniformBuffer
{
public:
    unsigned int m_uniformBuffer;
    int          m_allocatedSize;
    void*        m_uniformData;
    int          m_type;
    int          m_bufferBase;
public:
    InstanceUniformBuffer() : m_uniformBuffer(0), m_allocatedSize(0), m_uniformData(nullptr), m_type(0), m_bufferBase(1)
    {

    }

    void AllocateUniformBuffer(int nbytes)
    {
        m_uniformBuffer = CreateUniformBuffer(nbytes, nullptr, 1);
        m_allocatedSize = nbytes;
    }

    void ResizeUniformBuffer(int nbytes)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_uniformBuffer);
        glInvalidateBufferData(m_uniformBuffer);
        glBufferData(GL_UNIFORM_BUFFER, m_allocatedSize+nbytes, m_uniformData, GL_DYNAMIC_DRAW);
    }

    void SetTransformsData(void* data)
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, m_bufferBase, m_uniformBuffer);
        glBufferData(GL_UNIFORM_BUFFER, m_allocatedSize, data, GL_DYNAMIC_DRAW);
    }

    ~InstanceUniformBuffer()
    {

    }

};

vapeb ReopenMesh(const char* MeshSource)
{
    unsigned int vao;
    unsigned int vb;
    unsigned int ebo;

    

    float *bufferData;
    unsigned int *indexData;
    int directoryFetchError = 0;

    FILE *mesh_eb = getFileWithDirectory(MeshSource, 1, "rb", &directoryFetchError);
    fseek(mesh_eb, 0, SEEK_SET);

    if (directoryFetchError != 0)
    {
        printf("Bad directory in reopening mesh.");
        return {0, 0, 0, 0};
    }

    // Read the sizes
    int readMemorySize = 0;
    int readElementSize = 0;

    const int vertexSize = 8;
    int vertexes = 0; // count vertexes;

    fread(&readMemorySize, sizeof(int), 1, mesh_eb);
    if (readMemorySize == 0 || readMemorySize < 0)
    {
        return {0, 0, 0, 0};
    }
    vertexes = readMemorySize/vertexSize;

    bufferData = (float *)malloc(4 * readMemorySize);
    fread(bufferData, sizeof(float), readMemorySize, mesh_eb);
    fread(&readElementSize, sizeof(int), 1, mesh_eb);
    indexData = (unsigned int *)malloc(4 * readElementSize);
    if (readElementSize == 0 || readElementSize < 0)
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vb);

        unsigned int program = CreateShader("Objects/InstancedGeometry/instance.vs", "Objects/InstancedGeometry/instance.fs");

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferData(GL_ARRAY_BUFFER, (readMemorySize + 1) * sizeof(float), bufferData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        free(bufferData);
        free(indexData);

        return {program, vao, ebo, 1, readElementSize, vertexes};
    }else
    {
        fread(indexData, sizeof(unsigned int), readElementSize, mesh_eb);

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vb);
        glGenBuffers(1, &ebo);

        unsigned int program = CreateShader("Objects/InstancedGeometry/instance.vs", "Objects/InstancedGeometry/instance.fs");

        glBindVertexArray(vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (readElementSize) * sizeof(unsigned int), indexData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glBufferData(GL_ARRAY_BUFFER, (readMemorySize + 1) * sizeof(float), bufferData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid *)(sizeof(float) * 5));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        free(bufferData);
        free(indexData);

        return {program, vao, ebo, 0, readElementSize, vertexes};
    }
    
}

#endif