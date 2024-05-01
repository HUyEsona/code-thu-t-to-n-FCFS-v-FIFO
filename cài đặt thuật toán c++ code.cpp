#include<iostream> // Thư viện cho việc nhập xuất dữ liệu.
#include <iomanip> // Thư viện cho việc định dạng hiển thị dữ liệu.
using namespace std;

int twt = 0; // Biến toàn cục để lưu tổng thời gian chờ trung bình.

// Cấu trúc để lưu thông tin của mỗi tiến trình.
struct Process {
    int id, bt, at, ct, tat, wt;
};

Process p[100]; // Mảng lưu thông tin của các tiến trình.

// Hàm nhập thông tin về thời gian đến và thời gian burst của các tiến trình.
void Input(int n) {
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> p[i].at;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> p[i].bt;
        p[i].id = i + 1;
    }
}

// Hàm sắp xếp các tiến trình theo thời gian đến tăng dần.
void Sort(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                // Sắp xếp burst time, arrival time, và ID tương ứng.
                swap(p[j].bt, p[j + 1].bt);
                swap(p[j].at, p[j + 1].at);
                swap(p[j].id, p[j + 1].id);
            }
        }
    }
}

// Hàm tính toán completion time, turnaround time, và waiting time của các tiến trình.
void Calc(int n) {
    int sum = 0;
    sum = sum + p[0].at;
    for (int i = 0; i < n; i++) {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if (sum < p[i + 1].at) {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        }
    }
}

// Hàm hiển thị bảng kết quả và thông tin về thời gian chờ và thời gian quay vòng trung bình.
void Show(int n) {
    int tat = 0;
    cout << "Process\tArrival\tBurst\tWaiting\tTurn Around\tCompletion\n";
    for (int i = 0; i < n; i++) {
        cout << " P[" << p[i].id << "]\t " << p[i].at << "\t" << p[i].bt << "\t" << p[i].wt << "\t " << p[i].tat << "\t\t" << p[i].ct << "\n";
        twt += p[i].wt;
        tat += p[i].tat;
    }
    // Hiển thị thời gian chờ trung bình và thời gian quay vòng trung bình.
    cout << "Average Waiting Time: " << fixed << setprecision(2) << twt * 1.0 / n << endl;
    cout << "Average Turn Around Time : " << fixed << setprecision(2) << tat * 1.0 / n << endl;
}

// Hàm main để chạy chương trình.
int main() {
    int n;
    // Nhập số lượng tiến trình từ người dùng.
    cout << "Enter the number of processes in your system: ";
    cin >> n;
    // Gọi các hàm để nhập dữ liệu, sắp xếp, tính toán và hiển thị kết quả.
    Input(n);
    Sort(n);
    Calc(n);
    Show(n);
    return 0;
}
