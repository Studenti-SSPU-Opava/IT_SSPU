//
// Created by student on 16.10.2025.
//

#ifndef BOD_BOD_H
#define BOD_BOD_H


class bod {
public:
    bod();
    bod(int x, int y);
    bod(const bod &jinyObjekt);
    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
    double vzdalenost(const bod &jinyBod) const;
    ~bod();
private:
    int x;
    int y;
};


#endif //BOD_BOD_H
