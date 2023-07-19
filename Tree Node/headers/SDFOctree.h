#ifndef SDFOCT_TREEE
#define SDFOCT_TREEE


#include <SDFBoundingPrimitives.h>
#include <SDFSpell.h>
// bool FaceEquality(const SDFFace f0, const SDFFace f1)
// {
//     bool v0xMatch = (f0.v0.x == f1.v0.x);
//     bool v0yMatch = (f0.v0.y == f1.v0.y);
//     bool v0zMatch = (f0.v0.z == f1.v0.z);

//     bool v1xMatch = (f1.v1.x == f1.v1.x);
//     bool v1yMatch = (f1.v1.y == f1.v1.y);
//     bool v1zMatch = (f1.v1.z == f1.v1.z);

//     bool v2xMatch = (f1.v2.x == f1.v2.x);
//     bool v2yMatch = (f1.v2.y == f1.v2.y);
//     bool v2zMatch = (f1.v2.z == f1.v2.z);

//     return (f0.v0.x == f1.v0.x) &&
//            (f0.v0.y == f1.v0.y) &&
//            (f0.v0.z == f1.v0.z) &&
//            (f1.v1.x == f1.v1.x) &&
//            (f1.v1.y == f1.v1.y) &&
//            (f1.v1.z == f1.v1.z) &&
//            (f1.v2.x == f1.v2.x) &&
//            (f1.v2.y == f1.v2.y) &&
//            (f1.v2.z == f1.v2.z);


// }

// bool SameSign(float a, float b)
// {
//     return (a < 0 && b < 0) || (a > 0 && b > 0);
// }

// inline float AngleBetweenVectors(const SDFVec3 point, const SDFVec3 point1)
// {
//     return acos((Dot(point, point1))/(Mag(point)*Mag(point1)));
// }
// bool PointInTriangleDot(const SDFVec3 point, const SDFFace face)
// {
//     //Assembling corner vector of triangle.
//     const SDFVec3 cornerVector1 = Subtract(face.v1, face.v0);
//     //Assembling another corner vector of a triangle.
//     const SDFVec3 cornerVector2 = Subtract(face.v2, face.v0);

//     //Plane of the triangle.
//     const SDFVec3 planarNormal = Cross(cornerVector1, cornerVector2);

//     //Vx(x-p) + =
//     float coeff = -1 * (-face.v0.x * planarNormal.x) + (-face.v0.y * planarNormal.y) + (-face.v0.z * planarNormal.z);
//     float testPlanarValue = (planarNormal.x * point.x) + (planarNormal.y * point.y) + (planarNormal.z * point.z);

//     if(testPlanarValue != coeff)
//     {
//         return false;
//     }

//     //Distance value

//     float DistanceBetweenPointAndPlane = abs((planarNormal.x * point.x) + (planarNormal.y * point.y) + (planarNormal.z * point.z) - coeff)/Mag(planarNormal);

//     //Determine the dot product of all three vertexes with the point.

//     float DotVertexToPointA = Dot(Subtract(point, face.v0), planarNormal);
//     float DotVertexToVertexA = Dot(face.v0, face.v1);
//     float DotVertexToPointB = Dot(Subtract(point, face.v1), planarNormal);
//     float DotVertexToVertexB = Dot(face.v1, face.v2);
//     float DotVertexToPointC = Dot(Subtract(point, face.v1), planarNormal);
//     float DotVertexToVertexC = Dot(face.v2, face.v0);

//     return (SameSign(DotVertexToPointA, DotVertexToVertexA)) && (SameSign(DotVertexToPointB, DotVertexToVertexB)) && (SameSign(DotVertexToPointC, DotVertexToVertexC));
//     //if the dot is zero on the all the vectors in the point is in the plane
//     //an alternative to check the points orientation to the line segments of the triangle
// }

bool PointInTriangleDetermininant(const SDFVec3 point, const SDFFace face)
{
    const SDFVec2 v0Plane = ProjectDownPlane(face.v0, face.Normal, face.v0);
    const SDFVec2 v1Plane = ProjectDownPlane(face.v1, face.Normal, face.v0);
    const SDFVec2 v2Plane = ProjectDownPlane(face.v1, face.Normal, face.v0);

    bool Orientation = RightTurn(v0Plane, v1Plane, v2Plane);

    const SDFVec2 nTurn0 = (Orientation) ? v2Plane : v1Plane;
    const SDFVec2 nTurn1 = (Orientation) ? v1Plane : v2Plane;

    const SDFVec2 vPlane = ProjectDownPlane(point, face.Normal, face.v0);

    //in order of clockwise there for all must be right turns to beinside

    return (!RightTurn(vPlane, v0Plane, nTurn0) && !RightTurn(vPlane, nTurn0, nTurn1) && !RightTurn(vPlane, nTurn1, v0Plane));
}

