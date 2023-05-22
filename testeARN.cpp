#include <iostream>
#include "TSARN.h"

using namespace std;

int main() {
    ARN<int, int> tree;
    cout << "------------------------------------" <<endl;
    tree.add(23, 2);
    tree.add(8, 2 );
    tree.add(72, 2);
    tree.add(45, 2); 
    tree.add(20, 2); 
    tree.add(22, 2); 
    tree.add(54, 2); 
    tree.add(5, 2);
    tree.add(4, 2); 
    tree.add(3, 2); 

    cout << "------------------------------------" <<endl;

    cout <<"Raiz = " << tree.raiz->key << " Cor = "<< tree.raiz->cor<< endl;
    cout <<"Raiz esq = " << tree.raiz->esq->key << " Cor esq = "<< tree.raiz->esq->cor<< endl;


    return 0;
}