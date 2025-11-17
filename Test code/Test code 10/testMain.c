#include <stdio.h>
#include <stdlib.h>
#include "testFunction.h"

int main () {

    int a = 3;
    int b = 6;
    int c = 19;
    float average;

    average = testFunction(a, b, c);

    printf("average = %f",average);

}