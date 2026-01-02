namespace Geometry_Base {
static constexpr ld pi = std::numbers::pi_v<ld>;
static constexpr ld eps = 1e-8;

template <typename U, typename V> bool equal(U x, V y) {
  return -eps < x - y && x - y < eps;
}

template <typename T> int sign(T x) {
  if (-eps < x && x < eps) return 0; 
  return x < 0 ? -1 : 1;
}
  
template <typename T> 
struct Point {
  T x, y;

  Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}

  template <typename U> 
  operator Point<U>() { 
    return Point<U>(U(x), U(y));
  }

  Point &operator += (Point p) & {
    x += p.x; y += p.y; return *this;
  }

  Point &operator -= (Point p) & {
    x -= p.x; y -= p.y; return *this;
  }

  Point &operator += (T t) & {
    x += t; y += t; return *this;
  }

  Point &operator -= (T t) & {
    x -= t; y -= t; return *this;
  }

  Point &operator *= (T t) & {
    x *= t; y *= t; return *this;
  }

  Point &operator /= (T t) & {
    x /= t; y /= t; return *this;
  }

  Point operator - () const {
    return Point(-x, -y);
  }

  friend Point operator + (Point a, Point b) {
    return a += b;
  }
  
  friend Point operator - (Point a, Point b) {
    return a -= b;
  }

  friend Point operator + (Point a, T b) {
    return a += b;
  }

  friend Point operator - (Point a, T b) {
    return a -= b;
  }

  friend Point operator * (Point a, T b) {
    return a *= b;
  }

  friend Point operator * (T a, Point b) {
    return b *= a;
  }

  friend Point operator / (Point a, T b) {
    return a /= b;
  }

  friend bool operator < (Point a, Point b) {
    return equal(a.x, b.x) ? a.y < b.y - eps : a.x < b.x - eps;
  }

  friend bool operator > (Point a, Point b) {
    return b < a; 
  }

  friend bool operator == (Point a, Point b) {
    return !(a < b) && !(b < a); 
  }

  friend bool operator != (Point a, Point b) {
    return a < b || b < a; 
  }

  friend auto &operator >> (istream &is, Point &p) {
    return is >> p.x >> p.y; 
  }

  friend auto &operator << (ostream &os, Point p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

template <typename T> 
struct Line {
  Point<T> a, b;

  Line(Point<T> a_ = Point<T> (), Point<T> b_ = Point<T> ()) : a(a_), b(b_) {}

  template <typename U> 
  operator Line<U>() {
    return Line<U>(Point<U>(a), Point<U>(b));
  }

  friend auto &operator >> (istream &is, Line &l) {
    return is >> l.a.x >> l.a.y >> l.b.x >> l.b.y;
  }

  friend auto &operator << (ostream &os, Line l) {
    return os << "<" << l.a << ", " << l.b << ">";
  }
};

using Pi = Point<int>;
using Pl = Point<ll>;
using Pd = Point<ld>;

using Li = Line<int>;
using Ll = Line<ll>;
using Ld = Line<ld>;
}

using namespace Geometry_Base;
