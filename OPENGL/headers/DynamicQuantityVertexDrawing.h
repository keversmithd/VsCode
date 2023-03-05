#ifndef DYN_VERT_DRAW
#define DYN_VERT_DRAW
#include "GL/glew.h"

struct DynamicQuantityVertexBuffer
{
	unsigned int dynabuffer;
	size_t Size;
	DynamicQuantityVertexBuffer(size_t size);
	//Init
	void InitialGeneration();
	void InitialBinding();
	void InitialDataAllocation();
	void Unbind();
	//Update
	void InvalidateDynabuffer();
	void DeleteBuffer();
	void RegenerateBuffer();
	void AllocateData(const void* data);
	void AllocateSubData(const void* data, size_t size);
	//Abstract
	void UpdateData(void* data, size_t size);
};
struct StaticQuantityVertexArray
{
	unsigned int vertexarray;
	StaticQuantityVertexArray();
	//Init
	int InitialGeneration();
	int InitialBinding();
	int InitialDataAllocation();

};
struct DynamicQuantityIndexBuffer
{
	unsigned int dynamicindexbuffer;
};
struct DynamicQuantityVertexDrawing
{
	DynamicQuantityVertexBuffer VertexBuffer;

	DynamicQuantityVertexDrawing();

	int Update(int H);
	int RenderVertices();
};




#endif