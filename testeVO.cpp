#include "TSVO.h"
#include <iostream>

using namespace std;

int main() {
    TSVO<int, string> tsvo;
    tsvo.add(0, "Primeiro");
    tsvo.add(1, "Segundo");
    tsvo.add(2, "Terceiro");
    tsvo.add(27, "Macaco");
    tsvo.add (15, "1.5");
    
    //std::cout << tsvo.value(1) << std::endl; // Saída: "Segundo"
    
    tsvo.resize();
    
/*     int rank = tsvo.rank(3);
    std::cout << "Rank: " << rank << std::endl; // Saída: Rank: 2
    
    int selectedKey = tsvo.select(1);
    std::cout << "Selected Key: " << selectedKey << std::endl; // Saída: Selected Key: 2 */
    
    tsvo.show(5); // Saída: 1 2 3
    tsvo.add(1, "Flinstons");
    cout << endl;
    tsvo.show(5);

    /*
    //tsvo.show(3);
    cout << endl;
    std::cout << tsvo.value(1) << std::endl; */
    return 0;
}