#pragma once
#include "PlantCluster.h"
typedef PlantCluster TElem;

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

    ///extened the size of the elements if needed
    void resize(double new_capacity=2);

    ///returns the capacity of the vector
    int getCapacity();
};