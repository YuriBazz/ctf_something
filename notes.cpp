//
// Created by george on 20.02.2026.
//
#include <stdint.h>
#include <vector>



using namespace std;

namespace implicit_treap {
  struct node {
    node(int y) : x(y), sum(y){}
    int x;
    int p = rand();
    int s = 1;
    ll sum;
    node *l = nullptr, *r = nullptr, *pr = nullptr;
  };

  int size(node* v) {
    return v ? v->s : 0;
  }

  ll m(node* v) {
    return v ? v->sum : 0;
  }

  void upd(node* v) {
    if (!v) return;
    v->s = 1 + size(v->l) + size(v->r);
    v->sum = v->x + m(v->l) + m(v->r);
  }

  node* find(node* v, int i) {
    if (!v) return v;
    if (i == size(v->l) + 1) return v;
    if (i <= size(v->l)) return find(v->l, i);
    return find(v->r, i - size(v->l) - 1);
  }

  // TODO: Push all that hasn't &

  //TODO: t = l <- r ПРЕДПОЛАГАЕТСЯ, ЧТО КЛЮЧИ (IMPLICIT KEYS -- ПОРЯДОЧЕК БЛЯТЬ) СПРАВА БОЛЬШЕ КЛЮЧЕЙ СЛЕВА
  void merge (node* & t, node* l, node* r) {
    if (!l || !r)
      t = l ? l : r;
    else if (l->p > r->p)
      merge (l->r, l->r, r),  t = l;
    else
      merge (r->l, l, r->l),  t = r; // TODO: Понять, почему тут l <- r->l
    upd(t);
  }

  //TODO: [0, i) [i,n)
  void split (node* t, node* & l, node* & r, int i) {
    if (!t) {
      r = nullptr;
      l = nullptr;
      return;
    }
    if (i <= size(t->l)) {
      split(t->l, l, t->l, i);
      r = t;
    } else {
      split(t->r, t->r, r, i - size(t->l)- 1);
      l = t;
    }    upd(t);
  }

  void insert(node* &t, int i, int x) {
    node *t1, *t2;
    split(t, t1,t2,i);
    merge(t1, t1, new node(x));
    merge(t, t1,t2);
  }

  void erase(node* &t, int i) {
    if (!t) return;
    if (i == size(t->l) + 1) {
      merge(t, t->l, t->r);
    }else if (i <= size(t->l)) erase(t->l, i);
    else erase(t->r, i - size(t->l) - 1);
    upd(t);
  }

  ll get_sum(node* &t, int l, int r) {
    node *t1,*t2, *t3;
    split(t, t1, t3, r + 1);
    split(t1, t1,t2, l);
    ll res = t2->sum;
    merge(t, t1, t2);
    merge(t, t, t3);
    return res;
  }

  void reverse(node* &t, int l, int r) {
    node *t1,*t2, *t3;
    split(t, t1, t3, r + 1);
    split(t1, t1,t2, l);
    merge(t, t1, t2);
    merge(t, t, t3);
  }

  void dfs(node* v){
    if (!v)return;
    dfs(v->l);
    cout << v->x << ' ';
    dfs(v->r);
  }
}

namespace treap {
  struct node {
    int x; // TODO: Key
    int p = rand(); // TODO: priority
    node *l = nullptr, *r = nullptr;
    int s = 1;
  };

  int size(node* v) {
    return v ? v->s : 0;
  }

  void upd_s(node* v) {
    v->s = 1 + size(v->l) + size(v->r);
  }

  void split (node* t, int x, node* &l, node* & r) {
    if (!t)
      l = r = nullptr;
    else if (t->x <= x)
      split (t->r, x, t->r, r),  l = t;
    else
      split (t->l, x, l, t->l),  r = t;
    upd_s(l);
    upd_s(r);
  }

  void insert (node* &t, node* it) {
    if (!t)
      t = it;
    else if (it->p > t->p)
      split (t, it->x, it->l, it->r),  t = it;
    else
      insert (t->x <= it->x ? t->r : t->l, it);
    upd_s(t);
  }

