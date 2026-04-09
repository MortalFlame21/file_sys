#include <filesystem>
#include <ostream>
#include <string>
#include <string_view>
#include <iostream>

#include <cxxopts.hpp>

#include "file_sys.h"

namespace fs = std::filesystem;

struct opts_t {
    bool copy{};
    bool move{};
    bool print{};
    bool subdir{};
    fs::path path{};
    fs::path dest{};
};

void validate_opt(std::ostream& o, bool b, std::string_view msg, int code) {
    if (b) {
        o << msg << '\n';
        std::exit(code);
    }
}

opts_t sanitise_parse(cxxopts::Options& opts, int argc, char* argv[]) {
    opts.add_options()
        ("c,cp,copy", "copy path to dest")
        ("m,mv,move", "move path to dest")
        ("p,print", "print path (one level)")
        ("s,subdir", "print path and its subdirectories."
            "with copy it performs recursive copy.")
        ("path", "", cxxopts::value<fs::path>())
        ("dest", "", cxxopts::value<fs::path>())
        ("h,help", "Print usage")
    ;

    opts.parse_positional({"path", "dest"});
    opts.positional_help("[path] [dest]");

    auto res{opts.parse(argc, argv)};

    validate_opt(std::cout, res.contains("help"), opts.help(), EXIT_SUCCESS);
    validate_opt(std::cerr, !res.contains("path"),
        "Error: path: PATH is required.", EXIT_FAILURE);
    validate_opt(std::cerr, res.contains("move") && !res.contains("dest"),
        "Error: dest: DEST is required to move PATH", EXIT_FAILURE);

    auto copy{res["copy"].as<bool>()};
    auto move{res["move"].as<bool>()};
    auto print{res["print"].as<bool>()};
    auto subdir{res["subdir"].as<bool>()};
    auto path{res["path"].as<fs::path>()};
    auto dest{res["dest"].as<fs::path>()};

    // copy invariants:
    //      path != dest
    // move invariants:
    //      path != dest
    // print invariants:
    //      path is a directory
    const auto cm{copy || move};
    validate_opt(std::cerr, !cm && !fs::is_directory(path),
        "Error: path: PATH needs to be a directory to be printed.", EXIT_FAILURE);
    validate_opt(std::cerr, cm && !fs::exists(path),
        "Error: path: PATH needs to exist.", EXIT_FAILURE);
    validate_opt(std::cerr, cm && fs::exists(dest) && fs::equivalent(path, dest),
        "Error: path: PATH and DEST are the same.", EXIT_FAILURE);

    return {copy, move, print, subdir, path, dest};
}

int main(int argc, char* argv[]) {
    cxxopts::Options opts("file_sys", "Copy, move, print out directories and files");
    auto o{sanitise_parse(opts, argc, argv)};

    if (o.copy && o.subdir) {
        bb::copy(o.path, o.dest, fs::copy_options::recursive);
    }
    else if (o.copy) {
        bb::copy(o.path, o.dest, fs::copy_options::none);
    }
    else if (o.move) {
        bb::move(o.path, o.dest);
    }
    else if (o.subdir) {
        bb::print_subdir(o.path);
    }
    else {
        bb::print(o.path);
    }
}