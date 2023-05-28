#ifndef TSTSTREAP_H
#define TSTREAP_H
#include "TS.h"
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

template <class Key>
class NodeTreap : public Node<Key>{
public:
    NodeTreap(){};
    NodeTreap(Key key, Item val, int priority);
    
    Key key;
    Item val;
    int priority;
    NodeTreap<Key>* esq;
    NodeTreap<Key>* dir;
};


template <class Key>
NodeTreap<Key>::NodeTreap(Key key, Item val, int priority) : Node<Key>(key, val, priority), key(key), val(val), priority(priority), esq(nullptr), dir(nullptr) {}

template <class Key>
class TSTREAP: public TS<Key>{
    private:
        Key key;
        Item val;   
        int priority;
        //int N;
        NodeTreap<Key> *raiz = nullptr;
        vector<int> numerosIndisponiveis;

    public:
        TSTREAP(int N);
        int N;
        void add(Key key, Item val);
        Item value(Key key);
        bool isTSTREAP(NodeTreap<Key>* raiz);
        NodeTreap<Key> * put(NodeTreap<Key> *&raiz, Key key, Item &val);
};

template <class Key>
TSTREAP<Key>::TSTREAP(int N) : N(N) {}

template <class Key>
NodeTreap<Key> *rodaDir(NodeTreap<Key> *&raiz){
    NodeTreap<Key> *aux = raiz;
    raiz = raiz -> esq;
    aux -> esq = raiz -> dir;
    raiz -> dir = aux;

    return raiz;
}

template <class Key>
NodeTreap<Key> *rodaEsq(NodeTreap<Key>* &raiz){
    NodeTreap<Key> *aux = raiz;
    raiz = raiz -> dir;
    aux -> dir = raiz -> esq;
    raiz -> esq = aux;

    return raiz;
}

int save; // variavel global pra guardar o valor da prioridade ao inserir na arvore
template <class Key>
NodeTreap<Key> * TSTREAP<Key>::put(NodeTreap<Key> *&raiz, Key key, Item &val){
    if (raiz == nullptr) {
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> dist(1, N*100);

        int numero = dist(rng);
        while (find(numerosIndisponiveis.begin(), numerosIndisponiveis.end(), numero) != numerosIndisponiveis.end()) { // Garante que o numero gerado nao terá a mesma prioridade
            numero = dist(rng);
        }
        numerosIndisponiveis.push_back(numero);
        
        save = numero;
        raiz = new NodeTreap<Key>(key, val, numero);
    } 
    
    else if (key > raiz -> key){  //&& prior < raiz-> prior){
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
    else{
         raiz->val.numOcorrencia++;
         if (raiz->val.numOcorrencia > this->palavraMaisFreq) this->palavraMaisFreq = raiz->val.numOcorrencia;
    }

    if (raiz->val.numLetras > this->palavraMaisLonga) this->palavraMaisLonga = raiz->val.numLetras;
    if (NRL(key) > this->palavraNRL) this->palavraNRL = NRL(key);
    if (VSR(key) > this->palavraVSR) this->palavraVSR = VSR(key);

    return raiz;
}

template<class Key>
void TSTREAP<Key>::add(Key key, Item val){
    put(raiz, key, val);
    // << "Raiz = " << raiz->priority << endl;
}

template <class Key>
bool TSTREAP<Key>::isTSTREAP(NodeTreap<Key>* raiz) {
    if (raiz == nullptr) {
        return true;  // Uma árvore vazia é uma treap válida
    }

    if (raiz->esq != nullptr && raiz->esq->priority > raiz->priority) {
        return false;  // A propriedade de heap não é satisfeita
    }

    if (raiz->dir != nullptr && raiz->dir->priority > raiz->priority) {
        return false;  // A propriedade de heap não é satisfeita
    }

    // Verifica recursivamente se as subárvores também são treaps
    bool isLeftTreap = isTSTREAP(raiz->esq);
    bool isRightTreap = isTSTREAP(raiz->dir);

    return isLeftTreap && isRightTreap;
}

template <class Key>
Item find(NodeTreap<Key> * &raiz, Key key){
    if (raiz == nullptr){
        cout << "Essa key nao existe na árvore" << endl;
         return Item();
    }
    if (key > raiz -> key) return find(raiz -> dir, key);
    else if (key < raiz -> key) return find(raiz -> esq, key);
    else return raiz -> val;
}

template<class Key>
Item TSTREAP<Key>::value(Key key){
    return find(raiz, key);
}


#endif
