#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include "Helper.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using std::tuple;
using std::make_tuple;
using std::get;

tuple<vector<int>, float> encoding(string input) {
    // Vector kết quả là các số thập phân ứng với các kí tự (cả đơn và phức)
    vector<int> outputInts;
    float compressionRatio;

    // Bảng ASCII sẽ mở rộng cho các kí tự phức với index từ 256 trở lên
    unordered_map<string, int> alphabet;
    for (int i = 0; i <= 255; i++) {
        string s = "";
        alphabet[s + char(i)] = i;
    }

    int i = 0, j = 0;
    int letter_code = 256;
    string prev = "";
    string cur = "";
    string next = "";

    // next = prev + cur, cur luôn dài 1 kí tự
    // ta cộng dần cur vào prev cho đến khi prev đã có trong bảng chữ cái còn next thì chưa -> đánh số cho next
    while (i < input.length()) {
        // i là vị trí bắt đầu của mỗi kí tự có sẵn
        // j chạy sau i giúp mở rộng vùng tìm kiếm của next
        j = i;
        do {
            cur = input[j]; j++;
            prev = next;
            next = next + cur;
        } while (j < input.length() && alphabet.find(next) != alphabet.end());

        // AA, A và AA biết rồi -> thêm luôn AA vào alphabet
        if (j == input.length() && alphabet.find(next) != alphabet.end()) {
            prev = next;
            outputInts.push_back(alphabet[prev]);
        }
        // WYSG, WYS biết rồi nhưng WYSG thì chưa -> thêm WYSG vào alphabet, encode WYS, sẽ đưa được về trường hợp 2 (chỉ còn G)
        // và các trường hợp còn lại
        else {
            alphabet[next] = letter_code; letter_code++;
            outputInts.push_back(alphabet[prev]);
        }
        // i sẽ nhảy với bước nhảy = độ dài của kí tự cũ prev
        i += prev.length();
        prev = "";
        next = "";
    }

    
    int N = input.length() * 8;
    int n = outputInts.size() * 9;
    compressionRatio = 100.0 * (N - n) / N;
    for (int i = 0; i < outputInts.size(); i++) cout << outputInts[i] << " "; cout << endl;
    for (int i = 0; i < outputInts.size(); i++) cout << toBinary(outputInts[i]) << " "; cout << endl;
    cout << compressionRatio << endl;
    return make_tuple(outputInts, compressionRatio);
}
tuple<string, float> decoding(vector<int> input) {
    string outputStr = "";
    float compressionRatio;

    // Bảng ASCII sẽ mở rộng cho các kí tự phức với index từ 256 trở lên
    unordered_map<int, string> alphabet;
    for (int i = 0; i <= 255; i++) {
        string s = "";
        alphabet[i] = s + char(i);
    }

    int i = 0, j = 1;
    int letter_code = 256;
    int prev = -1;
    int cur = -1;
    string next = "";

    // prev là chữ cái trước
    // cur là chữ cái sau
    // next là chữ cái mới đc kết hợp từ chữ cái trước + kí tự đầu của chữ cái đầu
    while (i < input.size()) {
        prev = input[i]; 
        outputStr += alphabet[prev];
        i++;
        if (j < input.size()) {
            cur = input[j];
            next = alphabet[prev] + alphabet[cur][0];
            alphabet[letter_code] = next;
            j++;
            letter_code++;
        }
    }

    int n = input.size() * 9;
    int N = outputStr.length() * 8;
    compressionRatio = 100.0 * (N - n) / N;
    cout << outputStr << endl;
    cout << compressionRatio << endl;
    return make_tuple(outputStr, compressionRatio);
}