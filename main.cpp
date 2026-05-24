#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <algorithm>
#include <bitset>
#include <deque>
#include<complex>
#include <functional>
#include <chrono>
#include <cmath>
#include <span>
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
#include <array>
#define int int32_t
#define long int64_t
#define ulong uint64_t
#define uint uint32_t
#define uset unordered_set
#define umap unordered_map
#define sizet size_t
#define i128 __int128_t
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
#define vt vector
#define pb push_back
#define eb emplace_back
#define pii pair<int,int>
#define all(x) (x).begin(),(x).end()

using namespace std;
using namespace __gnu_pbds;
template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using omset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;
inline constexpr bool MULTITEST = 0;


void solve() {
    string s;
    cin >> s;
    string rev = s;
    reverse(all(rev));
    swap(s, rev);
    s += '$' + rev + '#';
    uint n = s.length();
    vt<uint> p(n), c(n); // TODO:  order, class of the equality
    {
        // TODO: k == 0
        vt<pair<char, uint>> a(n);
        for (uint i = 0; i < n; ++i) a[i] = {s[i], i};
        sort(all(a));
        for (uint i =0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (uint i = 1; i < n; ++i) {
                c[p[i]] = c[p[i-1]] + (a[i].first != a[i-1].first);
        }
    }

    uint k = 0;
    while (1u << k < n) {
        // TODO: k -> k +1
        vt<pair<pair<uint,uint>, uint>> a(n);
        for (uint i = 0; i < n; ++i) a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        sort(all(a));
        for (uint i =0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (uint i = 1; i < n; ++i) {
            c[p[i]] = c[p[i-1]] + (a[i].first != a[i-1].first);
        }
        k++;
    }

    for (auto x : p) cout << x << ' ' << s.substr(x, n - x) << '\n';

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ulong TESTS_COUNT = 1;
    if constexpr (MULTITEST) {
        cin >> TESTS_COUNT;
    }
#ifdef LOCAL
    for (uint _GENERIC_VARIABLE_NAME = 1; _GENERIC_VARIABLE_NAME <= TESTS_COUNT; ++_GENERIC_VARIABLE_NAME) {
        cout << "=== Test #" << _GENERIC_VARIABLE_NAME << " ===" << '\n';
        auto start = chrono::steady_clock::now();
        solve();
        auto end = chrono::steady_clock::now();
        auto res = chrono::duration<double>(end - start);
        cout << "\nTime: " << res.count() << 's' << '\n';
    }
#else
    for (uint _GENERIC_VARIABLE_NAME = 1; _GENERIC_VARIABLE_NAME <= TESTS_COUNT; _GENERIC_VARIABLE_NAME++) {
        solve();
        cout << '\n';
    }
#endif

    return 0;
}
