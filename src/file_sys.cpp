#include <iostream>
#include <string>

#include "file_sys.h"

namespace bb {
void copy(fs::path src, fs::path dst) {
    fs::copy(src, dst);
}

void move(fs::path src, fs::path dst) {
    fs::rename(src, dst);
}

fs::path rename_path(fs::path p) {
    return p;
}

void print(fs::path p, int level) {
    std::string tabs(level, '\t');
    std::cout << tabs << p.parent_path() << '\n';
    for (const auto& entry : fs::directory_iterator(p)) {
        std::string tabs(level + 1, '\t');
        std::cout << tabs << entry.path() << '\n';
    }
}

void print_subdir(fs::path p) {
    for (int i{}; const auto& entry : fs::directory_iterator(p)) {
        if (entry.is_directory()) {
            print(entry, i++);
        }
        else {
            std::string tabs(i + 1, '\t');
            std::cout << tabs << entry.path() << '\n';
        }
    }
}
} // namespace bb