  void merge (node* &t, node* l, node* r) {
    if (!l || !r)
      t = l ? l : r;
    else if (l->p > r->p)
      merge (l->r, l->r, r),  t = l;
    else
      merge (r->l, l, r->l),  t = r;
    upd_s(t);
  }

  void erase (node* & t, int x) {
    if (t->x == x) {
      node* th = t;
      merge (t, t->l, t->r);
      delete th;
    }
    else
      erase (x < t->x ? t->l : t->r, x);
    upd_s(t);
  }

  node* unite (node* l, node* r) {
    if (!l || !r)  return l ? l : r;
    if (l->p < r->p)  swap (l, r);
    node *lt, *rt;
    split (r, l->x, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    upd_s(l);
    return l;
  }
}

namespace bst_AVL {
  // TODO: Balanced BST -- In any case std::set<> should be used instead of this.
  // TODO: All other task, where you need AVL, you should use Treap
  //TODO: An example with size of subtrees
  //TODO: Implicit key:  with size of subtree we can find element by index

struct node {
  int x;
  node *l = nullptr,*r = nullptr;
  int h = 1;
  int s = 1;
};

int height(node* v) {
  return v ? v->h : 0;
}
int size(node* v) {
  return v ? v->s : 0;
}

node* rightRot(node* v) {
  node *l = v->l;
  node *r = l->r;
  l->r = v;
  v->l = r;
  v->h = max(height(v->l), height(v->r)) + 1;
  l->h= max(height(l->l), height(l->r))+ 1;
  v->s = size(v->l) + size(v->r) + 1;
  l->s = size(l->l) + size(l->r) + 1;
  return l;
}

node *leftRot(node *v) {
  node *r = v->r;
  node *l = r->l;
  r->l= v;
  v->r= l;
  v->h = max(height(v->l), height(v->r)) + 1;
  r->h= max(height(r->l), height(r->r))+ 1;
  v->s = size(v->l) + size(v->r) + 1;
  r->s = size(r->l) + size(r->r) + 1;
  return r;
}

int balance(node *v) {
  return v ? height(v->l) - height(v->r) : 0;
}

node *insert(node *v, int x) {
  if (!v) return new node{x};
  v->s++;
  if (x < v->x) {
    v->l= insert(v->l, x);
  }
  else {
    v->r= insert(v->r, x);
  }
  v->h = 1 + max(height(v->l),height(v->r));
  int bv = balance(v);
  if (bv > 1) {
    if (x < v->l->x) {
      return rightRot(v);
    }
    if (x > v->l->x) {
      v->l= leftRot(v->l);
      return rightRot(v);
    }
  }
  if (bv < -1) {
    if (x > v->r->x) {
      return leftRot(v);
    }
    if (x < v->r->x) {
      v->r= rightRot(v->r);
      return leftRot(v);
    }
  }
  return v;
}

node* min(node* v) {
  node* t = v;
  while (t->l) {
    t = t->l;
  }
  return t;
}

node *remove(node *v, int x) {
  if (!v) return v;

  if (x < v->x) {
    v->l = remove(v->l, x);
  } else if (x > v->x) {
    v->r = remove(v->r, x);
  } else {
    if (!v->l || !v->r) {
      node *temp = v->l ? v->l : v->r;

      if (!temp) {
        temp = v;
        v = nullptr;
      } else {
        *v = *temp;
      }
      delete temp;
    } else {
      node *temp = min(v->r);
      v->x = temp->x;
      v->r = remove(v->r, temp->x);
    }
  }

  if (!v) return v;

  v->h = 1 + max(height(v->l), height(v->r));
  v->s = 1 + size(v->l) + size(v->r);

  int bv = balance(v);

  if (bv > 1) {
    if (balance(v->l) >= 0) {
      return rightRot(v);
    }
    v->l = leftRot(v->l);
    return rightRot(v);
  }

  if (bv < -1) {
    if (balance(v->r) <= 0) {
      return leftRot(v);
    }
    v->r = rightRot(v->r);
    return leftRot(v);
  }
  return v;
}
int find(node* v, int k) {
  if (k - size(v->l) == 1) return v->x;
  if (k <= size(v->l)) return find(v->l, k);
  return find(v->r, k - size(v->l) -1);
}
}

namespace bst{
  //TODO: std::set<> is standard realisation of BST
  //TODO: But if there are need for special realisation, it could be smth like this
  //TODO: You should never use your own implementation instead of std::set<>

