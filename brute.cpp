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


void solve() {
    string s1 = "", s2;
    cin >> s2;
    cout << (s1 < s2);
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
