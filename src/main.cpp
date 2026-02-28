#include <iostream>
#include <fstream>
#include <string>
#include "task1.h"

#include <algorithm>

#include "SortingAlgorithms.h"
#include "Exponentiation.h"

#include <vector>
using namespace std;

// Task 1
// ==================================
static void write_d3_csv_task1a(const std::string& filename,
                                const std::vector<std::pair<int, std::int64_t>>& data) {
    std::ofstream out(filename);
    out << "impl,N,elapsed_ms,ops_total\n";
    for (const auto& [k, ops] : data) {
        out << "fib_recursive," << k << ",0," << ops << "\n";
    }
}

static void write_d3_csv_task1b(const std::string& filename,
                                const std::vector<std::pair<std::int64_t, std::int64_t>>& data) {
    std::ofstream out(filename);
    out << "impl,N,elapsed_ms,ops_total\n";
    for (const auto& [n, ops] : data) {
        out << "euclid_worst," << n << ",0," << ops << "\n";
    }
}


struct SortResult {
    string caseName; // "best","average","worst"
    int n;
    long long insComparisons;
    long long selComparisons;
};

string makeFilename(int n, string s, bool dir) {
    // caseTag should be: "" , "_sorted", or "_rSorted"


    // dir True? UserMode 2
    if (dir) {return "data/testSet/data" + to_string(n) + s + ".txt";}

    // dir false? UserMode 1
    return "data/smallSet/data" + to_string(n) + s + ".txt";
}

vector<int> loadData(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "ERROR: Could not open file: " << filename << "\n";
        return {};
    }

    vector<int> data;
    int x;
    while (fin >> x) {
        data.push_back(x);
    }
    return data;
}

vector<SortResult> task3(const int step, int userMode) {

    // instantiate class
    SortingAlgorithms sorter;

    // Vector of type SortResult struct
    vector<SortResult> results;


    if (userMode == 1) {
        string input;
        int number;


        while (true) {
            cout << "Please enter a number 1 - 100: ";
            cin >> input;

            try {
                number = stoi(input);

                if (number >= 1 && number <= 100 && number % 10 == 0) {
                    break;
                }

                cout << "Number must be 10, 20, ..., 100.\n";
            }
            catch (...) {
                cout << "Invalid input. Enter a number.\n";
            }
        }

        // best
        string sortedFile  = makeFilename(number, "_sorted", false);
        vector<int> sortedData = loadData(sortedFile);
        if (sortedFile.empty()) {
            cerr << "ERROR: One or more files failed to load for n=" << number << "\n";
            return {};
        }

        // average
        string randomFile = makeFilename(number, "", false);
        vector<int> randomData = loadData(randomFile);

        // worst
        string reverseSortedfile = makeFilename(number, "_rSorted", false);
        vector<int> reverseData = loadData(reverseSortedfile);


        vector<int> bestInsVec = sortedData;
        vector<int> bestSelVec = sortedData;

        vector<int> avgInsVec = randomData;
        vector<int> avgSelVec = randomData;

        vector<int> worstInsVec = reverseData;
        vector<int> worstSelVec = reverseData;


        long long  bestInsComp = 0, bestSelComp = 0;
        long long  avgInsComp = 0, avgSelComp = 0;
        long long  worstInsComp = 0, worstSelComp = 0;

        // ============================
        // Best

        // Insertion Sort
        sorter.insertSort(bestInsVec.data(), static_cast<int>(bestInsVec.size()), bestInsComp);

        //Selection Sort
        sorter.selectionSort(bestSelVec.data(), static_cast<int>(bestSelVec.size()), bestSelComp);

        results.push_back({"best", number, bestInsComp, bestSelComp});

        //=============================
        // Average

        // Insertion Sort
        sorter.insertSort(avgInsVec.data(), static_cast<int>(avgInsVec.size()), avgInsComp);

        //Selection Sort
        sorter.selectionSort(avgSelVec.data(), static_cast<int>(avgSelVec.size()), avgSelComp);

        results.push_back({"average", number, avgInsComp, avgSelComp});

        //=============================
        // Worst

        // Insertion Sort
        sorter.insertSort(worstInsVec.data(), static_cast<int>(worstInsVec.size()), worstInsComp);

        //Selection Sort
        sorter.selectionSort(worstSelVec.data(), static_cast<int>(worstSelVec.size()), worstSelComp);

        results.push_back({"worst", number, worstInsComp, worstSelComp});

        return results;

    }

    // loop to end of files in testSet.
    for (int i = 0; i <= 10000; i+=step) {

// ===========================================
        // Best case: dataI_sorted.txt
        {
            // generate the bestCase filename
            string filename  = makeFilename(i, "_sorted", true);

            // Load file data into a vector
            vector<int> sortedData = loadData(filename);
            if (sortedData.empty()) continue;

            // create 2 vectors: One for insertionSort and one for SelectionSort
            vector<int> insVecBest = sortedData;
            vector<int> selVecBest = sortedData;

            long long  InsertComparisons = 0;
            long long  SelectComparisons = 0;

            // Insertion Sort
            sorter.insertSort(insVecBest.data(), static_cast<int>(insVecBest.size()), InsertComparisons);

            //Selection Sort
            sorter.selectionSort(selVecBest.data(), static_cast<int>(selVecBest.size()), SelectComparisons);

            results.push_back({"best", i, InsertComparisons, SelectComparisons});

        }

// ===========================================
        //Average case: dataI.txt
        {
            // generate Average case filename
            string filename = makeFilename(i, "", true);

            // Load file data into a vector
            vector<int> randomData = loadData(filename);
            if (randomData.empty()) continue;

            // create 2 vectors and copy file data into them.
            vector<int> insVecAvg = randomData;
            vector<int> selVecAvg = randomData;

            long long InsertComparisons = 0;
            long long SelectComparisons = 0;

            sorter.insertSort(insVecAvg.data(), static_cast<int>(insVecAvg.size()), InsertComparisons);
            sorter.selectionSort(selVecAvg.data(), static_cast<int>(selVecAvg.size()), SelectComparisons);

            results.push_back({"average", i, InsertComparisons, SelectComparisons});


        }

// =========================================
        {
            // Generate Worst case filename
            string filename = makeFilename(i, "_rSorted", true);

            // Load file data into a vector
            vector<int> rSortedData = loadData(filename);
            if (rSortedData.empty()) continue;

            // create 2 vectors and copy file data into them.
            vector<int> insVecWorst = rSortedData;
            vector<int> selVecWorst = rSortedData;

            long long InsertComparisons = 0;
            long long SelectComparisons = 0;

            sorter.insertSort(insVecWorst.data(), static_cast<int>(insVecWorst.size()), InsertComparisons);
            sorter.selectionSort(selVecWorst.data(), static_cast<int>(selVecWorst.size()), SelectComparisons);

            results.push_back({"worst", i, InsertComparisons, SelectComparisons});


        }
    }
    return results;

}

