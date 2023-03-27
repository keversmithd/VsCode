#include <SDFArchive.h>
#include <array>
#include <memory>
class SDFGPTMeshTree {
public:
    SDFGPTMeshTree(const SDFBoundingVolume& boundingVolume) 
        : boundingVolume(boundingVolume), isLeaf(true) {}

    bool insertFace(const SDFFace& face) {
        if (!IntersectsThisBoundingVolumeBooleanT(GetVolumeOfFace(face), boundingVolume)) {
            return false;
        }
        
        if (isLeaf) {
            containedFaces.push_back(face);
            if (containedFaces.size() > MAX_FACES_PER_LEAF) {
                subdivide();
            }
            return true;
        } else {
            bool inserted = false;
            for (int i = 0; i < 8; i++) {
                if (children[i]->insertFace(face)) {
                    inserted = true;
                }
            }
            return inserted;
        }
    }

private:
    static const int MAX_FACES_PER_LEAF = 10;

    SDFBoundingVolume boundingVolume;
    bool isLeaf;
    std::vector<SDFFace> containedFaces;
    std::array<std::unique_ptr<SDFGPTMeshTree>, 8> children;

    SDFBoundingVolume SDFGPTMeshTree::getSubVolume(int childIndex) const
    {
        SDFBoundingVolume parentVolume = boundingVolume;
    

        return parentVolume;
    }

    void subdivide() {
        for (int i = 0; i < 8; i++) {
            SDFBoundingVolume childVolume = getSubVolume(i);
            children[i] = std::make_unique<SDFGPTMeshTree>(childVolume);
        }

        for (const auto& face : containedFaces) {
            for (int i = 0; i < 8; i++) {
                if (children[i]->insertFace(face)) {
                    break;
                }
            }
        }

        containedFaces.clear();
        isLeaf = false;
    }
};