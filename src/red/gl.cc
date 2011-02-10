#include "red/gl.h"

#include "cinder/Camera.h"

using namespace red;
using namespace ci;

void red::clearGL(const ci::ColorA &color, bool clearDepthBuffer)
{
	glClearColor( color.r, color.g, color.b, color.a );
	if( clearDepthBuffer ) {
		glDepthMask( GL_TRUE );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
	else
		glClear( GL_COLOR_BUFFER_BIT );
}

GLES2::GLES2()
{
}

void GLES2::setModelView(const Camera &cam)
{
    mModelView = cam.getModelViewMatrix();
}

void GLES2::setProjection(const Camera &cam)
{
    mProjection = cam.getProjectionMatrix();
}

