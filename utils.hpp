#ifndef UTILS_HPP
#define UTILS_HPP

#include "algorithms.hpp"
#include "generators.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

unordered_map<string, void(*)(int*, int, uint64&)> algorithms = {
    {"selection-sort", selectionSort},
    {"insertion-sort", insertionSort},
    {"shell-sort", bubbleSort},
    {"bubble-sort", bubbleSort},
    {"heap-sort", heapSort},
    {"merge-sort", [](int* arr, int n, uint64& comparisons) { mergeSort(arr, 0, n - 1, comparisons); }},
    {"quick-sort", [](int* arr, int n, uint64& comparisons) { quickSort(arr, 0, n - 1, comparisons); }},
    {"radix-sort", radixSort},
    {"counting-sort", countingSort},
    {"shaker-sort", shakerSort},
    {"flash-sort", flashSort}
};
string orderTypes[] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};
void (*generators[])(int*, int) = {generateRandomData, generateNearlySortedData, generateSortedData, generateReverseData};

int toInt(string s) {
    try {
        return stoi(s);
    }
    catch (const invalid_argument& e) {
        return 0;
    }
    catch (const out_of_range& e) {
        return 0;
    }
}

void readArray(string fileName, int*& arr, int& n) {
    ifstream fi(fileName);
    // Validate 'Given input' argument
    if (!fi.is_open()) {
        throw runtime_error("cannot open file \'" + fileName + "\'");
    }

    fi >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++) {
        fi >> arr[i];
    }
    fi.close();
}

void save(string fileName, int* arr, int n) {
    ofstream fo(fileName);
    fo << n << endl;
    for (int i = 0; i < n; i++) {
        fo << arr[i] << " ";
    }
    fo.close();
}

int* copy(int* arr, int n) {
    int* newArr = new int[n];
    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}

void createArray(int*& arr, string input, int& size, string order) {
    if (order.size()) {
        arr = new int[size];
        // Validate 'Input order' argument
        if (order == "-rand") {
            order = "Randomize";
            generateRandomData(arr, size);
        }
        else if (order == "-rev") {
            order = "Reversed";
            generateReverseData(arr, size);
        }
        else if (order == "-sorted") {
            order = "Sorted";
            generateSortedData(arr, size);
        }
        else if (order == "-nsorted") {
            order = "Nearly Sorted";
            generateNearlySortedData(arr, size);
        }
        else {
            delete[] arr; arr = nullptr;
            throw invalid_argument(order);
        }
        cout << "Input size: " << size << endl;
        cout << "Input order: " << order << endl;

        save("input.txt", arr, size);
    }
    else {
        readArray(input, arr, size);
        cout << "Input file: " << input << endl;
        cout << "Input size: " << size << endl;
    }
}

void printHelp() {
    cout << "Usage: main.exe -a <algorithm> <input-file-path> <output-parameter>\n"
                 << "\t\t-a <algorithm> <input-size> [<input-order>] <output-parameter>\n"
                 << "\t\t-c <algorithm_1> <algorithm_2> [<input-path> | <input-size> <input-order>]\n"
         << "Modes:\n"
         << "\t-a\t\tAlgorithm mode\n"
         << "\t-c\t\tCompare mode\n\n"
         << "Algorithms: selection-sort, insertion-sort, shell-sort, bubble-sort, heap-sort, merge-sort,\n"
         << "            quick-sort, radix-sort, counting-sort, shaker-sort, flash-sort\n\n"
         << "Input size: a positive integer\n\n"
         << "Input orders:\n"
         << "\t-rand\t\tRandomize\n"
         << "\t-nsorted\tNearly sorted\n"
         << "\t-sorted\t\tSorted\n"
         << "\t-rev\t\tReversed\n\n"
         << "Output parameters:\n"
         << "\t-time\t\tRunning time\n"
         << "\t-comp\t\tComparison count\n"
         << "\t-both\t\tBoth of -time and -comp\n";
}

#endif