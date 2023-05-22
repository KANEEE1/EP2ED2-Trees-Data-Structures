#ifndef TSA23_H
#define TSA23_H
#include "TS.h"

#include <iostream>
using namespace std;


template <class Key, class Item>
class Node23 : public Node<Key, Item>{
    public:
    Node23(){};
    Node23(Key key, Item val, bool twoNode);

    Key key1;
    Item val1;
    Key key2;
    Item val2;

    Node23 * less;      // Aponta para os menores que key1
    Node23 * between;   // Aponta para os entre key1 e key2
    Node23 * high;      // Aponta para os maiores que key2

    bool twoNode;
    bool leaf();

};


template <class Key, class Item>
Node23<Key, Item>::Node23(Key key, Item val, bool twoNode) : Node<Key, Item>(key, val, twoNode), key1(key), val1(val), twoNode(twoNode), less(nullptr), between(nullptr), high(nullptr) {}

template <class Key, class Item>
bool Node23<Key, Item>::leaf(){
    return (less == nullptr &&  between == nullptr && high == nullptr);
}

template <class Key, class Item>
class A23: public TS<Key,Item>{
    private:
        bool cresceu;  

    public:
        Node23<Key, Item> *raiz;  // tirei do privado para testar e conseguir acessar a raiz
        A23();
        ~A23();
        void add(Key key, Item val);
        Item value(Key key);
        bool isA23(Node23<Key, Item>* raiz);
        //void remove(Key key);
};

template <class Key, class Item>
A23<Key, Item>::A23() :  raiz(nullptr) {}

template <class Key, class Item>
A23<Key, Item>::~A23() {
    // Implemente a lógica de destruição da árvore ou liberação de memória aqui
}

