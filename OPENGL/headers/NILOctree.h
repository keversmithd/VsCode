#ifndef NILOCT
#define NILOCT
#include <vector>
struct NILOPoint
{
	float x, y, z;
    NILOPoint()
        : x(-69.69f), y(-69.69f), z(-69.69f)
    {

    }

    NILOPoint(float _x, float _y, float _c)
        : x(_x), y(_y), z(_c)
    {

    }

};
struct NILOQuad { NILOPoint topLeftFront, bottomRightBack; };

template<typename T, bool Empty(const T&), int InVolume(const T& Element, NILOQuad BoundingVolume), bool Equal(const T& Element, const T& Element1)>
struct NILOctree
{
    T* Geometries;
    NILOQuad BoundingVolume;
    NILOctree* children[8];
    //BBL, BBR, BTR, BTL, FBL, FBR, FTR, FTL

    NILOctree()
    {
        Geometries = new T();
        for (int i = 0; i < 8; i++) { children[i] = nullptr; }
    }
    NILOctree(T element) //Creates octree from element
    {
        Geometries = new T();
        Geometries[0] = element;
    }
    NILOctree(float x1, float y1, float z1, float x2, float y2, float z2)
    { 
        if (x1 > x2 || y1 < y2 || z1 > z2) {
            return;
        }
        Geometries = nullptr;
        BoundingVolume.topLeftFront = { x1, y1, z1 };
        BoundingVolume.bottomRightBack = { x2, y2, z2 };
        children[0] = nullptr; children[4] = nullptr;
        children[1] = nullptr; children[5] = nullptr;
        children[2] = nullptr; children[6] = nullptr;
        children[3] = nullptr; children[7] = nullptr;

    }
    int Insert(const T& Geometry)
    {
        int Quadrance = InVolume(Geometry, BoundingVolume);
        if (Quadrance == -1) { return 0; }
        if (Find(Geometry)) { return 0; } //If exists
        
        if (children[Quadrance]->Geometries == nullptr)
        {
            children[Quadrance]->Insert(Geometry);
        }
        else if(Empty(children[Quadrance]->Geometries))
        {
            children[Quadrance]->Geometries[0] = Geometry;
            return 1;
        }

    }
    
    bool Find(const T& Geometry)
    {
        int Quadrance = 0;
        if (Geometries == nullptr)
        {
            Quadrance = InVolume(Geometry);
            if (Quadrance == -1)
            {
                return false;
            }
            children[Quadrance].Find(Geometry);
        }
        else
        {
            int GeometriesSize = 0;
            for (int i = 0; i < GeometriesSize; i++)
            {
                if (Geometries[i] == Geometry)
                {
                    return true;
                }
            }
        }
        
    }
};



struct NILBoundingTree
{
    NILOPoint* Geometries;
    int GeometriesSize = 0;
    NILOQuad* BoundingBoxes;
    int BoundingBoxesSize = 0;

    NILBoundingTree* Quadrants[8];
    NILOQuad BoundingVolume;

    NILBoundingTree()
    {

    }



    NILOQuad FindNearestBoundingBox(float x, float y, float z)
    {

        NILBoundingTree* Root = this;
        if (BoundingBoxes != nullptr)
        {
            
        }

        for (int i = 0; i < 8; i++)
        {
            if (Quadrants[i] != nullptr)
            {

            }
        }
        

    }

    
    int ProximitySearchBoundingBox(float x, float y, float z)
    {
        float max = -1;
        float min = -1;

        for (int i = 0; i < BoundingBoxesSize; i++)
        {

        }

    }

    int CalculateQuadrance(float x, float y, float z)
    {

        NILOPoint SearchPoint = { x,y,z };
        NILOPoint BoundingFrustrum = { BoundingVolume.topLeftFront.x,BoundingVolume.bottomRightBack.y,  BoundingVolume.topLeftFront.z };
        NILOPoint Distance = Substract(SearchPoint, BoundingFrustrum);

         
        if (ContainsNegative(Distance)) { return -1; }
        float WidthDistance = x - BoundingVolume.topLeftFront.x;
        if (WidthDistance < 0) { return -1; }
        float BoundingWidth = BoundingVolume.bottomRightBack.x - BoundingVolume.topLeftFront.x;
        if (WidthDistance > BoundingWidth) { return -1; }
        float HeightDistance = y - BoundingVolume.bottomRightBack.y;
        if (HeightDistance < 0) { return -1; }
        float BoundingHeight = BoundingVolume.topLeftFront.y - BoundingVolume.bottomRightBack.y;
        if (HeightDistance > BoundingHeight) { return -1; }
        float DepthDistance = z - BoundingVolume.topLeftFront.z;
        if (DepthDistance < 0) { return -1; }
        float BoundingDepth = BoundingVolume.bottomRightBack.z - BoundingVolume.topLeftFront.z;
        if (DepthDistance > BoundingDepth) { return -1; }


        bool XQuadrance = (WidthDistance > BoundingWidth / 2); 
        int YQuadrance = (HeightDistance > BoundingHeight / 2) + (XQuadrance == 1);
        int ZQuadrance = (DepthDistance > BoundingHeight / 2) * ( 3 * (!XQuadrance && YQuadrance == 1) + 5 * (!XQuadrance && YQuadrance == 0) + 6 * (XQuadrance && YQuadrance == 0) );

        return (XQuadrance) + (YQuadrance) + (ZQuadrance);
    }

