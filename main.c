#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 100


typedef struct {
    char data[N];
    int top;

}StackType;

int len(StackType *S){
    return S->top;
}

void init(StackType *S){
    S->top = -1;
}

int isEmpty(StackType *S){
    return S->top == -1;
}

int isFull(StackType *S){
    return S->top == N - 1;
}



void push(StackType *S, char c){
    if(isFull(S))
        printf("Full.\n");
    else{
        S->top++;


        S->data[S->top] = c;
    }

}



char pop(StackType *S){
    if(isEmpty(S)){
        printf("Empty. \n");
        return -1;
    }
    char c = S ->data[S->top];
    S->top--;
    return c;
}

char peek(StackType *S){
    if(isEmpty(S)){
        printf("Empty. \n");
        return -1;
    }
    return S ->data[S->top];

}

int check(char str[]){
    StackType S;
    init(&S);
    char c, t;
    int n = strlen(str);

    for(int i = 0; i < n; i++){
        c = str[i];

        if(c == '(' || c == '{' || c =='['){
            push(&S, c);
        }else if(c == ')' || c == '}' || c ==']'){
            if(isEmpty(&S)){
                return 0;
            } else{
                t = pop(&S);
                if((t == '(' && c != ')')
                || (t == '{' && c != '}')
                || (t == '[' && c != ']')
                        ) return 0;
            }
        }
    }
    return isEmpty(&S);
}


int evaluate(char postfix[]){
    StackType S;
    init(&S);

    int op1,op2, value;
    char c;
    int n = strlen(postfix);

    for(int i=0; i<n; i++){
        c = postfix[i];

        if(c !='+' && c != '-'&& c !='*' && c !='/'){
            value = c -'0';
            push(&S, value);
        }
        else{
            op2 = pop(&S) - 48;
            op1 = pop(&S) - 48;

            switch (c) {
                case '+':
                    push(&S, op1 + op2);
                    break;

                case '-':
                    push(&S, op1 - op2);
                    break;

                case '*':
                    push(&S, op1 * op2);
                    break;

                case '/':
                    push(&S, op1 / op2);
                    break;
            }
        }
    }
    return pop(&S);
}


int prec(char op){
    switch(op)
    {
    case '(': case ')':
        return 0;
    case '+': case '-':
        return 1;
    case '*': case '/':
        return 2;

    }

}



void convert(char infix[], char postfix[]){
    StackType S,P,G;
    init(&S);
    init(&P);
    init(&G);

    char c, t ;
    int n = strlen(infix);
    for (int i = 0; i < n; i++){
        c = infix[i];
        switch(c){
            case '+': case '-': case '*':case '/':
                while (!isEmpty(&S) && prec(c) <= prec(peek(&S))) {
                    push(&P,pop(&S));
                }
                push(&S, c);
                break;

            case  '(':
                push(&S, c);
                break;
            case ')':
                t = pop(&S);
                while (t != '('){
                    push(&P, t);
                    t =pop(&S);
                }
                break;

            default:
                push(&P, c);
                break;

        }

    }
    while(!isEmpty(&S)){
        push(&P, pop(&S));
        }

    while(!isEmpty(&P)) {
        push(&G, pop(&P));}

    int i = 0;
    while(!isEmpty(&G)) {
       postfix[i] = pop(&G);
       ++i;
    }

}






int main() {
    char infix[N], postfix[N];

    scanf("%s", infix);


    convert(infix, postfix);
    printf("%d\n",strlen(postfix));
    for(int i=0; i <3;i++){
        printf("%c",postfix[i]);
    }






//     printf("%s = %d\n", infix, evaluate(postfix));

    return 0;
}