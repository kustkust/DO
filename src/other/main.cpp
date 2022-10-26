//
// Created by kust on 12.10.2022.
//
#include <string>
#include <iostream>

bool Inc(std::string &s) {
    int pos = 0;
    while (pos < s.size()) {
        if (s[pos] == 'A') {
            s[pos] = 'M';
            return true;
        }
        s[pos] = 'A';
        ++pos;
    }
    return false;
}

int Count(const std::string& s) {
    int count = 0;
    for (int i = 0; i < s.size() - 3; ++i) {
        if (s.substr(i, 4) == "MAMA") {
            ++count;
        }
    }
    return count;
}

int main() {
    std::string word(16, 'A');
    int64_t count = 0, total = 0;
    do {
        count += Count(word);
        ++total;
        if (total % 1000 == 0) {
            std::cout << total << std::endl;
        }
    } while (Inc(word));
    std::cout << static_cast<long double>(count) / total;
}