//
// Created by adamb on 26.02.2026.
//

#ifndef GENERATORRODNEHOCISLA_GRC_H
#define GENERATORRODNEHOCISLA_GRC_H
#include <string>


class grc {
public:
    grc();

    ~grc();

    std::string vygenerujRC(int d, int m, int r, int t);

    bool get_r(int r);

    bool get_m(int m);

    bool get_d(int d);

    bool get_t(int t);

    bool get_p(int p);
private:
    int den;
    int mesic;
    int rok;
    int triCisla;

    bool jeZena;
};


#endif //GENERATORRODNEHOCISLA_GRC_H
