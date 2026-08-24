#include <stdio.h>

int main(void) {
    int n, latas, copos, copos_quebrados;

    scanf("%d", &n);

    copos_quebrados = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &latas, &copos);
        if (latas > copos)
            copos_quebrados += copos;
    }

    printf("%d\n", copos_quebrados);

    return 0;
}