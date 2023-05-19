#include <iostream>
#include "TSABB.h"

int main() {
    TSABB<int, std::string> tree;

    // Adicionar elementos à árvore
    tree.add(10, "Alice");
    tree.add(5, "Bob");
    tree.add(15, "Charlie");
    tree.add(3, "David");
    tree.add(7, "Eve");

    return 0;
}