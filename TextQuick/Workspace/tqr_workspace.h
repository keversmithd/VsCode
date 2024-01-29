#ifndef TQR_WORKSPACE_H
#define TQR_WORKSPACE_H 

// #include <Vectors/tqr_vectors.h>
// #include <EventGrid/tqr_eventgrid.h>

#include "../Vectors/tqr_vectors.h"
#include "../EventGrid/tqr_eventgrid.h"
#include "../UIObject/tqr_uiobject.h"


namespace tqr{
    struct Workspace
    {
        private:
            tqr::EventGrid eventGrid;

        public:

        Workspace(tqr::CoordinatePlane workPlane)
        {
            //Set-Up event grid.
            eventGrid.Setup(workPlane.width, workPlane.height, 20, 20);

        }

        void Add(tqr::UIObject object)
        {


        }

    };
};

#endif
