#ifndef DISTANCE_VOLUME_CENTER
#define DISTANCE_VOLUME_CENTER

#include "LearnOpenglHelper.h"
#include "FGeom.h"
#include "Camera.h"


struct DistanceVolumeCenter;

struct DistanceVolumeNodes
{

    DistanceVolumeCenter* admin;

    DistanceVolumeNodes* parent;
    DistanceVolumeNodes* left;
    DistanceVolumeNodes* right;

    SDFBoundingVolume volume;
    SDFVec3 translation;
    SDFVec3 rotation;
    SDFVec3 scale;
    
    DistanceVolumeNodes() : admin(nullptr), left(nullptr), right(nullptr), parent(nullptr)
    {

    }

    void UpdateSelf() 
    {
        admin->remove(this);
    }
};

struct DistanceVolumeCenter
{
    private:
        DistanceVolumeNodes* root;
        int NumberOfNodes;
    public:
        DistanceVolumeCenter() : root(nullptr), NumberOfNodes(0)
        {

        }

        void remove(DistanceVolumeNodes* node)
        {
            //find successor
            
        }

        void insert(DistanceVolumeNodes node)
        {

            if(root == nullptr)
            {
                DistanceVolumeNodes* insertable = new DistanceVolumeNodes(node);
                insertable->admin = this;

            }

        }
    

};


#endif