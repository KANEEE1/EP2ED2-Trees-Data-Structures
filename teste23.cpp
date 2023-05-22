#include <iostream>
#include "TSA23.h"

using namespace std;

int main() {
    //TREAP<int, std::string> tree;
    bool eh23 = true;
    //for (int n = 0; n < 50; n++){
    A23<int, std::string> tree;
    cout << "------------------------------------" <<endl;
    tree.add(50, "Alice");
    tree.add(10, "Bob");
    tree.add(90, "Charlie");
    tree.add(1, "David"); 
    tree.add(99, "cedro"); 
    tree.add(30, "Pedaddasro"); 
    tree.add(40, "tedtero"); 
    tree.add(35, "x"); 
/*     tree.add(22, "ledro"); 
    tree.add(19, "bedrodadas");
    tree.add(14, "x");
    tree.add(13, "y");
    tree.add(17, "yz"); 
    tree.add(39, "yz"); */ 
    cout << "------------------------------------" <<endl;

    cout <<"Raiz key1 = " << tree.raiz->key1 << endl;
    cout <<"Raiz key2 = " << tree.raiz->key2 << endl;
    cout << "                                                "<<endl;
    cout <<"Less key1 = " << tree.raiz->less->key1 << endl;
    cout <<"Less key2 = " << tree.raiz->less->key2 << endl;
    cout <<"Less Less key1 = " << tree.raiz->less->less->key1 << endl;
    cout <<"Less Less key2 = " << tree.raiz->less->less->key2 << endl;
    cout <<"Less High key1 = " << tree.raiz->less->high->key1 << endl;
    cout <<"Less High key2 = " << tree.raiz->less->high->key2 << endl;
    cout << "                                                "<<endl; 
/*     cout <<"Bet key1 = " << tree.raiz->between->key1 << endl;
    cout <<"Bet key2 = " << tree.raiz->between->key2 << endl;
    cout <<"Bet Less key1 = " << tree.raiz->between->less->key1 << endl;
    cout <<"Bet Less key2 = " << tree.raiz->between->less->key2 << endl;
    cout <<"Bet Bet key1 = " << tree.raiz->between->between->key1 << endl;
    cout <<"Bet Bet key2 = " << tree.raiz->between->between->key2 << endl;
    cout <<"Bet High key1 = " << tree.raiz->between->high->key1 << endl;
    cout <<"Bet High key2 = " << tree.raiz->between->high->key2 << endl; */
    cout << "                                                "<<endl; 
    cout <<"High key1 = " << tree.raiz->high->key1 << endl;
    cout <<"High key2 = " << tree.raiz->high->key2 << endl;
    cout <<"High Less key1 = " << tree.raiz->high->less->key1 << endl;
    cout <<"High Less key2 = " << tree.raiz->high->less->key2 << endl;
    cout <<"High High key1 = " << tree.raiz->high->high->key1 << endl;
    cout <<"High High key2 = " << tree.raiz->high->high->key2 << endl; 


    return 0;
}