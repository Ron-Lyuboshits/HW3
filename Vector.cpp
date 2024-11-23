#include <iostream>
#include "Vector.h"

using std::cout;
using std::cerr;
using std::endl;

Vector::Vector(int n) : _elements(nullptr), _capacity(n<2 ? 2:n), _size(0), _resizeFactor(n < 2 ? 2 : n)
{
	_elements = new int[_capacity];
}

Vector::~Vector() {
	delete[] _elements;
}

int Vector::size() const {
	return _size;
}

int Vector::capacity() const {
	return _capacity;
}

int Vector::resizeFactor() const {
	return _resizeFactor;
}

bool Vector::empty() const {
	if (_size == 0) {
		return true;
	}
	return 0;
}

void Vector::push_back(const int& val) {
	if (_size == _capacity) {
		reserve(_capacity + _resizeFactor);
	}
	_elements[_size] = val;
	_size++;
	
}

int Vector::pop_back() {
	if (empty()) {
		cerr << "empty from pop : error";
		return -9999;
	}
	_size--;
	return _elements[_size];

}

void Vector::reserve(const int n) {
	if (n > _capacity) {
		int tmp = (n - _capacity) / _resizeFactor;
		int remainder = (n - _capacity) % _resizeFactor;
		if (remainder > 0) {
			tmp++;
		}
		int* newarray = new int[_capacity + _resizeFactor * tmp];
		for (int i = 0; i < _size; i++) {
			newarray[i] = _elements[i];
		}
		delete[] _elements;
		_elements = newarray;
		_capacity += _resizeFactor * tmp;
	}

}

void Vector::resize(const int n) {
	resize(n, 0);

}

void Vector::assign(const int val) {
	for (int i = 0; i < _size;i++) {
		_elements[i] = val;	
	}
}

void Vector::resize(const int n, const int& val) {
	if (n < _capacity) {
		int* newarray = new int[n];
		int min = (_size < n) ? _size : n;
		for (int i = 0; i < min; i++) {
			newarray[i] = _elements[i];
		}
		delete[] _elements;
		_elements = newarray;
		_size = min;
		_capacity = n;
	}
	else {
		reserve(n);
		while (_size < n) {
			push_back(val);
		}
	}
}

int& Vector::operator[](int n) const {
	if (n >= _size || n < 0) {
		cerr << "n is out of vector's size";
		return _elements[0];
	}
	return _elements[n];
}

Vector& Vector::operator=(const Vector& other) {
	int* newarray = new int[other._capacity];
	for (int i = 0; i < other._size;i++) {
		newarray[i] = other[i];
	}
	delete[] this->_elements;
	this->_elements = newarray;
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;
	return *this;
}

Vector::Vector(const Vector& other) {
	int* newarray = new int[other._capacity];
	for (int i = 0; i < other._size;i++) {
		newarray[i] = other[i];
	}
	this->_elements = newarray;
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_resizeFactor = other._resizeFactor;
}