//
// Created by kust on 05.10.2022.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

template<class T>
using Vec = std::vector<T>;

int main() {
//    auto &in = std::cin;
//    auto &out = std::cout;
    auto in = std::ifstream("in.txt");
    auto out = std::ofstream("out.txt");

    int n;
    in >> n;
    Vec<Vec<bool>> v(n, Vec<bool>(n, false));
    for (int i = 0; i < n; i++) {
        int x;
        while (true) {
            in >> x;
            if (x == 0) {
                break;
            }
            v[i][x - 1] = true;
        }
    }

    std::queue<int> q;
    Vec<int> from(n, -1);
    bool find = false;
    Vec<int> first_branch, second_branch;
    for (int i = 0; i < n && !find; ++i) {
        if (from[i] != -1) {
            continue;
        }
        q.push(i);
        while (!q.empty() && !find) {
            int cur = q.front();
            q.pop();
            for (int next = 0; next < n; ++next) {
                if (v[cur][next]) {
                    if (from[next] != -1) {
                        first_branch.push_back(next);
                        second_branch.push_back(cur);
                        find = true;
                        break;
                    }
                    q.push(next);
                    from[next] = cur;
                    v[next][cur] = false;
                }
            }
        }
    }

    if (find) {
        out << "N ";
        while (from[first_branch.back()] != -1) {
            first_branch.push_back(from[first_branch.back()]);
        }
        while (!second_branch.empty()) {
            second_branch.push_back(from[second_branch.back()]);
            for (int i = 0; i < first_branch.size(); ++i) {
                if (first_branch[i] == second_branch.back()) {
                    first_branch.resize(i + 1);
                    second_branch.pop_back();
                    while (!second_branch.empty()) {
                        first_branch.push_back(second_branch.back());
                        second_branch.pop_back();
                    }
                    break;
                }
            }
        }
        std::sort(first_branch.begin(), first_branch.end());
        for (int i: first_branch) {
            out << i + 1 << " ";
        }
    } else {
        out << "A";
    }
    int x;
    in >> x;
    return 0;
}
