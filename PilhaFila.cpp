#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
    int n;
} Fila;

typedef struct {
    No* topo;
    int n;
} Pilha;

void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->n = 0;
}

void enfileirar(Fila* fila, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->n++;
}

void desenfileirar(Fila* fila) {
    if (fila->n == 0) return;
    No* aux = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(aux);
    fila->n--;
}

int frente(Fila* fila) {
    if (fila->inicio == NULL) return 0;
    return fila->inicio->valor;
}

int estaVaziaFila(Fila* fila) {
    return fila->inicio == NULL;
}

void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
    pilha->n = 0;
}

void inserir(Pilha* pilha, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->n++;
}

void remover(Pilha* pilha) {
    if (pilha->n == 0) return;
    No* aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux);
    pilha->n--;
}

int topo(Pilha* pilha) {
    if (pilha->topo == NULL) return 0;
    return pilha->topo->valor;
}

int estaVaziaPilha(Pilha* pilha) {
    return pilha->topo == NULL;
}

void inverterFila(Fila* fila, Pilha* pilha) {
    while (!estaVaziaFila(fila)) {
        inserir(pilha, frente(fila));
        desenfileirar(fila);
    }
    while (!estaVaziaPilha(pilha)) {
        enfileirar(fila, topo(pilha));
        remover(pilha);
    }
}

int main() {
    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int n, valor;

    printf("Digite o número de elementos a serem enfileirados: ");
    scanf("%d", &n);

    printf("Digite os elementos:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        enfileirar(&fila, valor);
    }

    printf("Fila original: ");
    Fila tempFila = fila;
    while (!estaVaziaFila(&tempFila)) {
        printf("%d ", frente(&tempFila));
        desenfileirar(&tempFila);
    }
    printf("\n");

    // Recria a fila com os mesmos elementos
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        enfileirar(&fila, valor);
    }

    inverterFila(&fila, &pilha);

    printf("Fila invertida: ");
    while (!estaVaziaFila(&fila)) {
        printf("%d ", frente(&fila));
        desenfileirar(&fila);
    }
    printf("\n");

    return 0;
}
