#ifndef MAKE_MONOTOPE_TRI_H
#define MAKE_MONOTOPE_TRI_H 

#include <deque>
#include "../Chapter2Dcel/DCEL.h"
#include "../PqueArray.hpp"
#include "../RBTree.h"
#include <unordered_map>
#include "VertexInteriorAngle.h"

#pragma region VERTEX_TYPES

#define PIF 3.14159265358979323846f

enum VertexTypeEnum
{
    StartVertex = 1,
    SplitVertex = 2,
    EndVertex = 3,
    MergeVertex = 4,
    ErrorVertex = -1
};

//A-B are the query, and C and D are proposed edge of polygon.
bool InsideAndNonIntersecting(vec2 A, vec2 B, vec2 C, vec2 D, DCEL& Polygon)
{

    vec2 da = vec2(B.x-A.x,B.y-A.y);
    vec2 db = vec2(D.x-C.x,D.y-C.y);
    double ma = sqrt(da.x*da.x + da.y*da.y);
    double mb = sqrt(db.x*db.x + db.y*db.y);

    if(ma == 0 || mb == 0) return false;


    if((da.x/ma)==(db.x/mb) && (da.y/ma) == (db.x/mb)) // more specifically, if the delta between the unit vectors within a  certain length
    {
        return false;
    }

    vec2 N;

    if(Polygon.CounterClockwise == true)
    {
        N.x = -db.y;
        N.y = db.x;
    }else
    {
        N.x = db.y;
        N.y = -db.x;
    }

    vec2 dc = vec2(C.x-A.x,C.y-A.y);
    vec2 dd = vec2(D.x-B.x, D.y-B.y);

    float mdc = mag(dc);
    float mdd = mag(dd);

    double meep = 0.1;

    if(mdc <= meep && mdd <= meep)
    {
        return false;
    }

    double dn0 = dc.x*N.x + dc.y*N.y;
    double dn1 = dd.x*N.x + dd.y*N.y;

    bool s0 = (dn0 < 0);
    bool s1 = (dn1 < 0);

    if(s0 != s1)
    {
        return false;
    }

    if(s0 == s1)
    {
        return true;
    }
}

bool IsTurnVertex(DCELVec* vertex)
{
    DCELVec* Left = vertex->incident->prev->origin;
    DCELVec* Right = vertex->incident->next->origin;

    vec2 a = vertex->vertex;
    vec2 b = Left->vertex;
    vec2 c = Right->vertex;


    vec2 ba = vec2(b.x-a.x,b.y-a.y);
    vec2 ac = vec2(c.x-a.x,c.y-a.y);

    // if(ba.y == 0 || ba.x == 0)
    // {

    //     DCELVec* RightRight = Left->incident->prev->origin;
        
    //     vec2 d = RightRight->vertex;

    //     vec2 db = vec2(b.x-d.x,b.y-d.y);

    //     if(db.y < 0 && ac.y > 0 || db.y > 0 && ac.y < 0)
    //     {
    //         return true;
    //     }

    // }

    // if((ac.y == 0 || ac.x == 0) && (ba.y == 0 || ba.x == 0))
    // {
    //     vertex->vertex.display();
    // }




    float bay = a.y-b.y;
    float acy = c.y-a.y;



    return (bay < 0) && (acy > 0) || (acy < 0) && (bay > 0);

}

int VertexType(DCELVec* vertex)
{
    //start : two neighbors below it | interior angle at v is less than pi
    //split : two neighbors lie below it | interior angle at v is greater than pi
    //end: two neighbors above it | interior angle at v is less than pi
    //merge: two neighbors above it | interior angle at v is greater than pi

    //vertex->render();

    DCELVec* Left = vertex->incident->next->origin;
    //Left->render();
    DCELVec* Right = vertex->incident->prev->origin;
    //Right->render();

    vec2 a = vertex->vertex;

    vec2 b = Left->vertex;

    vec2 c = Right->vertex;

    bool Below = (b.y == a.y && b.x > a.x) && (c.y == a.y && c.x > a.x);
    bool Above = (b.y == a.y && b.x < a.x) && (c.y == a.y && c.x < a.x);


    if(b.y < a.y && c.y < a.y || Below)
    {   
        vec2 x = b-a;
        vec2 y = c-a;
        
        float a = AngleRadians(x,y);

        
        return (a < 1.57) ? 1 : 2;


    }else if(b.y > a.y && c.y > a.y || Above)
    {
        
        vec2 x = b-a;
        vec2 y = c-a;
        
        float a = AngleRadians(x,y);

        return (a < 1.57) ? 3 : 4;

    }else
    {
        return -1;
    }

}


