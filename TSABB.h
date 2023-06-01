#ifndef TSABB_H
#define TSABB_H
#include "TS.h"

using namespace std;

template <class Key>
class binarySearchTree : public Node<Key>{
public:
    binarySearchTree();
    binarySearchTree(Key key, Item val);
    
    Key key;
    Item val;
    binarySearchTree<Key> *esq;
    binarySearchTree<Key> *dir;
};

template <class Key>
binarySearchTree<Key>::binarySearchTree() : Node<Key>(), key(), val(), esq(nullptr), dir(nullptr) {}

template <class Key>
binarySearchTree<Key>::binarySearchTree(Key key, Item val) : Node<Key>(key, val, false), key(key), val(val), esq(nullptr), dir(nullptr) {}

template <class Key>
class TSABB: public TS<Key>{
    private:
        Key key;
        Item val; 
        binarySearchTree<Key> *raiz = nullptr; 

    public:
        void add(Key key, Item val);
        Item value(Key key);
        binarySearchTree<Key>* put(binarySearchTree<Key>* &raiz, Key key, Item &val);

};


template <class Key>
binarySearchTree<Key>* TSABB<Key>::put(binarySearchTree<Key>* &raiz, Key key, Item &val) {
    if (raiz == nullptr) {
        raiz = new binarySearchTree<Key>(key, val); // atribui o novo nó à raiz
    } 
    else if (key > raiz->key) {
        raiz->dir = put(raiz->dir, key, val);
    }
    else if (key < raiz->key) {
        raiz->esq = put(raiz->esq, key, val);
    } 
    else {
        raiz->val.numOcorrencia++;
        if (raiz->val.numOcorrencia > this->palavraMaisFreq) this->palavraMaisFreq = raiz->val.numOcorrencia;
    }

    if (raiz->val.numLetras > this->palavraMaisLonga) this->palavraMaisLonga = raiz->val.numLetras;
    if (NRL(key) > this->palavraNRL) this->palavraNRL = NRL(key);
    if (val.vogaisSR > this->palavraVSR) this->palavraVSR = val.vogaisSR;

    return raiz;
}

template <class Key>
void TSABB<Key>::add(Key key, Item val) {
    put(raiz,key,val);
}

template <class Key>
Item find(binarySearchTree<Key> * &raiz, Key key){
    if (raiz == nullptr){ 
        cout << "Essa chave não está na árvore" << endl;
        return Item();
    }
    if (key > raiz -> key) return find(raiz -> dir, key);
    else if (key < raiz -> key) return find(raiz -> esq, key);
    else if (key == raiz -> key) return raiz -> val;
    else return Item();
}

template <class Key>
Item TSABB<Key>::value(Key key) {
    return find(raiz, key);
}

#endif