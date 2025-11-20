// Skeleton implementations for zlomek class.
// All methods have empty bodies or placeholder return values.
// Logic to be implemented later.

#include "zlomek.h"

zlomek::zlomek() : jmenovatel(1), citatel(1) {

}
zlomek::zlomek(int citatel, int jmenovatel) {

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
        return false;
    } else {
        this->jmenovatel = jmenovatel;
        return true;
    }
}
bool zlomek::setZlomek(int citatel, int jmenovatel) {

return false; 
}
float zlomek::desetinne() const {

return 0.0f; 
}
bool zlomek::prevrat() {

return false; 
}
bool zlomek::kraceni() {

return false; 
}

void zlomek::swap(int &a, int &b) {

}
int zlomek::spolecnyDelitel(int a, int b) {

return 0; 
}