int VertexType2(DCELVec* vertex)
{
    if(vertex == nullptr || vertex->incident == nullptr || vertex->incident->next == nullptr)
    {
        return 0;
    }
    DCELVec* Left = vertex->incident->next->origin;
    Left->render();
    DCELVec* Right = vertex->incident->prev->origin;
    Right->render();

    vec2 a = vertex->vertex;

    vec2 b = Left->vertex;

    vec2 c = Right->vertex;

    bool Below = (b.y == a.y && b.x > a.x) && (c.y == a.y && c.x > a.x);
    bool Above = (b.y == a.y && b.x < a.x) && (c.y == a.y && c.x < a.x);


    if(b.y < a.y && c.y < a.y || Below)
    {   
        if(AngleArea(a,b,c))
        {
            return 1;
        }else
        {
            return 2;
        }


    }else if(b.y > a.y && c.y > a.y || Above)
    {
        
        if(AngleArea(a,b,c))
        {
            return 3;
        }else
        {
            return 4;
        }

    }else
    {
        return -1;
    }
}

#pragma endregion

#pragma region INTERIOR_RIGHT

    vec2 o;
    int currentOrientation = 0; //1 counter clockwise | 0 clock wse

    bool InteriorToRightRay(DCELVec* vi, DCEL& P)
    {
        rect boundingSystem = P.BoundingContainer;
        float width = boundingSystem.topRight.x - boundingSystem.bottomLeft.x;

        int stepsAllowed = 200;
        float rayStep = stepsAllowed/width;

        vec2 rayMan = vi->vertex;
        vec2 intersection;
        for(int r = 0; r < stepsAllowed; r++)   
        {

            rayMan.x += r*rayStep;

            for(int i = 0; i < P.edges.size(); i++)
            {
                if(linePointIntersection(P.edges[i]->origin->vertex, P.edges[i]->next->origin->vertex, rayMan, intersection))
                {
                    return true;
                }

            }



        }

    }

    bool InteriorToTheRight(DCELVec* vi) //If vi is counter clock wise, then if the next point is down, then interior to the right, if up then interior left.
    {

        //Previous "solution".
        vec2 a = vi->vertex;
        DCELVec* vip = vi->incident->next->origin;
        vec2 b = vip->vertex;



        

        if(b.y < a.y)
        {
            return (currentOrientation) ? 1 : 0;
        }else
        {
            return (currentOrientation) ? 0 : 1;
        }

        //Center 
        // vec2 a = vi->vertex;
        // DCELVec* vip = vi->incident->next->origin;
        // DCELVec* vipp = vi->incident->prev->origin;
        // vec2 b = vip->vertex;
        // vec2 c = vipp->vertex;

        // vec2 oa = vec2(a.x-o.x,a.y-o.y);
        // vec2 ob = vec2(b.x-o.x,b.y-o.y);
        // vec2 oc = vec2(c.x-o.x,c.y-o.y);

        // if(oa.x < 0 && ob.x < 0 && oc.x < 0)
        // {
        //     return true;
        // }

        // if(oa.x < 0 && oc.x < 0)
        // {
        //     return true;
        // }

        // return false;
        


        // vec2 ca = vec2(a.x-c.x,a.y-c.y);
        // vec2 ab = vec2(b.x-a.x,b.y-a.y);

        // return ((ca.x*ab.y) - (ab.y*ca.x)) < 0;



    }



#pragma endregion

