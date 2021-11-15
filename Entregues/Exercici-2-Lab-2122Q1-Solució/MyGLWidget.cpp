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

MyGLWidget::~MyGLWidget() {}

void MyGLWidget::paintGL () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Homers
    for (i = 0; i < NUM_HOMERS; ++i) {
        homerTransform();
        glBindVertexArray (VAO_Homer);
        glDrawArrays(GL_TRIANGLES, 0, modelHomer.faces().size()*3);
        glBindVertexArray (0);
    }
    // Terra
    terraTransform();
    glBindVertexArray (VAO_Terra);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray (0);
}

void MyGLWidget::homerTransform () {
    float escala = 1.83/midaModelHomer;
    float rotacio;
    if (i <= 10) rotacio = float(36*i*(float(M_PI)/180));
    else rotacio = float(56*i*(float(M_PI)/180));
    //LL2GLWidget::homerTransform();
    glm::mat4 TG(1.0f);

    // Right/Left
    TG = glm::translate(TG, glm::vec3(5, 0, 5));
    TG = glm::rotate(TG, gir, glm::vec3(0, 1, 0));
    TG = glm::rotate(TG, rotacio, glm::vec3(0, 1, 0));
    TG = glm::translate(TG, glm::vec3(0, 0, -radi));
    TG = glm::scale(TG, glm::vec3(escala, escala, escala));
    TG = glm::translate(TG, -baseHomer);
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::iniciCamera() {
    center = glm::vec3(5, 0, 5);
    dist = 15;
    zfar = 30;
}

void MyGLWidget::viewTransform () {
    iniciCamera();
    
    obs2 = glm::vec3(5, 15, 5);
    vrp2 = glm::vec3(5, 0, 5);
    up2 = glm::vec3(0, 0, -1);

    glm::mat4 VM(1.0f);
    if (persp) {    
        VM = glm::translate(VM, glm::vec3(0.0, 0.0, -dist));
        VM = glm::rotate(VM, fAngleX, glm::vec3(1, 0, 0));
        VM = glm::rotate(VM, fAngleY, glm::vec3(0, 1, 0));
        VM = glm::translate(VM, -center);
    } else {
        VM = glm::lookAt(obs2, vrp2, up2);
    }

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &VM[0][0]);
}

void MyGLWidget::projectTransform () {
  glm::mat4 Proj(1.0f);
  if (persp) Proj = glm::perspective (fov, ra, znear, zfar);
  else Proj = glm::ortho (-7.0f, 7.0f, -7.0f, 7.0f, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_Plus : {
            ++NUM_HOMERS;
            if (NUM_HOMERS > 15) NUM_HOMERS = 15;
            break;
        }
        case Qt::Key_Minus : {
            --NUM_HOMERS;
            if (NUM_HOMERS < 1) NUM_HOMERS = 1;
            break;
        }
        case Qt::Key_Up : {
            radi += 0.5;
            if (radi > 5) radi = 5;
            break;
        }
        case Qt::Key_Down : {
            radi -= 0.5;
            if (radi < 1.5) radi = 1.5;
            break;
        }
        case Qt::Key_Left : {
            gir += 0.5;
            break;
        }
        case Qt::Key_Right : {
            gir -= 0.5;
            break;
        }
        case Qt::Key_C : {
            if (persp) persp = false;
            else persp = true;
            viewTransform();
            projectTransform();
            break;
        }
        case Qt::Key_R : {
            NUM_HOMERS = 10;
            gir = 0;
            radi = 4;
            persp = true;
            fAngleY = 0;
            fAngleX = float(45*(float(M_PI)/180));
            viewTransform();
            projectTransform();
            break;
        }
        default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e) {
  makeCurrent();
  if (DoingInteractive == ROTATE) {
        if (e->x() > xClick) fAngleY = fAngleY + (e->x() - xClick) * M_PI/ample;
        else if (e->x() < xClick) fAngleY = fAngleY + (e->x() - xClick) * M_PI/ample;

        if (e->y() > yClick) fAngleX = fAngleX + (e->y() - yClick) * M_PI/alt;
        else if (e->y() < yClick) fAngleX = fAngleX + (e->y() - yClick) * M_PI/alt;
  }
  viewTransform();

  xClick = e->x();
  yClick = e->y();

  update();
}