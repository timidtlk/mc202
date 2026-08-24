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
    char nova_palavra[201];
    char frase[100000][200];
    int soma = -1;
    int pointer = 1;
    while (palavra[0] != '\n') {
        scanf("%s", palavra);
        
        // regra 4
        char num[6];
        int num_pointer = 0;
        int qtd_digitos = 0;
        for(int i = 0; i < (int) strlen(palavra); i++) {
            if (isdigit(palavra[i])) {
                num[num_pointer++] = palavra[i];
                qtd_digitos++;
                continue;
            } else if (num_pointer != 0) {
                num[num_pointer] = '\0';
                soma += atoi(num);
                num_pointer = 0;
            } else if (!isalnum(palavra[i])) {
                soma = 0;
                qtd_digitos++;
            }
            nova_palavra[i] = palavra[i+qtd_digitos];
        }
        strcpy(palavra, nova_palavra);
        strcpy(nova_palavra, "");

        //regra 2
        if (!is_vowel(palavra[0])) {
            char letra = palavra[0];

            for (int i = 0; i < 200; i++) {
                if (palavra[i+1] == '\0') {
                    nova_palavra[i] = letra;
                    break;
                }
                nova_palavra[i] = palavra[i+1];
                nova_palavra[i+1] = '\0';
            }
        } else {
            // regra 1
            strcpy(nova_palavra, palavra);
        }
        strcat(nova_palavra, "ma");

        // regra 3
        for(int i = 0; i < (int) strlen(palavra); i++) {
            strcat(nova_palavra, "a");
        }

        strcpy(frase[pointer++], nova_palavra);
    }
    
    if (soma != -1)
        sprintf(frase[0], "%d goats say:", soma);
    for (int i = 0; i < pointer; i++) {
        if (!strcmp(frase[i], "")) {
            printf("%s ", frase[i]);
        }
    }

    printf("\n");
}