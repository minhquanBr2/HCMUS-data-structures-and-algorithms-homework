#include "TableHandle.h"

// Lưu thành file để dễ access kết quả
// Ngoài biến đếm n và biến mảng thì lưu thêm biến type để xác định loại hàm find (findMin, findMax, findGCD) cần dùng
// Thay đổi giá trị mảng a hoặc giải phóng mảng a thì nhớ truyền THAM CHIẾU

// 1. Hàm ghi bảng vào file cho lệnh MAKE
void writeTable(fstream& f, int** a, int n, string type) {
    f << type << " " << n << endl;

    int size = n;
    int k = (int)log2(n) + 1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < size; j++)
            f << a[i][j] << " ";
        f << endl;
        size -= (int)pow(2, i);
    }

    f.close();
}
// 2. Hàm đọc bảng từ file cho lệnh QUERY
void readTable(fstream& f, int**& a, int& n, string& type) {
    f >> type >> n;

    int size = n;
    int k = (int)log2(n) + 1;
    a = new int* [k];

    for (int i = 0; i < k; i++) {
        a[i] = new int[size];
        for (int j = 0; j < size; j++)
            f >> a[i][j];
        size -= (int)pow(2, i);
    }

    f.close();
}
// 3. Hàm tạo bảng cho lệnh MAKE
int** createTable(int n, int* numbers, int (*find)(int, int), string type) {
    int size = n;
    int k = (int)log2(n) + 1;
    int** a = new int* [k];

    cout << type << " " << n << endl;
    for (int i = 0; i < k; i++) {
        a[i] = new int[size];
        for (int j = 0; j < size; j++) {
            if (i == 0)
                a[i][j] = numbers[j];
            else
                a[i][j] = find(a[i - 1][j], a[i - 1][j + (int)pow(2, i - 1)]);
            cout << a[i][j] << " ";
        }
        cout << endl;
        size -= (int)pow(2, i);
    }

    return a;
}
// 4. Hàm xử lý truy vấn cho lệnh QUERY
int query(int n, int low, int high, int** a, string type) {
    if (low < 0 || high >= n)
        return 1e9 + 7;
    // Chú ý range chỉ lấy từ low đến high chứ không lấy tất cả n số
    // Số thứ tự cột (k) không cần +1
    int k = (int)log2(high - low + 1);
    if (type == "MIN")
        return findMin(a[k][low], a[k][high - (int)pow(2, k) + 1]);
    else if (type == "MAX")
        return findMax(a[k][low], a[k][high - (int)pow(2, k) + 1]);
    else if (type == "GCD")
        return findGCD(a[k][low], a[k][high - (int)pow(2, k) + 1]);
}
// 5. Hàm xóa bảng cho cả 2 lệnh
void deleteTable(int**& a, int n) {
    int k = (int)log2(n) + 1;
    if (a) {
        for (int i = 0; i < k; i++) delete[] a[i];
        delete[] a;
        a = NULL;
    }
}