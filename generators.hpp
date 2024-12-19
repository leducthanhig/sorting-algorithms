#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <iostream>
#include <ctime>

using namespace std;

void generateRandomData(int* a, int n) {
	srand((unsigned int)time(0));

	for (int i = 0; i < n; i++) {
		a[i] = rand() % n;
	}
}

void generateSortedData(int* a, int n) {
	for (int i = 0; i < n; i++) {
		a[i] = i;
	}
}

void generateReverseData(int* a, int n) {
	for (int i = 0; i < n; i++) {
		a[i] = n - 1 - i;
	}
}

void generateNearlySortedData(int* a, int n) {
	for (int i = 0; i < n; i++) {
		a[i] = i;
	}
	
    srand((unsigned int)time(0));
	for (int i = 0; i < 10; i++) {
		int r1 = rand() % n;
		int r2 = rand() % n;
		swap(a[r1], a[r2]);
	}
}

#endif