//
// Created by student on 16.10.2025.
//



#include "bod.h"
#include <cmath>

//výchozí konstruktor
bod::bod():x(0),y(0) {
    //popřípadě se dá použít:
    //this -> x = 0;
    //this -> y = 0;
}

bod::bod(int x, int y) {
    this -> x = x;
    this -> y = y;
}

bod::bod(const bod &jinyObjekt) {

}

int bod::get_x() const {
    return this -> x;
}

int bod::get_y() const {
    return this -> y;
}

void bod::set_x(int x) {
    this -> x = x;
}

void bod::set_y(int y) {
    this -> y = y;
}

double bod::vzdalenost(const bod &jinyBod) const {
    double z = 0;
    z = sqrt(
            pow(this -> x - jinyBod.get_x(), 2)+
            pow(this -> y - jinyBod.get_y(), 2)
            );

    return z;
}

bod::~bod() {

}
