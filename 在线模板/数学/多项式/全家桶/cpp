搬运 / 截取自 https://yhx-12243.github.io/OI-transit/memos/12.html#poly-base
实在是, 太快了 !
目前只有基础运算类
constexpr int mod = 998'244'353;
constexpr int iv2 = (mod + 1) >> 1;
constexpr int unity = 31;

using u64 = unsigned long long;
using vec = int[N];
using pvec = int*;
using pii = pair<int, int>;
using Poly = vector<int>;

vec inv, fact, ifac;

inline int min(const int x, const int y) {return x < y ? x : y;}
inline int max(const int x, const int y) {return x < y ? y : x;}
inline int & reduce(int &x) {return x += x >> 31 & mod;}
inline int & neg(int &x) {return x = (!x - 1) & (mod - x);}
u64 ModPow(u64 a, int n, u64 c = 1) {for (n; n; n >>= 1, a = a * a % mod) if (n & 1) c = c * a % mod; return c;}

namespace Poly_Base {
  int l, n; 
  u64 iv; 
  vec w2; 

  void init(int n = N, bool dont_calc_factorials = true) {
    int i, t;
    for (inv[1] = 1, i = 2; i < n; ++i) inv[i] = u64(mod - mod / i) * inv[mod % i] % mod;
    if (!dont_calc_factorials) { 
      for (*ifac = *fact = i = 1; i < n; ++i) {
        fact[i] = (u64)fact[i - 1] * i % mod; ifac[i] = (u64)ifac[i - 1] * inv[i] % mod;
      }
    }
    t = min(n > 1 ? __lg(n - 1) : 0, 21);
    *w2 = 1;
    w2[1 << t] = ModPow(unity, 1 << (21 - t));
    for (i = t; i; --i) w2[1 << (i - 1)] = (u64)w2[1 << i] * w2[1 << i] % mod;
    for (i = 1; i < n; ++i) w2[i] = (u64)w2[i & (i - 1)] * w2[i & -i] % mod;
  }

  inline void NTT_init(int len) {
    n = 1 << (l = len);
    iv = mod - (mod - 1) / n;
  }

  void DIF(int *a) { // NTT正变换
    int i, *j, *k, len = n >> 1, R, *o;
    for (i = 0; i < l; ++i, len >>= 1) for (j = a, o = w2; j != a + n; j += len << 1, ++o) for (k = j; k != j + len; ++k) 
      R = (u64)*o * k[len] % mod, reduce(k[len] = *k - R), reduce(*k += R - mod);
  }

  void DIT(int *a) { // NT逆变换
    int i, *j, *k, len = 1, R, *o;
    for (i = 0; i < l; ++i, len <<= 1) for (j = a, o = w2; j != a + n; j += len << 1, ++o) for (k = j; k != j + len; ++k) 
      reduce(R = *k + k[len] - mod), k[len] = u64(*k - k[len] + mod) * *o % mod, *k = R;
  }

  inline void DNTT(int *a) {DIF(a);}
  inline void IDNTT(int *a) { DIT(a); reverse(a + 1, a + n); for (int i = 0; i < n; ++i) a[i] = a[i] * iv % mod;}

  inline void DIF(int *a, int *b) {memcpy(b, a, n << 2), DIF(b);}
  inline void DIT(int *a, int *b) {memcpy(b, a, n << 2), DIT(b);}
  inline void DNTT(int *a, int *b) {memcpy(b, a, n << 2), DNTT(b);}
  inline void IDNTT(int *a, int *b) {memcpy(b, a, n << 2), IDNTT(b);}
};

namespace Polynomial {
  using namespace Poly_Base;

  vec B1, B2, B3, B4, B5, B6, B7, B8, B9;

  void Mul(int deg, pvec a, pvec b, pvec c) { // 多项式乘, 多次调用注意初始化带来的复杂度
    if (!deg) {
      *c = (u64)*a * *b % mod;
      return ;
    }
    NTT_init(__lg(deg) + 2), DNTT(a, c), DNTT(b, B1);
    for (int i = 0; i < n; ++i) c[i] = (u64)c[i] * B1[i] % mod;
    IDNTT(c);
  }

  void Inv(int deg, pvec a, pvec b) { // 多项式求逆, a[0] 必须非零
    int i, len; assert(*a);
    if (*b = ModPow(*a, mod - 2), deg <= 1) return ;
    memset(b + 1, 0, i = 8 << __lg(deg - 1)); memset(B1, 0, i), *B1 = *a;
    for (len = 0; 1 << len < deg; ++len) {
      NTT_init(len + 1);
      memcpy(B1 + (n >> 1), a + (n >> 1), n << 1), DIF(b, B2), DIF(B1, B3);
      for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B2[i] % mod; DIT(B3);
			for (i = n >> 1; i < n; ++i) B3[i] = B3[n - i] * iv % mod;
			memset(B3, 0, n << 1), DIF(B3);
			for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B2[i] % mod; DIT(B3);
			for (i = n >> 1; i < n; ++i) b[i] = B3[n - i] * (mod - iv) % mod;
    }
  }

