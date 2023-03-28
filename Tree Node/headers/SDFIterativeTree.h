#ifndef ITER_TREE_H
#define ITER_TREE_H

#include <vector>
#include "SDFArchive.h";
#include <memory>
#include <assert.h>
#include <array>

struct SDFChildMemoryPoolAcessor;
struct SDFChildrenMemoryPool;

struct SDFIterativeTree
{
    public:
        static std::array<int, 8> IntersectionBuffer;
        static int IntersectionCount;

    public:
        SDFChildrenMemoryPool* ThisMemoryPool;
        SDFChildMemoryPoolAcessor Children;
        std::vector<SDFFace> ContainedFaces;
        SDFBoundingVolume BoundingVolume;
        bool LeafNode;
        
    public:
    //Problem #1: When generating a tree which only uses one child, eight must be allocated. Solution #1. There is no solution to this and must be included in this model. -Unsolved
    //Problem #2: When checking every child if intersection exists, the bounding volume may not be present, and there needs to be a specified period these children are generated. -Solved
    //Problem #3: A possible optimization is to use one singular interseciton data buffer, rather than allocating new ones.
    
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

    void EveryotherIntersection(const SDFBoundingVolume facialBoundingVolume, int canceledIndex = -1)
    {
        IntersectionCount = 0;

        for(int i = 0; i < 8; i++)
        {
            if( i != canceledIndex)
            {
                
            }
        }
    }

    bool RedistributedInsertion(const SDFFace face)
    {
        //During this call the intersection list of the main insertion algorithm is overwritten.
        //#Solution #1. Create a static backup for the pevious intersection list, and reinstantiate after re-inserting.
        //#Solution #2. Creating another set of static intersection list information for this function in specific.
        static std::array<int, 8> PreviousIntersectionBuffer = IntersectionBuffer;
        static int PreviousIntersectionCount = IntersectionCount;

        LeafNode = false;

        SDFBoundingVolume volumeOfFace;
        //gather and insert every other insertion.
        for(int i = 0; i < ContainedFaces.size(); i++)
        {
            volumeOfFace = GetVolumeOfFace(ContainedFaces[i]);
            
            EveryotherIntersection(volumeOfFace);

            for(int j = 0; j < IntersectionCount; j++)
            {
                bool InsertionCompleted = false;
                while(!InsertionCompleted)
                {
                    //if intersection is not leaf node, make leaf node.
                    //if intersection is leaf node and faces contains more than face per leaf then children[]->redistributed insertion.
                    //if intersection is a navigation node, then set iteration aspect to node, and re run exact logic ad infintum. [expansion]
                }
            }
        }

        IntersectionBuffer = PreviousIntersectionBuffer;
        IntersectionCount = PreviousIntersectionCount;

    }

    void GenerateChildrenBoundingVolumes()
    {
        


        const SDFVec3 centerOfParentVolume = CenterOfVolume(BoundingVolume);

        *Children[0] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z},centerOfParentVolume}, ThisMemoryPool);
        *Children[1] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z}}, ThisMemoryPool);
        *Children[2] = SDFIterativeTree({{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, centerOfParentVolume.z}}, ThisMemoryPool);
        *Children[3] = SDFIterativeTree({{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z}}, ThisMemoryPool);
        *Children[4] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool);
        *Children[5] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, centerOfParentVolume.z},{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool);
        *Children[6] = SDFIterativeTree({{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool);
        *Children[7] = SDFIterativeTree({centerOfParentVolume,{BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool);

        return;

        //0 Bottom Left Front:
        const SDFBoundingVolume BottomLeftFront = {{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z},centerOfParentVolume};
        //1 TopLeft Front:
        const SDFBoundingVolume TopLeftFront = {{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z}};
        //2 Bottom Right Front:
        const SDFBoundingVolume BottomRightFront = {{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, centerOfParentVolume.z}};
        //3 Top Right Front:
        const SDFBoundingVolume TopRightFront = {{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z}};
        //4 Bottom Left Back:
        const SDFBoundingVolume BottomLeftBack = {{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}};
        //5 Top Left Back:
        const SDFBoundingVolume TopLeftBack = {{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, centerOfParentVolume.z},{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z}};
        //6 Bottom Right Back:
        const SDFBoundingVolume BottomRightBack = {{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}};
        //7 Top Right Back:
        const SDFBoundingVolume TopRightBack = {centerOfParentVolume,{BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z}};
        
    }

    bool InsertFaceIntoTree(const SDFFace face)
    {
        const SDFBoundingVolume volumeOfFace = GetVolumeOfFace(face);
        const SDFVec3 centerOfFace = CenterOfFace(face);
        SDFIterativeTree* IterationZ0 = this;
        bool BaseIntersection = IntersectsThisBoundingVolumeBooleanT(IterationZ0->BoundingVolume, volumeOfFace);
        if(!BaseIntersection){return false;}

        //At this point it is verified that we will need to be searching the bounding boxes of the children and need to calculate their bounding boxes.

        GenerateChildrenBoundingVolumes();

        //So the children bounding volumes are generated.

        //Calculates list of intersections to be handled in regards to this current bounding container.

        IterationZ0->EveryotherIntersection(volumeOfFace);

        //Iterate through list of intersections and run the iterative code.

        for(int i = 0; i < IntersectionCount; i++)
        {
            bool InsertionCompleted = false;

            while(!InsertionCompleted)
            {
                //if intersection is not leaf node, make leaf node.
                //if intersection is leaf node and faces contains more than face per leaf then children[]->redistributed insertion.
                //if intersection is a navigation node, then set iteration aspect to node, and re run exact logic ad infintum. [expansion]
            }
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