#include "kniha.h" // hlavni hlavicka



static bool isDigitChar(char c) { // kontrola cislice
    return c >= '0' && c <= '9'; // vysledek
} // konec funkce



static bool isSpaceChar(char c) { // kontrola mezery
    return c == ' ' || c == '\t'; // vysledek
} // konec funkce



static char toUpperChar(char c) { // prevod na velke pismeno
    if (c >= 'a' && c <= 'z') { // male pismeno
        return static_cast<char>(c - ('a' - 'A')); // prevod
    }
    return c; // bez zmeny
} // konec funkce



Kniha::Kniha() : isbn(DEFAULT_ISBN), autor(DEFAULT_AUTOR), nazev(DEFAULT_NAZEV) { // vychozi konstruktor
} // konec konstruktoru



Kniha::Kniha(const std::string &isbn, const std::string &autor, const std::string &nazev)
    : isbn(DEFAULT_ISBN), autor(DEFAULT_AUTOR), nazev(DEFAULT_NAZEV) { // param. konstruktor
    if (!setKniha(isbn, autor, nazev)) { // pokus o nastaveni
        this->isbn = DEFAULT_ISBN; // navrat na vychozi
        this->autor = DEFAULT_AUTOR; // navrat na vychozi
        this->nazev = DEFAULT_NAZEV; // navrat na vychozi
    }
} // konec konstruktoru



Kniha::Kniha(const Kniha &other) : isbn(other.isbn), autor(other.autor), nazev(other.nazev) { // kopirovaci konstruktor
} // konec konstruktoru



Kniha::~Kniha() { // destruktor
} // konec destruktoru



bool Kniha::setIsbn(const std::string &isbn) { // nastaveni ISBN
    std::string parts[5]; // casti ISBN
    int count = 0; // pocet casti
    if (!parseIsbnParts(isbn, parts, count)) { // parsovani
        return false; // neplatne
    }

    std::string joined; // slozeny retezec
    for (int i = 0; i < count; ++i) { // pruchod castmi
        if (i > 0) { // pokud neni prvni
            joined += "-"; // pridani oddelovace
        }
        joined += parts[i]; // pridani casti
    }

    if (!isValidIsbn(joined)) { // kontrola ISBN
        return false; // neplatne
    }

    this->isbn = joined; // ulozeni
    return true; // uspech
} // konec metody



bool Kniha::setAutor(const std::string &autor) { // nastaveni autora
    if (!isValidTextLength(autor, MIN_AUTOR_LEN, MAX_AUTOR_LEN)) { // kontrola delky
        return false; // neplatne
    }
    this->autor = autor; // ulozeni
    return true; // uspech
} // konec metody



bool Kniha::setNazev(const std::string &nazev) { // nastaveni nazvu
    if (!isValidTextLength(nazev, MIN_NAZEV_LEN, MAX_NAZEV_LEN)) { // kontrola delky
        return false; // neplatne
    }
    this->nazev = nazev; // ulozeni
    return true; // uspech
} // konec metody



bool Kniha::setKniha(const std::string &isbn, const std::string &autor, const std::string &nazev) { // nastaveni cele knihy
    bool isbnOk = setIsbn(isbn); // nastaveni ISBN
    bool autorOk = setAutor(autor); // nastaveni autora
    bool nazevOk = setNazev(nazev); // nastaveni nazvu
    if (isbnOk && autorOk && nazevOk) { // vse platne
        return true; // uspech
    }

    this->isbn = DEFAULT_ISBN; // navrat na vychozi
    this->autor = DEFAULT_AUTOR; // navrat na vychozi
    this->nazev = DEFAULT_NAZEV; // navrat na vychozi
    return false; // neuspech
} // konec metody



std::string Kniha::getIsbn() const { // getter ISBN
    return isbn; // vratit hodnotu
} // konec metody



std::string Kniha::getAutor() const { // getter autora
    return autor; // vratit hodnotu
} // konec metody



std::string Kniha::getNazev() const { // getter nazvu
    return nazev; // vratit hodnotu
} // konec metody



std::string Kniha::getPrefix() const { // ziskani prefixu
    std::string parts[5]; // casti ISBN
    int count = 0; // pocet casti
    if (!parseIsbnParts(isbn, parts, count)) { // parsovani
        return ""; // neplatne
    }
    if (count == 5) { // ISBN-13
        return parts[0]; // prefix
    }
    return ""; // ISBN-10 nema prefix
} // konec metody



std::string Kniha::getRegion() const { // ziskani regionu
    std::string parts[5]; // casti ISBN
    int count = 0; // pocet casti
    if (!parseIsbnParts(isbn, parts, count)) { // parsovani
        return ""; // neplatne
    }
    if (count == 5) { // ISBN-13
        return parts[1]; // region
    }
    if (count == 4) { // ISBN-10
        return parts[0]; // region
    }
    return ""; // nezname
} // konec metody



