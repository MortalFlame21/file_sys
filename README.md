# File System

A repository that messes around with `std::filesystem`. The program can copy, move and print out directories and files.

## Usage

```shell
cmake -S . -B <BUILD_DIR>
make -C <BUILD_DIR>
./<BUILD_DIR>/file_sys <OPTIONS> <PATH> <DEST>
```

```shell
Copy, move, print out directories and files
Usage:
  file_sys [OPTION...] [path] [dest]

  -c, --copy    copy path to dest
  -m, --move    move path to dest
  -p, --print   print path (one level)
  -s, --subdir  print path and its subdirectories.with copy it performs
                recursive copy.
  -h, --help    Print usage
```
