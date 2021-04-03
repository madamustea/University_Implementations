#include <iostream>
#include"SortedMultiMap.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
	testAll();
	testRemoveKey();
	testAllExtended();

	


	std::cout << "Finished SMM Tests!" << std::endl;
	
	system("pause");
}