std::string Kniha::getVydavatel() const { // ziskani vydavatele
    std::string parts[5]; // casti ISBN
    int count = 0; // pocet casti
    if (!parseIsbnParts(isbn, parts, count)) { // parsovani
        return ""; // neplatne
    }
    if (count == 5) { // ISBN-13
        return parts[2]; // vydavatel
    }
    if (count == 4) { // ISBN-10
        return parts[1]; // vydavatel
    }
    return ""; // nezname
} // konec metody



std::string Kniha::getVydani() const { // ziskani vydani
    std::string parts[5]; // casti ISBN
    int count = 0; // pocet casti
    if (!parseIsbnParts(isbn, parts, count)) { // parsovani
        return ""; // neplatne
    }
    if (count == 5) { // ISBN-13
        return parts[3]; // vydani
    }
    if (count == 4) { // ISBN-10
        return parts[2]; // vydani
    }
    return ""; // nezname
} // konec metody



std::string Kniha::getIsbnBezOddelovacu() const { // ISBN bez oddelovacu
    return cleanIsbn(isbn); // vycistit
} // konec metody



size_t Kniha::getDelkaIsbnBezOddelovacu() const { // delka ISBN bez oddelovacu
    return getIsbnBezOddelovacu().size(); // delka
} // konec metody



Kniha &Kniha::operator=(const Kniha &other) { // operator prirazeni
    if (this != &other) { // ochrana proti samoprirazeni
        isbn = other.isbn; // kopie ISBN
        autor = other.autor; // kopie autora
        nazev = other.nazev; // kopie nazvu
    }
    return *this; // vratit sebe
} // konec operatoru



bool Kniha::operator==(const Kniha &other) const { // operator porovnani
    return isbn == other.isbn && autor == other.autor && nazev == other.nazev; // porovnani
} // konec operatoru



bool Kniha::isValidIsbn(const std::string &isbn) const { // kontrola ISBN
    std::string parts[5]; // casti ISBN
    int count = 0; // pocet casti
    if (!parseIsbnParts(isbn, parts, count)) { // parsovani
        return false; // neplatne
    }

    std::string clean = cleanIsbn(isbn); // vycistene ISBN
    if (clean.size() == 10) { // ISBN-10
        if (count != 4) { // pocet casti
            return false; // neplatne
        }
        if (parts[3].size() != 1) { // kontrolni cislice
            return false; // neplatne
        }
        if (!isValidIsbn10(clean)) { // kontrola souctu
            return false; // neplatne
        }
        return true; // platne
    }

    if (clean.size() == 13) { // ISBN-13
        if (count != 5) { // pocet casti
            return false; // neplatne
        }
        if (parts[0] != "978" && parts[0] != "979") { // kontrola prefixu
            return false; // neplatne
        }
        if (parts[4].size() != 1) { // kontrolni cislice
            return false; // neplatne
        }
        if (!isValidIsbn13(clean)) { // kontrola souctu
            return false; // neplatne
        }
        return true; // platne
    }

    return false; // neplatna delka
} // konec metody



bool Kniha::isValidTextLength(const std::string &text, int minLen, int maxLen) const { // kontrola delky
    int len = static_cast<int>(text.size()); // delka
    return len >= minLen && len <= maxLen; // vysledek
} // konec metody



bool Kniha::parseIsbnParts(const std::string &isbn, std::string parts[5], int &count) const { // parsovani ISBN
    count = 0; // vynulovat pocet
    std::string normalized = normalizeIsbnInput(isbn); // normalizace
    std::string current; // aktualni cast
    for (size_t i = 0; i < normalized.size(); ++i) { // pruchod znaky
        char c = normalized[i]; // aktualni znak
        if (c == '-' || isSpaceChar(c)) { // oddelovac
            if (!current.empty()) { // pokud je cast
                if (count >= 5) { // prekroceni limitu
                    return false; // neplatne
                }
                parts[count] = current; // ulozit cast
                ++count; // zvysit pocet
                current.clear(); // vynulovat
            }
            continue; // dalsi znak
        }

        if (isDigitChar(c)) { // cislice
            current.push_back(c); // pridat cislici
            continue; // dalsi znak
        }

        if (c == 'X' || c == 'x') { // X pro ISBN-10
            current.push_back('X'); // ulozit X
            continue; // dalsi znak
        }

        return false; // neplatny znak
    }

    if (!current.empty()) { // posledni cast
        if (count >= 5) { // prekroceni limitu
            return false; // neplatne
        }
        parts[count] = current; // ulozit cast
        ++count; // zvysit pocet
    }

    if (count < 4 || count > 5) { // povoleny pocet casti
        return false; // neplatne
    }
    return true; // ok
} // konec metody



