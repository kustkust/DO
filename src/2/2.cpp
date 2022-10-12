//
// Created by kust on 05.10.2022.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

template<class T>
using Vec = std::vector<T>;

int main() {
//    auto &in = std::cin;
//    auto &out = std::cout;
    auto in = std::ifstream("in.txt");
    auto out = std::ofstream("out.txt");

    int n;
    in >> n;
    Vec<int> input_data(n);
    int v_count = -1;
    for (int i = 0; i < n; ++i) {
        in >> input_data[i];
        if (input_data[i] == n && v_count == -1) {
            v_count = i;
        }
    }
    Vec<Vec<int>> v(v_count, Vec<int>(v_count, INT_MAX));
    for(int cur_v = 0; cur_v < v_count; ++cur_v) {
        if (input_data[cur_v] == input_data.size()) {
            break;
        }
        int cur = input_data[cur_v] - 1, next = input_data[cur_v + 1] - 1;
        while (cur < next) {
            v[cur_v][input_data[cur] - 1] = input_data[cur + 1];
            v[input_data[cur] - 1][cur_v] = input_data[cur + 1];
            cur += 2;
        }
    }

    Vec<Vec<int>> res(v_count);
    Vec<int> unused(v_count - 1);
    for (int i = 1; i < v_count; ++i) {
        unused[i - 1] = i;
    }
    Vec<int> dist(v_count), near(v_count, 0);
    dist.assign(v[0].begin(), v[0].end());
    for (int i = 0; i < v_count; ++i) {
        dist[i] = v[0][i];
    }
    int ostov_weight = 0;
    while (!unused.empty()) {
        int next_dist = INT_MAX, next_ind = 0;
        for (int i = 0; i < unused.size(); ++i) {
            if (dist[unused[i]] < next_dist) {
                next_dist = dist[unused[i]];
                next_ind = i;
            }
        }
        ostov_weight += next_dist;
        int next = unused[next_ind];
        res[next].push_back(near[next]);
        res[near[next]].push_back(next);
        unused[next_ind] = unused.back();
        unused.resize(unused.size() - 1);
        for (int i: unused) {
            if (dist[i] > v[next][i]) {
                dist[i] = v[next][i];
                near[i] = next;
            }
        }
    }

    for (auto &row: res) {
        std::sort(row.begin(), row.end());
        for (int i: row) {
            out << i + 1 << " ";
        }
        out << "0\n";
    }
    out << ostov_weight;
    return 0;
}
