#ifndef TQR_EVENT_GRID_H
#define TQR_EVENT_GRID_H 

#include "../UIObject/tqr_uiobject.h"
#include <vector>
#include <list>

namespace tqr
{
    struct EventGrid
    {   
        private:
            std::vector<std::vector<std::list<UIObject>>> eventGrid;
            
        public:

        EventGrid()
        {

        }

        EventGrid( float width, float height, int xdim, int ydim )
        {
            eventGrid.reserve(xdim);

            for(int i = 0; i < xdim; i++)
            {
                eventGrid[i].reserve(ydim);
            }
        }

        void Setup( float width, float height, int xdim, int ydim )
        {
            eventGrid.reserve(xdim);

            for(int i = 0; i < xdim; i++)
            {
                eventGrid[i].reserve(ydim);
            }
        }

        void Add(const UIObject& Object)
        {
          //std::list<UIObject>::iterator it;


          
        }

        ~EventGrid()
        {

        }
    };

};

#endif