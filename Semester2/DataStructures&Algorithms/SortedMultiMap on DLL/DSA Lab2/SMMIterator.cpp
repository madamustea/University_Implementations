#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include<stdexcept>
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	this->current = map.dllMap->head;
}

void SMMIterator::first() {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	this->current = map.dllMap->head;
}

void SMMIterator::next() {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	if (!valid()) throw std::exception();
	else if (this->current != NULL)
	{
		this->current = this->current->next;
	}
}


bool SMMIterator::valid() const {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	if (this->current == NULL)return false;
	else return true;
}

TElem SMMIterator::getCurrent() const {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	if (!valid()) throw std::exception();
	return this->current->info;
}


