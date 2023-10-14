#include <iostream>
#include "../Chapter2Dcel/DCEL.h"



bool BottomLeftMost(vec2 a, vec2 b)
{
    return (a.x < b.x) ? true : (a.x == b.x) ? (a.y < b.y) ? true : false : false;
}
bool TopLeftMost(vec2 a, vec2 b)
{
    return (a.y > b.y) ? true : (a.y == b.y) ? (a.x < b.x) ? true : false : false;
}
bool lineIntersection(const vec2 A, const vec2 B, DCELEdge* C)
{

    const vec2 DA = {B.x - A.x, B.y - A.y};

    const vec2 CS = C->origin->vertex; 
    const vec2 CE = C->twin->origin->vertex;
    const vec2 DB = {CE.x - CE.x, CS.y - CS.y};

    const double epsilon = 1e-9; // Tolerance threshold for floating-point comparisons

    double determinant = (DA.x * DB.y) - (DA.y * DB.x);

    if (std::abs(determinant) < epsilon)
    {
        // Lines are parallel or coincident
        return false;
    }

    double s = (A.y + (((DA.y * B.x) - (DA.y * A.x)) / DA.x) - B.y) / (DB.y - (DA.y * DB.x / DA.x));
    double t = (CE.x + (DB.x * s) - CS.x) / DA.x;

    if (t <= 1 + epsilon && t >= -epsilon && s <= 1 + epsilon && s >= -epsilon)
    {
        //intersection.x = A.start.x + DA.x * t;
        //intersection.y = A.start.y + DA.y * t;
        return true;
    }

    return false;
}



template<typename T>
void IncrementExtrema(T k, T& p, bool Decider)
{
    p = Decider ? k : p;
}
bool YMonotoneClassification(DCEL& Polygon)
{
    int PolygonSize = Polygon.verticies.size();

    DCELVec* TopMost = Polygon.verticies[0];
    DCELVec* BottomMost = TopMost;
    DCELVec* Iter;
    for(int i = 0; i < PolygonSize; i++)
    {
        Iter = Polygon.verticies[i];

        IncrementExtrema(Iter, TopMost, TopLeftMost(Iter->vertex, TopMost->vertex));
        IncrementExtrema(Iter, BottomMost, BottomLeftMost(Iter->vertex, TopMost->vertex));
    }


    Iter = TopMost;
    while(Iter != nullptr && Iter != BottomMost)
    {
        DCELVec* next = Iter->incident->next->origin;


        if(next->vertex.y > Iter->vertex.y)
        {
            return false;
        }

        Iter = next;

    }

    return true;

}
int AttainTurnVertexes(DCEL& Polygon)
{
    int PolygonSize = Polygon.verticies.size();

    DCELVec* TopMost = Polygon.verticies[0];
    DCELVec* BottomMost = TopMost;
    DCELVec* Iter, *Previous;
    for(int i = 0; i < PolygonSize; i++)
    {
        Iter = Polygon.verticies[i];

        IncrementExtrema(Iter, TopMost, TopLeftMost(Iter->vertex, TopMost->vertex));
        IncrementExtrema(Iter, BottomMost, BottomLeftMost(Iter->vertex, TopMost->vertex));
    }

    Iter = TopMost;
    Previous = TopMost;

    int NumberOfTurnVertexes = 0;

    while(Iter != nullptr && Iter != BottomMost)
    {
        
        DCELVec* next = Iter->incident->next->origin;
        Iter->render();
        next->render();

        bool NextDirection = (next->vertex.y > Iter->vertex.y);

        if(Previous != nullptr)
        {
            bool PreviousDirection = (Iter->vertex.y > Previous->vertex.y);
            

            if(PreviousDirection != NextDirection)
            {
                NumberOfTurnVertexes++;
            }
        }else if(NextDirection == true)
        {
            NumberOfTurnVertexes++;
        }

        Previous = Iter;
        Iter = next;
        
    }

    return NumberOfTurnVertexes;
}

