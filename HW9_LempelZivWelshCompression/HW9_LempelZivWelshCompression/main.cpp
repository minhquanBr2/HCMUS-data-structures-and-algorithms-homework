#include <iostream>
#include "Functions.h"

enum ErrorCode {
    SUCCESS,
    INVALID_SYNTAX
};

int main(int argc, char** argv){

    // WYS*WYGWYS*WYSWYSG
    // VCVJDVHVVVHGCGCCVHDJJCVHDJJHJVCHJVJCVVDCVCJDJVJHVDJV
    // BABAABAAA


    if (strcmp(argv[1], "-c") == 0) {
        string input(argv[2]);
        tuple<vector<int>, float> encodingOutput = encoding(input);
    }
    else if (strcmp(argv[1], "-e") == 0) {
        vector<int> input;
        for (int i = 2; i < argc; i++) input.push_back(stoi(string(argv[i])));
        tuple<string, float> decodingOutput = decoding(input);
    }
    else
        return ErrorCode::INVALID_SYNTAX;

    return 0;
}
