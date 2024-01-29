#ifndef UI_OBJECT
#define UI_OBJECT 

#include "../Vectors/tqr_vectors.h"

namespace tqr
{
    struct UIObject{

    private:
        tqr::Rect* boundingBox;
    public:
        UIObject()
        {
            boundingBox = new tqr::Rect();
        }
        void(*UIObject::mOnHover)();
        void(*UIObject::mOnClick)();
        void(*UIObject::mOnUpdate)();
    };
};



#endif