
void foo()
{
    auto a = [](){ return 0; };
    auto b = [](int x){ return x * x; };

    auto c = []{ return 0; };
    // CHECK-MESSAGES: :[[@LINE-1]]:14: warning: lambda expression with implicit parameter list [bsl-lambda-param-list]
}
