#ifndef LTX_CURVE_LIST_H
#define LTX_CURVE_LIST_H

#include "LTXStructures.h"

#include <vector>
#include <string>

#include "AVLBALANCE.hpp"
#include "Quadtree.h"



struct CurveNode
{
    Curve element;
    std::string id;
    int curvesequence; //the iteration from the head to this curve node

    LTXRect boundingArea;
    CurveNode* next;
    CurveNode* prev;

    CurveNode* leftLayer;
    CurveNode* rightLayer;

    CurveNode(Curve p_element, std::string p_id, int s_id, LTXRect p_bound_area) : element(p_element), id(p_id), curvesequence(s_id), next(nullptr), prev(nullptr), leftLayer(nullptr), rightLayer(nullptr)
    {

    }
};

int StringHash(const std::string HashThis)
{
    
    unsigned int FNV_OFFSET_BASIS = 0x811C9DC5;
    unsigned int FNV_PRIME = 0x01000193;
    unsigned int hashvalue = FNV_OFFSET_BASIS;

    for(int i = 0; i < HashThis.size(); i++)
    {
        hashvalue ^= HashThis[i];
        hashvalue *= FNV_PRIME;
        hashvalue &= 0xFFFFFFFF;
    }
    return hashvalue;
}

int CurveIdentification(CurveNode* A, CurveNode* B)
{
    if(A == nullptr || B == nullptr)
    {
        throw std::range_error("Incorrect Nodes");
    }

    int hash1 = StringHash(A->id + std::to_string(A->curvesequence));
    int hash2 = StringHash(B->id + std::to_string(B->curvesequence));

    if(hash1 < hash2)
    {
        return -1;
    }
    if(hash1 > hash2)
    {
        return 1;
    }

    return 0;

}



struct CurveList
{
    CurveNode* head; //specifically for attaching to trails of curves
    CurveNode* tail;
    
    avl_tree<CurveNode*> FreeCurves;
    Quadtree<CurveNode*> LocalCurves;

    LTXRect BoundingArea; 

    std::string CurrentID;
    int CurrentPathId = -1;

    CurveList(LTXRect Domain) : FreeCurves(CurveIdentification), LocalCurves(Domain), BoundingArea({{-6,-6},{-6,-6}}), head(nullptr), tail(nullptr)
    {

    }

    void startCurve(Curve SimpleCurve, std::string curveName)
    {

        CurrentID = curveName;
        CurrentPathId = 0;

        if(SimpleCurve.type == 0)
        {
            LTXRect boundingArea = SimpleCurve.Quadratic.BoundingRectangle();
            CurveNode* InsertableCurveNode = new CurveNode(SimpleCurve,  CurrentID, 0, boundingArea);

            head = InsertableCurveNode;
            
            tail = head;
            head->next = tail;
            tail->prev = head;

            FreeCurves.insert(InsertableCurveNode);
            LocalCurves.insert(InsertableCurveNode, BoundingArea);
            increment_bounding_area(BoundingArea);
        }
        if(SimpleCurve.type == 1)
        {
            LTXRect boundingArea = CubicBounding(SimpleCurve.Cubic);
            CurveNode* InsertableCurveNode = new CurveNode(SimpleCurve, CurrentID, 0, boundingArea);

            head = InsertableCurveNode;
            
            tail = head;
            head->next = tail;
            tail->prev = head;

            FreeCurves.insert(InsertableCurveNode);
            LocalCurves.insert(InsertableCurveNode, BoundingArea);
            increment_bounding_area(BoundingArea);
        }

        
    }

