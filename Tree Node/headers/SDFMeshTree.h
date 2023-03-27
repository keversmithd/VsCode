#ifndef SDFMESH_TREE
#define SDFMESH_TREE

#include <SDFArchive.h>

bool FaceEquality(const SDFFace f0, const SDFFace f1)
{
    bool v0xMatch = (f0.v0.x == f1.v0.x);
    bool v0yMatch = (f0.v0.y == f1.v0.y);
    bool v0zMatch = (f0.v0.z == f1.v0.z);

    bool v1xMatch = (f1.v1.x == f1.v1.x);
    bool v1yMatch = (f1.v1.y == f1.v1.y);
    bool v1zMatch = (f1.v1.z == f1.v1.z);

    bool v2xMatch = (f1.v2.x == f1.v2.x);
    bool v2yMatch = (f1.v2.y == f1.v2.y);
    bool v2zMatch = (f1.v2.z == f1.v2.z);

    return (f0.v0.x == f1.v0.x) &&
           (f0.v0.y == f1.v0.y) &&
           (f0.v0.z == f1.v0.z) &&
           (f1.v1.x == f1.v1.x) &&
           (f1.v1.y == f1.v1.y) &&
           (f1.v1.z == f1.v1.z) &&
           (f1.v2.x == f1.v2.x) &&
           (f1.v2.y == f1.v2.y) &&
           (f1.v2.z == f1.v2.z);


}


bool SameSign(float a, float b)
{
    return (a < 0 && b < 0) || (a > 0 && b > 0);
}

inline float AngleBetweenVectors(const SDFVec3 point, const SDFVec3 point1)
{
    return acos((Dot(point, point1))/(Mag(point)*Mag(point1)));
}

bool PointInTriangleDot(const SDFVec3 point, const SDFFace face)
{
    //Assembling corner vector of triangle.
    const SDFVec3 cornerVector1 = Subtract(face.v1, face.v0);
    //Assembling another corner vector of a triangle.
    const SDFVec3 cornerVector2 = Subtract(face.v2, face.v0);

    //Plane of the triangle.
    const SDFVec3 planarNormal = Cross(cornerVector1, cornerVector2);

    //Vx(x-p) + =
    float coeff = -1 * (-face.v0.x * planarNormal.x) + (-face.v0.y * planarNormal.y) + (-face.v0.z * planarNormal.z);
    float testPlanarValue = (planarNormal.x * point.x) + (planarNormal.y * point.y) + (planarNormal.z * point.z);

    if(testPlanarValue != coeff)
    {
        return false;
    }

    //Distance value

    float DistanceBetweenPointAndPlane = abs((planarNormal.x * point.x) + (planarNormal.y * point.y) + (planarNormal.z * point.z) - coeff)/Mag(planarNormal);

    //Determine the dot product of all three vertexes with the point.

    float DotVertexToPointA = Dot(Subtract(point, face.v0), planarNormal);
    float DotVertexToVertexA = Dot(face.v0, face.v1);
    float DotVertexToPointB = Dot(Subtract(point, face.v1), planarNormal);
    float DotVertexToVertexB = Dot(face.v1, face.v2);
    float DotVertexToPointC = Dot(Subtract(point, face.v1), planarNormal);
    float DotVertexToVertexC = Dot(face.v2, face.v0);

    return (SameSign(DotVertexToPointA, DotVertexToVertexA)) && (SameSign(DotVertexToPointB, DotVertexToVertexB)) && (SameSign(DotVertexToPointC, DotVertexToVertexC));

}
bool PointInTriangleAngles(const SDFVec3 point, const SDFFace face)
{
    const SDFVec3 VectorA = Subtract(point, face.v0);
    const SDFVec3 VectorB = Subtract(point, face.v1);
    const SDFVec3 VectorC = Subtract(point, face.v2);

    return ((AngleBetweenVectors(VectorA, VectorB) + AngleBetweenVectors(VectorB, VectorC) + AngleBetweenVectors(VectorC, VectorA)) == 2 * 3.14);

}