// bool PointInTriangleAngles(const SDFVec3 point, const SDFFace face)
// {
//     const SDFVec3 VectorA = Subtract(point, face.v0);
//     const SDFVec3 VectorB = Subtract(point, face.v1);
//     const SDFVec3 VectorC = Subtract(point, face.v2);

//     return ((AngleBetweenVectors(VectorA, VectorB) + AngleBetweenVectors(VectorB, VectorC) + AngleBetweenVectors(VectorC, VectorA)) == 2 * 3.14);

// }

// SDFVec3 ClosestPointOnTriangleProjection(const SDFVec3 point, const SDFFace face)
// {
//     const SDFVec3 V0 = Subtract(face.v1, face.v0);
//     //A to B
//     const SDFVec3 V1 = Subtract(face.v2, face.v0);
//     //A to C
//     const SDFVec3 V2 = Subtract(face.v2, face.v1);
//     //C to B

//     //Half Space = Half Of Euclidean space, seperated by hyperplane.
//     //Positive Half Space = Subset of space that contains the hyperplane and all the points on the same side of hyperplane as the normal vector.
//     //Negative Half Space is the other half.

//     //Intersection Of HalfSpaces : (X – A) · (B – A) = 0 and (X – A) · (C – A) = 0.

//     // Compute parametric position s for projection P’ of P on AB,
//     // P’ = A + s*AB, s = snom/(snom+sdenom)

//     //Calcualte vector from A to the Point
//     const SDFVec3 FaceAToPoint = Subtract(point, face.v0);
//     const SDFVec3 FaceBToPoint = Subtract(point, face.v1);
//     const SDFVec3 FaceCToPoint = Subtract(point, face.v2);

//     const SDFVec3 PointToA = Subtract(face.v0, point);
//     const SDFVec3 PointToB = Subtract(face.v1, point);
//     const SDFVec3 PointToC = Subtract(face.v2, point);

//     const SDFVec3 FaceBToA = Subtract(face.v0, face.v1);
//     const SDFVec3 FaceCToA = Subtract(face.v0, face.v2);
//     const SDFVec3 FaceCToB = Subtract(face.v1, face.v2);


//     //Dot Product Of Vector From A to Point and From A to B
//     float Snumerator = (Dot(FaceAToPoint, V0));
//     //Dot Product Of Vector B to Point and From B to A
//     float Sdenominator = (Dot(FaceBToPoint, FaceBToA));

//     float Tnumerator = Dot(FaceAToPoint, V1);
//     float Tdenominator = Dot(FaceCToPoint, FaceCToA);

//     if(Snumerator <= 0.0f && Tnumerator <= 0.0f) return face.v0;


//     float UNumerator = Dot(FaceBToPoint, V2);
//     float UDenominator = Dot(FaceCToPoint, FaceCToB);

//     if(Sdenominator <= 0.0f && UNumerator <= 0.0f) return face.v1;
//     if(Tdenominator <= 0.0f && UDenominator <= 0.0f) return face.v2;

//     const SDFVec3 TriangularNormal = Cross(V0, V1);
//     const float VC = Dot(TriangularNormal, Cross(PointToA, PointToB));

//     if (VC <= 0.0f && Snumerator >= 0.0f && Sdenominator >= 0.0f)
//         return Add(face.v0, Multiply(Snumerator/(Snumerator+Sdenominator), V0));

//     float VA = Dot(TriangularNormal, Cross(PointToB, PointToC));

//     if(VA <= 0.0f && UNumerator >= 0.0f && UDenominator >= 0.0f)
//         return Add(face.v1, Multiply(UNumerator/(UNumerator + UDenominator), V2));
    

//     float vb = Dot(TriangularNormal, Cross(PointToC, PointToA));

//     if(vb <= 0.0f && Tnumerator >= 0.0f && Tdenominator >= 0.0f)
//         return Add(face.v0, Multiply(Tnumerator/(Tnumerator + Tdenominator), V1));
    

//     float u = VA / (VA + vb + VC);
//     float v = vb / (VA + vb + VC);
//     float w = 1.0f - u - v;
//     return Add(Add(Multiply(u, face.v0), Multiply(v, face.v1)),Multiply(w, face.v2));

// }
// float DistanceFromPointToFace(const SDFVec3 point, const SDFFace face)
// {
//     //Assembling corner vector of triangle.
//     const SDFVec3 cornerVector1 = Subtract(face.v1, face.v0);
//     //Assembling another corner vector of a triangle.
//     const SDFVec3 cornerVector2 = Subtract(face.v2, face.v0);
//     //Findin the center of the face using line intersecitons.
//     const SDFVec3 FacialCenter = CenterOfFace(face);
//     //Finding a face to point vector to the plane of the triangle.

//     const SDFVec3 faceToPoint = Subtract(point, FacialCenter);
//     //Could be changed to a cannonical point on the triangle.

