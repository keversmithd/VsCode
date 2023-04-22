#ifndef ITER_TREE_H
#define ITER_TREE_H

#include <vector>
#include "SDFArchive.h"
#include <memory>
#include <assert.h>
#include <array>
#include <stack>



template<typename T>
struct SDFChildrenMemoryPool
{
    std::vector<T> IterativeTree;
    
    int currentIndex = 0;
    T* RetrieveNewChildren()
    {
        //add aditional assumptive size realocation for preformance, leave simple for now.
        IterativeTree.resize(IterativeTree.size()+8);
        T* dataPtr = IterativeTree.data() + currentIndex;
        currentIndex += 8;
        return dataPtr;
    }

};

template<typename T>
struct SDFChildMemoryPoolAcessor
{
    SDFChildrenMemoryPool<T>* MemoryPool;
    T* IterativeTreeEntry;
    SDFChildMemoryPoolAcessor() : IterativeTreeEntry(nullptr), MemoryPool(nullptr) {}
    SDFChildMemoryPoolAcessor(SDFChildrenMemoryPool<T>* memoryPool) : IterativeTreeEntry(nullptr), MemoryPool(memoryPool)
    {
        assert(MemoryPool != nullptr);
    }
    T* operator[] (int index)
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

template<typename T>
struct SDFStackBranchNode
{
    T* direction;
    int childIndex;
};

struct SDFIterativeTree
{
    public:
        int MaximumFaces;
        static std::stack<SDFStackBranchNode<SDFIterativeTree>> intersectionStack;
        bool GeneratedChildBoundingBoxes;
    public:
        SDFChildrenMemoryPool<SDFIterativeTree>* ThisMemoryPool;
        SDFChildMemoryPoolAcessor<SDFIterativeTree> Children;
        std::vector<SDFFace> ContainedFaces;
        SDFBoundingVolume BoundingVolume;
        bool LeafNode;
        
    public:
    //Problem #1: When generating a tree which only uses one child, eight must be allocated. Solution #1. There is no solution to this and must be included in this model. -Unsolved
    //Problem #2: When checking every child if intersection exists, the bounding volume may not be present, and there needs to be a specified period these children are generated. -Solved
    //Problem #3: A possible optimization is to use one singular interseciton data buffer, rather than allocating new ones. Solution #3: Not possible. -Unsolved
    //Problem #4: When using algorithm to redistribute, running traditional search for insertion generates an infinite string of children - Need to find a stopping point - Unsolved.
    //Problem #5: Had to use indirection for my iterative tree stack, but could also maybe some how use a secondary index into the memory pool?

