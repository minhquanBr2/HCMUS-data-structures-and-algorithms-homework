#include "FileHandle.h"

// 6. Kiểm tra file có trong danh sách không
int checkFileName(string fileName, vector<string> fileNames, int fileCount, const int maxFileCount) {
    bool check = false;
    for (int i = 0; i < fileNames.size(); i++) {
        if (fileNames[i] == fileName) {
            check = true;
            break;
        }
    }
    // File có sẵn
    if (check)
        return 1;
    // Chưa có file nhưng còn chõ trống
    else if (fileCount < maxFileCount)
        return 0;
    // Chưa có file và không còn chỗ trống
    else
        return -1;
}
// 7 & 8. Hàm đọc số lượng file chứa data từ fileCount.txt
int readFileCount(string name) {
    fstream f(name, std::ios::in);
    int fileCount = 0;
    f >> fileCount;
    f.close();
    return fileCount;
}
void writeFileCount(string name, int& fileCount) {
    fstream f(name, std::ios::out);
    f << fileCount;
    f.close();
}
// 9 & 10. Hàm đọc danh sách tên file chứa data từ fileNames.txt
vector<string> readFileNames(string name) {
    fstream f;
    f.open(name, std::ios::in);
    vector<string> fileNames; string fileName;
    while (f >> fileName) {
        fileNames.push_back(fileName);
    }
    f.close();
    return fileNames;
}
void writeFileNames(string name, vector<string> fileNames) {
    fstream f;
    f.open(name, std::ios::out);
    for (int i = 0; i < fileNames.size(); i++) {
        f << fileNames[i] << endl;
    }
    f.close();
}

