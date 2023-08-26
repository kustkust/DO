//
// Created by kust on 26.10.2022.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

template<class T>
using Vec = std::vector<T>;
template<class T>
using Que = std::queue<T>;
template<class T, class V>
using Pair = std::pair<T, V>;

int main() {
//    auto &in = std::cin;
//    auto &out = std::cout;
    auto in = std::ifstream("in.txt");
    auto out = std::ofstream("out.txt");
    int v_count;
    int tmp_v;
    in >> v_count;
    Vec<Vec<Pair<int, int>>> v_list(v_count, Vec<Pair<int, int>>{});
    Vec<int> deg_out(v_count, 0);
    for (int i = 0; i < v_count; ++i) {
        for (int j = 0; j < v_count; ++j) {
            in >> tmp_v;
            if (tmp_v > 0) {
                v_list[j].emplace_back(i, tmp_v);
                ++deg_out[i];
            }
        }
    }
    int start, finish;
    in >> start >> finish;
    --start;
    --finish;
    int max_ind = v_count;
    Vec<int> indexes(v_count, -1), names(v_count);
    Vec<Vec<Pair<int, int>>> sorted_list(v_count);
    Que<int> que;
    for (int i = 0; i < v_count; ++i) {
        if (deg_out[i] > 0 || indexes[i] != -1) {
            continue;
        }
        que.push(i);
        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            for (auto [prev, _]: v_list[cur]) {
                --deg_out[prev];
                if (deg_out[prev] == 0) {
                    que.push(prev);
                }
            }
            max_ind--;
            indexes[cur] = max_ind;
            names[max_ind] = cur;
            std::swap(sorted_list[max_ind], v_list[cur]);
            //sorted_list[max_ind] = std::move(v_list[cur]);
        }
    }

    if (indexes[start] > indexes[finish]) {
        out << "N";
    } else {
        Vec<int> weights(v_count, -1);
        Vec<int> from(v_count, -1);
        weights[start] = 0;
        for (int i = indexes[start] + 1; i < v_count; ++i) {
            for (auto [prev, weight]: sorted_list[i]) {
                if (weights[prev] != -1 && weights[prev] + weight > weights[names[i]]) {
                    weights[names[i]] = weights[prev] + weight;
                    from[names[i]] = prev;
                }
            }
        }

        if (from[finish] == -1) {
            out << "N";
            return 0;
        }
        Vec<int> ans;
        int cur = finish;
        while (cur != -1) {
            ans.push_back(cur);
            cur = from[cur];
        }
        out << "Y\n";
        for (int i = static_cast<int>(ans.size()) - 1; i >= 0; --i) {
            out << ans[i] + 1 << " ";
        }
        out << '\n' << weights[finish];
    }
}