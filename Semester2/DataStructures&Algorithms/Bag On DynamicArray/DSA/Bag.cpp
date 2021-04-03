#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	this->CapacityU = 10;
	this->nrOfElemetsU = 0;
	this->arrayU = new TElem[this->CapacityU];
	this->CapacityP = 9999;
	this->nrOfElementsP = 0;
	this->arrayP = new TElem[this->CapacityP];
}
void Bag::initializeU(int start) {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	for (int i = start; i < this->CapacityU; i++) {
		this->arrayU[i] = 0;

	}
}
void Bag::initializeP(int start) {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	for (int i = start; i < CapacityP; i++) {
		this->arrayP[i] = 0;
	}
}
void Bag::expandU() {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	this->CapacityU *= 2;
	TElem* tempArray = new TElem[this->CapacityU];
	for (int i = 0; i < this->nrOfElemetsU; i++) {
		tempArray[i] = this->arrayU[i];
	}
	delete[] this->arrayU;
	this->arrayU = tempArray;
	initializeU(this->nrOfElemetsU+1);

}
void Bag::expandP() {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	this->CapacityP *= 2;
	
	TElem* tempArray = new TElem[this->CapacityP];
	for (int i = 0; i < this->nrOfElementsP; i++) {
		tempArray[i] = this->arrayP[i];
	}
	delete[] this->arrayP;
	this->arrayP = tempArray;
	initializeU(this->nrOfElementsP+1);

}
void Bag::add(TElem elem) {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	int position = 0;
	if (search(elem) == true) {
		for (int i = 0; i < this->nrOfElemetsU; i++)
		{
			if (this->arrayU[i] == elem)
			{
				position = i;
				break;
			}
		}
		if (this->nrOfElementsP + 1 == this->CapacityP)
			expandP();

		this->arrayP[this->nrOfElementsP++] = position;
	}

	else {
	if (this->nrOfElemetsU + 1 == this->CapacityU)expandU();
	this->arrayU[this->nrOfElemetsU++] = elem;
		if (this->nrOfElementsP + 1 == this->CapacityP)expandP();
	this->arrayP[this->nrOfElementsP++] = this->nrOfElemetsU - 1;
	}


}
int Bag::getPositionOfElementInU(TElem e) {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	for (int i = 0; i < this->nrOfElemetsU; i++)
	{
		if (this->arrayU[i] == e)
		{
			return i;
		}
	}
	return 0;
}
int Bag::getPositionOfElementInP(TElem e) {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/

	for (int i = 0; i < this->nrOfElementsP; i++)
	{
		if (this->arrayP[i] == e)
		{
			return i;
		}
	}
	return 0;
}


bool Bag::remove(TElem elem) {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	
		if (!search(elem))
			return false;
		int positionInU = getPositionOfElementInU(elem);
		int positionInP = getPositionOfElementInP(positionInU);

		if (this->nrOccurrences(elem) == 1)
		{
			//delete from U
			for (int i = positionInU; i < this->nrOfElemetsU - 1; i++)
			{
				this->arrayU[i] = this->arrayU[i + 1];
			}
			this->nrOfElemetsU--;

			//delete from P
			for (int i = positionInP; i < this->nrOfElementsP - 1; i++)
			{
				this->arrayP[i] = this->arrayP[i + 1];
			}
			this->nrOfElementsP--;
			//decerement positions
			for (int i = 0; i < this->nrOfElementsP; i++)
			{
				if (this->arrayP[i] > positionInU)
					arrayP[i]--;
			}
		}
		else
		{
			//delete from P
			for (int i = positionInP; i < this->nrOfElementsP - 1; i++)
			{
				this->arrayP[i] = this->arrayP[i + 1];
			}
			this->nrOfElementsP--;
		}
		return true;
	}



bool Bag::search(TElem elem) const {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	int ok = 0;
	
	for (int i = 0; i < this->nrOfElemetsU; i++)
	{
		if (this->arrayU[i] == elem) ok = 1;
	}
	if (ok == 1){ return true; }
	else return false;
}

int Bag::nrOccurrences(TElem elem) const {
	/*Worst Case-Theta(n)
	Best Case-Theta(1)
	Average Case-Theta(n)*/
	int position = 0, nr = 0, ok = 0;
	for (int i = 0; i < this->nrOfElemetsU; i++) {
		
		if (this->arrayU[i] == elem)
		{
			position = i;
			ok = 1;
			break;
		}
	}
	if (ok == 0)return 0;
	
	
	for (int j = 0; j < this->nrOfElementsP; j++) {

		
		if (this->arrayP[j] == position)nr++;
	}
	;
	return nr;
	
}


int Bag::size() const {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	return this->nrOfElementsP;
}


bool Bag::isEmpty() const {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	if (this->nrOfElemetsU == 0)return true;
	else return false;
}

BagIterator Bag::iterator() const {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	
	return BagIterator(*this);
}


Bag::~Bag() {
	/*Worst Case-Theta(1)
	Best Case-Theta(1)
	Average Case-Theta(1)*/
	delete[] arrayU;
	delete[] arrayP;
}