    void append(Curve SimpleCurve)
    {
        CurrentPathId++;
        if(SimpleCurve.type == 0)
        {
            LTXRect boundingArea = SimpleCurve.Quadratic.BoundingRectangle();
            CurveNode* InsertableCurveNode = new CurveNode(SimpleCurve,  CurrentID, CurrentPathId, boundingArea);
            
            if(head == nullptr)
            {
                head = InsertableCurveNode;
                tail = head;
            }else
            {
                InsertableCurveNode->prev = tail;
                tail->next = InsertableCurveNode;
                tail = tail->next;
            }

            

            FreeCurves.insert(InsertableCurveNode);
            LocalCurves.insert(InsertableCurveNode, boundingArea);
            increment_bounding_area(boundingArea);
        }
        if(SimpleCurve.type == 1)
        {
            LTXRect boundingArea = CubicBounding(SimpleCurve.Cubic);
            CurveNode* InsertableCurveNode = new CurveNode(SimpleCurve,  CurrentID, CurrentPathId, boundingArea);

            if(head == nullptr)
            {
                head = InsertableCurveNode;
                tail = head;
            }else
            {
                InsertableCurveNode->prev = tail;
                tail->next = InsertableCurveNode;
                tail = tail->next;
            }

        
            FreeCurves.insert(InsertableCurveNode);
            LocalCurves.insert(InsertableCurveNode, boundingArea);
            increment_bounding_area(boundingArea);
        }
    }

    CurveNode* FindEmptyLayer(CurveNode* LayerHead, int Direction, int& LayerLevel)
    {
        CurveNode* Parent = LayerHead;
        if(Direction == 0)
        {
            while(LayerHead != nullptr)
            {
                Parent = LayerHead;
                LayerHead = LayerHead->leftLayer;
                LayerLevel++;
            }
        }

        if(Direction == 1)
        {
            while(LayerHead != nullptr)
            {
                Parent = LayerHead;
                LayerHead = LayerHead->rightLayer;
                LayerLevel++;
            }
        }

        return Parent;



    }

    void RadiallyThickenCurrentCurve(float degree, float radius)
    {
        if(head == nullptr)
        {
            return;
        }

        CurveNode* iterator = head;

        LTXPoint Rotation = {cos(degree*3.14/180), sin(degree*3.14/180)};
        Rotation*=radius;

        std::string LeftRightIdentification = (Rotation.x < 0) ? "Left"  : "Right";
        int LeftRightIndex = (Rotation.x > 0);
        while(iterator != nullptr)
        {
            Curve InnerCurve = iterator->element;
            LTXRect CurveBound;
            if(InnerCurve.type == 0)
            {
                
                InnerCurve.Quadratic.P1 += Rotation;
                if(iterator != head)
                {
                    InnerCurve.Quadratic.P0 += Rotation;
                }
                if(iterator != tail)
                {
                    InnerCurve.Quadratic.P2 += Rotation;
                }
                CurveBound = InnerCurve.Quadratic.BoundingRectangle();
            }

            if(iterator->element.type == 1)
            {
                

                InnerCurve.Cubic.P1 += Rotation;
                InnerCurve.Cubic.P2 += Rotation;
                if(iterator != head)
                {
                    InnerCurve.Cubic.P0 += Rotation;
                }
                if(iterator != tail)
                {
                    InnerCurve.Cubic.P3 += Rotation;
                }
                CurveBound = CubicBounding(InnerCurve.Cubic);
            }

            if(LeftRightIndex == 0)
            {
                int LayerLevel = 0;
                CurveNode* ExteriorLayer = FindEmptyLayer(iterator, 0, LayerLevel);
                
                CurveNode* InsertionNode = new CurveNode(InnerCurve, CurrentID+LeftRightIdentification+std::to_string(LayerLevel), iterator->curvesequence, CurveBound);
                InsertionNode->rightLayer = ExteriorLayer;
                if(ExteriorLayer->prev != nullptr && ExteriorLayer->prev->leftLayer != nullptr)
                {
                    InsertionNode->prev = ExteriorLayer->prev->leftLayer;
                    ExteriorLayer->prev->leftLayer->next = InsertionNode;
                }
                ExteriorLayer->leftLayer = InsertionNode;
                
                FreeCurves.insert(InsertionNode);
                LocalCurves.insert(InsertionNode, CurveBound);
                increment_bounding_area(CurveBound);
            }
            if(LeftRightIndex == 1)
            {
                int LayerLevel = 0;
                CurveNode* ExteriorLayer = FindEmptyLayer(iterator, 1, LayerLevel);
                CurveNode* InsertionNode = new CurveNode(InnerCurve, CurrentID+LeftRightIdentification+std::to_string(LayerLevel), iterator->curvesequence, BoundingArea);
                InsertionNode->leftLayer = ExteriorLayer;

                if(ExteriorLayer->prev != nullptr && ExteriorLayer->prev->rightLayer != nullptr)
                {
                    InsertionNode->prev = ExteriorLayer->prev->rightLayer;
                    ExteriorLayer->prev->rightLayer->next = InsertionNode;
                }
                ExteriorLayer->rightLayer = InsertionNode;

                FreeCurves.insert(InsertionNode);
                LocalCurves.insert(InsertionNode, CurveBound);
                increment_bounding_area(CurveBound);
            }

            iterator = iterator->next;
        }

    }

