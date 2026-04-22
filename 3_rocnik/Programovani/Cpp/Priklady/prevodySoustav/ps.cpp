#include "ps.h"
#include <cmath>
#include <algorithm>

const string CIFRY = "0123456789ABCDEF";

Soustavy::Soustavy(): cislo(0) {
    
}

Soustavy::Soustavy(string cislo, int zaklad) {
    setCislo(cislo, zaklad);
}

Soustavy::Soustavy(const Soustavy& cislo) {
    this ->cislo = cislo.cislo;
}

Soustavy::~Soustavy() {
}

string Soustavy::getCislo(int zaklad) const {
	if (!platnostSoustavy(zaklad)) {
        return "0";
    }
    return prevodNaJinouSoustavu(this ->cislo, zaklad);
}

bool Soustavy::setCislo(string cislo, int zaklad) {
    if (!platnostCisla(cislo, zaklad)) {
        return false;
    }
	this ->cislo = prevodNaDesitkovou((cislo), zaklad);
    return true;
}

bool Soustavy::platnostSoustavy(int zaklad) {
    return zaklad >= MIN_ZAKLAD && zaklad <= MAX_ZAKLAD;
}

bool Soustavy::platnostCisla(string cislo, int zaklad) {
    std::size_t found;
    if (!platnostSoustavy(zaklad)) {
        return false;
    }
    for (int i = 0; i < cislo.length(); i++) {
        found = CIFRY.find(cislo[i]);
        if (found == string::npos || found >= zaklad) {
            return false;
        }
    }
    return true;
        
}


unsigned int Soustavy::prevodNaDesitkovou(string cislo, int zaklad) {
    unsigned int soucet = 0;
    for (int i = 0; i < cislo.length(); i++) {
        soucet += CIFRY.find(cislo[i]) * pow(zaklad, cislo.length() - 1 - i);
    }
	return soucet;
}

string Soustavy::prevodNaJinouSoustavu(unsigned int cislo, int zaklad) {
    string zbytky = cislo == 0 ? "0" : "";
    while (cislo != 0) {
        zbytky += CIFRY[cislo % zaklad];
        cislo /= zaklad;
    }
    std::reverse(zbytky.begin(), zbytky.end());
    return zbytky;

}

ostream& operator<<(ostream& os, const Soustavy& soustava) {
    os << "cislo v dvojkove soustave: " << soustava.getCislo(2) << std::endl;
    os << "cislo v osmickove soustave: " << soustava.getCislo(8) << std::endl;
    os << "cislo v desitkove soustave: " << soustava.getCislo(10) << std::endl;
    os << "cislo v šestnáctkové soustave: " << soustava.getCislo(16) << std::endl;
    return os;
}