  struct node {
    int x;
    node *l, *r;
  };

  node* add(node *root, int x) {
    if (!root) return new node{x};
    if (x < root->x) root->l = add(root->l, x);
    else root->r = add(root->r,x);
    return root;
  }

  int find(node* root, int x) {
    if (!root) {
      int result = mm == INT32_MAX ? 0 : mm;
      mm = INT32_MAX;
      return result;
    }
    if (root-> x > x) {
      mm = min(mm, root->x);
      return find(root->l, x);
    }
    return find(root->r, x);
  }

  //TODO: Idiomatic realisation of find with implicit key
  node* find(int i, node* v) {
    if (!v) return v;
    if (i == 1 + size(v->l)) return v;
    if (i <= size(v->l)) return find(i, v->l);
    return find(i - size(v->l) - 1, v->r);
  }

}

namespace  sparse_table{
  //TODO: [l,r];
  //TODO: Builder
  sp = vector(K +1, vector<pair<int,int>>(ans.size()));
  for (sizet i = 0; i < h.size(); ++i) {
    sp[0][i] = {h[i], ans[i]};
  }
  for (int k = 1; k <= K; ++k) {
    for (sizet i = 0; i + (1<<k) <= h.size(); ++i) {
      sp[k][i] = min(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);
    }
  }

  ks = vector<int>(h.size() + 1);
  ks[1] = 0;
  for (sizet i = 2; i < h.size() + 1; ++i) {
    ks[i] = ks[i >> 1] + 1;
  }

  //TODO: Getter [l,r]
int get(int l, int r) {
  return min(sp[ks[r-l+1]][l], sp[ks[r-l+1]][r - (1 << ks[r-l+1]) + 1]).second;
}
}

namespace LCA{
  //TODO: Requires dfs with clock
  //TODO: Also it could require additional dfs to create parent[\cdot] for given tree
  bool isAncestor(int a, int b) {
    return t_in[a] <= t_in[b] && t_out[b] <= t_out[a];
  }

  int lca(int x, int y) {
    for (int k = K-1; k > -1; --k) {
      if (!isAncestor(up[k][x], y))
        x = up[k][x];
    }
    return isAncestor(x,y) ? x : up[0][x];
  }
  //TODO: Yet another way to impl lca
  /*
  if (d[x] < d[y]) swap(x,y);
    int dd = d[x] - d[y];
    int m1 = INT32_MAX, m2 = INT32_MAX;
    for (int k = K - 1; k > -1 && dd > 0; --k) {
      if (dd - (1 << k) >= 0) {
        m1 = min(m1, up[k][x].second);
        x = up[k][x].first;
        dd -= 1<<k;
      }
    }
    for (int k = K - 1; k > -1; --k) {
      if (up[k][x].first != up[k][y].first) {
        m1 = min(m1, up[k][x].second);
        m2 = min(m2, up[k][y].second);
        x = up[k][x].first;
        y = up[k][y].first;
      }
    }
   */
  //TODO: Euler's obhod. Needed for LCA -> RMQ
  void e_dfs(int x, int hh) {
    ind[x] = ans.size();
    h[x] = hh;
    ans.push_back(x);
    for (auto y : g[x]) {
      e_dfs(y, hh + 1);
      ans.push_back(x);
    }
  }
}

namespace segtree_top{

