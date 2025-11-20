//
// Created by student on 23.10.2025.
//

#include "kruznice.h"
#include <cmath>

kruznice::kruznice() : r(1) {

}

kruznice::kruznice(float r) {
    if (r <= 0) {
        r = 1;
    } else {
        this->r = r;
    }

}

float kruznice::get_r() const {
    return this -> r;
}

kruznice::~kruznice() {

}

double kruznice::prumer() const {
    return this -> r*2;
}

double kruznice::obsah() const {
    return M_PI* pow(this ->r, 2);
}

double kruznice::obvod() const {
    return M_PI * this ->r * 2;
}

kruznice::kruznice(const kruznice &jinyObjekt):r(jinyObjekt.get_r()) {

}

bool kruznice::set_r(float r) {
    if (r > 0){
        this -> r = r;
        return true;
    } else{
        return false;
    }
}