void FirstDiagonal(DCEL& Polygon)
{
    DCELVec* BottomMost = Polygon.verticies[0];
    DCELEdge* Iter = BottomMost->incident;
    DCELEdge* Origin = Iter;

    while(Iter != nullptr && Iter->next != nullptr && Iter->next != Origin)
    {
        Iter = Iter->next;
        IncrementExtrema(Iter->origin, BottomMost, BottomLeftMost(Iter->origin->vertex, BottomMost->vertex));
    }

    BottomMost->render();

    if(BottomMost != nullptr)
    {   
        DCELVec* u = BottomMost->incident->prev->origin;
        DCELVec* w = BottomMost->incident->twin->origin;

        u->render();
        w->render();

        const vec2 Start = u->vertex;
        const vec2 End = w->vertex;

        SpellVector(Start, End);

        DCELEdge* iter = u->incident;

        bool PotentialEdge = true;
        while(iter != nullptr && iter->origin != w && PotentialEdge == true)
        {
            if(lineIntersection(Start,End,iter))
            {   
                PotentialEdge = false;
            }

            iter->origin->render();

            iter = iter->next;

        }

        if(PotentialEdge == true)
        {
            //Start diagonal and split into two.

            DCELEdge* ForwardEdge;
            
            DCELEdge* BackwardEdge;
             
        }

        //to determine whether the line segment uw is present in the interior only, and so traverse to every point inside the triangle defined by  u v w
        //other wise find v' which the farthest point away from the line which is  inside of the triangle defined by u v w, and the diagonal is v, v'
        //other wise it is uw

        
    }
    






}

int main()
{

    DCEL Polygon;

    // Define the vertices of the polygon
    std::vector<vec2> vertices2 = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.5f, 0.5f},
        {2.0f, 1.0f},
        {2.5f, 1.5f},
        {3.0f, 1.5f},
        {3.5f, 1.0f},
        {4.0f, 0.5f},
        {4.5f, 0.0f},
        {5.0f, 0.0f},
        {5.0f, 1.0f},
        {4.5f, 1.5f},
        {4.0f, 2.0f},
        {3.0f, 2.0f},
        {2.0f, 1.5f},
        {1.5f, 1.0f},
        {1.0f, 0.5f},
        {0.5f, 1.0f},
        {0.0f, 1.5f}
    };


    std::vector<vec2> vertices = {
        {0.0f, 0.0f},
        {0.5f, 0.5f},
        {1.0f, 0.5f},
        {1.5f, 1.0f},
        {2.0f, 0.5f},
        {2.5f, 0.5f},
        {3.0f, 0.0f},
        {3.5f, 0.5f},
        {4.0f, 1.0f},
        {4.5f, 1.5f},
        {5.0f, 1.5f},
        {5.5f, 1.0f},
        {6.0f, 0.5f},
        {6.5f, 0.5f},
        {7.0f, 0.0f},
        {6.5f, -0.5f},
        {6.0f, -0.5f},
        {5.5f, 0.0f},
        {5.0f, -0.5f},
        {4.5f, -0.5f},
        {4.0f, 0.0f},
        {3.5f, -0.5f},
        {3.0f, -1.0f},
        {2.5f, -0.5f},
        {2.0f, -0.5f},
        {1.5f, -1.0f},
        {1.0f, -0.5f},
        {0.5f, -0.5f},
        {0.0f, 0.0f}
    };

    vec2 bottomLeftMost = vertices[0];
    rect BoundingContainer;
    
    // Add edges based on the vertices to form the polygon
    for (size_t i = 0; i < vertices.size()-(vertices.size() %2); i++)
    {
        vec2 a = vertices[i];
        vec2 b = vertices[i+1];

        BoundingContainer.IncrementBound(a);
        BoundingContainer.IncrementBound(b);

        Polygon.AddEdge(a, b);
    }

    Polygon.display();
    FirstDiagonal(Polygon);

    std::cout << "driving" << std::endl;
}