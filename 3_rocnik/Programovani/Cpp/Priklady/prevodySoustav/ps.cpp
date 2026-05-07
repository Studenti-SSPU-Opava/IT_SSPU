#include "ps.h"
#include <algorithm>

const std::string CIFRY = "0123456789ABCDEF";

Soustavy::Soustavy(): cislo(0) {
    
}

Soustavy::Soustavy(std::string cislo, int zaklad): cislo(0) {
    setCislo(cislo, zaklad);
}

Soustavy::Soustavy(const Soustavy& cislo) {
    this ->cislo = cislo.cislo;
}

Soustavy::~Soustavy() {
}

std::string Soustavy::getCislo(int zaklad) const {
	if (!platnostSoustavy(zaklad)) {
        return "0";
    }
    return prevodNaJinouSoustavu(this ->cislo, zaklad);
}

bool Soustavy::setCislo(std::string cislo, int zaklad) {
    if (!platnostCisla(cislo, zaklad)) {
        return false;
    }
	this ->cislo = prevodNaDesitkovou((cislo), zaklad);
    return true;
}

bool Soustavy::platnostSoustavy(int zaklad) {
    return zaklad >= MIN_ZAKLAD && zaklad <= MAX_ZAKLAD;
}

bool Soustavy::platnostCisla(std::string cislo, int zaklad) {
    std::size_t found;
    if (!platnostSoustavy(zaklad) || cislo.empty()) {
        return false;
    }
    for (int i = 0; i < cislo.length(); i++) {
        found = CIFRY.find(cislo[i]);
        if (found == std::string::npos || found >= zaklad) {
            return false;
        }
    }
    return true;
        
}


unsigned int Soustavy::prevodNaDesitkovou(std::string cislo, int zaklad) {
    unsigned int soucet = 0;
    for (int i = 0; i < cislo.length(); i++) {
        soucet = soucet * zaklad + CIFRY.find(cislo[i]);
    }
	return soucet;
}

std::string Soustavy::prevodNaJinouSoustavu(unsigned int cislo, int zaklad) {
    std::string zbytky = cislo == 0 ? "0" : "";
    while (cislo != 0) {
        zbytky += CIFRY[cislo % zaklad];
        cislo /= zaklad;
    }
    std::reverse(zbytky.begin(), zbytky.end());
    return zbytky;

}

std::ostream& operator<<(std::ostream& os, const Soustavy& soustava) {
    os << "cislo v dvojkove soustave: " << soustava.getCislo(2) << std::endl;
    os << "cislo v osmickove soustave: " << soustava.getCislo(8) << std::endl;
    os << "cislo v desitkove soustave: " << soustava.getCislo(10) << std::endl;
    os << "cislo v šestnáctkové soustave: " << soustava.getCislo(16) << std::endl;
    return os;
}

