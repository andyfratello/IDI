#include <QApplication>
#include "Galton.h"

int main (int argc, char **argv) 
{
  QApplication a(argc, argv);
  Galton form;
  form.show();
  a.exec ();
  return 0;
}

