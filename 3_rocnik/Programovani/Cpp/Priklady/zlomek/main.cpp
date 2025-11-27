#include <iostream>
#include "zlomek.h"



int main() {
    zlomek zlomek1 = zlomek(3, 4);
    zlomek zlomek2 = zlomek(2, 5);
    zlomek zlomek3 = zlomek(0, 1);
    zlomek zlomek4 = zlomek(5, 0); // Invalid denominator test
    std::cout << zlomek1;
    std::cout << zlomek2;
    std::cout << zlomek3;
    std::cout << zlomek4; // Should handle invalid case



}