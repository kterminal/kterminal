#include <iostream>

#include <my_lib.h>

int main(int, char**) {
    std::cout << "hello world" << std::endl;
    MyClass mc;
    mc.intro();
    return 0;
}

