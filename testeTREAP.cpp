#include <iostream>
#include "TREAP.h"

using namespace std;

int main() {
    TREAP<int, std::string> treap;

    treap.add(5, "Alice");
    treap.add(10, "Bob");
    treap.add(15, "Charlie");
    treap.add(3, "David");
    treap.add(99, "Pedro"); 
    treap.add(41, "Pedro"); 
    treap.add(51, "Pedro"); 
    treap.add(86, "Pedro"); 
    treap.add(15, "Pedro"); 
    treap.add(94, "Pedro"); 

    // Verificar se a árvore é uma BST
/*     bool isBSTResult = treap.isBST(treap.raiz);
    if (isBSTResult) {
        cout << "A árvore é uma BST" << endl;
    } else {
        cout << "A árvore não é uma BST" << endl;
    } */

    // Obter o valor correspondente a uma chave
/*     int key = 5;
    string value = treap.value(key);
    cout << "Valor correspondente à chave " << key << ": " << value << endl; */

    // Obter o tamanho da árvore
    /* int treapSize = size(treap.raiz);
    cout << "Tamanho da árvore: " << treapSize << endl; */

    cout << treap.raiz->priority << endl;

    return 0;
}