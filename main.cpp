#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#define INCLUDES_ 
#ifdef INCLUDES_
#include <algorithm>
#include <bitset>
#include <deque>
#include<complex>
#include <functional>
#include <chrono>
#include <iostream>
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
#endif
inline constexpr bool MULTITEST = 1;

uint len(pair<uint,uint> p, uint n) {
    if (p.first < p.second) return p.second - p.first - 1;
    return n + p.second - p.first - 1; // n - (p.first - p.second + 1)
}

void solve() {
    uint n,m;
    cin >> n >> m;
    vt<uint> a(m);
    for (uint i = 0; i < m; ++i) cin >> a[i];
    sort(all(a));
    vt<pair<uint,uint>> segs;
    segs.reserve(m);
    for (uint i = 0; i < m; ++i) segs.eb(a[i % m], a[(i + 1) % m]);
    sort(all(segs), [&](auto p1, auto p2) {
        return len(p1, n) > len(p2, n);
    });

    int k = 0;
    int count = n;
    for (auto &seg : segs) {
        int l = (int)len(seg, n) - 2 * k;
        if (l <= 0) continue;
        count -= l;
        count += l == 1 ? 0 : 1;
        k += 2;
    }
    cout << count;
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
        cout << "====== Test #" << _GENERIC_VARIABLE_NAME << " ======" << '\n';
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
