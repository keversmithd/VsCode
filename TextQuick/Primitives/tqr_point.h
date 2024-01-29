#ifndef TQR_POINT_H
#define TQR_POINT_H 

#include "../UIObject/tqr_uiobject.h"

namespace tqr
{
    struct Point : UIObject
    {

        Point()
        {
            mOnClick = OnClick;
            mOnHover = OnHover;
            mOnUpdate = OnUpdate;
        }

        

        void OnHover()
        {

        }
        void OnClick()
        {

        }
        void OnUpdate()
        {

        }

        


    };
};

#endif