14 warnings generated.
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:8:2: warning: float type not allowed (variable declaration) [bsl-for-loop]
        long double l = 0;
        ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:11:2: warning: float type not allowed (variable declaration) [bsl-for-loop]
        double d = 0;
        ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:14:2: warning: float type not allowed (variable declaration) [bsl-for-loop]
        double d2 = 0.0;
        ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:17:2: warning: float type not allowed (variable declaration) [bsl-for-loop]
        double d3;
        ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:22:10: warning: float type not allowed (literal) [bsl-for-loop]
        int f = 0.0;
                ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:27:38: warning: for loop must have single loop-counter [bsl-for-loop]
        for (int x = 0; x < 3 && y < 15; x++, y++) {}
                                            ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:30:7: warning: float type not allowed (variable declaration) [bsl-for-loop]
        for (float z = 0.0F; z < 1; z += 0.1F) {}
             ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:30:35: warning: float type not allowed (literal) [bsl-for-loop]
        for (float z = 0.0F; z < 1; z += 0.1F) {}
                                         ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:34:7: warning: float type not allowed (variable declaration) [bsl-for-loop]
        for (float z = 0.0F; z < 3; z += 1) {}
             ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:37:2: warning: float type not allowed (variable declaration) [bsl-for-loop]
        float w;
        ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:42:11: warning: float type not allowed (literal) [bsl-for-loop]
        for (w = 0.0F; w < 3; w += 1) {}
                 ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:45:15: warning: float type not allowed (literal) [bsl-for-loop]
        for (int i = 0.0F; i < 3; i += 1) {}
                     ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:48:30: warning: float type not allowed (literal) [bsl-for-loop]
        for (int i = 0; i < 3; i += 0.1F) {}
                                    ^
/home/yannan/Honeynet/llvm-project/clang-tools-extra/test/clang-tidy/bsl-temp.cpp:51:22: warning: float type not allowed (literal) [bsl-for-loop]
        for (int i = 0; i < 3.0F; i++) {}
                            ^
