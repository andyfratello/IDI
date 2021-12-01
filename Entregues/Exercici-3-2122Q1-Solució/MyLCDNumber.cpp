#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent=0):QLCDNumber(parent) {
    total = 0;
}

void MyLCDNumber::suma() {
    ++total;
    display(total);
}

void MyLCDNumber::reinicia() {
    total = 0;
    display(total);
}