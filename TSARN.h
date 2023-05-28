#ifndef TSARN_H
#define TSARN_H

#include "TS.h"

#include <iostream>
#include <string>

using namespace std;

template <class Key>
class NodeARN : public Node<Key> {
public:
    NodeARN() : Node<Key>(), pai(pai), esq(nullptr), dir(nullptr), cor('\0') {}
    NodeARN(Key key, Item val, char cor, NodeARN* pai) : Node<Key>(key, val, 0), pai(pai), esq(nullptr), dir(nullptr), cor(cor) {}

    NodeARN* pai;
    NodeARN* esq;
    NodeARN* dir;
    char cor;
};

template <class Key>
class ARN : public TS<Key> {
    private:
        Key key;
        Item val;
        char cor;
        //NodeARN<Key>* raiz;
        NodeARN<Key>* put(NodeARN<Key>* &raiz, Key key, Item val);
        NodeARN<Key>* rodaEsq(NodeARN<Key>* raiz);
        NodeARN<Key>* rodaDir(NodeARN<Key>* raiz);

    public:
        ARN();
        NodeARN<Key>* raiz;
        void add(Key key, Item val);
        Item value(Key key);
        //NodeARN<Key>* put(NodeARN<Key>* &raiz, Key key, Item val);
        
};

template <class Key>
ARN<Key>::ARN() : key(), val(), cor(), raiz(nullptr) {}

template <class Key>
NodeARN<Key>* ARN<Key>::rodaEsq(NodeARN<Key>* r) {
    NodeARN<Key> * q = r->dir;
    if(q == nullptr) return r;
    if(r->pai != nullptr && r->pai->esq != nullptr) r->pai->esq = q;
    //if(r->pai != nullptr && r->pai->dir != nullptr) r->pai->dir = q;
    q->pai = r->pai;
    r->dir = q->esq;
    r->pai = q;
    q->esq = r;
    if(r->dir != nullptr) r->dir->pai = r;  
    return q;
}

template <class Key>
NodeARN<Key>* ARN<Key>::rodaDir(NodeARN<Key>* q) {
    NodeARN<Key> * r = q->esq;
    //if(q->pai != nullptr && q->pai->esq != nullptr && q->key == q->pai->esq->key) q->pai->esq = r;
    if(q->pai != nullptr && q->pai->dir != nullptr) q->pai->dir = r;
    r->pai = q->pai;
    q->pai = r;
    q->esq = r->dir;
    r->dir = q;   
    if(q->esq != nullptr) q->esq->pai = q; 
    return r;
}

template <class Key>
NodeARN<Key> *ARN<Key>::put(NodeARN<Key> * &raiz, Key key, Item val){
    if(raiz == nullptr){
        raiz = new NodeARN<Key>(key, val, 'r', nullptr);
        return raiz;
    }

    NodeARN<Key> * p = raiz;
    bool achou = false;
    while(!achou){
        if(p->key == key){
            p->val.numOcorrencia++;
            return raiz;
        }
        else if ((key < p->key) && (p->esq != nullptr)) {
            cout << "Key= " << key << endl;
            cout << "Key raiz = " << p->key << endl;
            cout << "Key da esq = " << p->esq->key << endl;
            p = p->esq;
        }
        else if ((key < p->key) && (p->esq == nullptr)){
            achou = true;
        }
        else if((key > p->key) && (p->dir != nullptr)){
            p = p->dir;
        }
        else if((key > p->key) && (p->dir == nullptr)){
            achou = true;
        }
    }

    if (p->val.numLetras > this->palavraMaisLonga) this->palavraMaisLonga = p->val.numLetras;
    if (NRL(key) > this->palavraNRL) this->palavraNRL = NRL(key);
    if (VSR(key) > this->palavraVSR) this->palavraVSR = VSR(key);

    NodeARN<Key> * filho = new NodeARN<Key>(key, val, 'r', p);
    if(key < p->key) p->esq = filho;
    else p->dir = filho;

    NodeARN<Key> * q = new NodeARN<Key>();
    NodeARN<Key> * r = new NodeARN<Key>();

    while(true){
        if(p->cor == 'b') break;
        NodeARN<Key> * avo = p->pai;
        if(avo == nullptr){
            p->cor = 'b';
            break;
        }

        NodeARN<Key> * tio = new NodeARN<Key>();
        if(p == avo->esq) tio = avo->dir;
        else tio = avo->esq;
        if((tio != nullptr) && (tio->cor == 'r')){
            avo->cor = 'r';
            p->cor = tio->cor = 'b';
            filho = avo;
            p = avo->pai;
            if(p == nullptr) break;
        }

        else{
            if(p == avo->esq && filho == p->esq){
                NodeARN<Key> * q = rodaDir(avo);
                q->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = q;
                break;
            }
            else if(p == avo->esq && filho == p->dir){
                NodeARN<Key> * q = rodaEsq(p);
                NodeARN<Key> * r = rodaDir(avo);
                r->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = r;
                break;
            }
            else if(p == avo->dir && filho == p->dir){
                NodeARN<Key> * q = rodaEsq(avo);
                q->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = q;
                break;
            }
            else{
                NodeARN<Key> * q = rodaDir(p);
                NodeARN<Key> * r = rodaEsq(avo);
                r->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = r;
                break;
            }
        }
    }
    

    if (raiz->dir != nullptr) cout << raiz->dir->key << endl;
    if (raiz->esq != nullptr)cout << raiz->esq->key << endl;
    return raiz;
}


template <class Key>
void ARN<Key>::add(Key key, Item val) {
    cout << "Key= " << key << endl;
    put(raiz, key, val);
}

template <class Key>
Item find(NodeARN<Key>* raiz, Key key) {
    if (raiz == nullptr)
        return Item();
    if (raiz->key == key)
        return raiz->val;
    if (raiz->key > key)
        return find(raiz->esq, key);
    return find(raiz->dir, key);
}

template <class Key>
Item ARN<Key>::value(Key key) {
    return find(raiz, key);
}

#endif