SDFVec3 ClosestPointOnTriangleProjection(const SDFVec3 point, const SDFFace face)
{
    const SDFVec3 V0 = Subtract(face.v1, face.v0);
    //A to B
    const SDFVec3 V1 = Subtract(face.v2, face.v0);
    //A to C
    const SDFVec3 V2 = Subtract(face.v2, face.v1);
    //C to B

    //Half Space = Half Of Euclidean space, seperated by hyperplane.
    //Positive Half Space = Subset of space that contains the hyperplane and all the points on the same side of hyperplane as the normal vector.
    //Negative Half Space is the other half.

    //Intersection Of HalfSpaces : (X – A) · (B – A) = 0 and (X – A) · (C – A) = 0.

    // Compute parametric position s for projection P’ of P on AB,
    // P’ = A + s*AB, s = snom/(snom+sdenom)

    //Calcualte vector from A to the Point
    const SDFVec3 FaceAToPoint = Subtract(point, face.v0);
    const SDFVec3 FaceBToPoint = Subtract(point, face.v1);
    const SDFVec3 FaceCToPoint = Subtract(point, face.v2);

    const SDFVec3 PointToA = Subtract(face.v0, point);
    const SDFVec3 PointToB = Subtract(face.v1, point);
    const SDFVec3 PointToC = Subtract(face.v2, point);

    const SDFVec3 FaceBToA = Subtract(face.v0, face.v1);
    const SDFVec3 FaceCToA = Subtract(face.v0, face.v2);
    const SDFVec3 FaceCToB = Subtract(face.v1, face.v2);


    //Dot Product Of Vector From A to Point and From A to B
    float Snumerator = (Dot(FaceAToPoint, V0));
    //Dot Product Of Vector B to Point and From B to A
    float Sdenominator = (Dot(FaceBToPoint, FaceBToA));

    float Tnumerator = Dot(FaceAToPoint, V1);
    float Tdenominator = Dot(FaceCToPoint, FaceCToA);

    if(Snumerator <= 0.0f && Tnumerator <= 0.0f) return face.v0;


    float UNumerator = Dot(FaceBToPoint, V2);
    float UDenominator = Dot(FaceCToPoint, FaceCToB);

    if(Sdenominator <= 0.0f && UNumerator <= 0.0f) return face.v1;
    if(Tdenominator <= 0.0f && UDenominator <= 0.0f) return face.v2;

    const SDFVec3 TriangularNormal = Cross(V0, V1);
    const float VC = Dot(TriangularNormal, Cross(PointToA, PointToB));

    if (VC <= 0.0f && Snumerator >= 0.0f && Sdenominator >= 0.0f)
        return Add(face.v0, Multiply(Snumerator/(Snumerator+Sdenominator), V0));

    float VA = Dot(TriangularNormal, Cross(PointToB, PointToC));

    if(VA <= 0.0f && UNumerator >= 0.0f && UDenominator >= 0.0f)
        return Add(face.v1, Multiply(UNumerator/(UNumerator + UDenominator), V2));
    

    float vb = Dot(TriangularNormal, Cross(PointToC, PointToA));

    if(vb <= 0.0f && Tnumerator >= 0.0f && Tdenominator >= 0.0f)
        return Add(face.v0, Multiply(Tnumerator/(Tnumerator + Tdenominator), V1));
    

    float u = VA / (VA + vb + VC);
    float v = vb / (VA + vb + VC);
    float w = 1.0f - u - v;
    return Add(Add(Multiply(u, face.v0), Multiply(v, face.v1)),Multiply(w, face.v2));

}
float DistanceFromPointToFace(const SDFVec3 point, const SDFFace face)
{
    //Assembling corner vector of triangle.
    const SDFVec3 cornerVector1 = Subtract(face.v1, face.v0);
    //Assembling another corner vector of a triangle.
    const SDFVec3 cornerVector2 = Subtract(face.v2, face.v0);
    //Findin the center of the face using line intersecitons.
    const SDFVec3 FacialCenter = CenterOfFace(face);
    //Finding a face to point vector to the plane of the triangle.

    const SDFVec3 faceToPoint = Subtract(point, FacialCenter);
    //Could be changed to a cannonical point on the triangle.

    //Finding of the normal vector of the plane of the triangle.
    const SDFVec3 faceNormal = Cross(cornerVector1, cornerVector2);
    
    //Using vector projection definition ProjnV = u*v/|u|^2 * u
    const SDFVec3 facialProjection = Multiply(Dot(faceToPoint, faceNormal)/Dot(faceNormal, faceNormal), faceNormal);
    //We have the vector projection in standard terms.


    //Defined as the closest point on the plane.
    const SDFVec3 closestPoint = Add(facialProjection, face.v1);

    //Find magnitude between these points.
    return Mag(Subtract(closestPoint, point));
    
}



struct SDFMeshTree
{
    SDFMeshTree* Children[8];
    std::vector<SDFFace> ContainedFaces;
    SDFBoundingVolume BoundingVolume;

