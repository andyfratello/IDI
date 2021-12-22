// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void keyPressEvent(QKeyEvent* event);
    void carregaShaders();
    void initializeGL();
    void modelTransformPatricio();
    void modelTransformFocus();
  private:
    int printOglError(const char file[], int line, const char func[]);

  //int(rotacio*float(float(180)/float(M_PI)))%90 >= 
  GLuint colFocusLocC, posFocusLocC, colFocusLocE, posFocusLocE, colFocusLocP, posFocusLocP, transFocusLoc;
  glm::vec3 colFocusC, posFocusC, colFocusE, posFocusE, colFocusP, posFocusP;
  
  float focusZ = 0.0;
  float focusX = 0.0;

  float rotacio = 0.0; 
  float posX = 5.0;
  float posZ = 2.0;

  bool focus1 = false;
  bool focus2 = false;
  bool focus3 = false;

};
