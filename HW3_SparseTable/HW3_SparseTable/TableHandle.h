#pragma once
#include "Helper.h"
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

// Lưu thành file để dễ access kết quả
// Ngoài biến đếm n và biến mảng thì lưu thêm biến type để xác định loại hàm find (findMin, findMax, findGCD) cần dùng
// Thay đổi giá trị mảng a hoặc giải phóng mảng a thì nhớ truyền THAM CHIẾU

// 1. Hàm ghi bảng vào file cho lệnh MAKE
void writeTable(fstream& f, int** a, int n, string type);
// 2. Hàm đọc bảng từ file cho lệnh QUERY
void readTable(fstream& f, int**& a, int& n, string& type);
// 3. Hàm tạo bảng cho lệnh MAKE
int** createTable(int n, int* numbers, int (*find)(int, int), string type);
// 4. Hàm xử lý truy vấn cho lệnh QUERY
int query(int n, int low, int high, int** a, string type);
// 5. Hàm xóa bảng cho cả 2 lệnh
void deleteTable(int**& a, int n);