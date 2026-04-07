#ifndef SRC_HPP
#define SRC_HPP

#include <cstddef>
#include <iostream>

struct Permutation { // 置换
    int* mapping;     // 长度为 size 的数组，表示 a(i)
    size_t size;      // 元素个数

    // 初始化为恒等置换
    explicit Permutation(size_t n) : mapping(nullptr), size(n) {
        if (size > 0) {
            mapping = new int[size];
            for (size_t i = 0; i < size; ++i) mapping[i] = static_cast<int>(i);
        }
    }

    // 用给定映射初始化（拷贝）
    Permutation(const int* m, size_t n) : mapping(nullptr), size(n) {
        if (size > 0) {
            mapping = new int[size];
            for (size_t i = 0; i < size; ++i) mapping[i] = m[i];
        }
    }

    // 拷贝构造（深拷贝）
    Permutation(const Permutation& other) : mapping(nullptr), size(other.size) {
        if (size > 0) {
            mapping = new int[size];
            for (size_t i = 0; i < size; ++i) mapping[i] = other.mapping[i];
        }
    }

    // 拷贝赋值（深拷贝）
    Permutation& operator=(const Permutation& other) {
        if (this == &other) return *this;
        int* new_map = nullptr;
        if (other.size > 0) {
            new_map = new int[other.size];
            for (size_t i = 0; i < other.size; ++i) new_map[i] = other.mapping[i];
        }
        delete[] mapping;
        mapping = new_map;
        size = other.size;
        return *this;
    }

    // 移动构造
    Permutation(Permutation&& other) noexcept : mapping(other.mapping), size(other.size) {
        other.mapping = nullptr;
        other.size = 0;
    }

    // 移动赋值
    Permutation& operator=(Permutation&& other) noexcept {
        if (this == &other) return *this;
        delete[] mapping;
        mapping = other.mapping;
        size = other.size;
        other.mapping = nullptr;
        other.size = 0;
        return *this;
    }

    ~Permutation() {
        delete[] mapping;
        mapping = nullptr;
        size = 0;
    }

    // 将置换作用于数组：permutation[i] <- old[mapping[i]]
    void apply(int* permutation) const {
        if (size == 0) return;
        int* tmp = new int[size];
        for (size_t i = 0; i < size; ++i) tmp[i] = permutation[i];
        for (size_t i = 0; i < size; ++i) permutation[i] = tmp[mapping[i]];
        delete[] tmp;
    }

    // 置换乘法：this * other，先 other 后 this，与 apply 一致
    Permutation operator*(const Permutation& other) const {
        // 假设大小相同
        Permutation res(size);
        for (size_t i = 0; i < size; ++i) {
            res.mapping[i] = other.mapping[mapping[i]];
        }
        return res;
    }

    // 逆置换：inv[a(i)] = i
    Permutation inverse() const {
        Permutation inv(size);
        for (size_t i = 0; i < size; ++i) {
            inv.mapping[mapping[i]] = static_cast<int>(i);
        }
        return inv;
    }

    friend std::ostream& operator<<(std::ostream& os, const Permutation& p) {
        os << "[";
        for (size_t i = 0; i < p.size; ++i) {
            os << p.mapping[i];
            if (i + 1 < p.size) os << " ";
        }
        os << "]";
        return os;
    }
};

struct Transposition { // 对换
    int a, b;

    // 恒等对换
    Transposition() : a(0), b(0) {}

    Transposition(int x, int y) : a(x), b(y) {}

    // 在数组上交换 a 与 b 位置
    void apply(int* permutation, size_t size) const {
        if (static_cast<size_t>(a) < size && static_cast<size_t>(b) < size) {
            int t = permutation[a];
            permutation[a] = permutation[b];
            permutation[b] = t;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Transposition& t) {
        os << "{" << t.a << " " << t.b << "}";
        return os;
    }

    // 转换为置换
    Permutation toPermutation(size_t size) const {
        Permutation p(size);
        if (static_cast<size_t>(a) < size && static_cast<size_t>(b) < size) {
            p.mapping[a] = b;
            p.mapping[b] = a;
        }
        return p;
    }
};

struct Cycle { // 轮换
    int* elements;
    size_t size;

    Cycle(const int* elems, size_t k) : elements(nullptr), size(k) {
        if (size > 0) {
            elements = new int[size];
            for (size_t i = 0; i < size; ++i) elements[i] = elems[i];
        }
    }

    ~Cycle() {
        delete[] elements;
        elements = nullptr;
        size = 0;
    }

    // 将轮换作用在数组上：把 elements[i] 的值挪到 elements[(i+1)%k]
    void apply(int* permutation, size_t n) const {
        if (size == 0) return;
        // 复制涉及的值，避免覆盖
        for (size_t i = 0; i < size; ++i) {
            if (static_cast<size_t>(elements[i]) >= n) return;
        }
        int* buf = new int[size];
        for (size_t i = 0; i < size; ++i) buf[i] = permutation[elements[i]];
        for (size_t i = 0; i < size; ++i) {
            size_t ni = (i + 1) % size;
            permutation[elements[ni]] = buf[i];
        }
        delete[] buf;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cycle& c) {
        os << "{";
        for (size_t i = 0; i < c.size; ++i) {
            os << c.elements[i];
            if (i + 1 < c.size) os << " ";
        }
        os << "}";
        return os;
    }

    // 将轮换转换为同规模置换
    Permutation toPermutation(size_t n) const {
        Permutation p(n);
        if (size == 0) return p;
        for (size_t i = 0; i < size; ++i) {
            int from = elements[i];
            int to = elements[(i + 1) % size];
            if (static_cast<size_t>(from) < n && static_cast<size_t>(to) < n) {
                p.mapping[from] = to;
            }
        }
        return p;
    }
};

#endif // SRC_HPP
