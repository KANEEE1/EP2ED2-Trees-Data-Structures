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
        //binarySearchTree<Key> *raiz;

    public:
        binarySearchTree<Key> *raiz;  // tirei do privado para testar e conseguir acessar a raiz
        TSABB();
        ~TSABB();
        void add(Key key, Item val);
        Item value(Key key);
        bool isBST(binarySearchTree<Key>* raiz);
        binarySearchTree<Key>* put(binarySearchTree<Key>* &raiz, Key key, Item &val);

};

template <class Key>
TSABB<Key>::TSABB() : key(), val(), raiz(nullptr) {}

template <class Key>
TSABB<Key>::~TSABB() {
    // Implemente a lógica de destruição da árvore ou liberação de memória aqui
}

template <class Key>
bool TSABB<Key>::isBST(binarySearchTree<Key>* raiz) {
    static binarySearchTree<Key>* prev = nullptr;

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

template <class Key>
binarySearchTree<Key>* TSABB<Key>::put(binarySearchTree<Key>* &raiz, Key key, Item &val) {
    if (raiz == nullptr) {
        raiz = new binarySearchTree<Key>(key, val/* , 1 */); // atribui o novo nó à raiz
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
    if (VSR(key) > this->palavraVSR) this->palavraVSR = VSR(key);

    return raiz;
}

template <class Key>
void TSABB<Key>::add(Key key, Item val) {
    put(raiz,key,val);
}



template <class Key>
Item find(binarySearchTree<Key> * &raiz, Key key){
    if (raiz == nullptr) return Item();
    if (key > raiz -> key) return find(raiz -> dir, key);
    else if (key < raiz -> key) return find(raiz -> esq, key);
    else if (key == raiz -> key) return raiz -> val;
    else return Item();
}

template <class Key>
Item TSABB<Key>::value(Key key) {
    // Implemente a lógica para obter o valor correspondente à chave 'key' na árvore aqui
    return find(raiz, key);
}

#endif