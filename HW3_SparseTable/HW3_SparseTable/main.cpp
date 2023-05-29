// Lưu ý: các file chứa dữ liệu các bảng, số lượng thông số, danh sách tên bảng 
// sẽ được đặt chung với thư mục chứa file .exe (đối với VStudio là thư mục Debug)
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <math.h>
#include "FileHandle.h"
#include "TableHandle.h"
using namespace std;
#define INSUFFICIENT_ARGUMENTS 1
#define INVALID_INSTRUCTION 2
#define INVALID_TABLE_TYPE 3
#define COULD_NOT_ACCESS_FILE 4
#define FILE_COUNT_REACHED_LIMIT 5
const int MAX_FILE_COUNT = 5;
const string fileCountTXT = "fileCount.txt";
const string fileNamesTXT = "fileNames.txt";

int main(int argc, char** argv) {
    if (argc < 5)
        return INSUFFICIENT_ARGUMENTS;

    int** a = NULL;
    int n = 0;
    // table: A
    // query: Q

    // Ghi bảng mới -> file phải có sẵn hoặc còn chỗ trống
    if (strcmp(argv[1], "make") == 0) {
        string fileName = string(argv[2]) + ".txt";
        int fileCount = readFileCount(fileCountTXT);
        vector<string> fileNames = readFileNames(fileNamesTXT);
        int check = checkFileName(fileName, fileNames, fileCount, MAX_FILE_COUNT); 

        if (check == 1 || check == 0) {
            // Đọc bảng từ command line
            fstream f(fileName, ios::out);
            n = argc - 4;
            int* numbers = new int[n]; for (int i = 0; i < n; i++) numbers[i] = atoi(argv[i + 4]);
            if (strcmp(argv[3], "MIN") == 0)
                a = createTable(n, numbers, findMin, "MIN");
            else if (strcmp(argv[3], "MAX") == 0)
                a = createTable(n, numbers, findMax, "MAX");
            else if (strcmp(argv[3], "GCD") == 0)
                a = createTable(n, numbers, findGCD, "GCD");
            else
                return INVALID_TABLE_TYPE;
            // Ghi bảng vào file sau khi xử lý
            writeTable(f, a, n, argv[3]); 
            // Tăng số lượng file và lưu thêm tên file vừa đc khởi tạo
            if (check == 0) {
                fileCount++;
                writeFileCount("fileCount.txt", fileCount);
                fileNames.push_back(fileName);
                writeFileNames("fileNames.txt", fileNames);
            }
            // Xóa bảng, thu hồi bộ nhớ
            delete[] numbers;
            deleteTable(a, n);
        }
        else
            return FILE_COUNT_REACHED_LIMIT;
    }




    // Đọc bảng cũ -> file phải có sẵn
    else if (strcmp(argv[1], "query") == 0) {
        string fileName = string(argv[2]) + ".txt";
        int fileCount = readFileCount(fileCountTXT);
        vector<string> fileNames = readFileNames(fileNamesTXT);
        int check = checkFileName(fileName, fileNames, fileCount, MAX_FILE_COUNT);

        if (check == 1) {
            // Đọc bảng từ file và thông số từ command line
            fstream f(fileName, ios::in);
            int low = atoi(argv[3]);
            int high = atoi(argv[4]);
            string type = "";
            readTable(f, a, n, type);
            // Thực hiện truy vấn
            int res = query(n, low, high, a, type);
            cout << res << endl;
            // Xóa bảng`
            deleteTable(a, n);
        }
        else {
            return COULD_NOT_ACCESS_FILE;
        }        
    }

    else {
        return INVALID_INSTRUCTION;
    }
    return 0;
}