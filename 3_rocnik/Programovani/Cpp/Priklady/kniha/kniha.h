#ifndef KNIHA_KNIHA_H // ochrana proti vicenasobnemu vlozeni
#define KNIHA_KNIHA_H // konec ochrany

#include <ostream> // vystupni stream
#include <string> // retezce

#define DEFAULT_ISBN "978-0-321-56384-2" // vychozi ISBN
#define DEFAULT_AUTOR "Bjarne Stroustrup" // vychozi autor
#define DEFAULT_NAZEV "The C++ Programming Language" // vychozi nazev
#define MIN_AUTOR_LEN 3 // min delka autora
#define MAX_AUTOR_LEN 100 // max delka autora
#define MIN_NAZEV_LEN 3 // min delka nazvu
#define MAX_NAZEV_LEN 100 // max delka nazvu

class Kniha { // hlavni trida knihy
public:
    Kniha(); // vychozi konstruktor
    Kniha(const std::string &isbn, const std::string &autor, const std::string &nazev); // param. konstruktor
    Kniha(const Kniha &other); // kopirovaci konstruktor
    ~Kniha(); // destruktor

    bool setIsbn(const std::string &isbn); // nastaveni ISBN
    bool setAutor(const std::string &autor); // nastaveni autora
    bool setNazev(const std::string &nazev); // nastaveni nazvu
    bool setKniha(const std::string &isbn, const std::string &autor, const std::string &nazev); // nastaveni cele knihy

    std::string getIsbn() const; // ziskani ISBN
    std::string getAutor() const; // ziskani autora
    std::string getNazev() const; // ziskani nazvu

    std::string getPrefix() const; // ziskani prefixu
    std::string getRegion() const; // ziskani regionu
    std::string getVydavatel() const; // ziskani vydavatele
    std::string getVydani() const; // ziskani vydani
    std::string getIsbnBezOddelovacu() const; // ISBN bez oddelovacu
    size_t getDelkaIsbnBezOddelovacu() const; // delka ISBN bez oddelovacu

    Kniha &operator=(const Kniha &other); // prirazeni
    bool operator==(const Kniha &other) const; // porovnani

    friend std::ostream &operator<<(std::ostream &os, const Kniha &kniha); // vystupni operator

private:
    std::string isbn; // ulozene ISBN
    std::string autor; // ulozeny autor
    std::string nazev; // ulozeny nazev

    bool isValidIsbn(const std::string &isbn) const; // kontrola ISBN
    bool isValidTextLength(const std::string &text, int minLen, int maxLen) const; // kontrola delky textu
    bool parseIsbnParts(const std::string &isbn, std::string parts[5], int &count) const; // rozpad ISBN
    std::string normalizeIsbnInput(const std::string &isbn) const; // normalizace vstupu
    std::string cleanIsbn(const std::string &isbn) const; // odstraneni oddelovacu
    bool isValidIsbn10(const std::string &clean) const; // validace ISBN-10
    bool isValidIsbn13(const std::string &clean) const; // validace ISBN-13
    std::string regionToText(const std::string &region) const; // prevod regionu
};

#endif // konec ochrany
