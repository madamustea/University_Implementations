#include <iostream>
//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
    
    testAll();
    
    testAllExtended();
    testMostFrequent();

    std::cout << "Finished SMM Tests!" << std::endl;
    system("pause");
}
