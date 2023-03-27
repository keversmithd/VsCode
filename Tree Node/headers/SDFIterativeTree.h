#ifndef ITER_TREE_H
#define ITER_TREE_H

#include <vector>
#include "SDFArchive.h";
#include <memory>
#include <assert.h>

struct SDFChildMemoryPoolAcessor;
struct SDFChildrenMemoryPool;

struct SDFIterativeTree
{
    public:
        SDFChildrenMemoryPool* ThisMemoryPool;
        SDFChildMemoryPoolAcessor Children;
        std::vector<SDFFace> ContainedFaces;
        SDFBoundingVolume BoundingVolume;
        bool LeafNode;
        
    public:
    //Problem #1: When generating a tree which only uses one child, eight must be allocated.
    
    SDFChildMemoryPoolAcessor ChildrenAccessor;
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool* MemoryPool) : ThisMemoryPool(MemoryPool), Children(MemoryPool), BoundingVolume(BoundingVolume), LeafNode(false)
    {
        assert(MemoryPool != nullptr);
    }
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool* MemoryPool, const bool leafNode) : ThisMemoryPool(MemoryPool), Children(MemoryPool), LeafNode(leafNode), BoundingVolume(Volume)
    {
       assert(MemoryPool != nullptr);
    }
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool* MemoryPool, const SDFFace face) : ThisMemoryPool(MemoryPool), Children(MemoryPool), LeafNode(true), BoundingVolume(Volume)
    {
        ContainedFaces.push_back(face);
    }

    bool RedistributeInsert(const SDFFace face, SDFIterativeTree* IterationZ0)
    {
        //for faces in iterationZ0
        //check which children the bounding box intersects 
    }

    bool InsertFaceIntoTree(const SDFFace face)
    {
        SDFIterativeTree* IterationZ0 = this;


        bool InsertedCorrectly = false;
        while(!InsertedCorrectly)
        {
            const SDFBoundingVolume volumeOfFace = GetVolumeOfFace(face);
            const SDFVec3 centerOfFace = CenterOfFace(face);
            bool BaseIntersection = IntersectsThisBoundingVolumeBooleanT(IterationZ0->BoundingVolume, volumeOfFace);
            if(!BaseIntersection){return false;}
            int octaneOfChild = OctaneOfPoint(IterationZ0->BoundingVolume, centerOfFace);

            if(IterationZ0->Children[octaneOfChild]->LeafNode)
            {
                InsertedCorrectly = true;
            }
            if(!IterationZ0->Children[octaneOfChild]->LeafNode)
            {
                IterationZ0 = Children[octaneOfChild];       
            }

            //

        }
        


    }

    ~SDFIterativeTree(){}

};



struct SDFChildMemoryPoolAcessor
{
    SDFChildrenMemoryPool* MemoryPool;
    SDFIterativeTree* IterativeTreeEntry;
    SDFChildMemoryPoolAcessor() : IterativeTreeEntry(nullptr), MemoryPool(nullptr) {}
    SDFChildMemoryPoolAcessor(SDFChildrenMemoryPool* memoryPool) : IterativeTreeEntry(nullptr), MemoryPool(memoryPool)
    {
        assert(MemoryPool != nullptr);
    }
    SDFIterativeTree* operator[] (int index)
    {
        if(index < 0 || index > 7)
        {
            throw("Index Out Of Bounds");
            return nullptr;
        }
        EnsureChildren();
        return IterativeTreeEntry+index;
    }
    void EnsureChildren()
    {
        assert(MemoryPool != nullptr);
        
        if(IterativeTreeEntry == nullptr)
        {
            IterativeTreeEntry = MemoryPool->RetrieveNewChildren();
        }
        
    }
};

struct SDFChildrenMemoryPool
{
    std::vector<SDFIterativeTree> IterativeTree;
    int currentIndex = 0;
    SDFIterativeTree* RetrieveNewChildren()
    {

        //add aditional assumptive size realocation for preformance, leave simple for now.
        IterativeTree.resize(IterativeTree.size()+8);
        SDFIterativeTree* dataPtr = IterativeTree.data() + currentIndex;
        currentIndex += 8;
        return dataPtr;
    }

};


#endif