//     //Finding of the normal vector of the plane of the triangle.
//     const SDFVec3 faceNormal = Cross(cornerVector1, cornerVector2);
    
//     //Using vector projection definition ProjnV = u*v/|u|^2 * u
//     const SDFVec3 facialProjection = Multiply(Dot(faceToPoint, faceNormal)/Dot(faceNormal, faceNormal), faceNormal);
//     //We have the vector projection in standard terms.


//     //Defined as the closest point on the plane.
//     const SDFVec3 closestPoint = Add(facialProjection, face.v1);

//     //Find magnitude between these points.
//     return Mag(Subtract(closestPoint, point));
    
// }


enum OctantIndex
{
    BottomLeftFront = 0, 
    TopLeftFront = 1, 
    BottomRightFront = 2, 
    TopRightFront = 3,
    BottomLeftBack = 4, 
    TopLeftBack = 5,
    BottomRightBack = 6, 
    TopRightBack = 7, 
    Outside = 8
};

template<typename Assoc>
struct SDFOctex
{
    SDFVec3 Vertex;
    Assoc* object;

    SDFOctex(SDFVec3 vertex, Assoc* volume) : object(volume), Vertex(vertex)
    {   

    }

    ~SDFOctex()
    {

    }
};

template<typename Assoc>
struct SDFOctree
{
    SDFOctree* Parent;
    SDFOctree* Children[8];
    std::vector<SDFOctex<Assoc>> ContainedFaces;
    SDFBoundingVolume BoundingVolume;

    SDFOctree(const SDFBoundingVolume boundingVolume) : Children{nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr,nullptr},BoundingVolume(boundingVolume)
    {

    }
    SDFOctree(const SDFBoundingVolume boundingVolume, const SDFVec3 vertex, Assoc* volume) : Children{nullptr, nullptr, nullptr, nullptr,nullptr,nullptr, nullptr,nullptr}, BoundingVolume(boundingVolume)
    {
        ContainedFaces.push_back(SDFOctex<Assoc>(vertex, volume));
    }

    bool insertBoundingVolume(Assoc* assoc)
    {
        const SDFBoundingVolume bv = assoc->boundingVolume;
        DrawBoundingVolume(bv);
        insertPoint(bv.BottomRightBack, assoc);
        insertPoint(bv.TopLeftFront, assoc);
        insertPoint({bv.BottomRightBack.x, bv.BottomRightBack.y, bv.TopLeftFront.z}, assoc);
        insertPoint({bv.TopLeftFront.x, bv.BottomRightBack.y, bv.BottomRightBack.z}, assoc);
        insertPoint({bv.BottomRightBack.x, bv.TopLeftFront.y, bv.TopLeftFront.z}, assoc);
        insertPoint({bv.TopLeftFront.x, bv.TopLeftFront.y, bv.BottomRightBack.z}, assoc);
    }

    bool insertPoint(SDFVec3 vertex, Assoc* assoc)
    {
        SDFOctree* OctreeNode = this;
        bool Inserted = false;
        int searchDepth = 0;
        
        while(OctreeNode != nullptr && Inserted == false)
        {
            SDFBoundingVolume CurrentBoundingVolume = OctreeNode->BoundingVolume;
            DrawPoint(vertex);
            DrawBoundingVolume(CurrentBoundingVolume);

            if(PointContainedWithinBoundingVolumeBoolean(vertex, CurrentBoundingVolume))
            {
                int OctantIndex = OctaneOfPoint(vertex, CurrentBoundingVolume);
                const SDFBoundingVolume ChildVolume = VolumeOfChild(OctantIndex, CurrentBoundingVolume);
                if(OctantIndex != 8)
                {   
                    if(OctreeNode->Children[OctantIndex] == nullptr)
                    {
                        OctreeNode->Children[OctantIndex] = new SDFOctree(ChildVolume, vertex, assoc);
                        assoc->currentIndex = OctantIndex;
                        assoc->tree = OctreeNode;

                        Inserted = true;
                    }else
                    {
                        if(searchDepth > 2)
                        {
                            //split and distribute vertices of the into the subdivided state.
                            OctreeNode->ContainedFaces.push_back({vertex,assoc});
                            Inserted = true;
                        }else
                        {
                            OctreeNode = OctreeNode->Children[OctantIndex];
                            searchDepth++;
                        }

                    }
                }
            }else
            {
                
                return false;
            }
        }
        


    }

    bool removePoint(SDFVec3 vertex)
    {

        SDFOctree OctreeNode* = this;

        bool found = false;
        while(OctreeNode != nullptr && found == false)
        {
            SDFBoundingVolume CurrentBoundingVolume = OctreeNode->BoundingVolume;
            int octantIndex = OctaneOfPoint(vertex, CurrentBoundingVolume);

            if(children[octantIndex] != nullptr)
            {

                

            }

        }

    }

    bool removePoint(int childIndex)
    {
        
    }
    

    ~SDFOctree(){}
};


#endif