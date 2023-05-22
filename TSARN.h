#ifndef TSARN_H
#define TSARN_H

#include "TS.h"

#include <iostream>
#include <string>

using namespace std;

template <class Key, class Item>
class NodeARN : public Node<Key, Item> {
public:
    NodeARN() : Node<Key, Item>(), pai(pai), esq(nullptr), dir(nullptr), cor('\0') {}
    NodeARN(Key key, Item val, char cor, NodeARN* pai) : Node<Key, Item>(key, val, 0), pai(pai), esq(nullptr), dir(nullptr), cor(cor) {}

    NodeARN* pai;
    NodeARN* esq;
    NodeARN* dir;
    char cor;
};

template <class Key, class Item>
class ARN : public TS<Key, Item> {
    private:
        Key key;
        Item val;
        char cor;
        //NodeARN<Key, Item>* raiz;
        NodeARN<Key, Item>* put(NodeARN<Key, Item>* &raiz, Key key, Item val);
        NodeARN<Key, Item>* rodaEsq(NodeARN<Key, Item>* raiz);
        NodeARN<Key, Item>* rodaDir(NodeARN<Key, Item>* raiz);

    public:
        ARN();
        NodeARN<Key, Item>* raiz;
        void add(Key key, Item val);
        Item value(Key key);
};

template <class Key, class Item>
ARN<Key, Item>::ARN() : key(), val(), cor(), raiz(nullptr) {}

template <class Key, class Item>
NodeARN<Key, Item>* ARN<Key, Item>::rodaEsq(NodeARN<Key, Item>* r) {
    NodeARN<Key, Item>* q = r->dir;
    if (q == nullptr)
        return r;
    if (r->pai != nullptr)
        r->pai->dir = q;
    q->pai = r->pai;
    r->dir = q->esq;
    r->pai = q;
    q->esq = r;
    if (r->dir != nullptr)
        r->dir->pai = r;
    return q;
}

template <class Key, class Item>
NodeARN<Key, Item>* ARN<Key, Item>::rodaDir(NodeARN<Key, Item>* q) {
    NodeARN<Key, Item>* r = q->esq;
    if (q->pai != nullptr)
        q->pai->esq = r;
    r->pai = q->pai;
    q->pai = r;
    q->esq = r->dir;
    r->dir = q;
    if (q->esq != nullptr)
        q->esq->pai = q;
    return r;
}

template <typename Key, typename Item>
NodeARN<Key, Item>* ARN<Key, Item>::put(NodeARN<Key, Item>* &raiz, Key key, Item val) {
    if (raiz == nullptr) {
        raiz = new NodeARN<Key, Item>(key, val, 'r', nullptr);
        cout << raiz->key << endl;
        return raiz;
    }

    NodeARN<Key, Item>* p = raiz;
    bool achou = false;
    cout << p->key << endl;
    cout << key <<endl;
    while (!achou) {
        if (p->key == key) {
            p->val = val;
            return raiz;
        } else if (key < p->key) {
            if (p->esq != nullptr) {
                p = p->esq;
            } else {
                achou = true;
            }
        } else {
            if (p->dir != nullptr) {
                p = p->dir;
            } else {
                achou = true;
            }
        }
    }

    NodeARN<Key, Item>* novo = new NodeARN<Key, Item>(key, val, 'r', p);
    NodeARN<Key, Item>* filho = novo;
    if (key < p->key) {
        p->esq = filho;
    } else {
        p->dir = filho;
    }

    while (true) {
        if (p->cor == 'b') {
            break;
        }

        NodeARN<Key, Item>* avo = p->pai;
        if (avo == nullptr) {
            p->cor = 'b';
            break;
        }

        NodeARN<Key, Item>* tio = nullptr;
        if (p == avo->esq) {
            tio = avo->dir;
        } else {
            tio = avo->esq;
        }

        if (tio != nullptr && tio->cor == 'r') {
            avo->cor = 'r';
            p->cor = tio->cor = 'b';
            filho = avo;
            p = avo->pai;
            if (p == nullptr) {
                break;
            }
        } else {
            if (p == avo->esq && filho == p->esq) {
                NodeARN<Key, Item>* q = rodaDir(avo);
                q->cor = 'b';
                avo->cor = 'r';
                if (raiz == avo) {
                    raiz = q;
                }
                break;
            } else if (p == avo->esq && filho == p->dir) {
                NodeARN<Key, Item>* q = rodaEsq(p);
                NodeARN<Key, Item>* r = rodaDir(avo);
                r->cor = 'b';
                avo->cor = 'r';
                if (raiz == avo) {
                    raiz = r;
                }
                break;
            } else if (p == avo->dir && filho == p->dir) {
                NodeARN<Key, Item>* q = rodaEsq(avo);
                q->cor = 'b';
                avo->cor = 'r';
                if (raiz == avo) {
                    raiz = q;
                }
                break;
            } else {
                NodeARN<Key, Item>* q = rodaDir(p);
                NodeARN<Key, Item>* r = rodaEsq(avo);
                r->cor = 'b';
                avo->cor = 'r';
                if (raiz == avo) {
                    raiz = r;
                }
                break;
            }
        }
    }

    raiz->cor = 'b';
    return raiz;
}


template <class Key, class Item>
void ARN<Key, Item>::add(Key key, Item val) {
    put(raiz, key, val);
}

template <class Key, class Item>
Item find(NodeARN<Key, Item>* raiz, Key key) {
    if (raiz == nullptr)
        return Item();
    if (raiz->key == key)
        return raiz->val;
    if (raiz->key > key)
        return find(raiz->esq, key);
    return find(raiz->dir, key);
}

template <class Key, class Item>
Item ARN<Key, Item>::value(Key key) {
    return find(raiz, key);
}

#endif