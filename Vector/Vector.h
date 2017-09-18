#ifndef Vector_h
#define Vector_h

#include <iostream>

class Vector {
	private:
		int *_data;
		int size;
		int count;
		void init(int size);
	public:
		Vector();
		Vector(int size);

		void append();
		void insert();
		void remove();

		String print();
};

#endif
