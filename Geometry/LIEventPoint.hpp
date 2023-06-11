#ifndef LI_EVENT_POINT
#define LI_EVENT_POINT
#include "vectwo.hpp"
struct EventPoint
{
    line whole;
    vec2 part;
    
    private:
        friend std::ostream & operator<<(std::ostream &os, const EventPoint& p);
};

std::ostream & operator<<(std::ostream &os, const EventPoint& p)
{
    return os << "whole: " << "(" << p.whole.start.x << "," << p.whole.start.x << ")" << "--" << "(" << p.whole.end.x << "," << p.whole.end.y << ")";
}

struct EventPointHash {
    std::size_t operator()(const EventPoint& point) const {
        return ((point.whole.start.x + point.whole.start.y)+(point.whole.end.x + point.whole.end.y)*(point.part.x + point.part.y));
    }
};


bool operator==(const EventPoint lhs, const EventPoint rhs)
{
    return (lhs.whole.start.x == rhs.whole.start.x && lhs.whole.end.x == rhs.whole.end.x && lhs.whole.start.y == rhs.whole.start.y && lhs.whole.end.y == rhs.whole.end.y);
}

#endif