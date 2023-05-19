#ifndef TREAP_H
#define TREAP_H
#include "TS.h"
#include <random>

using namespace std;

template <class Key, class Item>
class binarySearchTree : public Node<Key, Item>{
public:
    binarySearchTree();
    binarySearchTree(Key key, Item val, int priority);
    
    Key key;
    Item val;
    int priority;
    binarySearchTree<Key, Item>* esq;
    binarySearchTree<Key, Item>* dir;
};

template <class Key, class Item>
binarySearchTree<Key, Item>::binarySearchTree() : Node<Key, Item>(), key(), val(), priority(0), esq(nullptr), dir(nullptr) {}

template <class Key, class Item>
binarySearchTree<Key, Item>::binarySearchTree(Key key, Item val, int priority) : Node<Key, Item>(key, val, priority), key(key), val(val), priority(priority)/* , pai(nullptr) */, esq(nullptr), dir(nullptr) {}

template <class Key, class Item>
class TREAP: public TS<Key,Item>{
    private:
        Key key;
        Item val;   
        int priority;
        //binarySearchTree<Key, Item> *raiz;

    public:
        binarySearchTree<Key, Item> *raiz;  // tirei do privado para testar e conseguir acessar a raiz
        TREAP();
        ~TREAP();
        void add(Key key, Item val);
        Item value(Key key);
        bool isTREAP(binarySearchTree<Key, Item>* raiz);
        //void remove(Key key);
};

template <class Key, class Item>
TREAP<Key, Item>::TREAP() : priority(0), key(), val(), raiz(nullptr) {}

template <class Key, class Item>
TREAP<Key, Item>::~TREAP() {
    // Implemente a lógica de destruição da árvore ou liberação de memória aqui
}

template <class Key, class Item>
binarySearchTree<Key, Item> *rodaDir(binarySearchTree<Key, Item> *&raiz){
    binarySearchTree<Key, Item> *aux = raiz;
    raiz = raiz -> esq;
    aux -> esq = raiz -> dir;
    raiz -> dir = aux;

    return raiz;
}

template <class Key, class Item>
binarySearchTree<Key, Item> *rodaEsq(binarySearchTree<Key, Item>* &raiz){
    binarySearchTree<Key, Item> *aux = raiz;
    raiz = raiz -> dir;
    aux -> dir = raiz -> esq;
    raiz -> esq = aux;

    return raiz;
}

int N = 0;
int save;
template <class Key, class Item>
binarySearchTree<Key, Item> * put(binarySearchTree<Key, Item> *&raiz, Key key, Item val){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    if(raiz == nullptr){
        int x = dist(rng);
        save = x;
/*         if(N == 0) x = 51;
        if(N == 1) x = 55;
        if(N == 2) x = 45;
        if(N == 3) x = 36;
        if(N == 4) x = 13; */
        cout << "Key = " << key  <<  ", Val = " << val << ", Priority = " << x << endl; 
        raiz = new binarySearchTree<Key, Item>(key, val, x);
        raiz -> priority = x;
        N++;
    } 
    else if (key > raiz -> key){//&& prior < raiz-> prior){
        put(raiz -> dir, key, val);

        if(save > raiz -> priority ){
            //cout << "RODOU ESQUERDA ";
            return rodaEsq(raiz);
        }
    }
    else if (key < raiz -> key ){//&& prior < raiz-> prior){
        put(raiz -> esq, key, val);
        if(save > raiz -> priority){
            //cout << "RODOU ESQUERDA ";
            return rodaDir(raiz);
        }
    }
    return raiz;
}

template<class Key, class Item>
void TREAP<Key, Item>::add(Key key, Item val){
    put(raiz, key, val);
    cout << "Raiz = " << raiz->priority << endl;
}

template<class Key, class Item>
Item TREAP<Key, Item>::value(Key key){
    return Item();
}

template <class Key, class Item>
bool TREAP<Key, Item>::isTREAP(binarySearchTree<Key, Item>* raiz) {
    return true;
}

#endif
