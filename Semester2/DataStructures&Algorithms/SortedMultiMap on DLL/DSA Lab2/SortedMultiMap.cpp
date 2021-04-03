#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {

	this->dllMap = new DLL();
	this->dllMap->head = NULL;
	this->dllMap->tail = NULL;
	this->relation = r;
}



void SortedMultiMap::add(TKey c, TValue v) {
	/*Best Case-theta(1)
	Worst Case-theta(n)
	Average Case-theta(n)*/
	Node* newNode = new Node();
	newNode->info.first = c;
	newNode->info.second = v;
	newNode->next = NULL;
	newNode->prev = NULL; 
	
	if(this->dllMap->head == NULL) {
		this->dllMap->head = newNode;
		this->dllMap->tail = newNode;
	}
	else if (this->dllMap->head == this->dllMap->tail)
	{
		if (!(this->relation(newNode->info.first, c)))
		{
			newNode->next = this->dllMap->head;
			this->dllMap->head->prev = newNode;
			this->dllMap->head = newNode;
		}
		else
		{
			newNode->prev = this->dllMap->head;
			this->dllMap->head->next = newNode;
			this->dllMap->tail = newNode;
		}
	}
	else {
		Node* currentNode = this->dllMap->head;
		while ((currentNode->next != NULL) && (this->relation(currentNode->info.first, c))) {
			currentNode = currentNode->next;
		}
		if (currentNode == this->dllMap->head)
		{
			if ((this->relation(c, currentNode->info.first)))
			{
				newNode->next = this->dllMap->head;
				this->dllMap->head->prev = newNode;
				this->dllMap->head = newNode;
			}
			else
			{
				newNode->next = this->dllMap->head->next;
				newNode->prev = this->dllMap->head;
				this->dllMap->head->next = newNode;
			}
		}
		else if (currentNode == this->dllMap->tail)
		{
			if (!(this->relation(c, currentNode->info.first)))
			{
				newNode->prev = this->dllMap->tail;
				newNode->next = nullptr;
				this->dllMap->tail->next = newNode;
				this->dllMap->tail = newNode;
			}
			else
			{
				newNode->next = this->dllMap->tail;
				newNode->prev = this->dllMap->tail->prev;
				this->dllMap->tail->prev->next = newNode;
				this->dllMap->tail->prev = newNode;
			}

		}
		else
		{
			if ((this->relation(c, currentNode->info.first)))
			{
				newNode->next = currentNode;
				newNode->prev = currentNode->prev;
				currentNode->prev->next = newNode;
				currentNode->prev = newNode;
			}
			else
			{
				newNode->next = currentNode->next;
				newNode->prev = currentNode;
				currentNode->next = newNode;
			}
		}
	}
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	/*Best Case-theta(1)
	Worst Case-theta(n)
	Average Case-theta(n)*/
	Node* temp;
	vector<TValue> vector;
	temp = this->dllMap->head;
	while (temp != NULL) {
		if (temp->info.first == c) {
			vector.push_back(temp->info.second);
		}
		temp = temp->next;
	}
	return vector;
}



bool SortedMultiMap::remove(TKey c, TValue v) {
	/*Best Case-theta(1)
	Worst Case-theta(n)
	Average Case-theta(n)*/
	if (this->isEmpty())
		return false;
	Node* currentNode;
	currentNode = this->dllMap->head;
	if ((currentNode ==this->dllMap->tail)&& (currentNode->info.first == c) && (currentNode->info.second == v)) {
		delete currentNode;
		this->dllMap->head = NULL;
		this->dllMap->tail = NULL;
		return true;
	}
	while (currentNode != NULL) {
		if ((currentNode->info.first == c) && (currentNode->info.second == v))
		{
			if (currentNode == this->dllMap->head) {
				this->dllMap->head = this->dllMap->head->next;
				this->dllMap->head->prev = NULL;
				delete currentNode;
			}
			else if (currentNode == this->dllMap->tail) {
				this->dllMap->tail = this->dllMap->tail->prev;
				this->dllMap->tail->next = NULL;
				delete currentNode;
			}
			else
			{
				currentNode->next->prev = currentNode->prev;
				currentNode->prev->next = currentNode->next;
				delete currentNode;
			}
			return true;
		}
		currentNode = currentNode->next;
	}

	return false;
}

vector<TValue> SortedMultiMap::removeKey(TKey key)
{
	vector<TValue>Values;
	
	/*Best Case-theta(1)
	Worst Case-theta(n)
	Average Case-theta(n)*/
	Node* node;
	node = this->dllMap->head;
	bool ok = 1;
	while (ok) {
		ok = 0;
		if(node)
		if (this->remove(key, node->info.second))
		{
			Values.push_back(node->info.second);
			ok = 1;
		}
		
		node = this->dllMap->head;
	}
	
	
	return Values;


}

int SortedMultiMap::size() const {
	/*Best Case-theta(1)
	Worst Case-theta(n)
	Average Case-theta(n)*/
	Node* node = this->dllMap->head;
	if(this->dllMap->tail)
	this->dllMap->tail->next = NULL;
	int size = 0;
	while (node!=NULL)
	{
		size++;
		node = node->next;
	}
	return size;
}

bool SortedMultiMap::isEmpty() const {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	if (size()==0)return true;
	else return false;
}

SMMIterator SortedMultiMap::iterator() const {
	/*Best Case-theta(1)
	Worst Case-theta(1)
	Average Case-theta(1)*/
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	Node* n = this->dllMap->head;
	while (n) {
		
		Node* next = n->next;
		delete n;
		n = next;
	}
	
}