std::string Kniha::normalizeIsbnInput(const std::string &isbn) const { // normalizace ISBN
    std::string trimmed; // docasny retezec
    for (size_t i = 0; i < isbn.size(); ++i) { // pruchod znaky
        char c = isbn[i]; // znak
        if (c != '\r' && c != '\n') { // vynechat konce radku
            trimmed.push_back(c); // pridat znak
        }
    }

    size_t start = 0; // zacatek
    while (start < trimmed.size() && isSpaceChar(trimmed[start])) { // preskocit mezery
        ++start; // posun
    }

    size_t end = trimmed.size(); // konec
    while (end > start && isSpaceChar(trimmed[end - 1])) { // preskocit mezery
        --end; // posun
    }

    std::string out = trimmed.substr(start, end - start); // oriznuti
    if (out.size() >= 4) { // muze obsahovat ISBN
        std::string prefix = out.substr(0, 4); // mozny prefix
        for (size_t i = 0; i < prefix.size(); ++i) { // prevod na velka pismena
            prefix[i] = toUpperChar(prefix[i]); // prevod
        }
        if (prefix == "ISBN") { // je to ISBN
            size_t pos = 4; // pozice za ISBN
            while (pos < out.size() && (out[pos] == ':' || isSpaceChar(out[pos]))) { // preskocit oddelovace
                ++pos; // posun
            }
            out = out.substr(pos); // zbytek
        }
    }

    return out; // vysledek
} // konec metody



std::string Kniha::cleanIsbn(const std::string &isbn) const { // odstraneni oddelovacu
    std::string normalized = normalizeIsbnInput(isbn); // normalizace
    std::string clean; // vycisteny retezec
    for (size_t i = 0; i < normalized.size(); ++i) { // pruchod znaky
        char c = normalized[i]; // znak
        if (isDigitChar(c)) { // cislice
            clean.push_back(c); // pridat cislici
        } else if (c == 'X' || c == 'x') { // X pro ISBN-10
            clean.push_back('X'); // pridat X
        }
    }
    return clean; // vysledek
} // konec metody



bool Kniha::isValidIsbn10(const std::string &clean) const { // validace ISBN-10
    if (clean.size() != 10) { // kontrola delky
        return false; // neplatne
    }

    int sum = 0; // soucet vah
    for (size_t i = 0; i < 10; ++i) { // pruchod cislicemi
        int value = 0; // hodnota cislice
        if (i == 9 && clean[i] == 'X') { // X na konci
            value = 10; // hodnota X
        } else if (isDigitChar(clean[i])) { // cislice
            value = clean[i] - '0'; // prevod
        } else {
            return false; // neplatny znak
        }

        int weight = 10 - static_cast<int>(i); // vypocet vahy
        sum += value * weight; // pricitani
    }

    return (sum % 11) == 0; // kontrola deleni 11
} // konec metody



bool Kniha::isValidIsbn13(const std::string &clean) const { // validace ISBN-13
    if (clean.size() != 13) { // kontrola delky
        return false; // neplatne
    }

    int sum = 0; // soucet vah
    for (size_t i = 0; i < 13; ++i) { // pruchod cislicemi
        if (!isDigitChar(clean[i])) { // musi byt cislice
            return false; // neplatne
        }
        int digit = clean[i] - '0'; // prevod na cislo
        int weight = (i % 2 == 0) ? 1 : 3; // stridani vah
        sum += digit * weight; // pricitani
    }

    return (sum % 10) == 0; // kontrola deleni 10
} // konec metody



std::string Kniha::regionToText(const std::string &region) const { // prevod regionu
    if (region == "0" || region == "1") { // anglicky
        return "anglicky"; // text regionu
    }
    if (region == "2") { // francouzsky
        return "francouzsky"; // text regionu
    }
    if (region == "3") { // nemecky
        return "nemecky"; // text regionu
    }
    if (region == "4") { // japonsky
        return "japonsky"; // text regionu
    }
    if (region == "5") { // rusky
        return "rusky"; // text regionu
    }
    if (region == "7") { // cinsky
        return "cinsky"; // text regionu
    }
    if (region == "80") { // cesky/slovensky
        return "cesky, slovensky"; // text regionu
    }
    return "neznamy"; // neznama skupina
} // konec metody



std::ostream &operator<<(std::ostream &os, const Kniha &kniha) { // vystup knihy
    std::string prefix = kniha.getPrefix(); // prefix ISBN
    std::string region = kniha.getRegion(); // region ISBN
    std::string vydavatel = kniha.getVydavatel(); // vydavatel
    std::string vydani = kniha.getVydani(); // vydani
    std::string regionText = kniha.regionToText(region); // popis regionu

    os << "ISBN " << kniha.getIsbn(); // hlavni ISBN
    if (!prefix.empty()) { // jen pro ISBN-13
        os << " Prefix: " << prefix; // vypis prefixu
    }
    os << " Region: " << region; // vypis regionu
    if (!regionText.empty()) { // vypis popisu
        os << " (" << regionText << ")"; // text regionu
    }
    os << " Vydavatel: " << vydavatel; // vypis vydavatele
    os << " Vydani: " << vydani; // vypis vydani
    os << " Autor: " << kniha.getAutor() << "\n"; // vypis autora
    os << "Nazev: " << kniha.getNazev() << "\n"; // vypis nazvu
    return os; // vratit stream
} // konec operatoru
