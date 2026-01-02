template <typename T>
struct Arg {
  int Start;        
  bool Is_include; 

  explicit Arg(int q = 1, bool inc = true) : Start(q), Is_include(inc) {}

  static Point<T> Rotate(Point<T> v, int k) {
    k &= 3;
    if (k == 0) return v;                 
    if (k == 1) return {v.y, -v.x};    
    if (k == 2) return {-v.x, -v.y};    
    return {-v.y, v.x};               
  }

  static bool Upper(const Point<T>& v) {
    return (v.y > 0) || (v.y == 0 && v.x >= 0);
  }

  bool operator() (const Point<T>& pa, const Point<T>& pb) const {
    int k = (Start - 1) & 3;
    Point<T> a = pa, b = pb;
    Point<T> va = (a.x == 0 && a.y == 0) ? Point<T>{1, 0} : a;
    Point<T> vb = (b.x == 0 && b.y == 0) ? Point<T>{1, 0} : b;
    va = Rotate(va, k);
    vb = Rotate(vb, k);

    auto upper = [&] (const Point<T>& v) -> bool {
      if (!Is_include && v.y == 0 && v.x > 0) return false;
      return Upper(v);
    };

    bool ua = upper(va), ub = upper(vb);
    if (ua != ub) return ua > ub;
    T cr = Cross(va, vb);
    if (cr != 0) return cr > 0;
    return Dot(pa, pa) < Dot(pb, pb);
  }
};
