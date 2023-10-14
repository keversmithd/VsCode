#ifndef GEOM_TRIANGULATION
#define GEOM_TRIANGULATION 

#include "../Chapter2Dcel/DCEL.h"
#include "QuadTree.h"



struct LineWithBox
{
    line impl;
    rect Bounding;

    LineWithBox(line i) : impl(i)
    {
        Bounding = i.bounding();
    }

    void Display()
    {
        impl.Display();
    }
};





int main()
{
    DCEL Polygon;
    DCEL Triangulation;
    
    
    std::vector<vec2> vertices = {
        {55.000000,494.000000},       
        {59.400005,445.776001},       
        {75.320000,399.328033},       
        {106.839996,359.791992},      
        {158.040009,332.304016},
        {233.000000,322.000000},
        {233.000000,322.000000},
        {363.000000,322.000000},
        {363.000000,322.000000},
        {396.592010,317.280029},
        {420.296021,303.920013},
        {435.503967,283.119995},
        {443.608032,256.080017},
        {446.000000,224.000000},
        {446.000000,224.000000},
        {446.000000,156.000000},
        {446.000000,156.000000},
        {436.520050,114.768005},
        {412.400024,88.464005},
        {380.119995,73.776001},
        {346.160004,67.391998},
        {317.000000,66.000000},
        {317.000000,66.000000},
        {260.272003,66.624001},
        {204.216034,68.112007},
        {152.623993,69.888000},
        {109.287994,71.376007},
        {78.000000,72.000000},
        {78.000000,72.000000},
        {78.000000,17.000000},
        {78.000000,17.000000},
        {99.200012,14.440001},
        {129.520004,10.680001},
        {165.839996,6.199999},
        {205.040009,1.480000},
        {244.000000,-3.000000},
        {244.000000,-3.000000},
        {244.000000,-90.000000},
        {244.000000,-90.000000},
        {302.000000,-90.000000},
        {302.000000,-90.000000},
        {302.000000,-8.000000},
        {302.000000,-8.000000},
        {365.760040,-6.496000},
        {424.960022,7.392000},
        {474.079987,36.928001},
        {507.600037,85.375999},
        {520.000000,156.000000},
        {520.000000,156.000000},
        {520.000000,224.000000},
        {520.000000,224.000000},
        {516.920044,273.376007},
        {504.480042,319.968018},
        {477.880005,359.071991},
        {432.320007,385.984009},
        {363.000000,396.000000},
        {363.000000,396.000000},
        {233.000000,396.000000},
        {233.000000,396.000000},
        {202.984009,398.512054},
        {174.792007,407.456024},
        {151.207993,424.944000},
        {135.016006,453.088013},
        {129.000000,494.000000},
        {129.000000,494.000000},
        {129.000000,560.000000},
        {129.000000,560.000000},
        {135.176010,607.687988},
        {152.488007,638.864075},
        {179.112000,656.695984},
        {213.224014,664.351990},
        {253.000000,665.000000},
        {253.000000,665.000000},
        {273.160034,664.064026},
        {323.080017,661.832031},
        {386.920013,659.167969},
        {448.840027,656.936035},
        {493.000000,656.000000},
        {493.000000,656.000000},
        {493.000000,714.000000},
        {493.000000,714.000000},
        {463.824036,717.240051},
        {426.632019,721.679993},
        {384.927979,726.599976},
        {342.216003,731.280029},
        {302.000000,735.000000},
        {302.000000,735.000000},
        {302.000000,824.000000},
        {302.000000,824.000000},
        {244.000000,824.000000},
        {244.000000,824.000000},
        {244.000000,738.000000},
        {244.000000,738.000000},
        {183.448013,732.256042},
        {131.824020,715.088074},
        {91.575989,682.992004},
        {65.152000,632.463989},
        {55.000000,560.000000},
        {55.000000,560.000000},
        {55.000000,494.000000},
    };

    vec2 bottomLeftMost = {(float)INT_MAX, (float)INT_MAX};
    DCELVec* bottomLeftMostPointer = nullptr;
    rect BoundingContainer;

    //std::cout << "\n\n\n\n\n\n\n\n new Entry \n\n\n\n\n\n\n\n" << std::endl;
    
    // Add edges based on the vertices to form the polygon
    for(size_t i = 0; i < vertices.size(); i++)
    {
        vec2 a = vertices[i];
        
        BoundingContainer.IncrementBound(a);

        

        Polygon.AppendPoint(a);

        if(a.x < bottomLeftMost.x)
        {   
            bottomLeftMost = a;
            bottomLeftMostPointer = Polygon.verticies.back();
        }

    }

    Polygon.MakeLoop();
    //BoundingContainer.Display();
    //bottomLeftMost.display();
    //Quadtree<LineWithBox> IntersectionMap(BoundingContainer);

    
    // for(size_t i = 0; i < vertices.size()-1; i++)
    // {
    //     vec2 a = vertices[i];
    //     vec2 b = vertices[i+1];
    //     LineWithBox l({a,b});
        
    //     IntersectionMap.insert(l, l.Bounding);
    // }

    

    DCELVec* Origin = bottomLeftMostPointer;

    
    DCELVec* U = Origin;
    DCELVec* V = U->incident->next->origin;

    

    while(U != nullptr && V != nullptr && V != Origin)
    {
        U->render();
        V->render();

        U = V;
        V = V->incident->next->origin;

        //First u-p that does not intersect,is bad
        //First u-p in range of non intersecting u-ps, that has most horizontal line
        //Move x-steps to the right in the quadtree or grid, for best option. seems better but not work in all cases
        //need to figure out when to jump back and go opposite way, once already triangulated area.



    }
    

    


    
    

    std::cout << "driving" << std::endl;
}

#endif