template <class Key, class Item>
Node23<Key, Item>* put(Node23<Key, Item>*& raiz, Key key, Item val, bool& cresceu) {
    if (raiz == nullptr) {
        cresceu = true;
        raiz = new Node23<Key, Item>(key, val, true);
        return raiz;
    }

    if (raiz->leaf()) {
        if (raiz->twoNode) {
            if (key == raiz->key1) {
                raiz->val1 = val;
                return raiz;
            } 
            else if (key < raiz->key1) {
                raiz->key2 = raiz->key1;
                raiz->val2 = raiz->val1;
                raiz->key1 = key;
                raiz->val1 = val;
            } 
            else {               
                raiz->key2 = key;
                raiz->val2 = val;
            }
            raiz->twoNode = false;
            cresceu = false;
            return raiz;
        } 
        else {
            if (key == raiz->key1 || key == raiz->key2) {
                // Atualizar o valor se a chave já existir
                if (key == raiz->key1) {
                    raiz->val1 = val;
                } else {
                    raiz->val2 = val;
                }
                return raiz;
            } 
            else {
                // Split ocorre quando a folha está cheia
                Node23<Key, Item>* novaRaiz = new Node23<Key, Item>();
                Node23<Key, Item>* novoNo1 = new Node23<Key, Item>();
                Node23<Key, Item>* novoNo2 = new Node23<Key, Item>();

                if (key < raiz->key1) {
                    novaRaiz->key1 = raiz->key1;
                    novaRaiz->val1 = raiz->val1;
                    novoNo1->key1 = key;
                    novoNo1->val1 = val;
                    novaRaiz->less = novoNo1;
                    novoNo2->key1 = raiz->key2;
                    novoNo2->val1 = raiz->val2;
                    novaRaiz->high = novoNo2;
                } else if (key < raiz->key2) {
                    novaRaiz->key1 = key;
                    novaRaiz->val1 = val;
                    novoNo1->key1 = raiz->key1;
                    novoNo1->val1 = raiz->val1;
                    novaRaiz->less = novoNo1;
                    novoNo2->key1 = raiz->key2;
                    novoNo2->val1 = raiz->val2;
                    novaRaiz->high = novoNo2;
                } else {
                    novaRaiz->key1 = raiz->key2;
                    novaRaiz->val1 = raiz->val2;
                    novoNo1->key1 = raiz->key1;
                    novoNo1->val1 = raiz->val1;
                    novaRaiz->less = novoNo1;
                    novoNo2->key1 = key;
                    novoNo2->val1 = val;
                    novaRaiz->high = novoNo2;
                }
                
                novaRaiz->twoNode = true;
                novaRaiz->less->twoNode = true;
                novaRaiz->high->twoNode = true;

                raiz = novaRaiz;
                cresceu = true;
                return raiz;
            }
        }
    } 
    else {
        if (key < raiz->key1) {
            Node23<Key, Item>* subarvore = put(raiz->less, key, val, cresceu);
            if (cresceu) {
                if (raiz->twoNode) {
                    raiz->key2 = raiz->key1;
                    raiz->val2 = raiz->val1;
                    raiz->key1 = subarvore->key1;
                    raiz->val1 = subarvore->val1;
                    raiz->less = subarvore->less;
                    raiz->between = subarvore->high;

                    raiz->twoNode = false;
                    cresceu = false;
                } 
                else {
                    Node23<Key, Item>* novaRaiz = new Node23<Key, Item>();
                    Node23<Key, Item>* novoNo2 = new Node23<Key, Item>();
                    novaRaiz->key1 = raiz->key1;
                    novaRaiz->val1 = raiz->val1;
                    novaRaiz->less = subarvore;                   
                    
                    novoNo2->key1 = raiz->key2;
                    novoNo2->val1 = raiz->val2;
                    novoNo2->less = raiz->between;
                    novoNo2->high = raiz->high;
                    novaRaiz->high = novoNo2;

                    novaRaiz->twoNode = true;
                    novoNo2->twoNode = true;
                    novaRaiz->less->twoNode= true;

                    cresceu = true;

                    raiz = novaRaiz;
                }
            }
        }
        else if (raiz->twoNode && key > raiz->key1) {
            Node23<Key, Item>* subarvore = put(raiz->high, key, val, cresceu);
            if (cresceu) {
                if (raiz->twoNode) {
                    raiz->key2 = subarvore->key1;
                    raiz->val2 = subarvore->val1;
                    raiz->between = subarvore->less;
                    raiz->high = subarvore->high;

                    raiz->twoNode = false;
                    cresceu = false;
                } else {
                    Node23<Key, Item>* novoNo = new Node23<Key, Item>();
                    novoNo->key1 = raiz->key2;
                    novoNo->val1 = raiz->val2;
                    novoNo->less = subarvore->less;
                    novoNo->high = raiz->high;
                    raiz->key2 = subarvore->key1;
                    raiz->val2 = subarvore->val1;
                    raiz->between = subarvore->less;
                    raiz->high = novoNo;

                    cresceu = false;
                }
            }
        }
        else if (!(raiz->twoNode) && key < raiz->key2){
            Node23<Key, Item>* subarvore = put(raiz->between, key, val, cresceu);
            if (cresceu) {
                Node23<Key, Item>* novoNo1= new Node23<Key, Item>();
                Node23<Key, Item>* novoNo2 = new Node23<Key, Item>();
                Node23<Key, Item>* novoNo3 = new Node23<Key, Item>();

                novoNo1->key1 = subarvore->key1;
                novoNo1->val1 = subarvore->val1;;

                novoNo2->key1 = raiz->key1;
                novoNo2->val1 = raiz->val1;
                novoNo2->less = raiz->less;
                novoNo2->high = subarvore->less;
                cout << novoNo2->twoNode << endl;

                novoNo3->key1 = raiz->key2;
                novoNo3->val = raiz->val2;
                novoNo3->high = raiz->high;
                novoNo3->less = subarvore->high;
                cout << novoNo3->twoNode << endl;

                novoNo2->twoNode = true;
                novoNo3->twoNode = true;
                novoNo1->twoNode = true;
                novoNo1->less = novoNo2;
                novoNo1->high = novoNo3;

                raiz = novoNo1;
                cout << raiz->twoNode << endl;

                cresceu = true;
                }
            }
        else {
            Node23<Key, Item>* subarvore = put(raiz->high, key, val, cresceu);
            if (cresceu) {
                if(raiz->twoNode){
                Node23<Key, Item>* novoNo = new Node23<Key, Item>();
                Node23<Key, Item>* novoNo2 = new Node23<Key, Item>();
                    raiz->key2 = subarvore->key1;
                    raiz->val2 = subarvore->val1;
                    novoNo->key1 = subarvore->less->key1; 
                    novoNo->val1 = subarvore->less->val1; 
                    raiz->between = novoNo;
                    novoNo2->key1 = subarvore->high->key1;
                    novoNo2->val1 = subarvore->high->val1;
                    raiz->high = novoNo2;


                    raiz->twoNode = false;
                    raiz->high->twoNode = true;
                    
                }
                else {
                    Node23<Key, Item>* novaRaiz = new Node23<Key, Item>();
                    Node23<Key, Item>* novoNo1 = new Node23<Key, Item>();
                    Node23<Key, Item>* novoNo2 = new Node23<Key, Item>();

                    novaRaiz->key1 = raiz->key2;
                    novaRaiz->val1 = raiz->val2;

                    novoNo1->key1 = raiz->key1;
                    novoNo1->val1 = raiz->val1;
                    novoNo1->less = raiz->less;
                    novoNo1->high = raiz->between;
                    novaRaiz->less = novoNo1;

                    novoNo2->key1 = key;
                    novoNo2->val1 = val;
                    novoNo2->less = subarvore->less;
                    novoNo2->high = subarvore->high;
                    novaRaiz->high = novoNo2;    

                    raiz = novaRaiz;    

                    raiz->less->twoNode = true;         
                    raiz->high->twoNode = true;      
                    raiz->twoNode = true;

                }
                cresceu = false;
            }
        }
            
    }
    return raiz;
}



template <class Key, class Item>
void A23<Key, Item>::add(Key key, Item val){
    put(raiz, key, val, cresceu);
}

template <class Key, class Item>
bool A23<Key, Item>::isA23(Node23<Key, Item>* raiz){
    return true;
}

template <class Key, class Item>
Item find(Node23<Key, Item> * raiz, Key key){
    if(raiz == nullptr) return Item();
    if(raiz->twoNode){
        if(raiz->key1 == key) return raiz->val1;
        if(raiz->key1 > key) return get(raiz->less, key);
        if(raiz->key1 < key) return get(raiz->high, key);
    }
    else{
        if(raiz->key1 == key) return raiz->val1;
        if(raiz->key2 == key) return raiz->val2;
        if(raiz->key1 > key) return get(raiz->less, key);
        if(raiz->key2 > key && key > raiz->key1) return get(raiz->between, key);
        if(raiz->key2 < key) return get(raiz->high, key);
    }
}

template <class Key, class Item>
Item A23<Key, Item>::value(Key key){
    return Item();
}

#endif