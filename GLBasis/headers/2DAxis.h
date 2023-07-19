#ifndef TD_AXIS_H
#define TD_AXIS_H

#include "LearnOpenglHelper.h"
#include "FGeom.h"






struct PlaneRenderer
{
private:
    SDFPlane m_plane;
    double m_dx;
    double m_dy;

    double m_pwidth;
    double m_pheight;

    SDFVec2 m_sub; //number of subdivisions required for x and y locations

    float m_horzRectRadius; //in relation to size of plane

    NGLProgram m_program;
    NGLVertexArray m_vertexArray;
    NGLBuffer m_DataBuffer;

    std::vector<float> memoryData;

public:
    PlaneRenderer(const SDFPlane Plane, double dx, double dy)
    {
        m_plane = Plane;

        m_dx = dx;
        m_dy = dy;

        m_pwidth = m_plane.BottomRight.x - m_plane.BottomLeft.x;
        m_pheight = m_plane.TopRight.y - m_plane.BottomRight.y;

        //Number Of Subdivisions Needed
        m_sub.x = m_pwidth/dx;
        m_sub.y = m_pheight/dy;

        //Thickness Of the Rectangles drawn
        m_horzRectRadius = 0.05*m_pwidth; //thickness based on horizontal size

    }

    void ConstructPlane()
    {
        SDFVec3 Origin = m_plane.BottomLeft;
        SDFVec3 Destination =  m_plane.TopLeft;
        SDFVec3 OD = Subtract(Destination, Origin);
        
        const SDFVec3 b_leftRight = Normalize(Subtract(m_plane.BottomRight, m_plane.BottomLeft));
        const SDFVec3 t_leftRight = Normalize(Subtract(m_plane.TopRight, m_plane.TopLeft));

        

        for(int i = 0; i < m_sub.y; i++)
        {
            Origin = Add(Origin, Multiply(b_leftRight, m_dx*i));
            Destination = Add(Destination, Multiply(t_leftRight, m_dx*i));
            
            fTriQuad(
                Subtract(Origin, {m_horzRectRadius, 0}),
                Add(Origin, {m_horzRectRadius, 0}),
                Add(Add(Origin, {m_horzRectRadius, 0}), OD),
                Add(Subtract(Origin, {m_horzRectRadius, 0}), OD),
                memoryData
            );

        }

        const SDFVec3 l_upDown = Normalize(Subtract(m_plane.TopLeft, m_plane.BottomLeft));
        const SDFVec3 r_upDown = Normalize(Subtract(m_plane.TopRight, m_plane.BottomLeft));
        
        Origin = m_plane.BottomLeft;
        Destination = m_plane.BottomRight;
        OD = Subtract(Destination, Origin);

        for(int j = 0; j < m_sub.x; j++)
        {
            Origin = Add(Origin, Multiply(l_upDown, m_dy*j));
            Destination = Add(Destination, Multiply(r_upDown, m_dy*j));

            fTriQuad(
                Subtract(Origin, {0, m_horzRectRadius}),
                Add(Origin, {0, m_horzRectRadius}),
                Add(Add(Origin, {0, m_horzRectRadius}), OD),
                Add(Subtract(Origin, {0, m_horzRectRadius}), OD),
                memoryData
            );
            
        }
    }

