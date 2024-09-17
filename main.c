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

void infijoAPostfijo(char exp[], char resultado[]) {
    Pila pila;
    inicializarPila(&pila);
    int i, j = 0;

    for (i = 0; exp[i] != '\0'; i++) {
        if (isdigit(exp[i])) {
            resultado[j++] = exp[i]; // Número directamente al resultado
        } else if (esOperador(exp[i])) {
            if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
                push(&pila, exp[i]);
            } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
                char open;
                if (exp[i] == ')') open = '(';
                else if (exp[i] == ']') open = '[';
                else open = '{';

                while (!estaVacia(&pila) && tope(&pila) != open) {
                    resultado[j++] = pop(&pila);
                }
                pop(&pila); // Eliminar '(' o '[' o '{'
            } else {
                while (!estaVacia(&pila) && precedencia(tope(&pila)) >= precedencia(exp[i])) {
                    resultado[j++] = pop(&pila);
                }
                push(&pila, exp[i]);
            }
        }
    }
    while (!estaVacia(&pila)) {
        resultado[j++] = pop(&pila);
    }
    resultado[j] = '\0'; // Cerrar la cadena
}

int evaluarPostfijo(char postfijo[]) {
    Pila pila;
    inicializarPila(&pila);
    int i, op1, op2;

    for (i = 0; postfijo[i] != '\0'; i++) {
        if (isdigit(postfijo[i])) {
            push(&pila, postfijo[i] - '0'); // Convertir carácter a número
        } else {
            op2 = pop(&pila);
            op1 = pop(&pila);
            switch (postfijo[i]) {
                case '+': push(&pila, op1 + op2); break;
                case '-': push(&pila, op1 - op2); break;
                case '*': push(&pila, op1 * op2); break;
                case '/': push(&pila, op1 / op2); break;
            }
        }
    }
    return pop(&pila);
}

int main() {
    char expresion[] = "{20*8} - [9/3] + (3*3)";
    char postfijo[MAX];

    infijoAPostfijo(expresion, postfijo);
    printf("Expresión postfija: %s\n", postfijo);
    printf("Resultado: %d\n", evaluarPostfijo(postfijo));

    return 0;
}