    void RotateThickenedPath(float rotation)
    {
        CurveNode* iterator = head;

        while(iterator != nullptr)
        {

            Curve* InnerCurve = &iterator->element;
            LTXPoint center = BoundingArea.center();

            if(InnerCurve->type == 0)
            {   
                InnerCurve->Quadratic.P0.rotate(rotation,center);
                InnerCurve->Quadratic.P1.rotate(rotation,center);
                InnerCurve->Quadratic.P2.rotate(rotation,center);
            }

            if(InnerCurve->type == 1)
            {
                InnerCurve->Cubic.P0.rotate(rotation,center);
                InnerCurve->Cubic.P1.rotate(rotation,center);
                InnerCurve->Cubic.P2.rotate(rotation,center);
                InnerCurve->Cubic.P3.rotate(rotation,center);
            }

            
            CurveNode* leftLayer = iterator->leftLayer;

            while(leftLayer != nullptr)
            {
                Curve* LayerCurve = &leftLayer->element;

                if(InnerCurve->type == 0)
                {   
                    LayerCurve->Quadratic.P0.rotate(rotation, center);
                    LayerCurve->Quadratic.P1.rotate(rotation, center);
                    LayerCurve->Quadratic.P2.rotate(rotation, center);
                }

                if(InnerCurve->type == 1)
                {
                    LayerCurve->Cubic.P0.rotate(rotation, center);
                    LayerCurve->Cubic.P1.rotate(rotation, center);
                    LayerCurve->Cubic.P2.rotate(rotation, center);
                    LayerCurve->Cubic.P3.rotate(rotation, center);
                }

                leftLayer = leftLayer->leftLayer;
            }

            CurveNode* rightLayer = iterator->rightLayer;


            while(rightLayer != nullptr)
            {
                Curve* LayerCurve = &rightLayer->element;

                if(InnerCurve->type == 0)
                {   
                    LayerCurve->Quadratic.P0.rotate(rotation, center);
                    LayerCurve->Quadratic.P1.rotate(rotation, center);
                    LayerCurve->Quadratic.P2.rotate(rotation, center);
                }

                if(InnerCurve->type == 1)
                {
                    LayerCurve->Cubic.P0.rotate(rotation, center);
                    LayerCurve->Cubic.P1.rotate(rotation, center);
                    LayerCurve->Cubic.P2.rotate(rotation, center);
                    LayerCurve->Cubic.P3.rotate(rotation, center);
                }

                rightLayer = rightLayer->rightLayer;
            }

            iterator = iterator->next;
        }

    }

