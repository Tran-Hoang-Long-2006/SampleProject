# Báo cáo Bài tập lớn - Nhóm 17

## 1. Thông tin nhóm
| STT | Họ và tên | MSSV | Vai trò |
|---|---|---|---|
| 1 | Trần Hoàng Long | 24022813 | Nhóm trưởng |
| 2 | Phan Huy Quang | 24022827 | Thành viên |
| 3 | Nguyễn Công Minh | 24022816 | Thành viên |
| 4 | Nguyễn Quang Vũ | 22026510 | Thành viên |
| 5 | Trịnh Tài Thu | 24022836 | Thành viên |

---

## 2. Thông tin bài tập
- **Tên bài toán**: Bài 6. Bài toán balô (Knapsack).
- **Đề bài**: Có N đồ vật, khối lượng `w[i]`, giá trị `v[i]`.
- **Gợi ý**:
  - Đệ quy xét từng đồ vật.
  - Có 2 lựa chọn: Chọn hoặc bỏ.
  - Nếu chọn, giảm sức chứa.
  - Nếu không chọn, chuyển sang đồ vật tiếp theo.




---

## 3. Hướng giải quyết bài toán

### a. Phân tích bài toán
Bài toán yêu cầu lựa chọn một tập hợp đồ vật từ N đồ vật, mỗi đồ vật có **khối lượng** `w[i]` và **giá trị** `v[i]`, sao cho tổng khối lượng không vượt quá `W` và tổng giá trị đạt được là lớn nhất.  

Đây là một bài toán **Balo 0/1 (0/1 Knapsack Problem)**, một bài toán kinh điển trong lập trình tối ưu và quy hoạch động. Ta cần tìm chiến lược chọn đồ vật tối ưu dựa trên trạng thái trước đó, thay vì thử tất cả các phương án.

---

### b. Thuật toán/Hướng tiếp cận

#### 1. **Ý tưởng chính**
- Sử dụng **quy hoạch động kết hợp đệ quy có nhớ (Memoization)** để tối ưu hóa quá trình tính toán.
- Dùng bảng nhớ `dp[i][W]` để lưu giá trị lớn nhất có thể đạt được khi xét `i` đồ vật với sức chứa tối đa `W`.
- Tránh tính toán lặp lại bằng cách lưu kết quả đã tính vào `dp[i][W]`.

#### 2. **Xây dựng công thức truy hồi**
- Nếu không còn đồ vật hoặc sức chứa đã đầy (`i == 0 || W == 0`), bài toán dừng lại với kết quả `0`.
- Nếu món đồ thứ `i` có khối lượng lớn hơn `W`, ta **bỏ qua** món đồ đó:  
  \[
  dp[i][W] = dp[i - 1][W]
  \]
- Nếu món đồ thứ `i` có thể được chọn, ta có hai lựa chọn:
  - **Không chọn món đó**, giá trị tối ưu giữ nguyên:  
    \[
    dp[i][W] = dp[i - 1][W]
    \]
  - **Chọn món đó**, giá trị tối ưu sẽ là giá trị món đồ cộng với giá trị tối ưu của bài toán con (sức chứa bị giảm đi `w[i]`):  
    \[
    dp[i][W] = dp[i - 1][W - w[i]] + v[i]
    \]
- Kết quả cuối cùng là giá trị lớn nhất giữa hai phương án trên:
  \[
  dp[i][W] = max(dp[i - 1][W], dp[i - 1][W - w[i]] + v[i])
  \]

#### 3. **Triển khai thuật toán**
- **Sử dụng đệ quy có nhớ (`knapsack_memo`)** để tính giá trị tối ưu:
  - Nếu đã tính trước đó (`dp[i][W] != -1`), trả về kết quả ngay.
  - Nếu không, tính toán theo công thức trên và lưu lại vào `dp[i][W]` để sử dụng sau này.
  
- **Truy xuất danh sách đồ vật được chọn (`find_selected_items`)**:
  - Duyệt ngược từ `N` về `1`, so sánh `dp[i][W]` với `dp[i-1][W]`:
    - Nếu khác nhau, món đồ thứ `i` đã được chọn.
    - Nếu giống nhau, món đồ đó không được chọn.
  - Xuất ra chuỗi nhị phân đại diện cho các món đồ được chọn.

#### 4. **Đánh giá độ phức tạp**
- **Không dùng bảng nhớ**: Đệ quy thông thường có độ phức tạp **O(2^N)**, quá lớn khi `N` lớn.
- **Dùng bảng nhớ (Memoization)**: Giảm độ phức tạp xuống **O(N * W)**, giúp tối ưu hiệu suất.

