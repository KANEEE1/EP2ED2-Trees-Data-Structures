#ifndef TS_H
#define TS_H

#include <iostream>
#include <string>

using namespace std;

struct Item {
    public:
    int numOcorrencia;
    int numLetras;
    int vogaisSR;

    Item(){}
};

template <class Key>
class Node {
public:
    Node(){}
    Node(Key key, Item val, bool twoNode) : key(key), val(val), esq(nullptr), dir(nullptr), high(nullptr) {}

    Key key;
    Item val;
    Node* esq;
    Node* dir;
    Node* high;
};


template <class Key>
class TS {
public:
    int palavraMaisFreq = 0;      // palavras mais frequentes
    int palavraMaisLonga = 0;     // palavras mais longa 
    int palavraNRL = -1;          // palavras mais longa que nao repete letra
    int palavraVSR = 0;           // palavras mais curtas com vogais distintas
    virtual void add(Key key, Item val) = 0;
    virtual Item value(Key key) = 0;
};

int VSR(const string &palavra) {      // Função que devolve quantas vogais sem repetição de uma palvra
    bool vogaisAchadas[5] = {false};  // Array de flags para acompanhar as vogais (a, e, i, o, u)
    int vogaisSR = 0;

    for (char c : palavra) {
        char lowercaseC = tolower(c);
        if (lowercaseC == 'a') {
            if (!vogaisAchadas[0]) {
                vogaisAchadas[0] = true;
                vogaisSR++;
            }
        } else if (lowercaseC == 'e') {
            if (!vogaisAchadas[1]) {
                vogaisAchadas[1] = true;
                vogaisSR++;
            }
        } else if (lowercaseC == 'i') {
            if (!vogaisAchadas[2]) {
                vogaisAchadas[2] = true;
                vogaisSR++;
            }
        } else if (lowercaseC == 'o') {
            if (!vogaisAchadas[3]) {
                vogaisAchadas[3] = true;
                vogaisSR++;
            }
        } else if (lowercaseC == 'u') {
            if (!vogaisAchadas[4]) {
                vogaisAchadas[4] = true;
                vogaisSR++;
            }
        }
    }

    return vogaisSR;
}

int NRL(const string& palavra) {  // Função que dada uma palavra que nao repete letras retorna a quant de letras dela.
    const int MAX_CHAR = 256;  // Assumindo o uso de caracteres ASCII
    int contadorLetras[MAX_CHAR] = {0};  // Inicializa o array com zeros
    
    // Verificação de letras repetidas
    for (char letra : palavra) {
        letra = tolower(letra);
        contadorLetras[static_cast<unsigned char>(letra)]++;
        if (contadorLetras[static_cast<unsigned char>(letra)] > 1) {
            return -1;  // Retorna -1 se houver letras repetidas
        }
    }
    
    return palavra.length();
}


#endif