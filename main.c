#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} Pila;

void inicializarPila(Pila *p) {
    p->top = -1;
}

int estaVacia(Pila *p) {
    return p->top == -1;
}

int estaLlena(Pila *p) {
    return p->top == MAX - 1;
}

// funci�n push
void push(Pila *p, char valor) {
    if (estaLlena(p)) {
        printf("Error: La pila esta llena\n");
        return;
    }
    p->items[++(p->top)] = valor;
}

//fujci�n pop
char pop(Pila *p) {
    if (estaVacia(p)) {
        printf("Error: La pila esta vac�a\n");
        return '\0';
    }
    return p->items[(p->top)--];
}

int esPalindromo(char str[]) {
    Pila pila;
    inicializarPila(&pila);
    int longitud = strlen(str);
    int mitad = longitud / 2; // mitad de la pila

    // ignora espacios y caracteres especiales
    for (int i = 0; i < longitud; i++) {
        if (isalnum(str[i])) {
            push(&pila, tolower(str[i]));
        }
    }

    for (int i = 0; i < mitad; i++) {
        if (isalnum(str[i])) {
            if (tolower(str[i]) != pop(&pila)) {
                return 0; // no es pal�ndromo
            }
        }
    }
    return 1; // es pal�ndromo
}

int main() {
    char frase[] = "Anita lava la tina";

    if (esPalindromo(frase)) {
        printf("La frase es un pal�ndromo\n");
    } else {
        printf("La frase no es un pal�ndromo\n");
    }

    return 0;
}
