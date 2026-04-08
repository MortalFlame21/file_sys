#include <filesystem>

namespace fs = std::filesystem;

namespace bb {
    void copy(fs::path src, fs::path dst, fs::copy_options o);
    void move(fs::path src, fs::path dst);
    void print(fs::path p);
    void print_subdir(fs::path p, int level = 0);
};