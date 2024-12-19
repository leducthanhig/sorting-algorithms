#include "utils.hpp"
#include <chrono>

using namespace chrono;

#define TIME_UNIT milliseconds

void execute(string algo1, string algo2, string input, string outPara = "", int size = 0, string order = "") {
    int *arr = nullptr;
    unsigned long long comparisons = 0, runtimes = 0;
    
    // Algorithm mode
    if (!algo2.size()) {
        if (input.size() || order.size()) {
            createArray(arr, input, size, order);

            auto start = steady_clock::now();
            algorithms[algo1](arr, size, comparisons);
            runtimes = duration_cast<TIME_UNIT>(steady_clock::now() - start).count();
            
            cout << "-------------------------------------\n";
            if (outPara == "-time") {
                cout << "Running time (ms): " << runtimes << endl;
            }
            else if (outPara == "-comp") {
                cout << "Comparisons: " << comparisons << endl;
            }
            else {
                cout << "Running time (ms): " << runtimes << endl;
                cout << "Comparisons: " << comparisons << endl;
            }

            save("output.txt", arr, size);
        }
        else {
            cout << "Input size: " << size << endl;
            
            for (int i = 0; i < 4; i++) {
                cout << "\nInput order: " << orderTypes[i] << endl;

                generators[i](arr, size);
                save("input_" + to_string(i + 1) + ".txt", arr, size);
                
                comparisons = 0;
                auto start = steady_clock::now();
                algorithms[algo1](arr, size, comparisons);
                runtimes = duration_cast<TIME_UNIT>(steady_clock::now() - start).count();
            
                cout << "-------------------------------------\n";
                if (outPara == "-time") {
                    cout << "Running time (ms): " << runtimes << endl;
                }
                else if (outPara == "-comp") {
                    cout << "Comparisons: " << comparisons << endl;
                }
                else {
                    cout << "Running time (ms): " << runtimes << endl;
                    cout << "Comparisons: " << comparisons << endl;
                }
            }
        }
    }
    // Comparison mode
    else {
        unsigned long long runtimes2 = 0, comparisons2 = 0;
        createArray(arr, input, size, order);

        int* arr_copy = copy(arr, size);
        auto start = steady_clock::now();
        algorithms[algo1](arr_copy, size, comparisons);
        runtimes = duration_cast<TIME_UNIT>(steady_clock::now() - start).count();
        delete[] arr_copy; arr_copy = nullptr;
        
        start = steady_clock::now();
        algorithms[algo2](arr, size, comparisons2);
        runtimes2 = duration_cast<TIME_UNIT>(steady_clock::now() - start).count();
        
        cout << "-------------------------------------\n";
        cout << "Running time (ms): " << runtimes << " | " << runtimes2 << endl;
        cout << "Comparisons: " << comparisons << " | " << comparisons2 << endl;
    }
    delete[] arr; arr = nullptr;
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            printHelp();
            return 0;
        }

        string mode = argv[1];
        if (mode == "-h" || mode == "help") {
            printHelp();
            return 0;
        }

        string algoName = argv[2];
        // Validate 'Algorithm' argument
        if (algorithms.find(algoName) == algorithms.end()) {
            throw invalid_argument(algoName);
        }
        
        // Validate 'Mode' argument
        if (mode == "-a") {
            if (argc < 5) {
                throw logic_error("");
            }
            
            cout << "ALGORITHM MODE\n";
            cout << "Algorithm: " << algoName << endl;

            int inputSize = toInt(argv[3]);
            // Validate 'Input size' argument
            if (inputSize < 0) {
                throw invalid_argument(argv[3]);
            }

            string outPara = argv[argc - 1];
            // Validate 'Output parameter' argument
            if (outPara != "-both" && outPara != "-time" && outPara != "-comp") {
                throw invalid_argument(outPara);
            }

            if (inputSize) {
                if (argc == 5) {
                    execute(algoName, "", "", outPara, inputSize);
                }
                else {
                    execute(algoName, "", "", outPara, inputSize, argv[4]);
                }
            }
            else {
                execute(algoName, "", argv[3], outPara);
            }
        }
        else if (mode == "-c") {
            string algoName2 = argv[3];
            // Validate 'Algorithm' argument
            if (algorithms.find(algoName2) == algorithms.end()) {
                throw invalid_argument(algoName2);
            }
            
            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algoName << " | " << algoName2 << endl;

            int inputSize = toInt(argv[4]);
            // Validate 'Input size' argument
            if (inputSize < 0) {
                throw invalid_argument(argv[4]);
            }
            
            if (inputSize) {
                execute(algoName, algoName2, "", "", inputSize, argv[5]);
            }
            else {
                execute(algoName, algoName2, argv[4]);
            }
        }
        else {
            throw invalid_argument(mode);
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Error: \'" << e.what() << "\' is not a valid argument\n";
        cout << "Please use `help` or `-h` for more information.\n";
    }
    catch (const logic_error& e) {
        cerr << "Error: one or more argument(s) missed\n";
        cout << "Please use `help` or `-h` for more information.\n";
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}