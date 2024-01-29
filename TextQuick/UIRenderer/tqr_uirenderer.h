#ifndef TQR_UI_RENDERER
#define TQR_UI_RENDERER

namespace tqr
{
    struct UIRenderer
    {
        UIRenderer()
        {

        }

        void* Paramters; //Meant to be like custom struct
        void (*UIRenderer::Draw)();
        void (*UIRenderer::UpdateGeometry)();

        ~UIRenderer()
        {

        }
    };
};

#endif