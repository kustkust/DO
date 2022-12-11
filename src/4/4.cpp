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
    for (bool &b: used) {
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

void Solve1(std::istream &in, std::ostream &out) {
    int count;
    in >> count;
    Matr<char> edge(count);
    for (int i = 0; i < count; ++i) {
        while (true) {
            char ch = static_cast<char>(in.get());
            if (ch == '0') {
                break;
            }
            if (ch >= 'a' && ch <= 'z') {
                edge[i].push_back(ch);
            }
        }
    }
    Vec<char> M(count, -1);
    Vec<int> rM(128, -1);
    Vec<bool> visit(128);
    Func<bool(int)> dfs = [&](int cur) {
        for (auto ch: edge[cur]) {
            if (ch != M[cur] && !visit[ch - 'a']) {
                visit[ch - 'a'] = true;
                if (rM[ch - 'a'] == -1 || dfs(rM[ch - 'a'])) {
                    M[cur] = ch;
                    rM[ch - 'a'] = cur;
                    return true;
                }
                visit[ch - 'a'] = false;
            }
        }
        return false;
    };
    for (int cur = 0; cur < count; ++cur) {
        visit.assign(128, false);
        if (!dfs(cur)) {
            out << "N\n";
            return;
        }
    }
    out << "Y\n";
    for (auto ch: M) {
        out << ch << " ";
    }
    out << "\n";
}


int main() {
    Str name;
    while (true) {
        std::cin >> name;
        if (name == "c0") {
            Solve(std::cin, std::cout);
        } else if (name == "c1") {
            Solve1(std::cin, std::cout);
        } else {
            std::ifstream fin(name);
            std::ofstream fout(name.erase(name.find_last_of('.'), Str::npos) + "_out.txt");
            Solve1(fin, fout);
        }
    }
}
