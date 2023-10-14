#include "Quadtree.h"
#include "QuadtreeHead.h"

struct Vec2
{
    float x,y;
};

struct Line
{
    Vec2 a;
    Vec2 b;

    LTXRect Bounding()
    {
        // r.x = a.x < b.x ? a.x : b.x;
        // r.y = a.y < b.y ? a.y : b.y;
        
        // r.z = a.x > b.x ? a.x : b.x;
        // r.w = a.y > b.y ? a.y : b.y;

        return {{a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y},{a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y}};
    }

    void Display()
    {
        printf("\\draw (%f,%f) -- (%f,%f);\n", a.x, a.y, b.x, b.y);
    }
};

int main()
{
    std::vector<Line> lines={
        {{-0.5,0.3},{-0.4,0.5}},
        {{0.5,0.3},{-0.2,0.5}},
        {{0.3,-0.3},{-0.2,-0.5}},
  
    };

    LTXRect r = {{-1, -1}, {1,1}};
    //r.Display();
    Quadtree<Line> Lines(r);
    for(int i = 0; i < lines.size(); i++)
    {
        Lines.insert(lines[i], lines[i].Bounding());
    }
    
    Lines.Display();
    
}