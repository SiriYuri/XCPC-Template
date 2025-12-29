重载后的 cin 支持 5e7 / s 的 int 读入
#include <bits/stdc++.h>
using namespace std;

namespace IOS {
int FLOAT_PRECSION = 6; std::ios::fmtflags FLOAT_FIELD = std::ios::fmtflags(0);
static const int BUFSIZE = 1 << 20; static char buf[BUFSIZE]; static int bi = BUFSIZE, bn = BUFSIZE;
inline char gc() {if (bi >= bn) {bn = fread(buf, 1, BUFSIZE, stdin); bi=0; if(!bn) return EOF;} return buf[bi++];}
struct io {
  inline void read(char &c) const {while (isspace(c = gc())) {}}
  inline void read(string &s) const {char c; read(c); s.clear(); while (!isspace(c) && c != EOF) s += c, c = gc();}
  inline void read(char* a) const {char c; read(c); while (!isspace(c) && c != EOF) *a++ = c, c = gc(); *a = '\0';}
  template <typename T> inline void read(T& x) const {x = 0; bool neg = false; char ch = gc(); while (ch!='-' && (ch<'0' || ch>'9')) ch = gc(); if (ch=='-') neg = true, ch = gc(); while (ch>='0' && ch<='9') x = x * 10 + (ch ^ 48), ch = gc(); if constexpr (std::is_floating_point_v<T>) {if (ch == '.') {T p = 0.1; ch = gc(); while (ch>='0' && ch<='9') x += p * (ch ^ 48), ch = gc(), p *= 0.1;}} if (neg) x = -x;}
  template <typename T> const io& operator >> (T& x) const {read(x); return *this;}

  inline void print(char c) const {putchar(c);}
  inline void print(const string& s) const {for (char c : s) putchar(c);}
  inline void print(const char* s) const {while (*s) putchar(*s++);}
  template <typename T> inline void print_integer(T x) const {if (x == 0) { putchar('0'); return; } if (x < 0) putchar('-'), x = -x; char s[40]; int p = 0; while (x) s[p++] = char('0' + x % 10), x /= 10; while (p--) putchar(s[p]);}

  template <typename T> inline void print(T x) const {if constexpr (std::is_integral_v<T>) {print_integer(x);} else if constexpr (std::is_floating_point_v<T>) {std::ostringstream oss; oss.setf(FLOAT_FIELD, std::ios::floatfield); oss << std::setprecision(FLOAT_PRECSION) << x; print(oss.str());}}
  template <typename T> const io& operator << (const T& x) const {print(x); return *this;}
  const io& operator << (const io& (*manip)(const io&)) const {return manip(*this);}

  using StdManip = std::ostream& (*)(std::ostream&);
  const io& operator << (StdManip manip) const {if (manip == static_cast<StdManip>(std::endl<char, std::char_traits<char>>)) {putchar('\n');fflush(stdout);} else if (manip == static_cast<StdManip>(std::flush)) {fflush(stdout);}return *this;}
  template <typename T = int> inline T read() {T x; read(x); return x;}

  struct SetPrec {int p; SetPrec(int _p) : p(_p) {}};
  const io& operator << (const SetPrec& sp) const {FLOAT_PRECSION = sp.p; return *this;}
};

inline io::SetPrec Set(int p) {return io::SetPrec(p);}
inline const io& endl(const io& io) { putchar('\n'); return io;}

inline const io& fixed(const io& io) {FLOAT_FIELD = std::ios::fixed; return io;}
inline const io& scientific(const io& io) {FLOAT_FIELD = std::ios::scientific; return io;}
inline const io& defaultfloat(const io& io) {FLOAT_FIELD = std::ios::fmtflags(0); return io;}

const io IO;
#define cin IO
#define cout IO
#define fast_endl IOS::endl
#define sets IOS::Set
}

namespace DEFINES {
#ifndef ONLINE_JUDGE
#include "mydebug.h"
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#define FILE freopen("ciallo.in", "r", stdin); freopen("ciallo.out", "w", stdout);
#else
#define dbg(...)
#define FILE
#endif

#define _count(x) (__builtin_popcountll(x))
#define log(x) (63 - __builtin_clzll(x))

constexpr int N = 1 << 20;
constexpr int M = 1 << 18;

using ll = long long;
using ull = unsigned long long;
using i128 = __int128;
using u128 = __uint128_t;
using ld = long double;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {return uniform_int_distribution<int>(l, r)(rng);}

template <typename T> int _size(const T& c) {return (int)c.size();}
template <typename T> T inf = numeric_limits<T>::max() / 2;
template <typename T> inline bool ckmax(T& a, const auto& b) {return a < b ? (a = b, true) : false;}
template <typename T> inline bool ckmin(T& a, const auto& b) {return b < a ? (a = b, true) : false;}
}

using namespace IOS;
using namespace DEFINES;

void solve() {
  
  return;
}

int main() {
  // int ___; cin >> ___ ; while (___--)
  solve();
  return 0;
}
