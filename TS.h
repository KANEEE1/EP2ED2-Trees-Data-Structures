#ifndef TS_H
#define TS_H
#include<string>
#include <iostream>
using namespace std;

template <class Key, class Item>
class Node{
    public:
        //Node(){};
        Node(Key key, Item val, int N) {};
        Key key;
        Item val;
        Node * esq;
        Node * dir;
        int N;
    };



template <class Key, class Item>

class TS {
    public:
        virtual void add(Key key, Item val) = 0;
        virtual Item value(Key key) = 0;
        /* virtual int rank(Key key){};
        virtual Key select(int k){}; */
};

#endif