#pragma region SEARCH_FOR_LEFT

    int CustomStatus(DCELEdge* e, DCELVec* vi)
    {

        vec2 a = e->origin->vertex;
        vec2 b = vi->vertex;

        if((a.y == b.y) && (a.x == b.x))
        {
            return 0;
        }

        return (a.y > b.y) ? 2 : (a.y == b.y) && (a.x < b.x) ?  2 : 1;

    }

    DCELVec* dataRaceVI = nullptr;

    int WallLeftHeurisitc(RBNode<DCELEdge*>* A, RBNode<DCELEdge*>* B)
    {
        //Any vertex in here is guarenteed to have an x less than dataRaceVI, so
        //But the Y doesn't have any guarentee or restrictions
        if(dataRaceVI == nullptr)
        {
            return 0;
        }
        vec2 a = A->val->origin->vertex;
        vec2 b = B->val->origin->vertex;

        vec2 i = dataRaceVI->vertex;

        float axDiff = (i.x-a.x); //Smaller positive number x Difference, also minimize this.
        float ayDiff = (i.y+a.y); //Large positive number magnitude of boths Y's, minimize this

        float bxDiff = (i.x-b.x);
        float byDiff = (i.y+b.y);

        float aheuristic = axDiff+ayDiff;
        float bheurisitc = bxDiff+byDiff;

        if(aheuristic > bheurisitc)
        {
            return 2;
        }else if(aheuristic == bheurisitc)
        {
            if(a.x < b.x)
            {
                return 2;
            }
            return 0;
        }else
        {
            return 1;
        }
    }

    DCELEdge* SearchForLeft(DCELVec* vi, RBTree<DCELEdge*>& T)
    {
        
        //Inorder traversal, and shortest non intersecting diagaonl with negative x


        RBNode<DCELEdge*>* Search = T.root;

        RBNode<DCELEdge*>* min = nullptr;

        dataRaceVI = vi;

        vec2 viVertex  = vi->vertex;

        HeapArray<RBNode<DCELEdge*>*> canidates(WallLeftHeurisitc); 

        while(Search != nullptr)
        {
            if(Search->val->origin->vertex.x < viVertex.x)
            {
                canidates.push(Search);
            }

            RBNode<DCELEdge*>* left = Search->left;
            RBNode<DCELEdge*>* right = Search->right;

            if(left != nullptr && left->val->origin->vertex.x < viVertex.x)
            {

                canidates.push(left);  
            }


            if(right != nullptr && right->val->origin->vertex.x < viVertex.x)
            {

                canidates.push(left);
                
            }



            Search = Search->right;


        }
        if(canidates.empty())
        {
            return nullptr;
        }
        return canidates.extractMax()->val;
    }

    DCELEdge* SearchForLeftNonIntersecting(DCELVec* vi, RBTree<DCELEdge*>& T, DCEL& polygon)
    {
        DCELEdge* incidentEdge = vi->incident;

        //need to still account for lines which are parallel which have the same vertices.
        DCELEdge* minimumEdge = nullptr; //add priority for merge and split vertices
        float minimumRoot = -1;
        bool initiator = false;

        std::deque<RBNode<DCELEdge*>*> q;
        vec2 lineIntersection;
        if(T.root != nullptr) q.emplace_back(T.root);
        while(!q.empty())
        {
            RBNode<DCELEdge*>* u = q.front();

            q.pop_front();
            if(u->left != nullptr)  q.emplace_back(u->left);
            if(u->right != nullptr) q.emplace_back(u->right);
            

            

            vec2 z = u->val->origin->vertex;

            // if(z == incidentEdge->origin->vertex || z == incidentEdge->next->origin->vertex || z == incidentEdge->prev->origin->vertex)
            // {
            //     continue;
            // }

            vec2 delta = vec2(z.x-vi->vertex.x,z.y-vi->vertex.y);
            if(delta.x >= 0)
            {
                continue;
            }

            for(int i = 0; i < polygon.edges.size(); i++)
            {

                if(lineIntersection2(vi->vertex, z, polygon.edges[i]->origin->vertex, polygon.edges[i]->next->origin->vertex, lineIntersection))
                {
                    continue;
                }

            }

            int vertexType = VertexType2(u->val->origin);

            if(initiator == false)
            {
                minimumRoot = sqrt(delta.x*delta.x + delta.y*delta.y);
                minimumEdge = u->val;
                initiator = true;
            }else
            {
                float mini = sqrt(delta.x*delta.x + delta.y*delta.y);
                rect polyContainer = polygon.BoundingContainer;
                double polyDist = (polyContainer.topRight.x-polyContainer.bottomLeft.x) * (polyContainer.topRight.y - polyContainer.bottomLeft.x);
                double acceptableEpsilon = polyDist/4; 

                if(vertexType == 2 || vertexType == 4 && mini < minimumRoot+acceptableEpsilon && mini > minimumRoot-acceptableEpsilon)
                {   
                    minimumEdge = u->val;
                    minimumRoot = mini;
                }else  
                if(mini < minimumRoot)
                {
                    minimumEdge = u->val;
                    minimumRoot = mini;
                }
            }   
                   
        }

        return minimumEdge;

    }

    //Soon add depriority to neighbor link lengths less than a certain value
    DCELEdge* SearchForNonIntersecting(DCELVec* vi, RBTree<DCELEdge*>& T, DCEL& polygon)
    {
        //open rule up to multiple directions, because this algorithm stinks balls
        DCELEdge* incidentEdge = vi->incident;

        //need to still account for lines which are parallel which have the same vertices.
        DCELEdge* minimumEdge = nullptr; //add priority for merge and split vertices
        float minimumRoot = -1;
        bool initiator = false;

        std::deque<RBNode<DCELEdge*>*> q;
        vec2 lineIntersection;
        if(T.root != nullptr) q.emplace_back(T.root);
        while(!q.empty())
        {
            RBNode<DCELEdge*>* u = q.front();

            q.pop_front();
            if(u->left != nullptr)  q.emplace_back(u->left);
            if(u->right != nullptr) q.emplace_back(u->right);
            
            vec2 z = u->val->origin->vertex;

            vec2 delta = vec2(z.x-vi->vertex.x,z.y-vi->vertex.y);

            for(int i = 0; i < polygon.edges.size(); i++)
            {

                if(lineIntersection2(vi->vertex, z, polygon.edges[i]->origin->vertex, polygon.edges[i]->next->origin->vertex, lineIntersection))
                {
                    continue;
                }

            }

            int vertexType = VertexType2(u->val->origin);

            if(initiator == false)
            {
                minimumRoot = sqrt(delta.x*delta.x + delta.y*delta.y);
                minimumEdge = u->val;
                initiator = true;
            }else
            {
                float mini = sqrt(delta.x*delta.x + delta.y*delta.y);
                rect polyContainer = polygon.BoundingContainer;
                double polyDist = (polyContainer.topRight.x-polyContainer.bottomLeft.x) * (polyContainer.topRight.y - polyContainer.bottomLeft.x);
                double acceptableEpsilon = polyDist/4; 

                if(vertexType == 2 || vertexType == 4 && mini < minimumRoot+acceptableEpsilon && mini > minimumRoot-acceptableEpsilon)
                {   
                    minimumEdge = u->val;
                    minimumRoot = mini;
                }else  
                if(mini < minimumRoot)
                {
                    minimumEdge = u->val;
                    minimumRoot = mini;
                }
            }   
                   
        }

        return minimumEdge;
    }

