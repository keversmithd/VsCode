
#include <iostream>
#include "DCEL.h"


void EdgeSetInPlane(DCEL& InsertionSet, const plane pl, int I)
{

    std::uniform_real_distribution<float> leftRight(pl.bottomLeft.x, pl.topRight.x);
    std::uniform_real_distribution<float> downUp(pl.bottomLeft.y, pl.topRight.y);

    float lr = leftRight(mt);
    float du = downUp(mt);

    float lr1 = leftRight(mt);
    float du1 = downUp(mt);
    for(int i = 0; i < I; i++)
    {
        lr = leftRight(mt);
        du = downUp(mt);

        lr1 = leftRight(mt);
        du1 = downUp(mt);

        if(du > du1)
        {
            InsertionSet.AddEdge({lr, du},{lr1, du1});
        }else
        {
            InsertionSet.AddEdge({lr1, du1}, {lr, du});
        }
    }
}

void RandomCompleteStructureWithOneHole(DCEL& InsertionSet, const plane pl, int I)
{

    std::uniform_real_distribution<float> leftRight(pl.bottomLeft.x, pl.topRight.x);
    std::uniform_real_distribution<float> downUp(pl.bottomLeft.y, pl.topRight.y);

    float RadialJunctionOuter = 1.0;
    float RadialJunctionInner = 0.6;

    float RadianSteps = (2.0 * 3.14)/I;

    float FluxX = leftRight(mt);
    float f0 = FluxX*(FluxX/abs(FluxX))*0.1;
    float FluxY = downUp(mt);

    Vec e0 = {f0, 0};

    Vec origin = {0,0};
    float Theta = 0;

    InsertionSet.AppendPoint(e0);

    for(int i = 1; i < I-1; i++)
    {
        Theta = RadianSteps * i;
        FluxX = leftRight(mt);
        FluxY = downUp(mt);

        e0 = {origin.x + RadialJunctionOuter*cos(Theta)+(FluxX/abs(FluxX))*(0.1*RadialJunctionOuter), origin.y + RadialJunctionOuter*sin(Theta)+(FluxY/abs(FluxY))*(0.1*RadialJunctionOuter)};

        InsertionSet.AppendPoint(e0);
    }

    e0 = {f0, 0};
    InsertionSet.AppendPoint(e0);

    DCELEdge* OuterInital = InsertionSet.edges[0];

    FluxX = leftRight(mt);
    FluxY = downUp(mt);

    int i = 0;

    InsertionSet.display();

    while(OuterInital != nullptr && OuterInital->next != nullptr)
    {
        Theta = RadianSteps * i;
        FluxX = leftRight(mt);
        FluxY = downUp(mt);

        DCELVec* Origin = OuterInital->origin;

        Vec OriginVertex = Origin->vertex;
        Vec V = vec2(FluxX*0.1, FluxY*0.1);
        Vec o1 = OriginVertex + (origin-OriginVertex)*(FluxX+FluxY)*RadialJunctionInner;
        o1.display();
        
        

        OuterInital = OuterInital->next->next;
        i += 2;
    }

    InsertionSet.display();

    printf("wtf");

    
}


struct IntersectionReportNode
{
    DCELVec* intersection;
    IntersectionSet LUC;
};

struct IntersectionEventNode
{
    DCELEdge* incident;
    bool UpperEndPoint;
};

std::vector<IntersectionReportNode> AllIntersections(DCEL* graph)
{
    RBTree<DCELVec*> Q(VerticleArrangement);
    
    StableArray<DCELVec*> DuplicatePoints;
    
    StatusTree T;
    IntersectionSet Sets;
    std::unordered_set<DCELEdge*> U;
    std::unordered_set<DCELEdge*> LC;
    std::unordered_set<DCELEdge*> UC;
    std::unordered_set<DCELEdge*> LUC;

    std::vector<IntersectionReportNode> Intersections;

    for(int i = 0; i < graph->verticies.size(); i++)
    {
        Q.InsertAndStoreDuplicates(graph->verticies[i], DuplicatePoints);
    }

    while(!Q.empty())
    {
        DCELVec* QueuePoint = Q.removeTop();


        std::vector<int> DuplicateEventIndices = DuplicatePoints.findAll(QueuePoint);
        for(int i = 0; i < DuplicateEventIndices.size(); i++)
        {
            int DuplicateIndex = DuplicateEventIndices[i];
            DCELVec* Duplicate = DuplicatePoints[DuplicateIndex];

            if(IsUpperEndPoint(Duplicate))
            {
                U.insert(Duplicate->incident);
            }
        }

        if(!T.Empty())
        {
            Sets.Clear();
            LC.clear();
            UC.clear();
            LUC.clear();

            T.AllWhichContain(QueuePoint, Sets);

            Union(Sets.L, Sets.C, LC);
            Union(UC, Sets.L, LUC);
            
            if(LUC.size() > 1)
            {
                Intersections.push_back({QueuePoint, Sets.L, Sets.C});
            }

            for(auto it = LC.begin(); it != LC.end(); it++)
            {
                DCELEdge* removalEdge = *it;

                T.remove(removalEdge);
            }

            if(UC.size() > 0)
            {
                for(auto it = UC.begin(); it != UC.end(); it++)
                {
                    DCELEdge* insertionEdge = *it;

                    T.insert(insertionEdge);
                }
                
            }else
            {
                
            }
            

        }
        
    }

}

DCEL OverlayOfTwoSubdivisions(DCEL graph1, DCEL graph2)
{
    std::vector<Vec> IntersectionPoints;

    int GraphId1 = graph1.id;
    int GraphId2 = graph2.id;

    graph1.insert(graph2);

}

int main()
{

    plane Domain = {{-5.0, -1.0}, {10.0, 1.0}};

    const int NumberOfLines = 5;
    DCEL Set1;
    RandomCompleteStructureWithOneHole(Set1, Domain, 20);





    
}