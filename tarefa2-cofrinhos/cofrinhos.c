#include <stdio.h>

int main(void) {
    int n, teste = 1, j, z;

    scanf("%d", &n);
    while (n != 0) {
        printf("Teste %d\n", teste++);
        int diferenca = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &j, &z);
            diferenca += j - z;

            printf("%d\n", diferenca);
        }
        printf("\n");
        scanf("%d", &n);
    }

    return 0;
}