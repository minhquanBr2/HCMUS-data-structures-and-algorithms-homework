#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include "Matcher.h"

enum ERROR_CODE {
    SUCCESSFUL,
    WRONG_NUMBER_OF_ARGUMENTS,
    WRONG_ALGO_CODE
};
using namespace std;

int stringMatching(const char* main, const char* pattern, string type, double& time) {
    int res;
    if (type == "BF") {
        auto begin = chrono::high_resolution_clock::now();
        res = Matcher::countBFmatch(main, pattern);
        auto end = chrono::high_resolution_clock::now();
        time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 1000000.0;
        return res;
    }
    else if (type == "RK") {
        auto begin = chrono::high_resolution_clock::now();
        res = Matcher::countRKmatch(main, pattern);
        auto end = chrono::high_resolution_clock::now();
        time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 1000000.0;
        return res;
    }
    else if (type == "KMP") {
        auto begin = chrono::high_resolution_clock::now();
        res = Matcher::countKMPmatch(main, pattern);
        auto end = chrono::high_resolution_clock::now();
        time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 1000000.0;
        return res;
    }
    else if (type == "BM") {
        auto begin = chrono::high_resolution_clock::now();
        res = Matcher::countBMmatch(main, pattern);
        auto end = chrono::high_resolution_clock::now();
        time = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / 1000000.0;
        return res;
    }
    else 
        exit(WRONG_ALGO_CODE);
}

int main(int argc, char** argv) {
    if (argc == 4) {
        fstream f;
        f.open(argv[1], ios::in);
        string main;
        f >> main;

        string pattern = argv[2];
        string type = argv[3];
        double time = 0;
        int count = stringMatching(main.c_str(), pattern.c_str(), type, time);

        cout << count << " " << fixed << setprecision(6) << time << endl;
    }

    else
        exit(WRONG_NUMBER_OF_ARGUMENTS);



    //char main[] = "AAABAAABABBAABAAAABA";
    //char pattern[] = "AA";
    
    //char main[] = "ONIONIONIONIONSONIONIONIONSONIONIONSL";
    //char pattern[] = "ONIONS";
    //cout << Matcher::countBFmatch(main, pattern) << "\n";
    //cout << Matcher::countRKmatch(main, pattern) << "\n";
    //cout << Matcher::countKMPmatch(main, pattern) << "\n";
    //cout << Matcher::countBMmatch(main, pattern) << "\n";
    return 0;
}