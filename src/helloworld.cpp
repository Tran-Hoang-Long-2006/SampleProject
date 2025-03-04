#include <iostream>
#include <vector>
using namespace std;

//Bảng nhớ (memoization)
vector<vector<int>> dp;

//Hàm đệ quy có nhớ
int knapsack_memo(int i, int W, int w[], int v[]) {
    if (i == 0 || W == 0) return 0;  //Điều kiện dừng
    if (dp[i][W] != -1) return dp[i][W]; //Nếu đã tính trước đó
    if (w[i - 1] > W) return dp[i][W] = knapsack_memo(i - 1, W, w, v); //Nếu không thể chọn món đồ i

    //Nếu có thể chọn, lấy max giữa bỏ qua hoặc chọn
    return dp[i][W] = max(knapsack_memo(i - 1, W, w, v),
                          knapsack_memo(i - 1, W - w[i - 1], w, v) + v[i - 1]);
}

//Hàm truy xuất chuỗi nhị phân kết quả
string find_selected_items(int N, int W, int w[], int v[]) {
    string result(N, '0'); //Khởi tạo chuỗi toàn '0'
    int weight = W;

    for (int i = N; i > 0; i--) {
        if (dp[i][weight] != dp[i - 1][weight]) { //Nếu chọn món i
            result[i - 1] = '1';  //Đánh dấu đã chọn
            weight -= w[i - 1]; //Trừ sức chứa
        }
    }

    return result;
}

int main() {
    //input
    int N, W;
    cout << "So do vat la (N): "; cin >> N;
    cout << "Khoi luong toi da la (W): "; cin >> W;
    int w[N], v[N];
    cout << "\nKhoi luong, gia tri cua do vat: \n";
    for (int i = 0; i < N; i++) {
        cout << "   Thu " << i+1 << " la: ";
        cin >> w[i] >> v[i];
    }

    //Khởi tạo bảng nhớ với -1
    dp.assign(N + 1, vector<int>(W + 1, -1));

    //output
    cout << "\n-------------------";
    cout << "\nGia tri lon nhat: " << knapsack_memo(N, W, w, v) << endl;
    cout << "Chuoi lua chon (dang 01): " << find_selected_items(N, W, w, v) << endl;

    return 0;
}
