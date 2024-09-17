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

void push(Pila *p, char val) {
    if (estaLlena(p)) {
        printf("Error: Pila llena\n");
        return;
    }
    p->items[++(p->top)] = val;
}

char pop(Pila *p) {
    if (estaVacia(p)) {
        printf("Error: Pila vacía\n");
        return '\0';
    }
    return p->items[(p->top)--];
}

char tope(Pila *p) {
    if (estaVacia(p)) {
        return '\0';
    }
    return p->items[p->top];
}

int precedencia(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '(':
        case '[':
        case '{': return 0;
        default: return -1;
    }
}

int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}



int main() {
    char expresion[] = "{20*8} - [9/3] + (3*3)";
    char postfijo[MAX];

    infijoAPostfijo(expresion, postfijo);
    printf("Expresión postfija: %s\n", postfijo);
    printf("Resultado: %d\n", evaluarPostfijo(postfijo));

    return 0;
}
