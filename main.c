#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* criarNo(int dado) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->data = dado;
    novoNo->prev = NULL;
    novoNo->next = NULL;
    return novoNo;
}

void inserirNoInicio(Node** cabeca, int dado) {
    Node* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        novoNo->next = *cabeca;
        (*cabeca)->prev = novoNo;
        *cabeca = novoNo;
    }
}

void inserirNoFim(Node** cabeca, int dado) {
    Node* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        Node* temp = *cabeca;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNo;
        novoNo->prev = temp;
    }
}

void inserirEmPosicao(Node** cabeca, int dado, int posicao) {
    Node* novoNo = criarNo(dado);
    if (posicao == 0 || *cabeca == NULL) {
        inserirNoInicio(cabeca, dado);
    } else {
        Node* temp = *cabeca;
        int i;
        for (i = 0; i < posicao - 1 && temp->next != NULL; ++i) {
            temp = temp->next;
        }
        novoNo->next = temp->next;
        novoNo->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = novoNo;
        }
        temp->next = novoNo;
    }
}

void excluirDoInicio(Node** cabeca) {
    if (*cabeca != NULL) {
        Node* temp = *cabeca;
        *cabeca = (*cabeca)->next;
        if (*cabeca != NULL) {
            (*cabeca)->prev = NULL;
        }
        free(temp);
    }
}

void excluirDoFim(Node** cabeca) {
    if (*cabeca != NULL) {
        Node* temp = *cabeca;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->prev != NULL) {
            temp->prev->next = NULL;
        } else {
            *cabeca = NULL;
        }
        free(temp);
    }
}

void excluirDaPosicao(Node** cabeca, int posicao) {
    if (*cabeca != NULL) {
        Node* temp = *cabeca;
        int i;
        for (i = 0; i < posicao && temp != NULL; ++i) {
            temp = temp->next;
        }
        if (temp != NULL) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                *cabeca = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
        }
    }
}

Node* pesquisarNo(Node* cabeca, int chave) {
    while (cabeca != NULL && cabeca->data != chave) {
        cabeca = cabeca->next;
    }
    return cabeca;
}

void exibirLista(Node* cabeca) {
    while (cabeca != NULL) {
        printf("%d -> ", cabeca->data);
        cabeca = cabeca->next;
    }
    printf("NULL\n");
}

int main() {
    Node* listaDuplamenteEncadeada = NULL;
    Node* listaCircular = NULL;

    inserirNoInicio(&listaDuplamenteEncadeada, 10);
    inserirNoFim(&listaDuplamenteEncadeada, 20);
    inserirEmPosicao(&listaDuplamenteEncadeada, 15, 1);

    inserirNoFim(&listaCircular, 30);
    inserirNoInicio(&listaCircular, 5);
    inserirEmPosicao(&listaCircular, 25, 2);

    printf("Lista Duplamente Encadeada: ");
    exibirLista(listaDuplamenteEncadeada);

    printf("Lista Circular: ");
    exibirLista(listaCircular);

    excluirDoInicio(&listaDuplamenteEncadeada);
    excluirDoFim(&listaDuplamenteEncadeada);
    excluirDaPosicao(&listaDuplamenteEncadeada, 1);

    excluirDoInicio(&listaCircular);
    excluirDoFim(&listaCircular);
    excluirDaPosicao(&listaCircular, 1);

    printf("Lista Duplamente Encadeada após a exclusão: ");
    exibirLista(listaDuplamenteEncadeada);

    printf("Lista Circular após a exclusão: ");
    exibirLista(listaCircular);

    int chaveParaPesquisar = 15;
    Node* noEncontrado = pesquisarNo(listaDuplamenteEncadeada, chaveParaPesquisar);
    if (noEncontrado != NULL) {
        printf("Nó com chave %d encontrado na Lista Duplamente Encadeada.\n", chaveParaPesquisar);
    } else {
        printf("Nó com chave %d não encontrado na Lista Duplamente Encadeada.\n", chaveParaPesquisar);
    }

    chaveParaPesquisar = 25;
    noEncontrado = pesquisarNo(listaCircular, chaveParaPesquisar);
    if (noEncontrado != NULL) {
        printf("Nó com chave %d encontrado na Lista Circular.\n", chaveParaPesquisar);
    } else {
        printf("Nó com chave %d não encontrado na Lista Circular.\n", chaveParaPesquisar);
    }

    return 0;
}
