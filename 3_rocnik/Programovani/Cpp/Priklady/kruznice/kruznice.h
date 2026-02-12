//
// Created by student on 23.10.2025.
//

#ifndef KRUZNICE_KRUZNICE_H
#define KRUZNICE_KRUZNICE_H


class kruznice {
public:
    kruznice();

    kruznice(float r);

    kruznice(const kruznice &jinyObjekt);

    ~kruznice();

    float get_r() const;

    bool set_r(float r);

    double prumer() const;

    double obsah() const;

    double obvod() const;

private:
    float r;
};


#endif //KRUZNICE_KRUZNICE_H
