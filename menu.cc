#include <iostream>
#include <string.h>

int *array;
int COUNT;
int SIZE;

void initialize() {
	COUNT = 0;
	SIZE = 2;
	array = new int[SIZE];
}

void finalize() {
	delete[] array;
}

void printArray() {
	std::cout << "[";
	for(int i = 0; i < COUNT; i++) {
		std::cout << array[i];
		if(i < COUNT - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "] size = " << SIZE << std::endl;
}

void growArray() {
	int s = SIZE;
	SIZE *= 2;
	int *newarray = new int[SIZE];
	memcpy(newarray, array, COUNT * sizeof(int));
	delete[] array;
	array = newarray;
	std::cout << "Vector grown from " << s << " to " << SIZE << std::endl;
}

void shrinkArray() {
	int s = SIZE;
	SIZE /= 2;
	int *newarray = new int[SIZE];
	memcpy(newarray, array, COUNT * sizeof(int));
	delete[] array;
	array = newarray;
	std::cout << "Vector shrunk from " << s << " to " << SIZE << std::endl;
}

void insertElement(int index, int element) {
	if(index > COUNT) {
		std::cout << "ERROR: Index out of bounds" << std::endl;
		return;
	}
	if(SIZE <= COUNT) {
		growArray();
	}
	memcpy(array, array, index * sizeof(int));
	memcpy(array + index + 1, array + index, (COUNT - index) * sizeof(int));
	array[index] = element;
	COUNT++;
}

void appendElement(int element) {
	insertElement(COUNT, element);
}

void removeElement() {
	if(COUNT <= 0) {
		std::cout << "ERROR: Vector is empty" << std::endl;
		return;
	}
	COUNT--;
	std::cout << "Removed 1 element" << std::endl;
	if(COUNT <= SIZE * 0.3) {
		shrinkArray();
	}
}

int main() {
	initialize();
	char option = '0';
	while(1) {
		switch(option) {
			case '0':
				std::cout << "Main Menu:\n\n1. Print the array\n"
				"2. Append element at the end\n"
				"3. Remove last element\n"
				"4. Insert one element\n"
				"5. Exit\n\n"
				"Select an option: ";
		
				std::cin >> option;
				break;

			case '1':  // Print the array
				option = '0';
				std::cout << "Array = ";
				printArray();
				break;
			case '2':  // Append element at the end
				option = '0';
				std::cout << "Enter new element: ";
				int appendEl;
				std::cin >> appendEl;
				appendElement(appendEl);
				break;
			case '3':  // Remove last element
				option = '0';				
				removeElement();
				break;
			case '4':  // Insert one element
				option = '0';
				std::cout << "Enter index of new element: ";
				int index;
				std::cin >> index;
				std::cout << "Enter new element: ";
				int insertEl;
				std::cin >> insertEl;

				insertElement(index, insertEl);
				break;
			case '5':  // Exit
				finalize();
				return 0;
			default:
				std::cout << "Invalid option " << option << '\n';
				option = '0';
				break;
		}
	}
}