    SDFMeshTree(const SDFBoundingVolume boundingVolume) : Children{nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr,nullptr},BoundingVolume(boundingVolume){}
    SDFMeshTree(const SDFBoundingVolume boundingVolume, const SDFFace face) : Children{nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr,nullptr}, BoundingVolume(boundingVolume)
    {
        ContainedFaces.push_back(face);
    }

    bool IntersectsThisBoundingVolumeVectorComplication(const SDFBoundingVolume T)
    {
        //Algorithm Update Log,
        //The Algorithm should be updated to find the intersection of rays from one box to other and find that distance


        //Calculating Centers
        const SDFVec3 CenterOfThisVolume = CenterOfVolume(BoundingVolume);
        const SDFVec3 CenterOfThatVolume = CenterOfVolume(T);

        //Distance between centers.
        
    
        //Calculating Radius Of That Volume

        const SDFVec3 BetweenVolumesReverse = Subtract(CenterOfThisVolume, CenterOfThatVolume);
        const SDFPlane IntersectedPlaneOfThatVolume = PlanarIntersection(BetweenVolumesReverse, T);
        const SDFVec3 IntersectionPointOfThatVolume = IntersectionOfLineAndPlane({CenterOfThatVolume, BetweenVolumesReverse}, IntersectedPlaneOfThatVolume);
        float ThatVolumeRadius = Mag(Subtract(IntersectionPointOfThatVolume, CenterOfThatVolume));


        //Calculating Radius Of This Volume
        const SDFVec3 BetweenVolumes = Subtract(CenterOfThatVolume, CenterOfThisVolume);
        const SDFPlane IntersectedPlaneOfThisVolume = PlanarIntersection(BetweenVolumes, BoundingVolume);
        const SDFVec3 IntersectionPointOfThisVolume = IntersectionOfLineAndPlane({CenterOfThisVolume, BetweenVolumes}, IntersectedPlaneOfThisVolume);
        float ThisVolumeRadius = Mag(Subtract(IntersectionPointOfThisVolume, CenterOfThisVolume));
        
        //

        //Length Of Vector
        if(Mag(Subtract(IntersectionPointOfThatVolume,IntersectionPointOfThisVolume)) < 0)
        {
            //collision
        }




    }
    bool IntersectsThisBoundingVolumeBoolean(const SDFBoundingVolume T)
    {
        float WThisVolume = BoundingVolume.BottomRightBack.x - BoundingVolume.TopLeftFront.x;
        float HThisVolume = BoundingVolume.TopLeftFront.y - BoundingVolume.BottomRightBack.y;
        float DThisVolume = BoundingVolume.BottomRightBack.z - BoundingVolume.TopLeftFront.z;

        bool XRange = (T.TopLeftFront.x < BoundingVolume.BottomRightBack.x && T.BottomRightBack.x > BoundingVolume.TopLeftFront.x) || (T.BottomRightBack.x < BoundingVolume.BottomRightBack.x && T.TopLeftFront.x > BoundingVolume.TopLeftFront.x);
        bool YRange = (T.TopLeftFront.y > BoundingVolume.BottomRightBack.y && T.BottomRightBack.y < BoundingVolume.TopLeftFront.y) || (T.BottomRightBack.y > BoundingVolume.BottomRightBack.y && T.TopLeftFront.y < BoundingVolume.TopLeftFront.y);
        bool ZRange = (T.TopLeftFront.z < BoundingVolume.BottomRightBack.z && T.BottomRightBack.z > BoundingVolume.TopLeftFront.z) || (T.BottomRightBack.z < BoundingVolume.BottomRightBack.z && T.TopLeftFront.z > BoundingVolume.TopLeftFront.z);


        if(T.TopLeftFront.x < BoundingVolume.BottomRightBack.x && T.BottomRightBack.x > BoundingVolume.TopLeftFront.x)
        {
            //In X Range
        }

        if(T.BottomRightBack.x < BoundingVolume.BottomRightBack.x && T.TopLeftFront.x > BoundingVolume.TopLeftFront.x)
        {
            //In X Range
        }

        if(T.TopLeftFront.y > BoundingVolume.BottomRightBack.y && T.BottomRightBack.y < BoundingVolume.TopLeftFront.y)
        {
            //In Y Range
        }

        if(T.BottomRightBack.y > BoundingVolume.BottomRightBack.y && T.TopLeftFront.y < BoundingVolume.TopLeftFront.y)
        {
            //In Y Range
        }
        

        if(T.TopLeftFront.z < BoundingVolume.BottomRightBack.z && T.BottomRightBack.z > BoundingVolume.TopLeftFront.z)
        {
            //In Z Range
        }

        if(T.BottomRightBack.z < BoundingVolume.BottomRightBack.z && T.TopLeftFront.z > BoundingVolume.TopLeftFront.z)
        {
            //In Z Range
        }

        return (XRange & YRange & ZRange);

    }
    bool ContainedWithinThisBoundingVolumeBoolean(const SDFBoundingVolume T)
    {

        bool Xrange = (T.TopLeftFront.x >= BoundingVolume.TopLeftFront.x && T.BottomRightBack.x <= BoundingVolume.BottomRightBack.x);
        bool Yrange = (T.BottomRightBack.y >= BoundingVolume.BottomRightBack.y && T.TopLeftFront.y <= BoundingVolume.TopLeftFront.y);
        bool Zrange = (T.TopLeftFront.z >= BoundingVolume.TopLeftFront.z && T.BottomRightBack.y <= BoundingVolume.TopLeftFront.z);
        return (Xrange && Yrange && Zrange);
        if(T.TopLeftFront.x >= BoundingVolume.TopLeftFront.x && T.BottomRightBack.x <= BoundingVolume.BottomRightBack.x)
        {
            //in xrange
        }
        if(T.BottomRightBack.y >= BoundingVolume.BottomRightBack.y && T.TopLeftFront.y <= BoundingVolume.TopLeftFront.y)
        {
            //in yrange
        }
        if(T.TopLeftFront.z >= BoundingVolume.TopLeftFront.z && T.BottomRightBack.y <= BoundingVolume.TopLeftFront.z)
        {
            //in zrange
        }


    }
    bool PointContainedWithinBoundingVolumeBoolean(const SDFVec3 point)
    {
        bool xrange = (point.x >= BoundingVolume.TopLeftFront.x && point.x <= BoundingVolume.BottomRightBack.x);
        bool yrange = (point.y >= BoundingVolume.BottomRightBack.y && point.y <= BoundingVolume.TopLeftFront.y);
        bool zrange = (point.z >= BoundingVolume.TopLeftFront.z && point.y <= BoundingVolume.BottomRightBack.z);
        return (xrange && yrange && zrange);
        if(point.x >= BoundingVolume.TopLeftFront.x && point.x <= BoundingVolume.BottomRightBack.x)
        {
            //inxrange
        }
        if(point.y >= BoundingVolume.BottomRightBack.y && point.y <= BoundingVolume.TopLeftFront.y)
        {
            //inyrange
        }
        if(point.z >= BoundingVolume.TopLeftFront.z && point.y <= BoundingVolume.BottomRightBack.z)
        {
            //inzrange
        }
    }
    int OctaneOfPoint(const SDFVec3 point)
    {
        const SDFVec3 centerOfVolume = CenterOfVolume(BoundingVolume);
        // 0 : BottomLeftFront, 1 : TopLeftFront, 2 : BottomRightFront, 3 : TopRightFront, 4 : BottomLeftBack, 5 : TopLeftBack, 6 : BottomRightBack, 7 : TopRightBack, 8 : Outside
        if(!PointContainedWithinBoundingVolumeBoolean(point)){ return 8; }
        return ((4 * (point.z > centerOfVolume.z)) + (2 * (point.x > centerOfVolume.x)) + (point.y > centerOfVolume.y));
        int ReturnIndex = 0;
        if(point.z > centerOfVolume.z)
        {
            ReturnIndex += 4;
        }
        if(point.x > centerOfVolume.x)
        {
            ReturnIndex += 2;
        }
        if(point.y > centerOfVolume.y)
        {
            ReturnIndex += 1;
        }
    }
    SDFBoundingVolume VolumeOfChild(int childIndex)
    {
        
    }

