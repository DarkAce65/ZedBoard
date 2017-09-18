#include <iostream>
#include <string.h>

void printArray(int *array, int count) {
	std::cout << "[";
	for(int i = 0; i < count; i++) {
		std::cout << array[i];
		if(i < count - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

void insertElement(int *array, int count, int size, int index, int element) {
	if(size > count) {
		memcpy(array, array, (index) * sizeof(int));
		memcpy(array + index + 1, array + index, (count - index) * sizeof(int));
		array[index] = element;
	}
}

int main() {
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
				std::cout << "You selected \"Print the array\"\n\n";
				option = '0';
				break;
			case '2':  // Append element at the end
				std::cout << "You selected \"Append element at the end\"\n\n";
				option = '0';
				break;
			case '3':  // Remove last element
				std::cout << "You selected \"Remove last element\"\n\n";
				option = '0';
				break;
			case '4':  // Insert one element
				std::cout << "You selected \"Insert one element\"\n\n";
				option = '0';
				break;
			case '5':  // Exit
				return 0;
			default:
				std::cout << "Invalid option " << option << '\n';
				option = '0';
				break;
		}
	}
}