    void CalculateQuadrances(NILOQuad BoundingVolume, int* Indexes)
    {
        int LowerLeftFront = CalculateQuadrance(BoundingVolume.topLeftFront.x, BoundingVolume.bottomRightBack.y, BoundingVolume.topLeftFront.z);
        int LowerRightFront = CalculateQuadrance(BoundingVolume.bottomRightBack.x, BoundingVolume.bottomRightBack.y, BoundingVolume.topLeftFront.z);
        int UpperLeftFront = CalculateQuadrance(BoundingVolume.bottomRightBack.x, BoundingVolume.topLeftFront.y, BoundingVolume.topLeftFront.z);
        int UpperRightFront = CalculateQuadrance(BoundingVolume.topLeftFront.x, BoundingVolume.topLeftFront.y, BoundingVolume.topLeftFront.z);
        int LowerLeftBack = CalculateQuadrance(BoundingVolume.topLeftFront.x, BoundingVolume.bottomRightBack.y, BoundingVolume.bottomRightBack.z);
        int LowerRightBack = CalculateQuadrance(BoundingVolume.bottomRightBack.x, BoundingVolume.bottomRightBack.y, BoundingVolume.bottomRightBack.z);
        int UpperLeftBack = CalculateQuadrance(BoundingVolume.bottomRightBack.x, BoundingVolume.topLeftFront.y, BoundingVolume.bottomRightBack.z);
        int UpperRightBack = CalculateQuadrance(BoundingVolume.topLeftFront.x, BoundingVolume.topLeftFront.y, BoundingVolume.bottomRightBack.z);
    }


    void ReadVertices(std::vector<NILOPoint>& Vertices, std::vector<NILOPoint>& Quadrances, std::vector<int> Indices)
    {
        if (Geometries != nullptr)
        {
            Indices.push_back(GeometriesSize);
            for (int i = 0; i < GeometriesSize; i++)
            {
                Vertices.push_back(Geometries[i]);
            }
        }

        NILOPoint LowerLeftFront = {BoundingVolume.topLeftFront.x, BoundingVolume.bottomRightBack.y, BoundingVolume.topLeftFront.z};
        NILOPoint LowerRightFront = {BoundingVolume.bottomRightBack.x, BoundingVolume.bottomRightBack.y, BoundingVolume.topLeftFront.z};
        NILOPoint UpperLeftFront = {BoundingVolume.bottomRightBack.x, BoundingVolume.topLeftFront.y, BoundingVolume.topLeftFront.z};
        NILOPoint UpperRightFront = {BoundingVolume.topLeftFront.x, BoundingVolume.topLeftFront.y, BoundingVolume.topLeftFront.z};
        NILOPoint LowerLeftBack = {BoundingVolume.topLeftFront.x, BoundingVolume.bottomRightBack.y, BoundingVolume.bottomRightBack.z};
        NILOPoint LowerRightBack = {BoundingVolume.bottomRightBack.x, BoundingVolume.bottomRightBack.y, BoundingVolume.bottomRightBack.z};
        NILOPoint UpperLeftBack = {BoundingVolume.bottomRightBack.x, BoundingVolume.topLeftFront.y, BoundingVolume.bottomRightBack.z};
        NILOPoint UpperRightBack = {BoundingVolume.topLeftFront.x, BoundingVolume.topLeftFront.y, BoundingVolume.bottomRightBack.z};

        Quadrances.push_back(LowerLeftFront);
        Quadrances.push_back(LowerRightFront);
        Quadrances.push_back(UpperLeftFront);
        Quadrances.push_back(UpperRightFront);
        Quadrances.push_back(LowerLeftBack);
        Quadrances.push_back(LowerRightBack);
        Quadrances.push_back(UpperLeftBack);
        Quadrances.push_back(UpperRightBack);

        for (int i = 0; i < 8; i++)
        {
            if (Quadrants[i] != nullptr)
            {
                Quadrants[i]->ReadVertices(Vertices, Quadrances, Indices);
            }
        }


    }
    inline NILOPoint Substract(NILOPoint A, NILOPoint B)
    {
        return NILOPoint(A.x - B.x, A.y - B.y, A.z - B.z);
    }
    inline bool ContainsNegative(NILOPoint A)
    {
        return (A.x < 0 || A.y < 0 || A.z < 0);
    }


};

#endif
