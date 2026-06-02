```cpp
template<class T>
constexpr T power(T base, i64 exp) {
    T res = 1;
    for (; exp > 0; exp >>= 1, base *= base) {
        if (exp & 1) res *= base;
    }
    return res;
}

struct Montgomery {
    u32 m;
    u64 ninv; 
    u32 r2;    

    constexpr Montgomery(u32 m_ = 1) : m(m_) {
        u64 inv = 1;
        for (int i = 0; i < 6; i++) {
            inv = inv * (2 - m_ * inv);
        }
        ninv = -inv;
        u64 r = u64((u128(1) << 64) % m_);
        r2 = u32(u128(r) * r % m_);
    }

    constexpr u32 reduce(u64 T) const {
        u64 m_val = T * ninv;               
        u128 t = u128(T) + u128(m_val) * m;  
        u64 t64 = u64(t >> 64);            
        return (t64 >= m) ? u32(t64 - m) : u32(t64);
    }

    constexpr u32 mul(u32 a, u32 b) const {
        return reduce(u64(a) * b);
    }

    constexpr u32 to_mont(u32 a) const {
        return reduce(u64(a) * r2);
    }

    constexpr u32 from_mont(u32 a) const {
        return reduce(a);
    }
};

template<u32 P> 
struct DynModInt {
private:
    u32 x; 
    static inline Montgomery mt{P > 0 ? P : 1};

public:
    static constexpr u32 default_mod = P; 

    constexpr DynModInt() : x(0) {}
    template<std::integral T> constexpr DynModInt(T x_) {
        i64 v = x_ % (i64)mod();
        if (v < 0) v += mod();
        x = mt.to_mont(u32(v));
    }

    static void setMod(u32 m) { mt = Montgomery(m); }
    static constexpr u32 mod() { return mt.m; }

    constexpr u32 val() const {
        return mt.from_mont(x);
    }

    constexpr DynModInt &operator += (const DynModInt &rhs) & {
        x += rhs.x;
        if (x >= mod()) x -= mod();
        return *this;
    }

    constexpr DynModInt &operator -= (const DynModInt &rhs) & {
        x = (x >= rhs.x) ? (x - rhs.x) : (x + mod() - rhs.x);
        return *this;
    }

    constexpr DynModInt &operator *= (const DynModInt &rhs) & {
        x = mt.mul(x, rhs.x); 
        return *this;
    }

    constexpr DynModInt &operator /= (const DynModInt &rhs) & {
        return *this *= rhs.inv();
    }

    constexpr DynModInt &operator ++ () & { return *this += 1; }
    constexpr DynModInt operator ++ (int) & { DynModInt tmp = *this; ++*this; return tmp; }
    constexpr DynModInt &operator -- () & { return *this -= 1; }
    constexpr DynModInt operator -- (int) & { DynModInt tmp = *this; --*this; return tmp; }

    constexpr DynModInt inv() const {
        u32 x_reg = mt.from_mont(x);
        i64 a = x_reg, b = mod(), u = 1, v = 0;
        while (b) {
            i64 t = a / b;
            a -= t * b;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        return DynModInt(u);
    }

    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    friend constexpr bool operator == (const DynModInt&, const DynModInt&) = default;
    friend constexpr auto operator <=> (const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() <=> rhs.val();
    }
    friend constexpr DynModInt operator + (DynModInt lhs, const DynModInt &rhs) { return lhs += rhs; }
    friend constexpr DynModInt operator - (DynModInt lhs, const DynModInt &rhs) { return lhs -= rhs; }
    friend constexpr DynModInt operator * (DynModInt lhs, const DynModInt &rhs) { return lhs *= rhs; }
    friend constexpr DynModInt operator / (DynModInt lhs, const DynModInt &rhs) { return lhs /= rhs; }
    
    friend std::istream &operator >> (std::istream &is, DynModInt &a) {
        i64 i; is >> i; a = i; return is;
    }
    friend std::ostream &operator << (std::ostream &os, const DynModInt &a) {
        return os << a.val();
    }
};

constexpr u32 P = 998'244'353;
using Z = DynModInt<P>;

struct Comb {
    int n;
    std::vector<Z> _fac, _invfac, _inv;
    
    Comb() : n{0}, _fac{Z(1)}, _invfac{Z(1)}, _inv{Z(0)} {}
    Comb(int n) : Comb() { init(n); }
    
    void reset() {
        n = 0;
        _fac = {Z(1)};
        _invfac = {Z(1)};
        _inv = {Z(0)};
    }
    
    void init(int m) {
        int current_mod = Z::mod();
        m = std::min(m, (int)current_mod - 1); 
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) { 
        if (m >= Z::mod()) return 0; 
        if (m > n) init(2 * m); 
        return _fac[m]; 
    }

    Z invfac(int m) { 
        if (m >= Z::mod()) return 0; 
        if (m > n) init(2 * m); 
        return _invfac[m]; 
    }

    Z inv(int m) { 
        if (m >= Z::mod()) return 0; 
        if (m > n) init(2 * m); 
        return _inv[m]; 
    }

    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        if (n >= Z::mod()) return 0; 
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;
```
