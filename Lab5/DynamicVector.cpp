#include "DynamicVector.h"
#include <string>
using namespace std;
DynamicVector::DynamicVector(int capacity) {
	this->size = 0;
	this->capacity = capacity;
	this->elements = new TElem[capacity];
}

DynamicVector::DynamicVector(const DynamicVector& d) {
	this->size = d.size;
	this->capacity = d.capacity;
	this->elements = new TElem[this->capacity];
	for (int index = 0; index < this->size; index++)
		this->elements[index] = d.elements[index];
}

DynamicVector::~DynamicVector() {
	delete[] this->elements;
}

DynamicVector& DynamicVector::operator=(const DynamicVector& d) {
	if (this == &d)
		return *this;
	this->size = d.size;
	this->capacity = d.capacity;
	delete[] this->elements;
	this->elements = new TElem[this->capacity];
	for (int index = 0; index < this->size; index++)
		this->elements[index] = d.elements[index];
	return *this;
}

void DynamicVector::add(const TElem& e) {
	if (this->size == this->capacity)
		this->resize();
	this->elements[this->size] = e;
	this->size++;
}

void DynamicVector::update(const TElem& e) {
	for (int index = 0; index < this->size; index++)
		if (this->elements[index].getCodedName() == e.getCodedName())
			this->elements[index] = e;
}

void DynamicVector::remove(const std::string& identifier) {
	int position;
	for (int index = 0; index < this->size; index++) 
		if (this->elements[index].getCodedName() == identifier) {
			position = index;
			break;
		}
	for (int index = position; index < this->size - 1; index++) 
		this->elements[index] = this->elements[index + 1];
	this->size--;
		
	
}

int DynamicVector::exist(const std::string& identifier) {
	for (int index = 0; index < this->size; index++)
		if (this->elements[index].getCodedName() == identifier)
			return 1;
	return -1;
}
void DynamicVector::resize(double new_capacity) {
	this->capacity *= static_cast <int> (new_capacity);
	TElem* new_elements = new TElem[this->capacity];
	for (int index = 0; index < this->size; index++)
		new_elements[index] = this->elements[index];
	delete[] this->elements;
	this->elements = new_elements;
}

int DynamicVector::getSize() {
	return this->size;
}

int DynamicVector::getCapacity() {
	return this->capacity;
}

TElem DynamicVector::getElement(int position) {
	return this->elements[position];
}


