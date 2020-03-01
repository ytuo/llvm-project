auto a = L"a";
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: non-ascii string literal [bsl-literals-ascii-only]

auto b = u"b";
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: non-ascii string literal [bsl-literals-ascii-only]

auto c = U"c";
// CHECK-MESSAGES: :[[@LINE-1]]:10: warning: non-ascii string literal [bsl-literals-ascii-only]

auto d = "d";
