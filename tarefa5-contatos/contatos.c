/*
 * Tarefa 5 - Contatos
 * 
 * Tentando resolver o problema a partir da implementação de uma Linked List
 *
 * Programador: Gustavo Santos Gil
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef char* string;

// definindo o tipo dos itens
typedef struct _contato {
    char nome[51];
    char endereco[101];
    char telefone[16];
    char data_nasc[9];
} contato;

// estruturas para organizar o código
typedef struct _no {
    contato dado;
    struct _no* proximo;
    struct _no* anterior;
} no;

typedef struct _lista {
    no* inicio;
    no* fim;
} lista;

// inicializa uma lista com seu início e fim como NULL e retorna ela 
lista* inicializar() {
    lista* l = (lista*) malloc(sizeof(lista));
    if (l != NULL){
        l->inicio = NULL;
        l->fim = NULL; 
    }
    return l;
}

void imprimir_contato(int i, contato c) {
    printf("(%d) %s\t%s\t%s\t%s\t\n", i, c.nome, c.endereco, c.telefone, c.data_nasc);
}

// dado um contato c, inseri-lo caso possível e retornar 1. caso não seja possível, retornar 0
int inserir(lista* l, contato c) {
    no* novo_no = (no*) malloc(sizeof(no));

    if (novo_no != NULL) {
        novo_no->dado = c;
        
        if (l->fim) { // caso já tenha um elemento na lista            
            novo_no->anterior = l->fim;
            novo_no->proximo = NULL;

            l->fim->proximo = novo_no;
            l->fim = novo_no;
        } else { // caso não            
            novo_no->anterior = NULL;
            novo_no->proximo = NULL;
            
            l->inicio = novo_no;
            l->fim = novo_no;
        }

        return 1;
    } else {
        return 0;
    }
}

int remover(lista* l, string nome) {
    int qtd = 0;
    
    no* i = l->inicio;
    while (i != NULL) {
        if (!strcmp(i->dado.nome, nome)) {
            no* removido = i;
            i = removido->anterior;

            if (removido == l->inicio) l->inicio = removido->proximo;
            if (removido == l->fim) l->fim = removido->anterior;
            
            if (removido->anterior)
                removido->anterior->proximo = removido->proximo;
            if (removido->proximo)
                removido->proximo->anterior = removido->anterior;

            free(removido);

            qtd++;
        }
        if (i != NULL)
            i = i->proximo;
    }
    return qtd;
}

void busca(lista* l, string nome) {
    int i = 1;
    int nenhum = 1;
    //for (no* n = l->inicio; n != NULL; n = n->proximo) {
    
    no* n = l->inicio;
    while (n != NULL) {
        if (strstr(n->dado.nome, nome)) {
            imprimir_contato(i, n->dado);
            nenhum = 0;
        }
        i++;
        if (n != NULL)
            n = n->proximo;
    }
    if (nenhum) {
        printf("Nenhum contato.\n");
    }
}

void imprimir(lista* l) {
    int i = 1;
    if (l->inicio == NULL) {
        printf("Nenhum contato.\n");
        return;
    }
    
    no* n = l->inicio;
    while (n != NULL) {
        imprimir_contato(i, n->dado);
        i++;
        n = n->proximo;
    }
}

int main(void) {
    // variavel que guarda a operação inserida pelo usuário
    char op;
    contato c;
    string termo = "";
    int result;
    lista* l = inicializar();
    
    do {
        op = getchar();
        switch (op) {
            case 'i':
                scanf(" %50[^\n]", c.nome);
                scanf(" %100[^\n]", c.endereco);
                scanf(" %15[^\n]", c.telefone);
                scanf(" %8[^\n]", c.data_nasc);
                if(inserir(l, c)) printf("\nContato para %s inserido.\n", c.nome);

                break;
            case 'r':
                scanf(" %50[^\n]", termo);
                result = remover(l, termo);
                printf("\nContatos de %s removidos: %d\n", termo, result);
                break;
            case 'b':
                scanf(" %50[^\n]", termo);
                printf("\nResultados da busca:\n");
                busca(l, termo);
                break;
            case 'p':
                printf("\nListagem:\n");
                imprimir(l);
                break;
            default:
                break;
        }
    } while (op != 'f');
    
    no* atual = l->inicio;
    while (atual != NULL) {
        no* proximo_no = atual->proximo;
        free(atual);  
        atual = proximo_no;
    }
    free(l);

    return 0;
}