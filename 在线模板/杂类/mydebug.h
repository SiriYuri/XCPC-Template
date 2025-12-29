By GPT :(
#pragma once
#include <bits/stdc++.h>

namespace debug_internal {

template <typename T>
struct is_iterable {
private:
    template <typename U>
    static auto test(int) -> decltype(std::begin(std::declval<U&>()), std::end(std::declval<U&>()), std::true_type());
    template <typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
struct is_string : std::is_same<T, std::string> {};

template<typename T>
struct is_pair : std::false_type {};
template<typename A, typename B>
struct is_pair<std::pair<A,B>> : std::true_type {};

template<typename T>
struct is_tuple {
private:
    template<typename U>
    static auto check(int) -> decltype(std::tuple_size<U>::value, std::true_type());
    template<typename>
    static std::false_type check(...);
public:
    static constexpr bool value = decltype(check<T>(0))::value;
};

inline void print_space(std::ostream& os) {
    os << ' ';
}

template<typename T>
void print(std::ostream& os, const T& v);

template<typename A, typename B>
void print(std::ostream& os, const std::pair<A,B>& p) {
    os << '(';
    print(os, p.first);
    os << ", ";
    print(os, p.second);
    os << ')';
}

template<typename Tuple, size_t I>
struct TuplePrinter {
    static void print_tuple(std::ostream& os, const Tuple& t) {
        TuplePrinter<Tuple, I-1>::print_tuple(os, t);
        os << ", ";
        debug_internal::print(os, std::get<I-1>(t));
    }
};

template<typename Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print_tuple(std::ostream& os, const Tuple& t) {
        debug_internal::print(os, std::get<0>(t));
    }
};

template<typename... Args>
void print(std::ostream& os, const std::tuple<Args...>& t) {
    os << '(';
    TuplePrinter<decltype(t), sizeof...(Args)>::print_tuple(os, t);
    os << ')';
}

template<typename T>
void print_iterable(std::ostream& os, const T& v) {
    os << '{';
    bool first = true;
    for (const auto& x : v) {
        if (!first) os << ", ";
        first = false;
        print(os, x);
    }
    os << '}';
}

template<typename T>
void print(std::ostream& os, std::stack<T> s) {
    os << '[';
    bool first = true;
    while (!s.empty()) {
        if (!first) os << ", ";
        first = false;
        print(os, s.top());
        s.pop();
    }
    os << ']';
}

template<typename T>
void print(std::ostream& os, std::queue<T> q) {
    os << '[';
    bool first = true;
    while (!q.empty()) {
        if (!first) os << ", ";
        first = false;
        print(os, q.front());
        q.pop();
    }
    os << ']';
}

template<typename T>
void print(std::ostream& os, std::priority_queue<T> pq) {
    os << '[';
    bool first = true;
    while (!pq.empty()) {
        if (!first) os << ", ";
        first = false;
        print(os, pq.top());
        pq.pop();
    }
    os << ']';
}

template<typename T>
void print(std::ostream& os, const T& v) {
    if constexpr (is_string<T>::value) {
        os << '"' << v << '"';
    } 
    else if constexpr (is_pair<T>::value) {
        print(os, v);
    } 
    else if constexpr (is_tuple<T>::value) {
        print(os, v);
    } 
    else if constexpr (is_iterable<T>::value) {
        print_iterable(os, v);
    } 
    else {
        os << v;
    }
}

} 

inline void dbg_out() { std::cerr << '\n'; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    debug_internal::print(std::cerr, H);
    if (sizeof...(T)) std::cerr << ' ';
    dbg_out(T...);
}