---

## 4. Ví dụ minh họa

### Ví dụ 1  
**Input:**  
N = 4, W = 5  
w = [2, 3, 4, 2]  
v = [3, 4, 5, 3]  

**Output:**  
Giá trị lớn nhất: 7  
Chuỗi lựa chọn: 1010  

**Giải thích:**  
- Sức chứa tối đa là **5**.  
- Các đồ vật:  
  1. Đồ vật 1: w = 2, v = 3  
  2. Đồ vật 2: w = 3, v = 4  
  3. Đồ vật 3: w = 4, v = 5  
  4. Đồ vật 4: w = 2, v = 3  
- Chọn đồ vật **1** và **2** (tổng w = 5, tổng v = 7).  
- Chuỗi lựa chọn: `1010` (chọn đồ vật 1 và 2, bỏ 3 và 4).  



### Ví dụ 2  
**Input:**  
N = 5, W = 10  
w = [1, 4, 5, 7, 2]  
v = [2, 3, 6, 8, 4]  

**Output:**  
Giá trị lớn nhất: 12  
Chuỗi lựa chọn: 01101  

**Giải thích:**  
- Sức chứa tối đa là **10**.  
- Các đồ vật:  
  1. Đồ vật 1: w = 1, v = 2  
  2. Đồ vật 2: w = 4, v = 3  
  3. Đồ vật 3: w = 5, v = 6  
  4. Đồ vật 4: w = 7, v = 8  
  5. Đồ vật 5: w = 2, v = 4  
- Chọn đồ vật **3**, **5** và **1** (tổng w = 10, tổng v = 12).  
- Chuỗi lựa chọn: `01101` (chọn đồ vật 1, 3, 5, bỏ 2 và 4).  



### Ví dụ 3  
**Input:**  
N = 6, W = 15  
w = [3, 8, 4, 5, 2, 6]  
v = [6, 10, 7, 8, 3, 9]  

**Output:**  
Giá trị lớn nhất: 24  
Chuỗi lựa chọn: 101011  

**Giải thích:**  
- Sức chứa tối đa là **15**.  
- Các đồ vật:  
  1. Đồ vật 1: w = 3, v = 6  
  2. Đồ vật 2: w = 8, v = 10  
  3. Đồ vật 3: w = 4, v = 7  
  4. Đồ vật 4: w = 5, v = 8  
  5. Đồ vật 5: w = 2, v = 3  
  6. Đồ vật 6: w = 6, v = 9  
- Chọn đồ vật **1, 3, 4, 6** (tổng w = 15, tổng v = 24).  
- Chuỗi lựa chọn: `101011` (chọn đồ vật 1, 3, 4, 6, bỏ 2 và 5).  


---

## 5. Link video báo cáo
[Video báo cáo nhóm 17](hcttps://drive.google.com/file/d/1pzIBjwQyO0dB1aaasqYZ9bobH50v7Ud_/view?usp=sharing)


---

## 6. Link source code
[Thư mục src](./src)

---
## 7. Ưu điểm và Hạn chế

### Ưu điểm
- **Tiết kiệm bộ nhớ**: Sử dụng **bảng nhớ (memoization)** giúp tránh tính toán lặp lại, giảm độ phức tạp thời gian.
- **Hiệu suất tốt**: Thuật toán có độ phức tạp **O(NW)**, phù hợp với bài toán có `N` và `W` không quá lớn.
- **Kết quả chính xác, dễ hiểu**: Lưu trạng thái của các lựa chọn, giúp truy xuất **chuỗi nhị phân lựa chọn** dễ dàng.

### Hạn chế
- **Tốn bộ nhớ khi sử dụng bảng 2D**: Khi `N` và `W` quá lớn (ví dụ `N = 1000`, `W = 10^5`), bảng `dp[N][W]` có thể gây tràn bộ nhớ.
- **Không phù hợp với `W` cực lớn**: Khi `W` quá lớn (hàng triệu), cần dùng phương pháp khác như **quy hoạch động xấp xỉ**.
- **Mất khả năng truy vết chuỗi lựa chọn khi tối ưu bộ nhớ**: Nếu tối ưu dùng **mảng một chiều `dp[W]`**, chương trình không thể truy vết danh sách đồ vật đã chọn.

### Giải pháp khắc phục
- **Cần truy vết chuỗi lựa chọn** → Dùng `dp[N][W]` như trong code ban đầu.
- **Cần tiết kiệm bộ nhớ** → Dùng `dp[W]`, nhưng không truy vết được danh sách đồ vật.
