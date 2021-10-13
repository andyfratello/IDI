#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void creaBuffersTronc();
    void creaBuffersCopa();
    void carregaShaders();

    void modelTransformArbre(const glm::vec3& posicio, float mida);
    
    // program
    QOpenGLShaderProgram *program;
    // attribute locations
    GLuint vertexLoc;
    // uniform locations
    // ...

    // VAOs
    GLuint VAOCopa, VAOTronc;

    // viewport
    GLint ample, alt;

    // info model arbre
    const float offsetBase = 0; // Trobeu el valor correcte
    const float midaModel  = 1; // Trobeu el valor correcte

    // info instancies
    static const int NUM_ARBRES = 12;
    static const float midaArbre[NUM_ARBRES];
    static const glm::vec3 posicioArbre[NUM_ARBRES];
    static const glm::vec3 colorArbre[NUM_ARBRES];
    static const glm::vec3 colorTronc;
};
