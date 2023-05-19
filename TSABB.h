#ifndef TSABB_H
#define TSABB_H
#include "TS.h"

using namespace std;

template <class Key, class Item>
class binarySearchTree : public Node<Key, Item>{
public:
    binarySearchTree();
    binarySearchTree(Key key, Item val, int N);
    
    Key key;
    Item val;
    int N;
    binarySearchTree<Key, Item> *esq;
    binarySearchTree<Key, Item> *dir;
};

template <class Key, class Item>
binarySearchTree<Key, Item>::binarySearchTree() : Node<Key, Item>(), key(), val(), N(0), esq(nullptr), dir(nullptr) {}

template <class Key, class Item>
binarySearchTree<Key, Item>::binarySearchTree(Key key, Item val, int N) : Node<Key, Item>(key, val, N), key(key), val(val), N(N), esq(nullptr), dir(nullptr) {}

template <class Key, class Item>
class TSABB: public TS<Key,Item>{
    private:
        int key;
        int val;   
        int N;
        binarySearchTree<Key, Item> *raiz;

    public:
        TSABB();
        ~TSABB();
        void add(Key key, Item item);
        Item value(Key key);
        //void remove(Key key);
};

template <class Key, class Item>
TSABB<Key, Item>::TSABB() : N(0), key(), val(), raiz(nullptr) {}

template <class Key, class Item>
TSABB<Key, Item>::~TSABB() {
    // Implemente a lógica de destruição da árvore ou liberação de memória aqui
}

template <class Key, class Item>
int size (binarySearchTree<Key, Item> *raiz){
    if (raiz == nullptr){
        return 0;
    }
    return raiz -> N;
}
/* template <class Key, class Item>
TSABB<Key, Item>::~TSABB() {
    delete raiz;
} */



template <class Key, class Item>
binarySearchTree<Key, Item>* put(binarySearchTree<Key, Item>* &raiz, Key key, Item val) {
    if (raiz == nullptr) {
        raiz = new binarySearchTree<Key, Item>(key, val, 1); // atribui o novo nó à raiz
    } 
    else if (key > raiz->key) {
        raiz->dir = put(raiz->dir, key, val);
    }
    else if (key < raiz->key) {
        raiz->esq = put(raiz->esq, key, val);
    } 
    else {
        raiz->val = val;
    }
    raiz->N = 1 + size(raiz->esq) + size(raiz->dir);
    return raiz;
}


template <class Key, class Item>
bool isBST(binarySearchTree<Key, Item>* raiz) {
    static binarySearchTree<Key, Item>* prev = nullptr;

    // Verifica se a árvore está vazia
    if (raiz == nullptr) {
        return true;
    }

    // Verifica a subárvore esquerda
    if (!isBST(raiz->esq)) {
        return false;
    }

    // Verifica se o elemento atual é maior que o anterior
    if (prev != nullptr && raiz->key <= prev->key) {
        return false;
    }
    prev = raiz;

    // Verifica a subárvore direita
    return isBST(raiz->dir);
}


template <class Key, class Item>
void TSABB<Key, Item>::add(Key key, Item val) {
    put(raiz,key,val);
}


template <class Key, class Item>
Item TSABB<Key, Item>::value(Key key) {
    // Implemente a lógica para obter o valor correspondente à chave 'key' na árvore aqui
    return Item();
}


#endif