  //TODO: Простейший сег три на максимум
  //TODO: При пропагейте не забывать, что прокидывать не надо только у листьев. При добавлении -- ПРОПАГЕЙТ ТОЛЬКО ТОЛКАЕТ ВНИЗ => ОПЕРАЦИЮ В ТОЧКЕ ПРИМЕНИТЬ НАДО
  //[lx, rx)
void relax(int x) {
  t[x] = max(t[(x<<1) + 1], t[(x<<1) +2]);
}

void build(int n, int x, int lx, int rx) {
  if (rx - lx == 1) {
    if (lx < n) t[x] = a[lx];
    else t[x] = INT32_MIN;
    return;
  }
  int m = lx + (rx - lx) / 2;
  build(n, (x<<1) + 1, lx, m);
  build(n, (x<<1) + 2, m , rx);
  relax(x);
}

void sset(int i, int v, int x, int lx, int rx) {
  if (rx - lx == 1) {
    t[x] = v;
    return;
  }
  int m = lx + (rx - lx) / 2;
  if (i < m) sset(i, v, (x<<1) + 1, lx, m);
  else sset(i, v, (x<<1) + 2, m, rx);
  relax(x);
}

int get(int v, int l, int x, int lx, int rx) {
  if (t[x] < v) return -2;
  if (rx <= l) return -2;
  if (rx - lx == 1) return lx;
  int m = lx + (rx - lx) /2;
  int left = get(v, l, (x << 1) + 1, lx, m);
  return left == -2 ? get(v,l ,(x << 1) + 2, m, rx) : left;
}
}

namespace segtree_down{
  vector<int> a;
  vector<pair<int,int>> t;
  //TODO: ZERO-BASE INDEXING
void build() {
  for (int i = 0; i < len; i++) {
    t[len + i] = {a[i],a[i]};
  }
  for (int v = len - 1; v > -1; --v) {
    t[v] = {min(t[2*v].first, t[2*v+ 1].first), max(t[2*v].second, t[2*v + 1].second)};
  }
}

void set(int i, int x) {
  i += len;
  t[i] = {x, x};
  for (i /= 2; i > 0; i /= 2) {
    t[i] = {min(t[2*i].first, t[2*i+ 1].first), max(t[2*i].second, t[2*i + 1].second)};
  }
}

//[l,r]
int get(int l, int r) {
  int mmin = INT32_MAX;
  int mmax = INT32_MIN;
  l += len; r += len;
  while (l <= r) {
    if (l%2 == 1) {
      mmin = min(mmin, t[l].first);
      mmax = max(mmax, t[l++].second);
    }
    if (r%2 == 0) {
      mmin = min(mmin, t[r].first);
      mmax = max(mmax, t[r--].second);
    }
    l /=2;
    r /=2;
  }
  return mmax - mmin;
}
}

namespace sqrt_optimization {
  //TODO : Kopelovich
}

namespace strings {
  namespace hashing {
    void build(int x, int n) {
      xs = vll(n + 1);
      xs[0] = 1;
      for (int i = 0; i < n ; ++i) {
        xs[i + 1] = (xs[i] * x % BASE + BASE) % BASE;
      }
    }

    namespace bad_polynomial_hasing {
      //TODO: h[x] = H(s[0...x-1])
      for (int i = 0; i < n; ++i){
        h[i + 1] = ((s[i] * xs[i] % BASE + h[i]) % BASE + BASE)% BASE;
      }

      //TODO: H([l,r)) * x^{l} = h[r] - h[l];
      //TODO: So, if you want to compare to substrings u should check witch left border is greater, and mult other hash by x^{max - min}
    }
    namespace good_polynomial_hashing {
      h[n+1];
      h[0] = 0
      for (uint i = 0; i< n; ++i)
        h[i + 1] = (h[i]*x %BASE + s[i]) % BASE
      //TODO: Легко заметиь, что такой способ хеширования позволяет легко получать хеш подстроки H([l,r)) = h[r] - h[l]*x^{r-l}
    }

    ulong generate_random_base() {
      static random_device rd;
      static mt19937_64 gen(rd());
      static uniform_int_distribution<ulong> dist(239, B2 - 1);
      return dist(gen);
    }
    struct pair_hash {
      template <class T1, class T2>
      size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        size_t seed = hash1 + 0x9e3779b9 + (hash2 << 6) + (hash2 >> 2);
        return seed;
      }
    };
    //TODO: Anti Anti-Hash-Test STL Hashtable
    mt19937 gen(time(NULL));
    mem1.rehash(n + gen() %n);


