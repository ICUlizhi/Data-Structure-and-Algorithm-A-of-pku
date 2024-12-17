#include <bits/stdc++.h>

using namespace std;

const int maxn = 20005;
int n, a[maxn], tmp[maxn], ans = 0;

void mergeSort(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  mergeSort(l, mid);
  mergeSort(mid + 1, r);
  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r) {
    if (a[i] <= a[j]) tmp[k++] = a[i++];
    else {
      tmp[k++] = a[j++];
      ans += mid - i + 1;
    }
  }
  while (i <= mid) tmp[k++] = a[i++];
  while (j <= r) tmp[k++] = a[j++];
  for (int i = l; i <= r; ++i) a[i] = tmp[i];
  return;
}

int main() {
  while (cin >> n && n) {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ans = 0;
    mergeSort(1, n);
    cout << ans << endl;
  }
  return 0;
}