#pragma endregion

#pragma region VERTEX_HANDLING

    void HandleStartVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& P)
    {
        DCELEdge* ei = vi->incident;
        helper.insert({ei,vi});
        T.insert(ei);
    }

    void HandleEndVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& P)
    {
        DCELEdge* eimo = vi->incident->prev;
        std::unordered_map<DCELEdge *, DCELVec *>::iterator helperpath = helper.find(eimo);
        if(helperpath != helper.end())
        {
            int vertexType = VertexType2(helperpath->second);
            if(vertexType == MergeVertex || vertexType == SplitVertex) // is not edge of polygon
            {
                DCELEdge* Diagonal = new DCELEdge(vi);
                Diagonal->next = helperpath->first;
                SpellEdge(vi->vertex, helperpath->first->origin->vertex);
            }
        }
        T.remove(eimo);
    }

    void HandleSplitVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& P)
    {
        DCELEdge* ej = SearchForLeftNonIntersecting(vi, T, P);

        ej->display();

        std::unordered_map<DCELEdge *, DCELVec *>::iterator helperpath = helper.find(ej);
        if(helperpath != helper.end())
        {

            DCELEdge* Diagonal = new DCELEdge(vi);
            Diagonal->next = helperpath->first;
            
            SpellEdge(vi->vertex, helperpath->first->origin->vertex);
        }

        if(ej != nullptr)
        {
            helper[ej] = vi;
        }
        helper[vi->incident] = vi;
        T.insert(vi->incident);

    }

    void HandleMergeVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& P)
    {

        DCELEdge* eimo = vi->incident->prev;
        //Verify that prev is indeed the last edge with origin two vertices back.
        std::unordered_map<DCELEdge *, DCELVec *>::iterator helperpath = helper.find(eimo);
        if(helperpath != helper.end())
        {
            int vertexType = VertexType2(helperpath->second);
            if(vertexType == MergeVertex || vertexType == SplitVertex) //and regular vertex is good for specific conditions
            {
                DCELEdge* Diagonal = new DCELEdge(vi);
                Diagonal->next = helperpath->first;
                SpellEdge(vi->vertex, helperpath->first->origin->vertex);
            }
        }
        T.remove(eimo);

        DCELEdge* ej = SearchForLeftNonIntersecting(vi, T, P); // reported intersecting value
        if(ej == nullptr)
        {
            return;
        }
        if(ej != nullptr)
        {
            ej->origin->vertex.display();
            ej->next->origin->vertex.display();
            
        }
    
        helperpath = helper.find(ej);

        if(helperpath != helper.end())
        {
            int vertexType = VertexType2(helperpath->second);
            if(vertexType == MergeVertex)
            {
                SpellEdge(vi->vertex, helperpath->first->origin->vertex);
            }
        }

        helper[ej] = vi;


    }

    void HandleRegularVertex(DCELVec* vi, RBTree<DCELEdge*>& T, std::unordered_map<DCELEdge*, DCELVec*>& helper, DCEL& P)
    {
        bool AlternativeCase = false;

        T.insert(vi->incident); //To be extra
        helper.insert({vi->incident, vi});
        if(InteriorToTheRight(vi))
        {
            DCELEdge* eimo = vi->incident->prev;
            
            //vi->incident->twin->next;
            std::unordered_map<DCELEdge*, DCELVec*>::iterator found = helper.find(eimo);
            if(found != helper.end())
            {
                if(VertexType2(found->second) == MergeVertex || VertexType2(found->second) == SplitVertex) //I'd say if its either a merge vertex or a split vertex, then please work.
                {
                    SpellEdge(vi->vertex, found->first->origin->vertex);
                    
                    T.remove(eimo);
                    T.insert(vi->incident);
                    helper[vi->incident] = vi;

                }else
                {
                    AlternativeCase = true;
                }
                
            }else
            {
                AlternativeCase = true;
            }

            if(AlternativeCase == true)
            {
                DCELEdge* ej = SearchForLeftNonIntersecting(vi, T, P);

                if(ej != nullptr)
                {
                    ej->origin->vertex.display();
                    ej->next->origin->vertex.display();
                    
                }
                if (ej == nullptr)
                {
                    return;
                }
                
                std::unordered_map<DCELEdge*, DCELVec*>::iterator found = helper.find(ej);

                if(found != helper.end())
                {

                    if(VertexType2(found->second) == MergeVertex || VertexType2(found->second) == SplitVertex)
                    {
                        SpellEdge(vi->vertex, found->first->origin->vertex);
                    }
                }

            }




        }else
        {

        }


    }

