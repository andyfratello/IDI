// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::modelTransformPatricio() {
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(posX, 0, posZ));
  TG = glm::rotate(TG, rotacio, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::translate(TG, -centreBasePatr);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformFocus() {
  glm::mat4 TGfocus(1.0f);
  TGfocus = glm::translate(TGfocus, glm::vec3(5.0+focusX, 1.5, 2.0+focusZ));
  TGfocus = glm::rotate(TGfocus, rotacio, glm::vec3(0.0, 1.0, 0.0));
  TGfocus = glm::translate(TGfocus, glm::vec3(-1.5, 0.0, 0.0));
  glUniformMatrix4fv (transFocusLoc, 1, GL_FALSE, &TGfocus[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {

  case Qt::Key_Right:
    ++posX;
    ++focusX;
    if (posX > 9) {
      posX = 9;
      --focusX;
    }
    break;

  case Qt::Key_Left:
    --posX;
    --focusX;
    if (posX < 1) {
      posX = 1;
      ++focusX;
    }
    break;

  case Qt::Key_Down:
    ++posZ;
    ++focusZ;
    if (posZ > 9) {
      posZ = 9;
      --focusZ;
    }    
    break;

  case Qt::Key_Up:
    --posZ;
    --focusZ;
    if (posZ < 1) {
      posZ = 1;
      ++focusZ;
    }
    break;

  case Qt::Key_R:
    rotacio += float(45*(float(M_PI)/180));
    break;

  case Qt::Key_C:
    if (focus1) focus1 = false;
    else focus1 = true;

    if (not focus1) colFocusC = glm::vec3(0.9, 0.2, 0.2);
    else colFocusC = glm::vec3(0.0, 0.0, 0.0);
    glUniform3fv(colFocusLocC, 1, &colFocusC[0]);
    break;

  case Qt::Key_E:
    if (focus2) focus2 = false;
    else focus2 = true;
   
    if (not focus2) colFocusE = glm::vec3(0.2, 0.9, 0.2);
    else colFocusE = glm::vec3(0.0, 0.0, 0.0);
    glUniform3fv(colFocusLocE, 1, &colFocusE[0]);
    break;

  case Qt::Key_P:
    if (focus3) focus3 = false;
    else focus3 = true;
   
    if (not focus3) colFocusP = glm::vec3(0.2, 0.2, 0.9);
    else colFocusP = glm::vec3(0.0, 0.0, 0.0);
    glUniform3fv(colFocusLocP, 1, &colFocusP[0]);
    break;

  default: LL4GLWidget::keyPressEvent(event); break;
  }
  modelTransformFocus();
  update();
}

void MyGLWidget::carregaShaders() {
    LL4GLWidget::carregaShaders();
    colFocusLocC = glGetUniformLocation(program->programId(), "colFocusC");
    posFocusLocC = glGetUniformLocation(program->programId(), "posFocusC");
    colFocusLocE = glGetUniformLocation(program->programId(), "colFocusE");
    posFocusLocE = glGetUniformLocation(program->programId(), "posFocusE");
    colFocusLocP = glGetUniformLocation(program->programId(), "colFocusP");
    posFocusLocP = glGetUniformLocation(program->programId(), "posFocusP");
    transFocusLoc = glGetUniformLocation (program->programId(), "TGfocus");
}

void MyGLWidget::initializeGL() {
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();
  
  posFocusC = glm::vec3(0.0, 0.0, 0.0);
  colFocusC = glm::vec3(0.9, 0.2, 0.2);
  glUniform3fv(posFocusLocC, 1, &posFocusC[0]);
  glUniform3fv(colFocusLocC, 1, &colFocusC[0]);

  posFocusE = glm::vec3(8.0, 3.0, 2.0);
  colFocusE = glm::vec3(0.2, 0.9, 0.2);
  glUniform3fv(posFocusLocE, 1, &posFocusE[0]);
  glUniform3fv(colFocusLocE, 1, &colFocusE[0]);

  posFocusP = glm::vec3(focusX, 0.0, focusZ);
  //posFocusP = glm::vec3(centreBasePatr[0], centreBasePatr[1]/2, 1.0);
  colFocusP = glm::vec3(0.2, 0.2, 0.9);
  glUniform3fv(posFocusLocP, 1, &posFocusP[0]);
  glUniform3fv(colFocusLocP, 1, &colFocusP[0]);

  modelTransformFocus();
  iniEscena();
  iniCamera();
}
