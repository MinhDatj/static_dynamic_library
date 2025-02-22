#include <stdio.h>
#include "add.h"
#include "sub.h"

int main() {
    printf("17 + 42 = %d\n", add(17, 42));
    printf("17 - 42 = %d\n", minus(17, 42));
    return 0;
}