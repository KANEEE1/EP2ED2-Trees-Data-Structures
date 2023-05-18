#ifndef TSVO_H
#define TSVO_H
#include "TS.h"

using namespace std;


/* template <class Key, class Item> 
class parChaveValor{
    public:
        /* parChaveValor(){};
        parChaveValor(Key key, Item val) {}; 
        Key key;
        Item val;
        //parChaveValor() : key(), val() {}
        parChaveValor(Key key, Item val) : key(key), val(val) {}
};

template <class Key, class Item>
parChaveValor<Key, Item>::parChaveValor(Key key, Item val){
    this->key = key;
    this->val = val;
};

 */
template <class Key, class Item> 
class parChaveValor{
    public:
    parChaveValor(){};
    parChaveValor(Key key, Item val);
    Key key;
    Item val;
};
 
template <class Key, class Item>
parChaveValor<Key, Item>::parChaveValor(Key key, Item val){
    this->key = key;
    this->val = val;
}

template <class Key, class Item>
class TSVO: public TS<Key, Item>{
    private:
        int tam;
        int nelem;
        Key key;
        Item val;
        parChaveValor<Key, Item> *v;

    public:
        TSVO();
        ~TSVO();
        void add (Key key, Item val);
        Item value (Key key);
        void resize ();
/*         int rank(Key key);
        Key select(int k);  */
        void show(int n);
};

template <class Key, class Item>
TSVO<Key, Item>::TSVO() : tam(1), key(), val(), nelem(1) {
    v = new parChaveValor<Key, Item>[tam];
}

template <class Key, class Item>
TSVO<Key, Item>::~TSVO() {
    if (v != nullptr) delete [] v;
}

template <class Key, class Item>
void TSVO<Key, Item>::add(Key key, Item val) {
/*     if (nelem == 0){
        v[0].key = key;
        v[0].val = val;
        nelem = 1;
        return;
    } */

      if (nelem == tam) {
        this->resize();
    }
    
    /* cout << "------------------------------------------------------" << endl;
    for (int i = 0; i < nelem; i++){
        cout << "key" << v[i].key << endl;
    }
    cout << "------------------------------------------------------" << endl;
 */


    int lo = 0, hi = nelem - 1;
    int place = nelem; // inicialmente, assume que o elemento será inserido no final
    
    // Encontrar o local de inserção utilizando busca binária
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid].key == key) {
            v[mid].val = val; // Se a chave já existir, atualiza o valor
            return;
        } 
        else if (v[mid].key < key) {
            lo = mid + 1;
        } 
        else {
            place = mid; // Atualiza o local de inserção
            hi = mid - 1;
        }
    }
    
    //cout << place << endl;
    // Desloca os elementos para a direita para abrir espaço para o novo elemento
    for (int i = nelem; i > place; i--) {
        v[i] = v[i-1];
    }
    
    // Insere o novo elemento no local correto
    v[place].key = key;
    v[place].val = val;
    nelem++;
}

template <class Key, class Item>
Item TSVO<Key, Item>::value(Key key) {
    int lo = 0, hi = tam-1;
    while (lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if (v[mid].key == key) return v[mid].val;
        else if (v[mid].key > key) hi = mid - 1;
        else if (v[mid].key < key) lo = mid + 1;
    }
    return Item();
}

template <class Key, class Item>
void TSVO<Key, Item>::resize() {
    int novoTam = 2 * tam;
    parChaveValor<Key, Item>* novoV = new parChaveValor<Key, Item>[novoTam];
    for (int i = 0; i < tam; i++) {
        novoV[i] = v[i];
    }
    delete[] v;
    v = novoV;
    tam = novoTam;
}

/* template <class Key, class Item>
int TSVO<Key, Item>::rank(Key key){
    int lo = 0, hi = tam - 1;
    while(lo <= hi){
        int mid = (lo + hi) / 2;
        if(v[mid].key == key)
            return mid;
        if(v[mid].key < key)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return lo;
} */
/* 
template <class Key, class Item>
Key TSVO<Key, Item>::select(int k){
    //checar se k entra dentro dos nelem
    return v[k].key;
}  */

template <class Key, class Item>
void TSVO<Key, Item>::show(int n){
    for (int i = 0; i < n; i++){
        cout <<v[i].key << " " <<  v[i].val << endl;
    }
}

#endif