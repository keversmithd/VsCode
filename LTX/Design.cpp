
#include "headers/LTXStructures.h"

#include "LTXCurveList.h"


int main()
{

    float textwidth = 452.969;
    float textheight = 652.696;

    CurveList curveList({{-1000, -1000}, {1000, 1000}});

    float mountWidth = 40;
    float mountHeight = 20;
    float left = 72;
    float right = 72;

    LTXRect CenterMountWorkspace; CenterMountWorkspace.bottomLeft={(textwidth/2)-mountWidth/2,-mountHeight/2}; CenterMountWorkspace.topRight={(textwidth/2)+mountWidth/2, mountHeight/2};

    //CenterMountWorkspace.ReadNamed();

    LTXPoint AnchorPoint = {0,0};
    LTXPoint ControlPoint1 = {0.45, 0.15};
    LTXPoint EndPoint1 = {0.4, 0.45};
    LTXPoint ControlPoint2 = {0.35, 0.55};
    LTXPoint ControlPoint3 = {0.25, 0.5};
    LTXPoint EndPoint2 = {0.30, 0.45};
     

    LTXQuadraticBezier Curve1 = {AnchorPoint, ControlPoint1, EndPoint1, CenterMountWorkspace};

    
    LTXCubicBezier Curve2 = {EndPoint1, ControlPoint2, ControlPoint3, EndPoint2, CenterMountWorkspace};

    LTXPoint AXA = {CubicBounding(Curve2).topRight.x,CubicBounding(Curve2).bottomLeft.y};
    LTXPoint AXB = {CubicBounding(Curve2).topRight.x,CubicBounding(Curve2).topRight.y};

    Curve2.Draw();

    Curve2.reflect(AXA,AXB);

    Curve2.Draw();

    // curveList.append(Curve1);
    // curveList.append(Curve2);
    // curveList.RadiallyThickenCurrentCurve(90, 3);
    // curveList.RadiallyThickenCurrentCurve(360, 10);
    // //curveList.RotateThickenedPath(-90);
    // curveList.ReflectThickenPath({0,1});

    // curveList.read();






}