    //TODO: Операции в кольце сразу с двумя элементами
    struct fnum {
      static constexpr ulong B1 = 1e9 + 9, B2 = 1e9 + 7;
      ulong a, b;
      fnum() : a(0), b(0) {}
      fnum(ulong x, ulong y) : a(x % B1), b(y % B2){}
      fnum(ulong x ) : a(x % B1), b(x % B2){}
      fnum operator +(const fnum& o) const {return {(a + o.a) % B1, (b + o.b) % B2};}
      fnum operator -(const fnum& o) const {return {(a +B1 - o.a) % B1, (b + B2 -  o.b) % B2};}
      fnum operator *(ulong x) const {return {a * x %B1, b*x%B2 };}
      fnum operator *(const fnum& o) const {return {a * o.a %B1, b*o.b%B2 };}
      fnum operator +(ulong x) const {return {(a + x) %B1, (b + x)%B2 };}
      bool operator==(const fnum &o) const {return  a == o.a && b == o.b;}
    };
    fnum x = {generate_random_base(fnum::B1 - 1), generate_random_base(fnum::B2 - 1)};



    //TODO:: Hash wrapper для строк
    template<class hash>
    struct stringw {
      uint n;
      const char *s;
      hash *h;

      stringw(string_view sv) : n(sv.size()), s(sv.data()), h(nullptr) {
        h = new hash[n + 1];
        h[0] = 0;
        for (uint i = 0; i < n; ++i) {
          h[i + 1] = h[i] * x + s[i];
        }
      }
      ~stringw() {
        delete[] h;
      }

      //[l,r)
      hash substr(uint l, uint r) {
        return h[r] - h[l] * xs[r- l];
      }
    };

    //TODO: Tree hashing
    //TODO:  h(v) = \sum_{u \in child[v]} h^2(u) + h(u) \cdot x^k + const  (mod m1) ((k -- index of child))
  }
  namespace pi_function {
    vt<int> pi(s.length() + 1, 0);
    int k = -1;
    pi[0] = k;
    for (uint i = 1; i <= s.length(); ++i) {
      while (k > -1 && s[k] != s[i-1]) {
        k = pi[k];
      }
      pi[i] = ++k; // безусловный инкремент, из-за -1
    }
  }
  namespace z_function {
    vt<int> z;
    void zz(const string &s) {
      z = vt(s.length(), 0);
      int l = 0, r = 0;
      for (int i = 1; i < s.length(); ++i) {
        int k = max(0, min(r - i, z[i - l]));
        while (s[i + k] == s[k]) k++;
        z[i] = k;
        if (i + z[i] > r) l = i, r = i + z[i];
      }
    }
  }
}

namespace graphs {
  //TODO: FB -- достаточно смешной алгоритм описываемый
  /*
   * TODO:   for(int v = 0; v < |V|; ++v) for(edge : Edges) if(good(edge)) relax(edge);
   */

  //TODO: Kun Вообще очень смешно: дфсиком ищется дополняющая цепь; нашлась -- обнуляем использованные вершины; нет -- мы в макс парсоче
  vt<char> u;
  vi pp;
  bool dfs(int v) {
    u[v] = 1;
    for (int i = head[v]; i != -1; i = graph[i].next) {
      auto &e = graph[i];
      if (e.f == 1 && (pp[e.b - n - 1] == -1 || (!u[pp[e.b - n - 1]] && dfs(pp[e.b - 1 - n])))) {
        pp[e.b - n - 1] = e.a;
        return 1;
      }
    }
    return 0;
  }