#pragma endregion

int YPriority(DCELVec* A, DCELVec* B)
{
    vec2 a = A->vertex;
    vec2 b = B->vertex;

    if(a.y > b.y)
    {
        return 2;
    }else if(a.y == b.y)
    {
        if(a.x < b.x)
        {
            return 2;
        }
        return 0;
    }else
    {
        return 1;
    }
}

int YPriorityStatus(DCELEdge* A, DCELEdge* B)
{
    vec2 a = A->origin->vertex;
    vec2 b = B->origin->vertex;
    return (a.x < b.x) ? 2 : 1;
    return (a.y > b.y) ? 2 : (a.y == b.y) && (a.x < b.x) ?  2 : 1;
}

void MakeMonotone(DCEL& SimplePolygon)
{

    bool IsMonotone = true;

    HeapArray<DCELVec*> Q(YPriority);
    for(int i = 0; i < SimplePolygon.verticies.size(); i++)
    {
        Q.push(SimplePolygon.verticies[i]);
    }
    
    DCELVec* vi = nullptr;

    RBTree<DCELEdge*> T(YPriorityStatus);

    std::unordered_map<DCELEdge*, DCELVec*> helper;

    while(!Q.empty())
    {
        vi = Q.extractMax();
        vi->vertex.display();
        int vertexType = 0;

        vertexType = VertexType2(vi);

        if(vertexType != -1)
        {
            if(vertexType == StartVertex)
            {
                HandleStartVertex(vi, T, helper, SimplePolygon);
            }else if(vertexType == SplitVertex)
            {
                HandleSplitVertex(vi, T, helper, SimplePolygon);
            }else if(vertexType == EndVertex)
            {
                HandleEndVertex(vi, T, helper, SimplePolygon);
            }else if(vertexType == MergeVertex)
            {
                HandleMergeVertex(vi, T, helper, SimplePolygon);
            }
        }else
        {
            HandleRegularVertex(vi, T, helper, SimplePolygon);
        }
    }

}

