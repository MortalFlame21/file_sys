#include <iostream>
#include <string>

#include "file_sys.h"

namespace bb {
void copy(fs::path src, fs::path dst, fs::copy_options o) {
    fs::copy(src, dst, o);
}

void move(fs::path src, fs::path dst) {
    fs::rename(src, dst);
}

void print(fs::path p) {
    std::cout << p << '\n';
    for (const auto& entry : fs::directory_iterator(p)) {
        std::cout << '\t'
            << ((entry.is_directory()) ? entry.path() : entry.path().filename()) << '\n';
    }
}

void print_subdir(fs::path p, int level) {
    std::string sp(level, '\t');
    std::cout << sp << ((level == 0) ? p : p.filename()) << '\n';
    for (const auto& entry : fs::directory_iterator(p)) {
        if (entry.is_directory())
            print_subdir(entry.path(), level + 1);
        else
            std::cout << sp << '\t' << entry.path().filename() << '\n';
    }
}
} // namespace bb