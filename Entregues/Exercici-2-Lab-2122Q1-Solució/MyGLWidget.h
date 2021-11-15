#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void homerTransform();
    virtual void viewTransform();
    virtual void projectTransform ();
    virtual void iniciCamera();
    //virtual void initializeGL();
    virtual void keyPressEvent (QKeyEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    //virtual void mousePressEvent (QMouseEvent *event);

  private:
    int printOglError(const char file[], int line, const char func[]);

  int i, NUM_HOMERS = 10;
  float dist, radi = 4, gir = 0;
  bool persp = true;

  float fAngleY = 0;
  float fAngleX = float(45*(float(M_PI)/180));

  glm::vec3 obs2, vrp2, up2;
  glm::vec3 center;

};