    void SplitAndRedistribute(const SDFFace face)
    {
        for(int i = 0; i < ContainedFaces.size(); i++)
        {
            InsertionOfFaceIntoOctreeAlgorithm1(ContainedFaces.at(i));
        }
    }

    void SearchNeighbors(const SDFFace face, const SDFBoundingVolume BoundingVolumeOfFace, const SDFVec3 centerOfFace, int CenterOctane)
    {

        bool VolumeIntersection = false;
        for(int i = 0; i < 8; i++)
        {
            if(i != CenterOctane)
            {
                const SDFBoundingVolume volumeOfChild = VolumeOfChild(i);
                VolumeIntersection = IntersectsThisBoundingVolumeBooleanT(BoundingVolumeOfFace, volumeOfChild);
                if(VolumeIntersection)
                {
                    if(Children[i] == nullptr)
                    {
                        //Creates new leaf node.
                        Children[i] = new SDFMeshTree(volumeOfChild, face);
                    }else if (Children[i]->ContainedFaces.empty())
                    {

                        //Internal Node Located, Run Insertion On Internal Node
                        Children[i]->InsertionOfFaceIntoOctreeAlgorithm1(face);

                    }else{
                        Children[i]->SplitAndRedistribute(face);
                    }

                }
            }
        }
    }

