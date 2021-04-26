#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <string_view>

#include "abcg.hpp"
#include "model.hpp"
#include "trackball.hpp"
#include "camera.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  int m_viewportWidth{};
  int m_viewportHeight{};

  Model m_model;
  int m_trianglesToDraw{};

  Camera m_camera;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};


  TrackBall m_trackBallModel;
  TrackBall m_trackBallLight;
  float m_zoom{};

  glm::vec3 m_eyePosition{0,0,1.0f};
  glm::mat4 m_modelMatrix{1.0f};
  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projMatrix{1.0f};

  // Shaders
  const std::vector<const char*> m_shaderNames{
      "cubereflect", "cuberefract", "normalmapping", "texture", "blinnphong",
      "phong",       "gouraud",     "normal",        "depth"};
  std::vector<GLuint> m_programs;
  int m_currentProgramIndex{};

  // Mapping mode
  // 0: triplanar; 1: cylindrical; 2: spherical; 3: from mesh
  int m_mappingMode{};

  // Light and material properties
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka;
  glm::vec4 m_Kd;
  glm::vec4 m_Ks;
  float m_shininess{};

  // Skybox
  const std::string m_skyShaderName{"skybox"};
  GLuint m_skyVAO{};
  GLuint m_skyVBO{};
  GLuint m_skyProgram{};

  // clang-format off
  const std::array<glm::vec3, 36>  m_skyPositions{
    // Front
    glm::vec3{-25, -25, +25}, glm::vec3{+25, -25, +25}, glm::vec3{+25, +25, +25},
    glm::vec3{-25, -25, +25}, glm::vec3{+25, +25, +25}, glm::vec3{-25, +25, +25},
    // Back
    glm::vec3{+25, -25, -25}, glm::vec3{-25, -25, -25}, glm::vec3{-25, +25, -25},
    glm::vec3{+25, -25, -25}, glm::vec3{-25, +25, -25}, glm::vec3{+25, +25, -25},
    // Right
    glm::vec3{+25, -25, -25}, glm::vec3{+25, +25, -25}, glm::vec3{+25, +25, +25},
    glm::vec3{+25, -25, -25}, glm::vec3{+25, +25, +25}, glm::vec3{+25, -25, +25},
    // Left
    glm::vec3{-25, -25, +25}, glm::vec3{-25, +25, +25}, glm::vec3{-25, +25, -25},
    glm::vec3{-25, -25, +25}, glm::vec3{-25, +25, -25}, glm::vec3{-25, -25, -25},
    // Top
    glm::vec3{-25, +25, +25}, glm::vec3{+25, +25, +25}, glm::vec3{+25, +25, -25},
    glm::vec3{-25, +25, +25}, glm::vec3{+25, +25, -25}, glm::vec3{-25, +25, -25},
    // Bottom
    glm::vec3{-25, -25, -25}, glm::vec3{+25, -25, -25}, glm::vec3{+25, -25, +25},
    glm::vec3{-25, -25, -25}, glm::vec3{+25, -25, +25}, glm::vec3{-25, -25, +25}
  };
  // clang-format on

  void initializeSkybox();
  void renderSkybox();
  void terminateSkybox();
  void loadModel(std::string_view path);
  void update();
};

#endif