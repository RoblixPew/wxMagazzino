#pragma once
#include <string>

using namespace std;

struct Prodotto {
    string nomeprodotto[100];
    double prezzo[100];
    int quantita[100];
};

class Magazzino {
public:
    Prodotto p;
    int contap;

    Magazzino() {
        contap = 0;
    }
};
