#include "MyLabel.h"

MyLabel::MyLabel(QWidget *parent=0):QLabel(parent) {}

void MyLabel::cami() {
    emit clean();
    setText("o");
    if(rand()%2 == 0) emit nl();
    else emit nr();
}

void MyLabel::esborra() {
    setText("-");
}