#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char c) {
    switch (c) {
    case 'a': case 'A':
    case 'e': case 'E':
    case 'i': case 'I':
    case 'o': case 'O':
    case 'u': case 'U':
        return 1;        
    }
    return 0;
}

int main(void) {
    char palavra[101];
    char* frase[200000];
    int soma = -1;
    int pointer = 1;

    while (scanf("%100s", palavra) == 1) {
        
        // regra 4
        char limpa[101];
        int idx_limpa = 0;
        char num[101];
        int num_idx = 0;

        for (int i = 0; palavra[i] != '\0'; i++) {
            if (isdigit(palavra[i])) {
                num[num_idx++] = palavra[i];
            } else {
                if (num_idx > 0) {
                    num[num_idx] = '\0';
                    if (soma == -1) soma = 0;
                    soma += atoi(num);
                    num_idx = 0;
                }
                if (isalpha(palavra[i])) {
                    limpa[idx_limpa++] = palavra[i];
                    if (soma == -1) soma = 0;
                }
            }
        }
        if (num_idx > 0) {
            num[num_idx] = '\0';
            if (soma == -1) soma = 0;
            soma += atoi(num);
        }
        limpa[idx_limpa] = '\0';
        strcpy(palavra, limpa);

        if (strlen(palavra) == 0) continue;

        int tam_necessario = strlen(palavra) + 2 + pointer + 1;
        char *nova_palavra = malloc(tam_necessario * sizeof(char));

        if (!is_vowel(palavra[0])) {
            // regra 2
            strcpy(nova_palavra, palavra + 1);
            int len = strlen(nova_palavra);
            nova_palavra[len] = palavra[0];
            nova_palavra[len + 1] = '\0';
        } else {
            // regra 1
            strcpy(nova_palavra, palavra);
        }
        strcat(nova_palavra, "ma");

        // regra 3
        for (int i = 0; i < pointer; i++) {
            strcat(nova_palavra, "a");
        }
        frase[pointer++] = nova_palavra;
    }
    
    if (soma != -1) {
        frase[0] = malloc(50 * sizeof(char));
        sprintf(frase[0], "%d goats say:", soma);
        printf("%s ", frase[0]);
        free(frase[0]);
    }

    for (int i = 1; i < pointer; i++) {
        printf("%s%s", frase[i], (i == pointer - 1) ? "" : " ");
        free(frase[i]);
    }
    printf("\n");

    return 0;
}