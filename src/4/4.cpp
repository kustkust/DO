//
// Created by kust on 07.12.2022.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <stack>
#include <filesystem>

template<class T>
using Vec = std::vector<T>;
template<class T>
using Matr = Vec<Vec<T>>;
template<class T>
using Set = std::unordered_set<T>;
template<class T>
using Stack = std::stack<T>;
template<class T>
using Que = std::queue<T>;
template<class T, class V>
using Pair = std::pair<T, V>;
using Str = std::string;
template<class T, size_t count>
using Arr = std::array<T, count>;
template<class F>
using Func = std::function<F>;

void Solve(std::istream &in, std::ostream &out) {
    int count;
    in >> count;
    Matr<char> sets(count);
    for (int i = 0; i < count; ++i) {
        while (true) {
            char ch = static_cast<char>(in.get());
            if (ch == '0') {
                break;
            }
            if (ch >= 'a' && ch <= 'z') {
                sets[i].push_back(ch);
            }
        }
    }
    bool used[128]{};
    for (bool& b : used) {
        b = false;
    }
    Vec<char> res(count);
    Func<bool(int)> rec = [&](int cur_set) {
        if (cur_set == count) {
            return true;
        }
        for (auto nxt: sets[cur_set]) {
            if (!used[nxt]) {
                used[nxt] = true;
                res[cur_set] = nxt;
                if (rec(cur_set + 1)) {
                    return true;
                }
                used[nxt] = false;
            }
        }
        return false;
    };
    if (rec(0)) {
        out << "Y\n";
        for (int i = 0; i < count; ++i) {
            out << res[i];
        }
    } else {
        out << "N\n";
    }
}


int main() {
    Str name;
    std::cin>> name;
    if(name=="c") {
        Solve(std::cin, std::cout);
    } else {
        std::ifstream fin(name);
        std::ofstream fout(name.erase(name.find_last_of('.'), Str::npos) + "_out.txt");
        Solve(fin, fout);
    }
}
