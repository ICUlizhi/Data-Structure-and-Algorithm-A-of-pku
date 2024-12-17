#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    deque<int> minDeque, maxDeque;
    vector<int> a, b;

    for (int i = 0; i < n; i++) {
        while (!minDeque.empty() && minDeque.front() <= i - k) {
            minDeque.pop_front(); 
        }
        while (!minDeque.empty() && arr[minDeque.back()] >= arr[i]) {
            minDeque.pop_back();  
        }
        minDeque.push_back(i);
        while (!maxDeque.empty() && maxDeque.front() <= i - k) {
            maxDeque.pop_front();
        }
        while (!maxDeque.empty() && arr[maxDeque.back()] <= arr[i]) {
            maxDeque.pop_back(); 
        }
        maxDeque.push_back(i);
        if (i >= k - 1) {
            a.push_back(arr[minDeque.front()]);
            b.push_back(arr[maxDeque.front()]);
        }
    }

    for (auto i : a) {
        cout << i << ' ';
    }
    cout << endl;
    for (auto i : b) {
        cout << i << ' ';
    }
    return 0;
}