void DisplayVertexTypes(DCEL& SimplePolygon)
{

    for(int f = 0; f < SimplePolygon.faces.size(); f++)
    {

        DCELEdge* IncidentEdge = SimplePolygon.faces[f]->incident;
        DCELEdge* OriginEdge = IncidentEdge;

        while(IncidentEdge->next != nullptr && OriginEdge != IncidentEdge->next)
        {

            vec2 NextOrigin = IncidentEdge->origin->vertex;
            vec2 NextDestination = IncidentEdge->next->origin->vertex;

            vec2 DeltaNext = {NextDestination.x - NextOrigin.x, NextDestination.y - NextOrigin.x};
            vec2 NormalNext = {-DeltaNext.y, DeltaNext.x};

            //printf("\\draw[fill=black] (%f,%f) circle (0.5pt);\n", NextOrigin.x, NextOrigin.y);
            //printf("\\draw[fill=black] (%f,%f) circle (0.5pt);\n", NextDestination.x, NextDestination.y);
            printf("\\draw (%f,%f) -- (%f,%f);\n", NextOrigin.x, NextOrigin.y, NextDestination.x, NextDestination.y);
            
            int vertexType = VertexType(IncidentEdge->origin);
            vec2 centerLocation = IncidentEdge->origin->vertex;
            //centerLocation.display();
            
            float boxLength = 5;



            if(vertexType == 1)
            {
                //draw box
                
                printf("\\draw (%f,%f)--(%f,%f)--(%f,%f)-- (%f,%f)--cycle;\n", centerLocation.x-boxLength,centerLocation.y-boxLength,centerLocation.x+boxLength,centerLocation.y-boxLength,centerLocation.x+boxLength,centerLocation.y+boxLength, centerLocation.x-boxLength, centerLocation.y+boxLength);

            }

            if(vertexType == 2)
            {

                
                printf("\\draw[fill=black] (%f,%f) -- (%f,%f) -- (%f,%f)-- cycle;\n", centerLocation.x-boxLength,centerLocation.y-boxLength, centerLocation.x+boxLength,centerLocation.y-boxLength, centerLocation.x, centerLocation.y+boxLength);
            }

            if(vertexType == 3)
            {
                printf("\\draw[fill=black] (%f,%f)--(%f,%f)--(%f,%f)-- (%f,%f)--cycle;\n", centerLocation.x-boxLength,centerLocation.y-boxLength,centerLocation.x+boxLength,centerLocation.y-boxLength,centerLocation.x+boxLength,centerLocation.y+boxLength, centerLocation.x-boxLength, centerLocation.y+boxLength);
            }

            if(vertexType == 4)
            {

                printf("\\draw[fill=black] (%f,%f) -- (%f,%f) -- (%f,%f)-- cycle;\n", centerLocation.x-boxLength,centerLocation.y+boxLength, centerLocation.x+boxLength,centerLocation.y+boxLength, centerLocation.x, centerLocation.y-boxLength);

            }

            IncidentEdge = IncidentEdge->next;
        }

            
    }

    

}


#endif