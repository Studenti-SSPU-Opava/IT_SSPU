//
// Created by adamb on 26.02.2026.
//

#include "grc.h"
#include <string>
#include <iostream>

grc::grc() {
    den = 28;
    mesic = 12;
    rok = 2010;
    triCisla = 987;
    jeZena = false;
}

grc::~grc() {
}

std::string grc::vygenerujRC(int d, int m, int r, int t) {
    long long rc = 0;
    int zbytek;
    do {
        d = den;
        r = (rok%100);
        t = triCisla;
        if (jeZena == true) {
            m = mesic +50;
        } else {
            m = mesic;
        }
        rc = r*10000000 + m*100000 + d*1000 + t;
        zbytek = rc%11;
        if (zbytek == 10) {
            t = (rand()%1000);
            triCisla = t; //proti zacyklovani
        }
    }while (zbytek == 10);

    rc = (rc*10) + zbytek;
    return std::to_string(rc);
}

bool grc::get_d(int d){
    den = d;
    if (den > 31) {
        return false;
    } else if (den ==31 && (mesic == 1 || mesic == 3 || mesic == 5 || mesic == 7 || mesic == 8 || mesic == 10 || mesic == 12)){
        return true;
    } else if (den ==30 && (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11)){
        return true;
    } else if (den == 29 && mesic == 2 && (((rok % 4 == 0) && (rok % 100 != 0)) || (rok % 400 == 0))) {
        return true;
    } else if (den == 28 && mesic == 2) {
        return true;
    } else if (den >= 1 && den <=28){
        return true;
    } else {
        return false;
    }
}

bool grc::get_m(int m) {
    mesic = m;
    if (mesic <= 0 || mesic > 12) {
        return false;
    } else {
        return true;
    }
}

bool grc::get_r(int r) {
    rok = r;
    if (rok < 1954 || rok > 2053) {
        return false;
    } else {
        return true;
    }
}

bool grc::get_t(int t) {
    triCisla = t;
    if (triCisla <= 0 || triCisla > 1000) {
        return false;
    } else {
        return true;
    }
}

bool grc::get_p(int p) {
    std::cout << "Zadejte cislo 0 (muz) nebo 1 (zena):" << std::endl;
    std::cin >> p;
    if (p == 1) {
        jeZena = true;
        return true;
    } else if (p == 0){
        jeZena = false;
        return true;
    } else {
        return false;
    }
}
