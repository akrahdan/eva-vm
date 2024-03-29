
#include <iostream>
#include "src/vm/EvaVM.h"
#include "src/vm/EvaValue.h"

int main(int argc, char const *argv[]) {
    EvaVM vm;

    auto result = vm.exec(R"(
        42
    )");
    log(AS_NUMBER(result));
    std::cout << "All done \n";
    return 0;
}