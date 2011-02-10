// Copyright (c) 2010 The Native Client SDK Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cube.h"
#include "red/Vbo.h"

#include <algorithm>

// #include "shader_util.h"
#include "transforms.h"

using namespace ci;
using namespace ci::gl;

namespace tumbler {

static const size_t kVertexCount = 24;
static const int kIndexCount = 36;

Cube::Cube() : width_(1), height_(1) {
}

Cube::~Cube() {
}

void Cube::PrepareOpenGL() {
  CreateShaders();
  CreateCube();
  glEnable(GL_DEPTH_TEST);
}

void Cube::Resize(int width, int height) {
  width_ = std::max(width, 1);
  height_ = std::max(height, 1);
  // Set the viewport
  glViewport(0, 0, width_, height_);

  // Update the perspective projection matrix with a 60 degree FOV.
  GLfloat aspect = static_cast<GLfloat>(width_) / static_cast<GLfloat>(height_);
  mCamera.setPerspective(30.0f, aspect, 0.1f, 1000.0f);
}

void Cube::Draw() {
  mGL.clear(ColorA(0.9, 0.9, 0.9, 1.0), true);

  // Compute a new model-view matrix, then use that to make the composite
  // model-view-projection matrix: MVP = MV . P.

  mCamera.setEyePoint(Vec3f(0, 0, 5.0f));
  mCamera.lookAt(Vec3f(0, 0, 0));

  //  init cube orientation
  Matrix44f transform = mOrientation.toMatrix44();
  Matrix44f camMatrix = mCamera.getProjectionMatrix() * mCamera.getModelViewMatrix();
  Matrix44f mvp = camMatrix * transform;

  mShader.bind();
  mShader.uniform("u_mvp", mvp);
  mCube.vertexAttribPointer(mShader, "a_position");
  mCube.vertexAttribPointer(mShader, "a_color");
  mCube.attrib("index").bind();
  glDrawElements(GL_TRIANGLES, kIndexCount, GL_UNSIGNED_SHORT, 0);

  mCube.unbind();
}

bool Cube::CreateShaders() 
{
  #include "shaders/f_red.glsl.h"
  #include "shaders/v_red.glsl.h"

  mShader = GlslProg(shader_v_red, shader_f_red);

  return true;
}

void Cube::CreateCube() {
  static const GLfloat cube_vertices[] = {
    // Vertex coordinates
    // Bottom
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    // Top
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    // Back
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    // Front
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    // Left
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    // Right
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f
  };

  static const GLfloat cube_colors[] = {
    // Color values

    // Bottom
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    // Top
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    // Back
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    // Front
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    // Left
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    // Right
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0
  };

  static const GLushort cube_indices[] = {
    // Bottom
    0, 2, 1,
    0, 3, 2,
    // Top
    4, 5, 6,
    4, 6, 7,
    // Back
    8, 9, 10,
    8, 10, 11,
    // Front
    12, 15, 14,
    12, 14, 13,
    // Left
    16, 17, 18,
    16, 18, 19,
    // Right
    20, 23, 22,
    20, 22, 21
  };

  // positions
  mCube.makeAttrib("a_position", GL_ARRAY_BUFFER, 3, GL_FLOAT, 3 * sizeof(GLfloat));
  mCube.attrib("a_position").bind();
  mCube.attrib("a_position").bufferData(kVertexCount * sizeof(GLfloat) * 3, cube_vertices, GL_STATIC_DRAW);

  // colors
  mCube.makeAttrib("a_color", GL_ARRAY_BUFFER, 3, GL_FLOAT, 3 * sizeof(GLfloat));
  mCube.attrib("a_color").bind();
  mCube.attrib("a_color").bufferData(kVertexCount * sizeof(GLfloat) * 3, cube_colors, GL_STATIC_DRAW);

  // index array
  mCube.makeAttrib("index", GL_ELEMENT_ARRAY_BUFFER);
  mCube.attrib("index").bind();
  mCube.attrib("index").bufferData(kIndexCount * sizeof(GLushort), cube_indices, GL_STATIC_DRAW);

  mCube.unbind();
}

}  // namespace tumbler
