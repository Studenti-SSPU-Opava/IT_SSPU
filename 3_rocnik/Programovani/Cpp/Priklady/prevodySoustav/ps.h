#ifndef PS_H
#define PS_H

#include <string>
#include <ostream>

class Soustavy
{
    public:
        static const int MIN_ZAKLAD = 2;
        static const int MAX_ZAKLAD = 16;
        Soustavy();
        Soustavy(std::string cislo, int zaklad);
        Soustavy(const Soustavy& cislo);
        ~Soustavy();
        std::string getCislo(int zaklad) const;
        bool setCislo(std::string cislo, int zaklad);
        static bool platnostCisla(std::string cislo, int zaklad);
    private:
        unsigned int cislo;
        static bool platnostSoustavy(int zaklad);
        static unsigned int prevodNaDesitkovou(std::string cislo, int zaklad);
        static std::string prevodNaJinouSoustavu(unsigned int cislo, int zaklad);
};

std::ostream& operator<<(std::ostream& os, const Soustavy& soustava);

#endif
