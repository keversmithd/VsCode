#ifndef TQR_VECTORS_H
#define TQR_VECTORS_H 

#include <math.h>

namespace tqr{

    struct Vec2{
        float x,y;

        double length()
        {
            return sqrt(x*x + y*y);
        }
    };

    struct Vec3{

        private:
            float x,y,z;
        public:

        Vec3()
        {

        }

        double length()
        {
            return sqrt(x*x + y*y + z*z);
        }

        void divide(float value)
        {
            if(value == 0)
            {
                return;
            }
            x/=value;
            y/=value;
            z/=value;
        }

        Vec3(float x,  float y, float z)
        {
            
        }
    };

    struct Vec4{

    };

    #pragma region BOUND_ING_BOXES

    struct Rect
    {
        Vec2 bottomLeft;
        Vec2 topRight;

        Vec2 center()
        {
            float mx = bottomLeft.x + ((topRight.x - bottomLeft.x)/2);
            float my = bottomLeft.y + ((topRight.y - bottomLeft.y)/2);

            return {mx,my};
        }

        void ReadNamed()
        {
            char r1[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
            char r2[2] = {(char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a')};
        }

        void Display()
        {
        }

    };

    bool ContainedInBoundingArea(const Rect Subject, const Rect Area)
    {
        return ((Subject.bottomLeft.x >= Area.bottomLeft.x && Subject.bottomLeft.x <= Area.topRight.x) &&
        (Subject.bottomLeft.y >= Area.bottomLeft.y && Subject.bottomLeft.y <= Area.topRight.y));
    }

    bool IntersectsBoundingArea(const Rect Subject, const Rect Area)
    {

        return ((Subject.bottomLeft.x >= Area.bottomLeft.x) && (Subject.bottomLeft.x <= Area.topRight.x) || (Subject.topRight.x >= Area.bottomLeft.x) && (Subject.bottomLeft.x <= Area.topRight.x)) 
        && ((Subject.bottomLeft.y >= Area.bottomLeft.y) && (Subject.bottomLeft.y <= Area.topRight.y) || (Subject.topRight.y >= Area.bottomLeft.y) && (Subject.bottomLeft.y <= Area.topRight.y));

    }

    bool ContainedInBoundingArea(const Vec2 Subject, const Rect Area)
    {
        return (Subject.x >= Area.bottomLeft.x && Subject.x <= Area.topRight.x) && (Subject.y >= Area.bottomLeft.y && Subject.y <= Area.topRight.y);
    }
 

    #pragma endregion

    #ifndef COORDINATE_PLANE
    #define COORDINATE_PLANE 

    struct CoordinatePlane
    {
        private:

        public:
        Vec3 x;
        Vec3 y;
        double width;
        double height;

        CoordinatePlane(Vec3 x, Vec3 y) 
        {
            width = x.length();
            height = y.length();
            x.divide(width);
            y.divide(height);
        }

        CoordinatePlane(Vec3 x, Vec3 y, float width, float height)
        {
            
        }

        ~CoordinatePlane()
        {

        }
    };

    #endif

};

#endif