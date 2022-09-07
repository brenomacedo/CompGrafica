#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"

using std::string;



int main () {

    Vector estranho (1, 2, 3);
    Vector estranhoSoma (1, 2, 3);
    Vector estranho2 = estranho * estranhoSoma;
    std::cout << estranho2[1] << std::endl;

    return 0;
}