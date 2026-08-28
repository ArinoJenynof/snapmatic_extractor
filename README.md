# Snapmatic Extractor
Extract your locally saved snapmatic photos into JPG format.

# Compiling
Toolchain supporting C++23 standard, cause I want to try new things yet don't know what things to try for.

### Notes
1. UCRT64 `g++` needs to link to `-lstdc++exp` for `<print>` support.
2. CLANG64 `clang++` is unknown.
3. LLVM with MSSTL seems fine.
4. LLVM with `libc++` is unknown.
5. *How do you even run `cl.exe` like the other 2 compilers in commandline?*
6. Potential `CMakeLists.txt`?
