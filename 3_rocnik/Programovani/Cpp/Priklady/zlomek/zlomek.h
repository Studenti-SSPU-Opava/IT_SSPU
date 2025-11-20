//
// Created by student on 20.11.2025.
//

#ifndef DYNAMICKEPOLE_ZLOMEK_H
#define DYNAMICKEPOLE_ZLOMEK_H


class zlomek{
public:    
    zlomek();
    zlomek(int citatel, int jmenovatel);
    zlomek(zlomek &kopirka);
    ~zlomek();
    int getCitatel() const;
    int getJmenovatel() const;
    void setCitatel(int citatel);
    bool setJmenovatel(int jmenovatel);
    bool setZlomek(int citatel, int jmenovatel);
    float desetinne() const;
    bool prevrat();
    bool kraceni();
private:
    int citatel;
    int jmenovatel;
    void swap(int &a, int &b);
    int spolecnyDelitel(int a, int b);
};


#endif //DYNAMICKEPOLE_ZLOMEK_H
