#ifndef TSVO_H
#define TSVO_H

#include "TS.h"
#include <string>

using namespace std;

template <class Key>
class pairKeyValue {
public:
    pairKeyValue(){}
    pairKeyValue(Key key, Item val) : key(key), val(val) {}
    Key key;
    Item val;

};

template <class Key>
class TSVO : public TS<Key> {
    private:
        //int tam;
        //int nelem;
        Item val;

        //pairKeyValue<Key> *v;

    public:
        int tam;
        int nelem;
        pairKeyValue<Key> *v;
        TSVO();
        ~TSVO();
        void add(Key key, Item val);
        Item value(Key key);
        void resize();
        //void show(int n);
};

template <class Key>
TSVO<Key>::TSVO() : tam(1), nelem(0) {
    v = new pairKeyValue<Key>[tam];
}

template <class Key>
TSVO<Key>::~TSVO() {
    delete[] v;
}

template <class Key>
void TSVO<Key>::add(Key key, Item val) {
    if (nelem == tam) {
        this->resize();
    }

    int lo = 0, hi = nelem - 1;
    int place = nelem;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid].key == key) {
            v[mid].val.numOcorrencia++;
            if (v[mid].val.numOcorrencia > this->palavraMaisFreq) this->palavraMaisFreq = v[mid].val.numOcorrencia;
            return;
        } else if (v[mid].key < key) {
            lo = mid + 1;
        } else {
            place = mid;
            hi = mid - 1;
        }
    }

    for (int i = nelem; i > place; i--) {
        v[i] = v[i - 1];
    }

    v[place].key = key;
    v[place].val = val;
    if (v[place].val.numLetras > this->palavraMaisLonga) this->palavraMaisLonga = v[place].val.numLetras;
    if (NRL(key) > this->palavraNRL) this->palavraNRL = NRL(key);
    if (val.vogaisSR > this->palavraVSR) this->palavraVSR = val.vogaisSR;
    nelem++;
}

template <class Key>
Item TSVO<Key>::value(Key key) {
    int lo = 0, hi = tam - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid].key == key) {
            return v[mid].val;
        } else if (v[mid].key > key) {
            hi = mid - 1;
        } else if (v[mid].key < key) {
            lo = mid + 1;
        }
    }
    return Item();
}

template <class Key>
void TSVO<Key>::resize() {
    int novoTam = 2 * tam;
    pairKeyValue<Key> *novoV = new pairKeyValue<Key>[novoTam];
    for (int i = 0; i < tam; i++) {
        novoV[i] = v[i];
    }
    delete[] v;
    v = novoV;
    tam = novoTam;
}

#endif