    // TODO: Собственно, Кун
  void kun() {
    pp = vi(n, -1);
    u = vt<char>(2 * n + 2, false);
    for (int i = 1; i <= n; ++i)
      if (dfs(i)) fill(all(u), false);

    vi ord(n);
    for (int i = 0; i < n; ++i) {
      int b = i + 1 + n;
      int a = pp[i];
      ord[a- 1] = b - n;
      for (int x = head[a]; x != -1; x = graph[x].next) {
        auto &e = graph[x];
        if (e.b == b) {
          e.f--;
          graph[x ^ 1].f++;
          break;
        }
      }
    }
    for (int i = 0; i < n; ++i) cout << ord[i] << ' ';
  }
}

namespace math {
  //TODO: Расиширеный Евклид
  {
    // x a + y b = gcd(a,b)
    int gcd(int a, int b, int &x, int &y) {
      if (b == 0) {
        x = 1, y = 0;
        return b;
      }
      int x1, y1, g = gcd(b, a % b, x1, y1);
      x = y1, y = x1 - a / b * y1;
      return g;
    } 
  }
  //TODO: Eratoshen
  {
    constexpr uint N = 1.5e6;

    vt<char> mark;
    vt<ulong> primes;

    void e() {
      mark = vt<char>(N,false);
      for (uint i = 2; i * i < N; ++i) {
        if (mark[i]) continue;
        for (uint j = i * i; j < N; j+=i)
          mark[j] = true;
      }

      primes.reserve(N);

      for (uint i = 2; i < N; ++i)
        if (!mark[i]) primes.pb(i);
    }
  }
  //TODO: Euler's function
  {
    uint phi = n;
    for (auto p : primes) {
      if (p * p > n) break;
      if (!(n % p)) {
        phi = phi / p  * (p-1);
        while (!(n%p)) n/=p;
      }
    }
    if (n > 1) phi = phi / n * (n - 1);
    cout << phi  << '\n';
  }
  //TODO: Vector field's basis (Primitive Gauss)
  {
    uint n;

    vt<uint> pos;
    vt<vt<double>> basis;

    bool eq(double a, double b) {
      return abs(a - b) < 0.5e-6;
    }


    void add() {
      vt<double> a(n);
      for (uint i = 0; i < n; ++i) cin >> a[i];
      for (sizet i = 0; i < basis.size(); ++i) {
        if (eq(a[pos[i]], 0)) continue;
        double c = a[pos[i]] / basis[i][pos[i]];
        for (sizet j = 0; j < a.size(); ++j)
          a[j] -= basis[i][j] * c;
      }
      sizet i = 0;
      while (i < a.size() && eq(a[i], 0)) i++;
      if (i == a.size()) return;
      basis.pb(a);
      pos.pb(i);
    }
    //TODO: Знак определителя O(n + I)
    for (uint i = 0; i < n; ++i) {
      while (pos[i] != i) {
        sign = - sign;
        swap(pos[i], pos[pos[i]]);
      }
    }
    //TODO: Тут можно лишь отметить, что не стоит забывать про обратный ход Гаусса
  }
  // TODO: FFT (recursion)
  {
    void sfft(vt<num> &a, bool f = false) {
      ulong n = a.size();
      if (n == 1) return;
      vt<num> b(n/2),c(n/2);
      for (ulong i = 0; i < n; ++i) (i%2 ? c :b)[i / 2] = a[i];
      sfft(b, f),sfft(c, f);
      for (ulong i = 0; i < n; ++i) a[i] = b[i % (n/2)] + exp(2 * PI * (f ? n - i : i) * I  / (n * 1.0)) * c[i % (n / 2)];
    }

    void sfft_inverse(vt<num> &f) {
      sfft(f, true);
      for (ulong i = 0; i < f.size(); ++i) f[i] /=f.size();
    }
  }
  // TODO: FFT (non - recursive)
  {
    int K;
    ulong N;

    vt<num> root;
    vt<ulong> rev;

    void init() {
      root = vt<num>(N);
      rev = vt<ulong>(N);
      for (ulong  i = 0; i < N; ++i) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (K -1)); // позиции будут, как будто отреверсировали битовую запись
      for (ulong k = 1; k < N; k *= 2) {
        // root[k...2k) будет хранить первые k корней степени 2k.
        // Тогда w_{i + k} = -w_i
        root[k] = {1,0};
        num x = exp(PI * I / (k * 1.0));
        for (ulong i = 1; i < k; ++i) {
          root[k + i] = i % 2 ? root[(k + i) / 2] * x : root[(k + i) / 2];
        }
      }
    }