    void ReflectThickenPath(LTXPoint axis)
    {
        CurveNode* iterator = head;

        while(iterator != nullptr)
        {

            Curve* InnerCurve = &iterator->element;
            if(InnerCurve->type == 0)
            {   
                InnerCurve->Quadratic.P0.reflect(axis);
                InnerCurve->Quadratic.P1.reflect(axis);
                InnerCurve->Quadratic.P2.reflect(axis);
            }

            if(InnerCurve->type == 1)
            {
                InnerCurve->Cubic.P0.reflect(axis);
                InnerCurve->Cubic.P1.reflect(axis);
                InnerCurve->Cubic.P2.reflect(axis);
                InnerCurve->Cubic.P3.reflect(axis);
            }

            
            CurveNode* leftLayer = iterator->leftLayer;

            while(leftLayer != nullptr)
            {
                Curve* LayerCurve = &leftLayer->element;

                if(InnerCurve->type == 0)
                {   
                    LayerCurve->Quadratic.P0.reflect(axis);
                    LayerCurve->Quadratic.P1.reflect(axis);
                    LayerCurve->Quadratic.P2.reflect(axis);
                }

                if(InnerCurve->type == 1)
                {
                    LayerCurve->Cubic.P0.reflect(axis);
                    LayerCurve->Cubic.P1.reflect(axis);
                    LayerCurve->Cubic.P2.reflect(axis);
                    LayerCurve->Cubic.P3.reflect(axis);
                }

                leftLayer = leftLayer->leftLayer;
            }

            CurveNode* rightLayer = iterator->rightLayer;


            while(rightLayer != nullptr)
            {
                Curve* LayerCurve = &rightLayer->element;

                if(InnerCurve->type == 0)
                {   
                    LayerCurve->Quadratic.P0.reflect(axis);
                    LayerCurve->Quadratic.P1.reflect(axis);
                    LayerCurve->Quadratic.P2.reflect(axis);
                }

                if(InnerCurve->type == 1)
                {
                    LayerCurve->Cubic.P0.reflect(axis);
                    LayerCurve->Cubic.P1.reflect(axis);
                    LayerCurve->Cubic.P2.reflect(axis);
                    LayerCurve->Cubic.P3.reflect(axis);
                }

                rightLayer = rightLayer->rightLayer;
            }

            iterator = iterator->next;
        }
    }

    void increment_bounding_area(LTXRect NewBoundingRectangle)
    {
        if(BoundingArea.bottomLeft.x == -6 && BoundingArea.topRight.x == -6)
        {
            BoundingArea = NewBoundingRectangle;
        }else
        {
            BoundingArea.bottomLeft.x = (NewBoundingRectangle.bottomLeft.x < BoundingArea.bottomLeft.x) ? NewBoundingRectangle.bottomLeft.x : BoundingArea.bottomLeft.x;
            BoundingArea.bottomLeft.y = (NewBoundingRectangle.bottomLeft.y < BoundingArea.bottomLeft.y) ? NewBoundingRectangle.bottomLeft.y : BoundingArea.bottomLeft.y;
            BoundingArea.topRight.x = (NewBoundingRectangle.topRight.x > BoundingArea.topRight.x) ? NewBoundingRectangle.topRight.x : BoundingArea.topRight.x;
            BoundingArea.topRight.y = (NewBoundingRectangle.topRight.y > BoundingArea.topRight.y) ? NewBoundingRectangle.topRight.y : BoundingArea.topRight.y;
        }
        
    }

    void read()
    {
        read(FreeCurves.root);
    }

    void read(avl_node<CurveNode*>* n)
    {

        if(n == nullptr)
        {   
            return;
        }

        read(n->left);
        read(n->right);

        Curve InnerCurve = n->value->element;
        if(InnerCurve.type == 0)
        {
            InnerCurve.Quadratic.ReadNamed();
        }

        if(InnerCurve.type == 1)
        {
            InnerCurve.Cubic.ReadNamed();
        }


    }

    ~CurveList()
    {
        
    }


};


#endif