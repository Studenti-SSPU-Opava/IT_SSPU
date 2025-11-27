
#include "zlomek.h"
#include <iostream>

zlomek::zlomek() : jmenovatel(1), citatel(1) {

}



zlomek::zlomek(int citatel, int jmenovatel) : jmenovatel(1), citatel(1) {

    if (jmenovatel == 0) {
        std::cout<< citatel << "/" << jmenovatel << " => Jmenovatel nemůže být nula. Nahrazuji zlomkem 1/1" << std::endl;
    } else{
        setZlomek(citatel, jmenovatel);
    }
}



zlomek::zlomek(zlomek &kopirka) : citatel(kopirka.getCitatel()), jmenovatel(kopirka.getJmenovatel()) {

}



zlomek::~zlomek() {

}



int zlomek::getCitatel() const { 
    return this->citatel; 
}



int zlomek::getJmenovatel() const { 
    return this->jmenovatel; 
}



void zlomek::setCitatel(int citatel) {
    this->citatel = citatel;    
}



bool zlomek::setJmenovatel(int jmenovatel) {
    if (jmenovatel == 0) {
        std::cout << "Jmenovatel nemůže být nula." << std::endl;
        return false;
    } else {
        this->jmenovatel = jmenovatel;
        return true;
    }
}



bool zlomek::setZlomek(int citatel, int jmenovatel) {
    if (setJmenovatel(jmenovatel)) {
        setCitatel(citatel);
        return true;
    } else {
        return false;
    }
}



float zlomek::desetinne() const {
    return (float) citatel / (float) jmenovatel; 
}


bool zlomek::prevrat() {
    if (getCitatel() != 0) {
        swap(citatel, jmenovatel);
        return true;
    } else {
        return false; 
    }
}



bool zlomek::kraceni() {
    if (this->citatel == 0) {
        int delitel = spolecnyDelitel(this->citatel, this->jmenovatel);
        this->jmenovatel /= delitel;
        this->citatel /= delitel;
        return true;
    }
}



void zlomek::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}



int zlomek::spolecnyDelitel(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a; 
}



std::ostream & operator<<(std::ostream &os, const zlomek &z) {
    os << z.getCitatel() << "/" << z.getJmenovatel() << ", " << z.desetinne() << std::endl;
    return os;
}