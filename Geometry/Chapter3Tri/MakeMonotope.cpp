#include "MakeMonotope.h"
#include "TriangulateMonotone.h"



int main()
{
    std::vector<vec2> MeshWithInnerFace = {
        {4,0},
        {4,30},
        {15,30},
        {56,36},
        {75,45},
        {327,665},
        {312,707},
        {394,737},
        {645,46},
        {665,36},
        {709,30},
        {721,30},
        {721,0},
        {464,0},
        {464,30},
        {478,30},
        {530,36},
        {552,46},
        {478,249},
        {216,249},
        {133,46},
        {156,36},
        {207,30},
        {221,30},
        {221,0},
        {4,0},
        {-69,-69},
        {237,300},
        {460,300},
        {355,589},
    };

    // std::vector<vec2> MeshWithInnerFace = {
    //     {0,0},
    //     {100,-50},
    //     {98, 20},
    //     {150,15},
    //     {160,40},
    //     {115,35},
    //     {110,65},
    //     {0, 55},
    //     {-98, 20},
    //     {-150,15},
    //     {-160,40},
    //     {-115,35},
    //     {-110,65},
    //     {-180,65},
    //     {-180,-20},
    //     {0,0},
    // };




    printf("Update DCEL implementation to contain access to inner faces, distinguish between interior and exterior boundaries.");

    //Iterate through 12 vertice | Test topology viewer.

    vec2 bottomLeftMost = {(float)INT_MAX, (float)INT_MAX};
    DCELVec* bottomLeftMostPointer = nullptr;
    rect BoundingContainer;

    std::cout << "\n\n\n\n\n\n\n\n new Entry \n\n\n\n\n\n\n\n" << std::endl;
    
    DCEL Polygon;

    for(int i = 0; i < MeshWithInnerFace.size(); i++)
    {
        vec2 a = MeshWithInnerFace[i];
        Polygon.FaceExtraAppendPoint(a);
        
        Polygon.BoundingContainer.IncrementBound(a);
        

    }

    float xmin = Polygon.BoundingContainer.bottomLeft.x;
    float ymin = Polygon.BoundingContainer.bottomLeft.y; 
    float rectWidth = Polygon.BoundingContainer.topRight.x-Polygon.BoundingContainer.bottomLeft.x;
    float rectHeight = Polygon.BoundingContainer.topRight.y-Polygon.BoundingContainer.bottomLeft.y;
    printf("std::vector<Point> MeshWithInnerFace {\n\t");
    for(int i = 0; i < MeshWithInnerFace.size(); i++)
    {
        vec2 pt = MeshWithInnerFace[i];
        vec2 nc = vec2((pt.x-xmin)/rectWidth, (pt.y-ymin)/rectHeight);

        printf("\t{%f,%f},\n",nc.x,nc.y);

    }
    printf("};\n");

    o = Polygon.BoundingContainer.center();

    currentOrientation = orientation(Polygon.edges[0]->origin->vertex, Polygon.edges[0]->next->origin->vertex, Polygon.edges[0]->next->next->origin->vertex);

    Polygon.CounterClockwise = !(currentOrientation);
    Polygon.Origin = Polygon.BoundingContainer.center();

    Polygon.MakeLoopOnActiveFace();

    DCEL TriangulatedEdges;
    DisplayVertexTypes(Polygon);
    //MakeMonotone(Polygon);
    //TriangulateMonotonePolygon2(Polygon, TriangulatedEdges);
    



    return 0;
}