void task2(int userMode) {

    Exponentiation exp;

    if (userMode == 1) {

        cout << "We are calculating a^n." << endl;

        int a, n;

        bool aVal = false, bVal = false;

        string input;
        int number = 0;

        while (true) {

            if (!aVal) {
                cout << "Please enter an integer for \"a\": ";
                cin >> input;

                try {
                    number = stoi(input);

                    a = number;
                    aVal = true;
                    continue;
                }
                catch (...) {
                    cout << "Invalid input. Enter a number.\n";
                    continue;
                }
            }

            cout << "Please enter an integer for \"n\": ";
            cin >> input;

            try {
                number = stoi(input);

                n = number;
                break;
            }
            catch (...) {
                cout << "Invalid input. Enter a number.\n";
            }


        }


        cout << "Your \'a\' value: " << a << endl << "Your \'n\' value: " << n << endl;

        long long db1Count = 0, dbcfCount = 0, dacCount = 0;
        long long db1Results = 0, dbcfResults = 0, dacResults = 0;

        db1Results = exp.decreaseByOne(a, n, db1Count);
        dbcfResults = exp.decreaseByConstantFactor(a, n, dbcfCount);
        dacResults = exp.divideAndConquer(a, n, dacCount);

        cout << "Number of basic Operations" << endl;
        cout << "decreaseByOne: " << db1Count << endl << "decreaseByConstantFactor: " << dbcfCount << endl
            << "divideAndConquer: " << dacCount << endl << endl;

        cout << "function results" << endl;
        cout << "decreaseByOne: " << db1Results << endl << "decreaseByConstantFactor: " << dbcfResults << endl
            << "divideAndConquer: " << dacResults << endl;

    }



}

void task1(int mode) {

    if (mode == 1) {
        cout << "Please enter k for Fib(k): ";
        int k;
        cin >> k;

        FibResult fibK = fib_count(k);
        cout << "Fib(" << k << ") = " << fibK.value << "\n";
        cout << "A(" << k << ") additions = " << fibK.addCount << "\n";

        // IMPORTANT: avoid recomputing fib_count(k) again (it's expensive)
        FibResult fibK1 = fib_count(k + 1);

        std::int64_t m = fibK1.value;
        std::int64_t n = fibK.value;

        GcdResult gcdRes = gcd_count(m, n);
        cout << "gcd(Fib(" << k + 1 << "), Fib(" << k << ")) = " << gcdRes.value << "\n";
        cout << "D(n) modulo ops = " << gcdRes.modCount << "\n";
    }
    else if (mode == 2) {
        // You choose k-range for scatter plots
        // Safe default for recursive fib growth:
        int kMin = 1;
        int kMax = 40;

        auto t1a = task1a_scatter_data(kMin, kMax);
        auto t1b = task1b_scatter_data(kMin, kMax);

        write_d3_csv_task1a("task1a_fib.csv", t1a);
        write_d3_csv_task1b("task1b_gcd.csv", t1b);

        cout << "Generated:\n";
        cout << "  task1a_fib.csv (k vs A(k))\n";
        cout << "  task1b_gcd.csv (n=Fib(k) vs D(n))\n";
        cout << "Now open your provided D3 HTML and load these CSV files.\n";
    }


}

int main() {

    cout << "What mode?" << endl <<  "type \'1\' for user Testing mode" << endl <<  "type \'2\' for Scatter plot mode" << endl;
    string userMode;



    cin >> userMode;

    while (userMode != "1" && userMode != "2") {
        cout<< "Please enter 1 or 2:" << endl;
        cin >> userMode;
    }

    int mode = std::stoi(userMode);

    //======================
    task1(mode);
    task2(mode);
    vector<SortResult> task3Results = task3(200, mode);


    for (size_t i = 0; i < task3Results.size(); i++) {
        cout << task3Results[i].caseName << " "
                  << task3Results[i].n << " "
                  << task3Results[i].insComparisons << " "
                  << task3Results[i].selComparisons << endl;
    }

    return 0;
}



