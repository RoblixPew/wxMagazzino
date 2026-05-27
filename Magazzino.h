#pragma once
#include <string>

using namespace std;

struct Prodotto {
    string nome;
    double prezzo;
    int quantita;
};

class Magazzino {
public:
    Prodotto p[100];
    int contap;

    Magazzino() {
        contap = 0;
    }
};
