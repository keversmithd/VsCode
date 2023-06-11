#include "Chapter1ConvexHull.h"


int main()
{
    const plane Domain{{0.0, 0.0}, {1.0, 1.0}};
    std::vector<vec2> Set = SetInPlane(Domain, 10);

    DisplayVectorSet(Set);
    std::vector<vec2> CHull = ConvexHull(Set);
    
    DisplayVectorEdgeSet(CHull);
}