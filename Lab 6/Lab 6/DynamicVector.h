#pragma once
#include <algorithm>
#include <iterator>

template <typename TElem>


class DynamicVector {
    
  private:

    TElem* elements;
    int size;
    int capacity;

  public:
    ///default constructor
    DynamicVector(int capacity=10);

    ///constructor
    DynamicVector(const DynamicVector& d);

    ///destructor
    ~DynamicVector();

    ///define the operator
    DynamicVector& operator=(const DynamicVector& d);

    ///return the size of the elements
    int getSize();

    ///returns an element according to its position
    TElem getElement(int position);

    /// add an element
    void add(const TElem& e);

    ///update a specific element
    void update(const TElem& e);

    ///remove a specific element
    void remove(const std::string& identifier);

    ///returns 1 if there exists such an element, and -1 otherwise
    int exist(const std::string& identifier);

    ///returns the capacity of the vector
    int getCapacity();

   private:
    ///extened the size of the elements if needed
    void resize(double new_capacity=2);

public:
    class iterator {
    private:
        TElem* pointer;

    public:
        iterator() = default;
        iterator(TElem* ptr) :pointer{ ptr } {}
        TElem operator*();
        bool operator!=(const iterator& it);
        typename iterator operator++();
        typename iterator operator++(int x);
        bool operator==(const iterator& it);

    };

public:
    typename iterator begin();
    typename iterator end();

    
};

template <class TElem>
inline DynamicVector<TElem>::DynamicVector(int capacity) :size{ 0 }, capacity{ capacity }
{
    elements = new TElem[capacity];
}

template <class TElem>
inline DynamicVector<TElem>::DynamicVector(const DynamicVector& d) {
    size = d.size;
    capacity = d.capacity;
    elements = new TElem[capacity];
    for (int index = 0; index < size; index++)
        elements[index] = d.elements[index];
}

template <class TElem>
inline DynamicVector<TElem>::~DynamicVector() {
    delete[]elements;
}

template <class TElem>
inline DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector& d) {
    if (this == &d)
        return *this;
    this->size = d.size;
    this->capacity = d.capacity;
    delete[]this->elements;
    this->elements = new TElem[this->capacity];
    for (int index = 0; index < this->size; index++)
        this->elements[index] = d.elements[index];
    return *this;

}

template<class TElem>
inline void DynamicVector<TElem>::add(const TElem& e) {
    if (size == capacity)
        resize();
    elements[size++] = e;
    
}

template <class TElem>
inline void DynamicVector<TElem>::update(const TElem& e) {
    for (int index = 0; index < this->size; index++)
        if (this->elements[index].getCodedName() == e.getCodedName())
            this->elements[index] = e;
}

template <class TElem>
void DynamicVector<TElem>::remove(const std::string& identifier) {
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

template <class TElem>
inline int DynamicVector<TElem>::exist(const std::string& identifier) {
    for (int index = 0; index < this->size; index++)
        if (this->elements[index].getCodedName() == identifier)
            return 1;
    return -1;
}

template <class TElem>
inline void DynamicVector<TElem>::resize(double new_capacity) {
    this->capacity *= static_cast <int> (new_capacity);
    TElem* new_elements = new TElem[this->capacity];
    for (int index = 0; index < this->size; index++)
        new_elements[index] = this->elements[index];
    delete[] this->elements;
    this->elements = new_elements;
}

template <class TElem>
inline int DynamicVector<TElem>::getSize() {
    return this->size;
}


template <class TElem>
inline int DynamicVector<TElem>::getCapacity() {
    return this->capacity;
}


template <class TElem>
inline TElem DynamicVector<TElem>::getElement(int position) {
    return this->elements[position];
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::begin() {
    return iterator{elements };
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::end() {
    return iterator{ elements + size };
}


template <class TElem>
inline TElem DynamicVector<TElem>::iterator::operator*() {
    return (*this->pointer);
}

template <class TElem>
inline bool DynamicVector<TElem>::iterator::operator!=(const iterator& it) {

    return (this->pointer != it.pointer);
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::iterator::operator++() {
    this->pointer++;
    return *this;
}

template <class TElem>
inline typename DynamicVector<TElem>::iterator DynamicVector<TElem>::iterator::operator++(int x) {
    iterator aux{ *this };
    this->pointer++;
    return aux;
}

template <class TElem>
inline bool DynamicVector<TElem>::iterator::operator==(const iterator& it)
{
    return !(this->pointer != it.pointer);
}