    void InsertionOfFaceIntoOctreeAlgorithm1(const SDFFace face)
    {
        const SDFBoundingVolume BoundingVolumeOfFace = GetVolumeOfFace(face);
        const SDFVec3 centerOfFace =  CenterOfFace(face);
        bool BoundingIntersection = IntersectsThisBoundingVolumeBoolean(BoundingVolumeOfFace);
        if(!BoundingIntersection){return;}



        //GatherCenterOfOctane
        int CenterOctane = OctaneOfPoint(centerOfFace);
        bool ContainedWithinOctane = ContainedWithinThisBoundingVolumeBoolean(BoundingVolumeOfFace);

        if(!ContainedWithinOctane)
        {
            SearchNeighbors(face, BoundingVolumeOfFace, centerOfFace, CenterOctane);
        }

        const SDFBoundingVolume volumeOfChild = VolumeOfChild(CenterOctane);
        //After searching and inserting children nodes.

        if(Children[CenterOctane] == nullptr)
        {
            //Creates new leaf node.
            Children[CenterOctane] = new SDFMeshTree(volumeOfChild, face);

        }else if (Children[CenterOctane]->ContainedFaces.empty())
        {
            //Internal Node Located, Run Insertion On Internal Node
            Children[CenterOctane]->InsertionOfFaceIntoOctreeAlgorithm1(face);
        }
        else
        {
            Children[CenterOctane]->SplitAndRedistribute(face);
        }

        //Basiccaly compoelte?
    }

    bool FindFaceInContainedFaces(const SDFFace face)
    {
        for(int i = 0; i < ContainedFaces.size(); i++)
        {
            if(FaceEquality(face, ContainedFaces[i]))
            {
                return true;
            }
        }
    }

    bool SearchByFace(const SDFFace face)
    {
        const SDFBoundingVolume BoundingVolumeOfFace = GetVolumeOfFace(face);
        const SDFVec3 centerOfFace = CenterOfFace(face);
        int CenterOctane = OctaneOfPoint(centerOfFace);
        bool BoundingIntersection = IntersectsThisBoundingVolumeBoolean(BoundingVolumeOfFace);
        if(!BoundingIntersection){return false;}
        
        if(Children[CenterOctane] == nullptr)
        {

        }else if (Children[CenterOctane]->ContainedFaces.empty())
        {
            bool FaceFoundInChildren =  Children[CenterOctane]->SearchByFace(face);
            if(FaceFoundInChildren){ return true; }

        }else
        {
            bool FaceFoundInOctane = Children[CenterOctane]->FindFaceInContainedFaces(face);
            if(FaceFoundInOctane){return true;}

            

        }

        bool ContainedWithinOctane = ContainedWithinThisBoundingVolumeBoolean(BoundingVolume);
        if(!ContainedWithinOctane)
        {
            for(int i = 0; i < 8; i++)
            {
                if(i == CenterOctane)
                {

                }else
                {
                    return SearchByFace(face);
                }
            }
            
        }

        return false;

    }

    SDFFace SearchForFaceByPoint(const SDFVec3 point)
    {
        bool IsPointContainedWithinVolume = PointContainedWithinBoundingVolumeBoolean(point);
        if(!IsPointContainedWithinVolume){return SDFFace();}

        //After point has been located within volume determine octane

        int octaneOfPoint = OctaneOfPoint(point);
        
        if(Children[octaneOfPoint] == nullptr)
        {
            return SDFFace();
        }else if(Children[octaneOfPoint]->ContainedFaces.empty())
        {
            Children[octaneOfPoint]->SearchForFaceByPoint(point);
        }else
        {
            struct minDistanceIndex{float minDistance = 0; int facialIndex = -1;} minDistance;
            for(int i = 0; i < ContainedFaces.size(); i++)
            {
                float CalculatedDistance = DistanceFromPointToFace(point, ContainedFaces[i]);
                minDistance = (CalculatedDistance < minDistance.minDistance) ? minDistanceIndex{CalculatedDistance, i} : minDistance; 
            }

            if(minDistance.facialIndex != -1)
            {
                return Children[octaneOfPoint]->ContainedFaces[minDistance.facialIndex];
            }
            
        }

        return SDFFace();
    }

    ~SDFMeshTree(){}
};


#endif