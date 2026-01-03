namespace Vector {
  template <typename T> 
  T Cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
  }

  template <typename T> 
  T Cross(Point<T> p1, Point<T> p2, Point<T> p0) {
    return Cross(p1 - p0, p2 - p0);
  }

  template <typename T> 
  T Dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
  }

  template <typename T> 
  T Dot(Point<T> p1, Point<T> p2, Point<T> p0) {
    return Dot(p1 - p0, p2 - p0);
  }

  template <typename T> 
  ld Distance(T x1, T y1, T x2, T y2) {
    return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  }

  template <typename T> 
  ld Distance(Point<T> a, Point<T> b) {
    return Distance(a.x, a.y, b.x, b.y);
  }

  template <typename T> 
  T Ex_Distance(T x1, T y1, T x2, T y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  }

  template <typename T> 
  T Ex_Distance(Point<T> a, Point<T> b) {
    return Ex_Distance(a.x, a.y, b.x, b.y);
  }

  template <typename T> 
  T Manhattan_Distance(Point<T> a, Point<T> b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
  }

  Point<ld> Standardize(Point<ld> vec) {
    return vec / sqrt(vec.x * vec.x + vec.y * vec.y);
  }

  ld Deg(ld x) {
    return x * 180 / pi;
  }

  ld Arc(ld x) {
    return pi / 180 * x;
  }

  ld Angle(ld a, ld b, ld c) {
    return acosl((a * a + b * b - c * c) / (2.0 * a * b));
  }

  ld Angle(Point<ld> a, Point<ld> b) {
    return fabsl(atan2l(Cross(a, b), a.x * b.x + a.y * b.y));
  }

  template <typename T> 
  Point<T> _Rotate(Point<T> p1, Point<T> p2) {
    Point<T> vec = p1 - p2; return {-vec.y, vec.x};
  }

  Point<ld> Rotate(Point<ld> a, Point<ld> b, ld rad, bool f = true) {
    ld dx = a.x - b.x, dy = a.y - b.y; 
    if (f) return {dx * cos(rad) - dy * sin(rad) + b.x, dx * sin(rad) + dy * cos(rad) + b.y}; 
    else return {dx * cos(rad) + dy * sin(rad) + b.x, -dx * sin(rad) + dy * cos(rad) + b.y};
  }

  template <typename T> 
  bool Online(Point<T> a, Point<T> b, Point<T> c) {
    return sign(Cross(b, a, c)) == 0;
  }

  template <typename T> 
  bool Online(Point<T> p, Line<T> l) {
    return Online(p, l.a, l.b);
  }

  template <typename T> 
  bool Left(Point<T> p, Line<T> l) {
    return Cross(l.b, p, l.a) > 0;
  }

  template <typename T> 
  bool Same_Side(Point<T> p1, Point<T> p2, Line<T> l) {
    T val = Cross(p1, l.a, l.b) * Cross(p2, l.a, l.b); return sign(val) == 1;
  }

  template <typename T> 
  bool Different_Side(Point<T> p1, Point<T> p2, Line<T> l) {
    T val = Cross(p1, l.a, l.b) * Cross(p2, l.a, l.b); return sign(val) == -1;
  }

  template <typename T> 
  bool Parallel(Line<T> l1, Line<T> l2) {
    return sign(Cross(l1.a - l1.b, l2.a - l2.b)) == 0;
  }

  template <typename T> 
  bool Vertical(Line<T> l1, Line<T> l2) {
    return sign(Dot(l1.a - l1.b, l2.a - l2.b)) == 0;
  }

  Point<ld> Line_Intersection(Line<ld> l1, Line<ld> l2) {
    assert(!Parallel(l1, l2)); 
    ld val = Cross(l2.b - l2.a, l1.a - l2.a) / Cross(l2.b - l2.a, l1.a - l1.b); 
    return l1.a + (l1.b - l1.a) * val;
  }

  Point<ld> Project(Point<ld> p, Line<ld> l) {
    return Line_Intersection({p, p + _Rotate(l.a, l.b)}, l);
  }

  ld Distance(Point<ld> p, Line<ld> l) {
    return Distance(p, Line_Intersection({p, p + _Rotate(l.a, l.b)}, l));
  }

  template<typename T> 
  bool OnSegment(Point<T> p, Line<T> l, bool f = true) {
    if (f) return sign(Cross(p, l.a, l.b)) == 0 && min(l.a.x, l.b.x) <= p.x && p.x <= max(l.a.x, l.b.x) && min(l.a.y, l.b.y) <= p.y && p.y <= max(l.a.y, l.b.y); 
    else return OnSegment(p, l) && min(l.a.x, l.b.x) < p.x && p.x < max(l.a.x, l.b.x) && min(l.a.y, l.b.y) < p.y && p.y < max(l.a.y, l.b.y);
  }

  pair<Point<ld>, ld> Point_to_Segment(Point<ld> p, Line<ld> l) {
    if (sign(Dot(p, l.b, l.a)) == -1) {return {l.a, Distance(p, l.a)};} 
    else if (sign(Dot(p, l.a, l.b)) == -1) {return {l.b, Distance(p, l.b)};} 
    return {Project(p, l), Distance(p, l)};
  }

  template <typename T> 
  Line<T> Median(Line<T> l) {
    Point<T> mid = (l.a + l.b) / 2; return {mid, mid + _Rotate(l.a, l.b)};
  }

  template<typename T> 
  tuple<int, Point<T>, Point<T>> Segment_Intersection(Line<T> l1, Line<T> l2) {
    auto [s1, e1] = l1; auto [s2, e2] = l2;
    auto A = max(s1.x, e1.x), AA = min(s1.x, e1.x); auto B = max(s1.y, e1.y), BB = min(s1.y, e1.y);
    auto C = max(s2.x, e2.x), CC = min(s2.x, e2.x); auto D = max(s2.y, e2.y), DD = min(s2.y, e2.y);
    if (A < CC || C < AA || B < DD || D < BB) {return {0, {}, {}};}
    if (sign(Cross(e1 - s1, e2 - s2)) == 0) {
      if (sign(Cross(s2, e1, s1)) != 0) {return {0, {}, {}};}
      Point<T> p1(max(AA, CC), max(BB, DD)), p2(min(A, C), min(B, D));
      if (!OnSegment(p1, l1)) {swap(p1.y, p2.y);}
      if (p1 == p2) {return {3, p1, p2};} else {return {2, p1, p2};}
    }
    auto cp1 = Cross(s2 - s1, e2 - s1); auto cp2 = Cross(s2 - e1, e2 - e1);
    auto cp3 = Cross(s1 - s2, e1 - s2); auto cp4 = Cross(s1 - e2, e1 - e2);
    if (sign(cp1 * cp2) == 1 || sign(cp3 * cp4) == 1) {return {0, {}, {}};}
    Pd p = Line_Intersection(l1, l2);
    if (sign(cp1) != 0 && sign(cp2) != 0 && sign(cp3) != 0 && sign(cp4) != 0) {return {1, p, p};} else {return {3, p, p};}
  }
 
  template <typename T>
  bool Segment_Intersect(Line<T> l1, Line<T> l2, bool f = true) {
    auto [s1, e1] = l1; auto [s2, e2] = l2;
    auto A  = max(s1.x, e1.x), AA = min(s1.x, e1.x); auto B  = max(s1.y, e1.y), BB = min(s1.y, e1.y);
    auto C  = max(s2.x, e2.x), CC = min(s2.x, e2.x); auto D  = max(s2.y, e2.y), DD = min(s2.y, e2.y);
    if (!(A >= CC && B >= DD && C >= AA && D >= BB)) return false;

    auto onBox = [&](Point<T> p, Point<T> a, Point<T> b) -> bool {
      return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
    };

    T c1 = Cross(s2, e1, s1), c2 = Cross(e2, e1, s1), c3 = Cross(s1, e2, s2), c4 = Cross(e1, e2, s2);
    int sgn1 = sign(c1), sgn2 = sign(c2), sgn3 = sign(c3), sgn4 = sign(c4);
    if (f) {
      if (sgn1 == 0 && onBox(s2, s1, e1)) return true; if (sgn2 == 0 && onBox(e2, s1, e1)) return true;
      if (sgn3 == 0 && onBox(s1, s2, e2)) return true; if (sgn4 == 0 && onBox(e1, s2, e2)) return true;
      return (sgn1 * sgn2 < 0 ) && (sgn3 * sgn4 < 0 );
    } 
    if (sgn1 == 0 || sgn2 == 0 || sgn3 == 0 || sgn4 == 0) return false;
    return (sgn1 * sgn2 < 0 ) && (sgn3 * sgn4 < 0 );
  }
};

using namespace Vector;
