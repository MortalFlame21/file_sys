# File System

A repository that messes around with `std::filesystem`. The program can copy, move and print out directories and files.

## Usage

```shell
cmake -S . -B <BUILD_DIR>
make -C <BUILD_DIR>
./<BUILD_DIR>/file_sys <OPTIONS> <PATH>
```

```shell
Copy, move, print out directories and files.
Usage:
  File System [OPTION...]

  -c, --cp, --copy
  -m, --mv, --move
  -p, --print
  -h, --help
```
