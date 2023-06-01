#ifndef TSARN_H
#define TSARN_H

#include "TS.h"
#include <queue>

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
        NodeARN<Key>* raiz = nullptr;
        NodeARN<Key>* put(NodeARN<Key>* &raiz, Key key, Item val);
        NodeARN<Key>* rodaEsq(NodeARN<Key>* raiz);
        NodeARN<Key>* rodaDir(NodeARN<Key>* raiz);

    public:
        void add(Key key, Item val);
        Item value(Key key);
        
};

template <class Key>
NodeARN<Key>* ARN<Key>::rodaEsq(NodeARN<Key>* r) {
    NodeARN<Key> * q = r->dir;
    if(q == nullptr) return r;
    if(r->pai != nullptr && r->pai->esq != nullptr && r->key == r->pai->esq->key) r->pai->esq = q;
    if(r->pai != nullptr && r->pai->dir != nullptr && r->key == r->pai->dir->key) r->pai->dir = q;
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
    if(q->pai != nullptr && q->pai->esq != nullptr && q->key == q->pai->esq->key) q->pai->esq = r;
    if(q->pai != nullptr && q->pai->dir != nullptr && q->key == q->pai->dir->key) q->pai->dir = r;
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
            if (p->val.numOcorrencia > this->palavraMaisFreq) this->palavraMaisFreq = p->val.numOcorrencia;
            return raiz;
        }
        else if ((key < p->key) && (p->esq != nullptr)) {
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

    NodeARN<Key> * filho = new NodeARN<Key>(key, val, 'r', p);

    if (filho->val.numLetras > this->palavraMaisLonga) this->palavraMaisLonga = filho->val.numLetras;
    if (NRL(key) > this->palavraNRL) this->palavraNRL = NRL(key);
    if (val.vogaisSR > this->palavraVSR) this->palavraVSR = val.vogaisSR;

    if(key < p->key) p->esq = filho;
    else p->dir = filho;

    NodeARN<Key> * aux1 = new NodeARN<Key>();
    NodeARN<Key> * aux2 = new NodeARN<Key>();

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
            p->cor = tio->cor = 'b';
            if (avo != raiz) avo->cor = 'r';
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
                aux1 = rodaEsq(p);
                aux2 = rodaDir(avo);
                aux2->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = aux2;
                break;
            }
            else if(p == avo->dir && filho == p->dir){
                aux1 = rodaEsq(avo);
                aux1->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = aux1;
                break;
            }
            else{
                aux1 = rodaDir(p);
                aux2 = rodaEsq(avo);
                aux2->cor = 'b';
                avo->cor = 'r';
                if(raiz == avo) raiz = aux2;
                break;
            }
        }
    }  
    return raiz;
}


template <class Key>
void ARN<Key>::add(Key key, Item val) {
    put(raiz, key, val);
}

template <class Key>
Item find(NodeARN<Key>* raiz, Key key) {
    if (raiz == nullptr){
        cout << "Essa chave não está na árvore" << endl;
        return Item();
    }
    if (raiz->key == key)return raiz->val;
    if (raiz->key > key) return find(raiz->esq, key);
    else return find(raiz->dir, key);
}

template <class Key>
Item ARN<Key>::value(Key key) {
    return find(raiz, key);
}

template <class Key>
void exibirKeysArvoreBinaria(NodeARN<Key>* raiz) {
    queue<pair<NodeARN<Key>*, int>> fila;
    fila.push(make_pair(raiz, 0));

    while (!fila.empty()) {
        pair<NodeARN<Key>*, int> par = fila.front();
        NodeARN<Key>* no = par.first;
        int nivel = par.second;
        fila.pop();

        if (no->dir != nullptr) fila.push(make_pair(no->dir, nivel + 1));
        if (no->esq != nullptr) fila.push(make_pair(no->esq, nivel + 1));

        cout << "Nível " << nivel << ": " << no->key << " " << no->cor << endl;
    }
    cout << endl;
}

#endif