    SDFIterativeTree()
    {

    }

    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool<SDFIterativeTree>* MemoryPool) : ThisMemoryPool(MemoryPool), Children(MemoryPool), BoundingVolume(Volume), LeafNode(false), MaximumFaces(0), GeneratedChildBoundingBoxes(false)
    {
        assert(MemoryPool != nullptr);
    }
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool<SDFIterativeTree>* MemoryPool, const bool leafNode) : ThisMemoryPool(MemoryPool), Children(MemoryPool), LeafNode(leafNode), BoundingVolume(Volume), MaximumFaces(3), GeneratedChildBoundingBoxes(false)
    {
       assert(MemoryPool != nullptr);
    }
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool<SDFIterativeTree>* MemoryPool, const SDFFace face) : ThisMemoryPool(MemoryPool), Children(MemoryPool), LeafNode(true), BoundingVolume(Volume), MaximumFaces(3), GeneratedChildBoundingBoxes(false)
    {
        assert(MemoryPool != nullptr);
        ContainedFaces.push_back(face);
    }
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool<SDFIterativeTree>* MemoryPool, const bool leafNode, int maximumFaces) : ThisMemoryPool(MemoryPool), Children(MemoryPool), LeafNode(leafNode), BoundingVolume(Volume), GeneratedChildBoundingBoxes(false)
    {
       assert(MemoryPool != nullptr);
        MaximumFaces = (maximumFaces > 0) ? maximumFaces : 3;
    }
    SDFIterativeTree(const SDFBoundingVolume Volume, SDFChildrenMemoryPool<SDFIterativeTree>* MemoryPool, const SDFFace face, int maximumFaces) : ThisMemoryPool(MemoryPool), Children(MemoryPool), LeafNode(true), BoundingVolume(Volume), GeneratedChildBoundingBoxes(false)
    {
        assert(MemoryPool != nullptr);
        MaximumFaces = (maximumFaces > 0) ? maximumFaces : 3;
        ContainedFaces.push_back(face);
    }
    

    void EveryotherIntersection(const SDFBoundingVolume facialBoundingVolume, int canceledIndex = -1)
    {

        if(!GeneratedChildBoundingBoxes)
        {
            GenerateChildrenBoundingVolumes();
        }

        for(int i = 0; i < 8; i++)
        {
            if(i != canceledIndex && IntersectsThisBoundingVolumeBooleanT(facialBoundingVolume, Children[i]->BoundingVolume))
            {
                intersectionStack.push({this,  i});
            }
        }
    }

    bool RedistributedInsertion(const SDFFace face)
    {

        SDFBoundingVolume volumeOfFace = GetVolumeOfFace(face);
        EveryotherIntersection(volumeOfFace);

        for(int i = 0; i < ContainedFaces.size(); i++)
        {
            volumeOfFace = GetVolumeOfFace(ContainedFaces[i]);

            for(int i = 0; i < 8; i++)
            {
                if(IntersectsThisBoundingVolumeBooleanT(volumeOfFace, Children[i]->BoundingVolume))
                {
                    Children[i]->ContainedFaces.push_back(face);
                }
            }
        }
        LeafNode = false;
        

    }

    void GenerateChildrenBoundingVolumes()
    {
        
        const SDFVec3 centerOfParentVolume = CenterOfVolume(BoundingVolume);

        *Children[0] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z},centerOfParentVolume}, ThisMemoryPool, true);
        *Children[1] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z}}, ThisMemoryPool, true);
        *Children[2] = SDFIterativeTree({{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, centerOfParentVolume.z}}, ThisMemoryPool, true);
        *Children[3] = SDFIterativeTree({{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.TopLeftFront.z},{BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, centerOfParentVolume.z}}, ThisMemoryPool, true);
        *Children[4] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{centerOfParentVolume.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool, true);
        *Children[5] = SDFIterativeTree({{BoundingVolume.TopLeftFront.x, centerOfParentVolume.y, centerOfParentVolume.z},{centerOfParentVolume.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool, true);
        *Children[6] = SDFIterativeTree({{centerOfParentVolume.x, BoundingVolume.BottomRightBack.y, centerOfParentVolume.z},{BoundingVolume.BottomRightBack.x, centerOfParentVolume.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool, true);
        *Children[7] = SDFIterativeTree({centerOfParentVolume,{BoundingVolume.BottomRightBack.x, BoundingVolume.TopLeftFront.y, BoundingVolume.BottomRightBack.z}}, ThisMemoryPool);

        GeneratedChildBoundingBoxes = true;

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
        const SDFBoundingVolume volumeOfFace = GetVolumeOfFace(face); //Volume of face
        //const SDFVec3 centerOfFace = CenterOfFace(face); //Center Point of face //irrellevant
        bool BaseIntersection = IntersectsThisBoundingVolumeBooleanT(BoundingVolume, volumeOfFace); //Whether or not the bounding boxes even touch.
        if(!BaseIntersection){return false;}

        //At this point it is verified that we will need to be searching the bounding boxes of the children and need to calculate their bounding boxes.
        if(!GeneratedChildBoundingBoxes)
        {
            GenerateChildrenBoundingVolumes();
        }
        //So the children bounding volumes are generated.

        //Calculates list of intersections to be handled in regards to this current bounding container.

        EveryotherIntersection(volumeOfFace); //adds to intersection queue/general vector

        //Iterate through list of intersections and run the iterative code.
        SDFIterativeTree* calculatedIntersection;
        bool insertionCompleted = false;

        int intsersectionsContainedFaceAmount = 0;
        int intersectionsMaximumFaces = 0;
        bool intersectionsLeafNodeStatus = 0;
        SDFBoundingVolume volumeOfIntersection;

        SDFStackBranchNode<SDFIterativeTree> loadingIteration;

        for(int i = 0; !intersectionStack.empty(); i++) //for all intersections inside of intersection queue run this algorithm
        {
            loadingIteration = intersectionStack.top();
            intersectionStack.pop();

            calculatedIntersection = loadingIteration.direction->Children[loadingIteration.childIndex]; //instead of being sent by index a stack could contain a pointer, and an index?

            //could also possibly call "memoryPool[loadingIntersection.treeIndex]"

            //retrieving information from intersections once.
            
            intsersectionsContainedFaceAmount = calculatedIntersection->ContainedFaces.size();
            intersectionsMaximumFaces = calculatedIntersection->MaximumFaces;
            intersectionsLeafNodeStatus = calculatedIntersection->LeafNode;
            
            
            if(intersectionsLeafNodeStatus && intsersectionsContainedFaceAmount <= intersectionsMaximumFaces)
            {
                calculatedIntersection->ContainedFaces.push_back(face);

            }else if (intersectionsLeafNodeStatus && intsersectionsContainedFaceAmount >= intersectionsMaximumFaces)
            {
                calculatedIntersection->RedistributedInsertion(face); 
            }else
            {
                calculatedIntersection->EveryotherIntersection(volumeOfFace); 
            }

        }

    }
        
    ~SDFIterativeTree(){}

};






#endif