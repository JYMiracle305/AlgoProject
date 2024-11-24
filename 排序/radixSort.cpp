#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int item;

int digit(item x, int d) {
    int i;
    for (i = 0; i < d; i++)
        x /= 10;
    return x % 10;
}

void bucketsort(vector<item>& A, int n, int d) {
    vector<vector<item>> buckets(10);
    for (int i = 0; i < n; i++) {
        buckets[digit(A[i], d)].push_back(A[i]);
    }
    int index = 0;
    for (int i = 0; i < 10; i++) {
        for (auto num : buckets[i]) {
            A[index++] = num;
        }
        buckets[i].clear();
    }
}

// 基数排序
void radixsort(vector<item>& A, int n, int d) {
    for (int i = 0; i < d; i++)
        bucketsort(A, n, i);
}

vector<int> fib_mod(int n, int Q) {
    vector<int> fib(n + 1, 0);
    fib[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % Q;
    }
    fib.erase(fib.begin());
    return fib;
}

int weighted_sum(const vector<int>& fib_mod_seq, int Q) {
    vector<int> sorted_seq = fib_mod_seq;
    radixsort(sorted_seq, sorted_seq.size(), 10);
    
    int weighted_sum = 0;
    for (size_t i = 0; i < sorted_seq.size(); ++i) {
        weighted_sum += (i + 1) * sorted_seq[i];
        weighted_sum %= Q;
    }
    return weighted_sum;
}

int main() {
    int T;
    cin >> T;
    
    for (int t = 0; t < T; ++t) {
        int n, Q;
        cin >> n >> Q;
        
        vector<int> fib_mod_seq = fib_mod(n, Q);
        
        int result = weighted_sum(fib_mod_seq, Q);
    
        cout << result << endl;
    }
    
    return 0;
}