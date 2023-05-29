#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::fstream;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;


// 6. Kiểm tra file có trong danh sách không
int checkFileName(string fileName, vector<string> fileNames, int fileCount, const int maxFileCount);
// 7 & 8. Hàm đọc số lượng file chứa data từ fileCount.txt
int readFileCount(string name);
void writeFileCount(string name, int& fileCount);
// 9 & 10. Hàm đọc danh sách tên file chứa data từ fileNames.txt
vector<string> readFileNames(string name);
void writeFileNames(string name, vector<string> fileNames);
