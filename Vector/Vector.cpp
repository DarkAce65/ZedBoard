#include "Vector.h"
#include <iostream>

void Vector::init(int size) {
	this->_data = new int[size];
	this->size = size;
	this->count = 0;
}

Vector::Vector() {
	init(10);
}

Vector::Vector(int size) {
	init(size);
}

int count() {
	return this->count;
}

void append(int element) {
	if(this->size <= this->count) {
		size *= 2;
		int *newdata = new int[size];
		memcpy(newdata, this->_data, count);
		delete[] this->_data;
		this->_data = newdata;
	}
	this->_data[count] = element;
	count++;
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
	os << "<";
	for(int i = 0; i < vec.count(); i++) {
		if(i == vec.count() - 1) {
			os << vec._data[i];
		}
		else {
			os << vec._data[i] << ", ";
		}
	}
	os << ">";
	return os;
}