    void fft(vt<num> &a, vt<num> &fa) {
      for (ulong i = 0; i < N; ++i) fa[rev[i]] = a[i];
      for (ulong k = 1; k < N; k *=2) {
        for (ulong i = 0; i < N; i += 2 *k) { // ?????
          for (uint j = 0; j < k; ++j) {
            num x = root[k + j] * fa[i + j + k];
            fa[i + j + k] = fa[i + j] - x;
            fa[i + j] += x;
          }
        }
      }
    }

    vt<num> tb(string &s) {
      vt<num> r;
      for (int i = s.size(); i > 0; i-=BD) {
        int start = max(0, i - BD);
        r.eb(stoi(s.substr(start, i - start)));
      }
      return r;
    }


    void ifft(vt<num> &fa, vt<num> &a) {
      fft(fa,a);
      reverse(a.begin() + 1, a.end());
      for (uint i = 0; i < N; ++i) a[i] /= N;
    }
  }
}

namespace flows {
  { // TODO: Примитивный FF.
    struct Edge {
      int a,b,f,c,next;
    };

    vt<Edge> edges;
    vi head;
    vt<bool> u;
    int n;
    int s, t;

    void add(int a, int b, int c) {
      edges.pb({a,b,0,c,head[a]});
      head[a] = edges.size() - 1;
      edges.pb({b,a, 0, 0, head[b]});
      head[b] = edges.size() -1;
    }

      /*
       * TODO: Почему-то не написал, возможно когда-нибудь.
       * TODO: Ясно, что проталкивать можно >1 величины потока.
       * TODO: Самое приятное -- проталкивать степени двойки на уменьшение
       */
      bool dfs(int v) {
      u[v] = 1;
      for (int i = head[v]; i != -1; i = edges[i].next) {
        auto &e = edges[i];
        if (e.f < e.c && !u[e.b]&& (e.b == t || dfs(e.b))) {
          e.f++, edges[i ^ 1].f--;
          return 1;
        }
      }
      return 0;
    }

      //TODO: Примерно так проталкивать
      val = 1 << 30;
      while (val != 0) {
          while (dfs(s,val)) {
              flow += val;
              fill(all(u), 0); //TODO: u -- used[\cdot]
          }
          fill(all(u), 0);
          val >>= 1;
      }

    void print() {
      int v = 0;
      while (v != t) {
        int j = head[v];
        while (j != -1 && edges[j].f <= 0) j = edges[j].next;
        if (j == -1) {
          cout << "Error " << v;
          return;
        }
        cout << edges[j].b << ' ';
        edges[j].f--;
        v = edges[j].b;
      }
    }
  }
}

namespace suff_array {
namespace simple {
     string s;
     cin >> s;
     s += '$';
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
 }

namespace normal {
    s += '\31';
    uint n = s.length();
    vt<uint> p(n), c(n); // TODO:  order, class of the equality
    //TODO: k == 0
    for (uint i = 0; i < n; ++i) p[i] = i; // TODO: Initial order
    sort(all(p), [&](uint i, uint j) {
        return s[i] < s[j];
    });  // TODO: Initial p sorting
    uint cc = 0; // TODO: Class counter
    for (uint i = 0; i < n ; ++i) cc += (i && s[p[i]] != s[p[i-1]]), c[p[i]] = cc; // TODO: Count classes and set class for every pos