  void Div_Mod(int A, int B, pvec a, pvec b, pvec q, pvec r) { // 多项式除法与取模, 计算 q = a / b, r = a % b, deg(a) = A, deg(b) = B
    if (A < B) {
      memcpy(r, a, (A + 1) << 2);
      memset(r + (A + 1), 0, (B- A) << 2);
      return ;
    }
    int Q = A - B, i, l_ = Q ? __lg(Q) + 1 : 0;
    NTT_init(l_);
    for (i = 0; i <= Q && i <= B; ++i) B4[i] = b[B - i];
		memset(B4 + i, 0, (n - i) << 2);
    Inv(i = Q + 1, B4, B5);
    reverse_copy(a + B, a + (A + 1), B4), NTT_init(++l_),
		memset(B4 + i, 0, (n - i) << 2), memset(B5 + i, 0, (n - i) << 2);
    Mul(2 * Q, B4, B5, q), reverse(q, q + (Q + 1)),
		memset(q + i, 0, (n - i) << 2);
    if (!B) return;
    NTT_init(__lg(2 * B - 1) + 1);
		for (i = 0; i <= Q && i < B; ++i) B2[i] = b[i], B3[i] = q[i];
		memset(B2 + i, 0, (n - i) << 2), memset(B3 + i, 0, (n - i) << 2),
		Mul(2 * (B - 1), B2, B3, r), memset(r + i, 0, (n - i) << 2);
    for (i = 0; i < B; ++i) reduce(r[i] = a[i] - r[i]);
  }

  void Dif(int deg, pvec a, pvec b) { // 多项式求导
    for (int i = 1; i <= deg; ++i) b[i - 1] = (u64)a[i] * i % mod;
  }

  void Int(int deg, pvec a, pvec b, int constant = 0) { // 多项式积分, 默认积分常数为0
    for (int i = deg; i; --i) b[i] = (u64)a[i - 1] * ::inv[i] % mod;
    *b = constant;
  }

  void Dif_Qua(int deg, pvec a, pvec b) { // 商导
    assert(*a);
    if (deg <= 1) {*b = ModPow(*a, mod - 2, a[1]); return ;}
    int i, len = __lg(deg - 1);
    Inv((deg + 1) / 2, a, B4), NTT_init(len + 1),
		memset(B4 + (n >> 1), 0, n << 1), DIF(B4, B2),
    Dif(deg, a, B1), memcpy(B3, B1, n << 1),
		memset(B3 + (n >> 1), 0, n << 1), DIF(B3);
    for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B2[i] % mod;
		DIT(B3, b), *b = *b * iv % mod;
		for (i = 1; i < n >> 1; ++i) b[i] = b[n - i] * iv % mod;
		memset(b + (n >> 1), 0, n << 1);
    DIF(b, B4), DIF(a, B3);
		for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B4[i] % mod; DIT(B3);
		for (i = n >> 1; i < n; ++i) B3[i] = (B3[n - i] * iv + mod - B1[i]) % mod;
		memset(B3, 0, n << 1), DIF(B3);
		for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B2[i] % mod; DIT(B3);
		for (i = n >> 1; i < n; ++i) b[i] = B3[n - i] * (mod - iv) % mod;
  }

  void Ln(int deg, pvec a, pvec b) { // 多项式求对数
    assert(*a == 1);
    --deg ? (Dif_Qua(deg, a, b), Int(deg, b, b)) : void (*b = 0);
  }

  void Exp(int deg, pvec a, pvec b) { // 多项式指数
    int i, len; pvec c = B6; assert(!*a);
    if (*b = 1, deg <= 1) return;
		if (b[1] = a[1], deg == 2) return;
    memset(b + 2, 0, i = 8 << __lg(deg - 1)), memset(c, 0, i), memset(B1, 0, i),
		*c = 1, neg(c[1] = b[1]);
    for (len = 1; 1 << len < deg; ++len) {
			NTT_init(len + 1);
			DIF(c, B2), DIF(b, B3);
			for (i = 0; i < n; ++i) B4[i] = (u64)B3[i] * B2[i] % mod; DIT(B4);
			for (i = n >> 1; i < n; ++i) B4[i] = B4[n - i] * iv % mod;
			memset(B4, 0, n << 1), DIF(B4);
			for (i = 0; i < n; ++i) B4[i] = (u64)B4[i] * B2[i] % mod; DIT(B4);
			for (i = n >> 1; i < n; ++i) B4[i] = B4[n - i] * (mod - iv) % mod;
			memcpy(B4, c, n << 1), DIF(B4);
			Dif(n >> 1, b, B1), DIF(B1, B5);
			for (i = 0; i < n; ++i) B4[i] = (u64)B4[i] * B5[i] % mod; DIT(B4);
			for (i = n >> 1; i < n; ++i) reduce(B5[i] = (a[i] + B4[n - i + 1] * (mod - iv) % mod * ::inv[i]) % mod);
			memset(B5, 0, n << 1), DIF(B5);
			for (i = 0; i < n; ++i) B5[i] = (u64)B5[i] * B3[i] % mod; DIT(B5);
			for (i = n >> 1; i < n; ++i) b[i] = B5[n - i] * iv % mod;
			if (2 << len >= deg) return;
			DIF(b, B3);
			for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B2[i] % mod; DIT(B3);
			for (i = n >> 1; i < n; ++i) B3[i] = B3[n - i] * iv % mod;
			memset(B3, 0, n << 1), DIF(B3);
			for (i = 0; i < n; ++i) B3[i] = (u64)B3[i] * B2[i] % mod; DIT(B3);
			for (i = n >> 1; i < n; ++i) c[i] = B3[n - i] * (mod - iv) % mod;
		}
  }

  void Sqrt(int deg, pvec a, pvec b) {
    Ln(deg, a, B7);
    for (int i = 0; i < deg; i++) B7[i] = (u64)B7[i] * iv2 % mod;
    Exp(deg, B7, b);
  }

  void Pow(int deg, int power, pvec a, pvec b) {
    Ln(deg, a, B8);
    for (int i = 0; i < deg; i++) B8[i] = (u64)B8[i] * power % mod;
    Exp(deg, B8, b);
  }
};
