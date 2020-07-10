#include "state.h"
#include "vm.h"
#include <iostream>

int main(int argc, const char **argv)
{
    State state;
    VM vm(&state);
    vm.run();
    return 0;
}