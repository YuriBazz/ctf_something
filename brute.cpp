#include <algorithm>
#include <deque>
#include <functional>
#include <chrono>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int int32_t
#define long int64_t
#define ulong uint64_t
#define uint uint32_t
#define uset unordered_set
#define umap unordered_map
#define sizet size_t
#define i128 __int128_t
#define vi vector<int>
#define gr vector<vector<int>>
#define vl vector<long>
#define vd vector<double>
#define vt vector
#define pb push_back
#define pii pair<int,int>
#define all(x) (x).begin(),(x).end()

using namespace std;
using namespace __gnu_pbds;
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using omset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;


ulong B1 = 1e9 + 9;

ulong generate_random_base() {
  static random_device rd;
  static mt19937_64 gen(rd());
  static uniform_int_distribution<ulong> dist(1, B1 - 1);
  return dist(gen);
}

string s, t;
uint n;
vt<ulong> hs, ht1;
vt<ulong> xs;
void build() {
  xs = vt<ulong>(n + 1);
  hs = vt<ulong>(n +1);
  ht1 = vt<ulong>(n + 1);
  ulong x = generate_random_base();
  xs[0] = 1;
  hs[0] = 0;
  ht1[0] = 0;
  for (sizet i = 0; i < n; ++i) {
    xs[i+1] = xs[i]*x % B1;
    hs[i+1] = (hs[i] * x % B1 + s[i]) % B1;
    ht1[i+1] = (ht1[i] * x % B1 + t[i]) % B1;
  }
}

ulong get_hash(uint l, uint r, bool f) {
  return f ? (hs[r] + B1 - hs[l]*xs[r-l]%B1) % B1 : (ht1[r] + B1 - ht1[l]*xs[r-l]%B1) % B1;
}

int index = -1;

bool p(uint m) {
  umap<ulong, uint> mem;
  for (uint i = 0 ; i + m < n + 1; ++i) {
    mem[get_hash(i, i + m, true)] = i + 1;
  }
  for (uint j = 0; j + m < n + 1; ++j){
    uint x = mem[get_hash(j, j + m,false)];
    if (x) {
      index = x - 1;
      return true;
    }
  }
  return false;
}

void solve() {
  cin>> n;
  cin >> s >> t;
  build();

  uint l = 0, r = n + 1;
  while (r - l > 1) {
    uint m = l + (r - l) / 2;
    if (p(m)) l = m;
    else r = m;
  }
  cout << s.substr(index, l);
}



int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int TESTS_COUNT = 1;
  //cin >> TESTS_COUNT;
#ifdef LOCAL
  for (int _GENERIC_VARIABLE_NAME = 1; _GENERIC_VARIABLE_NAME <= TESTS_COUNT; ++_GENERIC_VARIABLE_NAME){
    cout << "=== Test #" << _GENERIC_VARIABLE_NAME << " ===\n";
    auto start = chrono::steady_clock::now();
    solve();
    auto end = chrono::steady_clock::now();
    auto res = chrono::duration<double>(end - start);
    cout << "\nTime: " << res.count() << 's' << endl;
  }
#else
  for (int _GENERIC_VARIABLE_NAME = 1; _GENERIC_VARIABLE_NAME <= TESTS_COUNT; _GENERIC_VARIABLE_NAME++) {
    solve();
    cout << '\n';
  }
#endif

  return 0;
}
