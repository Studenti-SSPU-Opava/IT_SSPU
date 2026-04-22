#ifndef PS_H
#define PS_H

#include <string>
#include <ostream>
using std::string;
using std::ostream;

class Soustavy
{
    public:
        static const int MIN_ZAKLAD = 2;
        static const int MAX_ZAKLAD = 16;
        Soustavy();
        Soustavy(string cislo, int zaklad);
        Soustavy(const Soustavy& cislo);
        ~Soustavy();
        string getCislo(int zaklad) const;
        bool setCislo(string cislo, int zaklad);
        static bool platnostCisla(string cislo, int zaklad);
    private:
        unsigned int cislo;
        static bool platnostSoustavy(int zaklad);
        static unsigned int prevodNaDesitkovou(string cislo, int zaklad);
        static string prevodNaJinouSoustavu(unsigned int cislo, int zaklad);
};

ostream& operator<<(ostream& os, const Soustavy& soustava);

#endif
