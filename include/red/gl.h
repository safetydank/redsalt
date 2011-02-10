#ifndef RED_GL_H
#define RED_GL_H

#include <GLES2/gl2.h>

#include "cinder/Quaternion.h"
#include "cinder/Matrix.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Rect.h"

#include <boost/smart_ptr.hpp>
using boost::shared_ptr;

namespace cinder {
    class Camera;
}

namespace red {

//  common functions
void clearGL(const ci::ColorA &color, bool clearDepthBuffer);

/**
  *  High level interface to OpenGL
  */
template <typename GLIMPL>
class RedGL
{
public:
    RedGL() { }
    ~RedGL() { }

    void clear(const ci::ColorA &color, bool clearDepthBuffer) {
        clearGL(color, clearDepthBuffer);
    }

    void setModelView(const ci::Camera &cam)  { 
        static_cast<GLIMPL*>(this)->setModelView(cam); 
    }

    void setProjection(const ci::Camera &cam) { 
        static_cast<GLIMPL*>(this)->setProjection(cam); 
    }

    void setMatrices(const ci::Camera &cam) {
        setModelView(cam);
        setProjection(cam);
    }
};

/**
  * Implementation of OpenGL ES 2.0 interface
  */
class GLES2 : public RedGL<GLES2>
{
public:
    GLES2();
    ~GLES2() { }

    void setModelView(const ci::Camera &cam);
    void setProjection(const ci::Camera &cam);

private:
    ci::Matrix44f mModelView;
    ci::Matrix44f mProjection;
};

}
#endif
