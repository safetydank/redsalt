// Copyright 2010 The Native Client SDK Authors. All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#ifndef EXAMPLES_TUMBLER_CUBE_H_
#define EXAMPLES_TUMBLER_CUBE_H_

#include "red/gl.h"
#include "red/Vbo.h"
#include "red/GlslProg.h"

#include "cinder/Camera.h"
#include "cinder/Quaternion.h"

#include "basic_macros.h"

namespace tumbler {

// The Cube class provides a place to implement 3D rendering.  It has a 
// frame that it occupies in a browser window.
class Cube {
 public:
  Cube();
  ~Cube();
  
  // Called once when a new RenderContext is first bound to the view.  The
  // bound context is guaranteed to be current and valid before calling this
  // method.
  void PrepareOpenGL();

  // Called whenever the size of the browser view changes.  This method is
  // called at least once when the view is first made visible.  Clamps the
  // sizes to 1.
  void Resize(int width, int height);

  // Called every time the view need to be drawn.  The bound context is
  // guaranteed to be current and valid before this method is called.  The
  // visible portion of the context is flushed to the browser after this
  // method returns.
  void Draw();

  // Accessor for width and height.  To change these, call Resize.
  const int width() const { return width_; }
  const int height() const { return height_; }

  // Accessor/mutator for the camera orientation.
  void GetOrientation(float* orientation) const {
    orientation[0] = static_cast<float>(mOrientation.v.x);
    orientation[1] = static_cast<float>(mOrientation.v.y);
    orientation[2] = static_cast<float>(mOrientation.v.z);
    orientation[3] = static_cast<float>(mOrientation.w);
  }
  void SetOrientation(const float* orientation) {
    mOrientation.v.x = static_cast<GLfloat>(orientation[0]);
    mOrientation.v.y = static_cast<GLfloat>(orientation[1]);
    mOrientation.v.z = static_cast<GLfloat>(orientation[2]);
    mOrientation.w = static_cast<GLfloat>(orientation[3]);
  }

 private:
  // Create the shaders used to draw the cube, and link them into a program.
  // Initializes |shader_progam_object_|, |position_loction_| and
  // |mvp_location_|.
  bool CreateShaders();

  // Generates a cube as a series of GL_TRIANGLE_STRIPs, and initializes
  // |index_count_| to the number of indices in the index list used as a VBO.
  // Creates the |vbo_ids_| required for the vertex and index data and uploads
  // the the VBO data.
  void CreateCube();

  int width_;
  int height_;

  // GLuint cube_vbos_[3];

  // PORTING TO CINDER
  cinder::CameraPersp mCamera;
  cinder::Quatf mOrientation;

  // OpenGL interface
  red::GLES2 mGL;
  cinder::gl::GlslProg mShader;
  cinder::gl::VbosMesh mCube;

  DISALLOW_COPY_AND_ASSIGN(Cube);
};

}  // namespace tumbler

#endif  // EXAMPLES_TUMBLER_CUBE_H_