    void ConstructSquaredAxis()
    {
        float arrowHeight = 0.05;
        float arrowThickness = 0.05;

        float shaftLength = 0.05;
        float tipLength = 0.05;
        float tipRadius = 0.05;
        float baseRadius = 0.2;
        float shaftRadius = 0.05;

        float SubdivisionFaces = 3;
        float HorizontalDivisions = 2;

        float borderRadius = 0.2;

        SDFVec3 axis = Subtract(m_plane.BottomRight, m_plane.BottomLeft);
        SDFVec3 axisnorm = Normalize(Cross(axis, m_plane.BottomLeft));
        SDFVec3 axisnnorm = Normalize(Cross(axisnorm, m_plane.BottomLeft));
        
        float axisLength = Mag(axis);
        float axisdx = axisLength/HorizontalDivisions;
        float dr = (2*3.14159265359)/SubdivisionFaces;

        SDFVec3 p_left = m_plane.BottomLeft, p_right = m_plane.BottomRight;

        SDFVec3 c1,c2,c3,c4;

        for(int i = 0; i < HorizontalDivisions; i++)
        {
            p_right = Add(p_right, Normalize(Multiply(axis, axisdx)));
            for(float j = 0; j < SubdivisionFaces; j+=2)
            {
                c1 = {(p_left.x) + (borderRadius*cos(j*dr)*axisnorm.x) + (borderRadius*sin(j*dr)*axisnnorm.x), (p_left.y) + (borderRadius*cos(j*dr)*axisnorm.y) + (borderRadius*sin(j*dr)*axisnnorm.y), (p_left.z) + (borderRadius*cos(j*dr)*axisnorm.z) + (borderRadius*sin(j*dr)*axisnnorm.z)};
                
                c2 = {(p_right.x) + (borderRadius*cos(j*dr)*axisnorm.x) + (borderRadius*sin(j*dr)*axisnnorm.x), (p_right.y) + (borderRadius*cos(j*dr)*axisnorm.y) + (borderRadius*sin(j*dr)*axisnnorm.y), (p_right.z) + (borderRadius*cos(j*dr)*axisnorm.z) + (borderRadius*sin(j*dr)*axisnnorm.z)};

                c3 = {(p_left.x) + (borderRadius*cos((j+1)*dr)*axisnorm.x) + (borderRadius*sin((j+1)*dr)*axisnnorm.x), (p_left.y) + (borderRadius*cos((j+1)*dr)*axisnorm.y) + (borderRadius*sin((j+1)*dr)*axisnnorm.y), (p_left.z) + (borderRadius*cos((j+1)*dr)*axisnorm.z) + (borderRadius*sin((j+1)*dr)*axisnnorm.z)};
                
                c4 = {(p_right.x) + (borderRadius*cos((j+1)*dr)*axisnorm.x) + (borderRadius*sin((j+1)*dr)*axisnnorm.x), (p_right.y) + (borderRadius*cos((j+1)*dr)*axisnorm.y) + (borderRadius*sin((j+1)*dr)*axisnnorm.y), (p_right.z) + (borderRadius*cos((j+1)*dr)*axisnorm.z) + (borderRadius*sin((j+1)*dr)*axisnnorm.z)};

                fTriQuad(c1, c2, c3, c4, memoryData);

                if(i == 0)
                {
                    fTri(p_left, c1, c3, memoryData);
                }else
                if(i == 1){
                    fTri(p_right, c2, c4, memoryData);
                }

            }
            p_left = p_right;
        }


        const SDFVec3 ShaftBegin = p_right;
        const SDFVec3 ShaftEnd = Add(p_right, Normalize(Multiply(axis, shaftLength)));
        const SDFVec3 ShaftTip = Add(ShaftEnd, Normalize(Multiply(axis, shaftLength)));
        

        for(float j = 0; j < SubdivisionFaces; j+=2)
        {
            

            c1 = {(ShaftBegin.x) + (shaftRadius*cos(j*dr)*axisnorm.x) + (shaftRadius*sin(j*dr)*axisnnorm.x), (ShaftBegin.y) + (shaftRadius*cos(j*dr)*axisnorm.y) + (shaftRadius*sin(j*dr)*axisnnorm.y), (ShaftBegin.z) + (shaftRadius*cos(j*dr)*axisnorm.z) + (shaftRadius*sin(j*dr)*axisnnorm.z)};
            
            c2 = {(ShaftEnd.x) + (shaftRadius*cos(j*dr)*axisnorm.x) + (shaftRadius*sin(j*dr)*axisnnorm.x), (ShaftEnd.y) + (shaftRadius*cos(j*dr)*axisnorm.y) + (shaftRadius*sin(j*dr)*axisnnorm.y), (ShaftEnd.z) + (shaftRadius*cos(j*dr)*axisnorm.z) + (shaftRadius*sin(j*dr)*axisnnorm.z)};

            c3 = {(ShaftBegin.x) + (shaftRadius*cos((j+1)*dr)*axisnorm.x) + (shaftRadius*sin((j+1)*dr)*axisnnorm.x), (ShaftBegin.y) + (shaftRadius*cos((j+1)*dr)*axisnorm.y) + (shaftRadius*sin((j+1)*dr)*axisnnorm.y), (ShaftBegin.z) + (shaftRadius*cos((j+1)*dr)*axisnorm.z) + (shaftRadius*sin((j+1)*dr)*axisnnorm.z)};
            
            c4 = {(ShaftEnd.x) + (shaftRadius*cos((j+1)*dr)*axisnorm.x) + (shaftRadius*sin((j+1)*dr)*axisnnorm.x), (ShaftEnd.y) + (shaftRadius*cos((j+1)*dr)*axisnorm.y) + (shaftRadius*sin((j+1)*dr)*axisnnorm.y), (ShaftEnd.z) + (shaftRadius*cos((j+1)*dr)*axisnorm.z) + (shaftRadius*sin((j+1)*dr)*axisnnorm.z)};

            fTriQuad(c1, c2, c3, c4, memoryData);

            SDFVec3 c1 = {(ShaftEnd.x) + (baseRadius*cos(j*dr)*axisnorm.x) + (baseRadius*sin(j*dr)*axisnnorm.x), (ShaftEnd.y) + (baseRadius*cos(j*dr)*axisnorm.y) + (baseRadius*sin(j*dr)*axisnnorm.y), (ShaftEnd.z) + (baseRadius*cos(j*dr)*axisnorm.z) + (baseRadius*sin(j*dr)*axisnnorm.z)};
            
            SDFVec3 c2 = {(ShaftTip.x) + (baseRadius*cos(j*dr)*axisnorm.x) + (baseRadius*sin(j*dr)*axisnnorm.x), (ShaftTip.y) + (baseRadius*cos(j*dr)*axisnorm.y) + (baseRadius*sin(j*dr)*axisnnorm.y), (ShaftTip.z) + (baseRadius*cos(j*dr)*axisnorm.z) + (baseRadius*sin(j*dr)*axisnnorm.z)};

            SDFVec3 c3 = {(ShaftEnd.x) + (tipRadius*cos((j+1)*dr)*axisnorm.x) + (tipRadius*sin((j+1)*dr)*axisnnorm.x), (ShaftEnd.y) + (tipRadius*cos((j+1)*dr)*axisnorm.y) + (tipRadius*sin((j+1)*dr)*axisnnorm.y), (ShaftEnd.z) + (tipRadius*cos((j+1)*dr)*axisnorm.z) + (tipRadius*sin((j+1)*dr)*axisnnorm.z)};
            
            SDFVec3 c4 = {(ShaftTip.x) + (tipRadius*cos((j+1)*dr)*axisnorm.x) + (tipRadius*sin((j+1)*dr)*axisnnorm.x), (ShaftTip.y) + (tipRadius*cos((j+1)*dr)*axisnorm.y) + (tipRadius*sin((j+1)*dr)*axisnnorm.y), (ShaftTip.z) + (tipRadius*cos((j+1)*dr)*axisnorm.z) + (tipRadius*sin((j+1)*dr)*axisnnorm.z)};

            fTriQuad(c1, c2, c3, c4, memoryData);
            //construct the basial triangles


        }




        const SDFVec3 Yaxis = Subtract(m_plane.TopLeft, m_plane.BottomLeft);
        const SDFVec3 YNorm = Normalize(Cross(Yaxis, m_plane.BottomLeft));
        const SDFVec3 YNNorm = Normalize(Cross(YNorm, Yaxis));

        





    }

    void ConstructBuffers()
    {

    }

    


    ~PlaneRenderer()
    {

    }


};



#endif