#include <logic.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // logical not
    for (int i = 0; i < 2; i++) {
        printf("NOT %d = %d\n", i, NOT(i));
    }

    printf("\n");

    // logical conjunction
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d AND %d = %d\n", i, j, AND(i, j));
        }
    }

    printf("\n");

    // logical disjunction
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d OR %d = %d\n", i, j, OR(i, j));
        }
    }

    printf("\n");

    // logical implication
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d IMPLIES %d = %d\n", i, j, IMPLIES(i, j));
        }
    }

    printf("\n");

    // logical nor
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d NOR %d = %d\n", i, j, NOR(i, j));
        }
    }

    return 0;
}
