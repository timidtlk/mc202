#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int somar(int v[], int* R, int r, int inicio, int fim) {
    int soma = 0;

    for (int i = inicio; i <= fim; i++) {
        if (i % r == 0 && i + r-1 < fim) {
            soma += R[i / r];
            i += r-1;
        } else {
            soma += v[i];
        }
    }

    return soma;
}

void atualizar(int v[], int r, int R[], int i, int x) {
    int antigo = v[i];
    int rI = (int) floor((double) i / r);

    R[rI] += x - antigo;

    v[i] = x;
}

int main(void) {
    char op;
    int size, param1, param2, i, r, resultado;

    scanf("%d", &size);
    
    int v[size];

    // definindo o vetor r
    r = ceil(sqrt(size));
    int size2 = ceil((double) size / r);
    int* R = calloc(size2, sizeof(int));
    
    // lendo os dados
    for (i = 0; i < size; i++) {
        scanf("%d ", &v[i]);
        
        R[i / r] += v[i];
    }

    while (scanf(" %c %d %d", &op, &param1, &param2) != EOF) {
        if (op == 's') {
            resultado = somar(v, R, r, param1, param2);
            printf("%d\n", resultado);
        } else if (op == 'a') {
            atualizar(v, r, R, param1, param2);
        }
    }
    free(R);
    
    return 0;
}