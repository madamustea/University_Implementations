#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
{
	this->current = 0;
	
}

void BagIterator::first() {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	this->current = 0;
}


void BagIterator::next() {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	if (valid() == false) throw std::exception();
	else this->current++;
}


bool BagIterator::valid() const {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	if ((this->current >= 0) && (this->current < bag.nrOfElementsP)) return true;
	else return false;
}



TElem BagIterator::getCurrent() const
{/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	if (valid() == false)throw std::exception();
	else return bag.arrayU[bag.arrayP[current]];
}

void BagIterator::last() {
	this->current = bag.nrOfElementsP-1;
}
bool BagIterator::valid2() const {
	return (this->current > 0) && (this->current <= bag.nrOfElementsP);
}
void BagIterator::previous()
{/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)
	The pseudocode for the function:
	subalgorith previous is:
		if this.current<=0 && this.current>bag.nrOfElemetsP then
			throw Exception
		else
			this.current--;
		end-if
		
		
	end-subalgorithm*/
	if ((this->current <= 0) && (this->current > bag.nrOfElementsP))throw std::exception();
	
	else this->current--;
}
