#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long uint64;

// ============= Bubble Sort =============
void bubbleSort(int* a, int n, uint64& comparisons) {
    for (int i = 0; ++comparisons && i < n - 1; ++i) {
        for (int j = 0; ++comparisons && j < n - i - 1; ++j) {
            if (++comparisons && a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// ============= Merge Sort =============
void merge(int* a, int p, int q, int r, uint64& comparisons) {
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1);
    vector<int> M(n2);

    for (int i = 0; ++comparisons && i < n1; i++)
        L[i] = a[p + i];

    for (int j = 0; ++comparisons && j < n2; j++)
        M[j] = a[q + 1 + j];

    int i = 0, j = 0, k = p;
    while ((++comparisons && i < n1) && (++comparisons && j < n2)) {
        if (++comparisons && L[i] <= M[j]) {
            a[k++] = L[i++];
        }
        else {
            a[k++] = M[j++];
        }
    }
    while (++comparisons && i < n1) {
        a[k++] = L[i++];
    }
    while (++comparisons && j < n2) {
        a[k++] = M[j++];
    }
}

void mergeSort(int* a, int l, int r, uint64& comparisons) {
    if (++comparisons && l < r) {
        int m = l + (r - l) / 2;

        mergeSort(a, l, m, comparisons);
        mergeSort(a, m + 1, r, comparisons);

        merge(a, l, m, r, comparisons);
    }
}

// ============= Quick Sort =============
void quickSort(int* arr, int low, int high, uint64& comparisons) {
    int i = low, j = high, mid = arr[low + (high - low) / 2];
    while (++comparisons && i <= j) {
        while (++comparisons && arr[i] < mid) i++;
        while (++comparisons && mid < arr[j]) j--;
        if (++comparisons && i <= j) {
            swap(arr[i], arr[j]);
            i++; j--;
        }
    }
    if (++comparisons && i < high) quickSort(arr, i, high, comparisons);
    if (++comparisons && low < j) quickSort(arr, low, j, comparisons);
}

// ============= Helper functions for Counting Sort and Radix Sort =============
int findMax(int* arr, int n, uint64& comparisons) {
    int maxVal = arr[0];
    for (int i = 1; ++comparisons && i < n; i++) {
        if (++comparisons && arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

int findMin(int* arr, int n, uint64& comparisons) {
    int minVal = arr[0];
    for (int i = 1; ++comparisons && i < n; i++) {
        if (++comparisons && arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

// ============= Counting Sort =============
void countingSort(int* arr, int n, uint64& comparisons) {
    int max_val = findMax(arr, n, comparisons);
    int min_val = findMin(arr, n, comparisons);
    int range = max_val - min_val + 1;

    vector<int> count(range, 0);
    vector<int> output(n);

    for (int i = 0; ++comparisons && i < n; i++) {
        count[arr[i] - min_val]++;
    }

    for (int i = 1; ++comparisons && i < range; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; ++comparisons && i >= 0; i--) {
        output[--count[arr[i] - min_val]] = arr[i];
    }

    for (int i = 0; ++comparisons && i < n; i++) {
        arr[i] = output[i];
    }
}

// ============= Radix Sort =============
void radixSort(int* arr, int n, uint64& comparisons) {
    int max_val = findMax(arr, n, comparisons);
    for (int exp = 1; ++comparisons && max_val / exp > 0; exp *= 10) {
        vector<int> count(10, 0);
        vector<int> output(n);

        for (int i = 0; ++comparisons && i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; ++comparisons && i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; ++comparisons && i >= 0; i--) {
            output[--count[(arr[i] / exp) % 10]] = arr[i];
        }

        for (int i = 0; ++comparisons && i < n; i++) {
            arr[i] = output[i];
        }
    }
}

// ============= Shaker Sort =============
void shakerSort(int* arr, int n, uint64& comparisons) {
    bool swapped = true;
    int start = 0, end = n - 1;

    while (++comparisons && swapped) {
        swapped = false;

        for (int i = start; ++comparisons && i < end; i++) {
            if (++comparisons && arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (++comparisons && !swapped) break;

        swapped = false;
        end--;

        for (int i = end - 1; ++comparisons && i >= start; i--) {
            if (++comparisons && arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

// ============= Insertion Sort =============
void insertionSort(int* arr, int n, uint64& comparisons) {
	for (int i = 1; ++comparisons && i < n; i++) {
		int j = i - 1;
		int key = arr[i];
		while (++comparisons && j >= 0 && ++comparisons && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

// ============= Heap Sort =============
void heapify(int* arr, int n, int i, uint64& comparisons) {
	int largest = i; 
	int left = 2 * i + 1; 
	int right = 2 * i + 2; 

	if (++comparisons && left < n) {
		if (++comparisons && arr[left] > arr[largest]) {
			largest = left;
		}
	}

	if (++comparisons && right < n) {
		if (++comparisons && arr[right] > arr[largest]) {
			largest = right;
		}
	}
	
    if (++comparisons && largest != i) {
		swap(arr[largest], arr[i]);
		heapify(arr, n, largest, comparisons);
	}
}

void heapSort(int* a, int n, uint64& comparisons) {
	for (int i = n / 2 - 1; ++comparisons && i >= 0; i--) {
		heapify(a, n, i, comparisons);
	}
	
	for (int i = n - 1; ++comparisons && i > 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0, comparisons);
	}
}

// ============= Shell Sort =============
void shellSort(int* arr, int n, uint64& comparisons) {
	for (int gap = n / 2; ++comparisons && gap > 0; gap /= 2) {
		for (int i = gap; ++comparisons && i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; ++comparisons && j >= gap && ++comparisons && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}

// ============= Selection Sort =============
void selectionSort(int* arr, int n, uint64& comparisons) {
	for (int i = 0; ++comparisons && i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; ++comparisons && j < n; j++) {
			if (++comparisons && arr[j] < arr[min]) min = j;
		}
		swap(arr[i], arr[min]);
	}
}

// ============= Flash Sort =============
void flashSort(int* arr, int n, uint64& comparisons) {
    if (++comparisons && n < 2) {
        return;
    }
    
    // Classification
    int a_imin = arr[0], imax = 0;
    for (int i = 1; ++comparisons && i < n; i++) {
        if (++comparisons && arr[i] < a_imin) {
            a_imin = arr[i];
        }
        if (++comparisons && arr[i] > arr[imax]) {
            imax = i;
        }
    }
    
    if (++comparisons && a_imin == arr[imax]) {
        return;
    }
    
    int m = max(static_cast<int>(0.45 * n), 1);
    int* l = new int[m]();
    double c1 = (m - 1.0) / (arr[imax] - a_imin);
    for (int i = 0; ++comparisons && i < n; i++) {
        l[static_cast<int>(c1 * (arr[i] - a_imin))]++;
    }
    
    for (int i = 1; ++comparisons && i < m; i++) {
        l[i] += l[i - 1];
    }
    
    swap(arr[imax], arr[0]);
    
    // Permutation
    int nmove = 0, j = 0, k = m - 1;
    while (++comparisons && nmove < n - 1) {
        while (++comparisons && j > l[k] - 1) {
            j++;
            k = static_cast<int>(c1 * (arr[j] - a_imin));
        }
        
        int flash = arr[j];
        while (++comparisons && j != l[k]) {
            k = static_cast<int>(c1 * (flash - a_imin));
            swap(flash, arr[l[k] - 1]);
            l[k]--;
            nmove++;
        }
    }
    
    // Insertion sort
    for (int i = 1; ++comparisons && i < n; i++) {
        int tmp = arr[i], j = i - 1;
        while (++comparisons && j >= 0 && ++comparisons && arr[j] > tmp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }
    
    delete[] l;
}

#endif