    vt<uint> pos(n + 1);
    uint k = 0; // TODO: Действительно 0, т.к. по нему строится c2 для k == 1
    while (1u << k < n) {
        fill(all(pos), 0);
        vt<uint> p2(n), c2(n);
        for (uint i = 0; i < n; ++i) pos[c[i] + 1]++; // TODO: Для каждого c[i] < n насчитываем их кол-во
        for (uint i = 1; i < n; ++i) pos[i] += pos[i-1]; // TODO: Теперь, pos хранит для каждого класса позицию его страта.

        for (uint i = 0; i < n; ++i) {
            uint j = (n + p[i] - (1u << k)) % n; // TODO: Позиция начала первой половины текущего суффикса (т.е. всего суффикса s[p[i]]...$....s[j]...s[p[i]]...)
            //TODO: Но эти же первые половины уже имеют какие-то свои классы эквивалентности, т.к. их длина тоже 1 << k
            p2[pos[c[j]]++] = j; //TODO: Поставили строку s[j, j + 1 << k] на свою позицию
        }
        uint cc = 0;
        for (uint i = 0; i < n; ++i) cc += (i && pair{c[p2[i]], c[(p2[i] + (1u << k)) % n]} != pair{c[p2[i -1]], c[(p2[i - 1] + (1u << k)) % n]}), c2[p2[i]] = cc;
        c = move(c2);
        p = move(p2);
        k++;

        //TODO: LCP для sa (n -- длина s + '$')

        uint k = 0;
        vt<uint> lcp(n);
        for (uint i = 0; i < n - 1; ++i) {
            // TODO: Идем в порядке уменьшения длины суффиксов
            uint x = c[i]; // TODO: Позиция суффикса s[i...] в suff arr (акшуали просто класс эквивалентности, с последнего пробега построения)
            uint j = p[x - 1]; // TODO: предыдущий перед s[i...]
            while (s[i + k] == s[j + k]) k++;
            lcp[x] = k; // TODO: Позиция для сравнения x-1, x
            if (k) k--; // TODO: Переход к суффиксу меньшей длины срезает кол-во общих символов на 1
        }
        for (uint i = 0; i < n; ++i) cout << lcp[i] << '\n'; // TODO: lcp[0] не имеет смысла, т.к. там всегда '$', а предыдущего не существует
    }
    }

namespace karas {
    //TODO: Оказывается, Ахо-корасик не сильно страшный

    inline constexpr char BASE = ' ';
    inline constexpr uint ALPH = 96;

    struct node {
        array<node*, ALPH> next;
        node *parent = nullptr;
        node *suf;
        uint p_char = 0;
        bool terminal = false;

        void add(string_view s) {
            node *cur = this;
            uint n = s.length();
            for (uint i = 0; i < n; ++i) {
                uint j = s[i] - BASE;
                if (!cur->next[j]) cur->next[j] = new node();
                node *next = cur->next[j];
                next->parent = cur;
                next->p_char = j;
                cur = next;
            }
            cur->terminal = 1;
        }

        void init_suff() {
            queue<node*> q;
            q.emplace(this);
            while (!q.empty()) {
                node *v = q.front();
                q.pop();
                for (uint i = 0; i < ALPH; ++i) {
                    if (!v->next[i]) continue;
                    q.emplace(v->next[i]);
                }
                if (v == this) continue;
                uint x = v->p_char;
                node *p = v->parent->suf;
                while (!p->next[x]) p = p->suf;
                v->suf = p->next[x];
                v->terminal |= v->suf->terminal;
            }
        }

        void init_root() {
            node *f = new node();
            for (uint i = 0; i < ALPH; ++i) f->next[i] = this;
            this->parent = f;
            this->suf = f;
            f->suf = f;
        }

        bool find(string_view s) {
            node* cur = this;

            uint n = s.length();
            for (uint i = 0; i < n; ++i) {
                if (cur->terminal) return 1;
                uint j = s[i] - BASE;
                auto temp = cur;
                while (!temp->next[j]) temp = temp->suf;
                cur = temp->next[j];
            }
            return cur->terminal;
        }
    };
}
}

namespace dsu {
    // TODO : Idiomatic version with pathes evr
    vector<int> dsu;
    int find(int x){
        if(dsu[x] != x) {
            dsu[x] = find(dsu[x]);
        }
        return dsu[x];
    }
    void join(int x, int y){
        x = find(x);
        y = find(y);
        dsu[y] = x;
    }
}