#include "stackcalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char	**ft_split(char const *s, char c);
int pushLSExprToken(LinkedStack* pStack, ExprToken data)
{
    StackNode   temp;

    temp.data.value = data.value;
    temp.data.type = data.type;
    if (pushLS(pStack,temp))
        return (TRUE);
    return (FALSE);
}

void printToken(ExprToken element)
{
    switch (element.type)
    {
        case lparen:
            printf("float : %f, type : lparen\n", element.value);
            break;
        case rparen:
            printf("float : %f, type : rparen\n", element.value);
            break;
        case times:
            printf("float : %f, type : times\n", element.value);
            break;
        case divide:
            printf("float : %f, type : divied\n", element.value);
            break;
        case plus:
            printf("float : %f, type : plus\n", element.value);
            break;
        case minus:
            printf("float : %f, type : minus\n", element.value);
            break;
        case operand:
            printf("float : %f, type : operand\n", element.value);
            break;
        default :
            break;    
    }
}

void    calcoperand(LinkedStack *pStack, float value)
{
    ExprToken temp;

    temp.value = value;
    temp.type = operand;
    pushLSExprToken(pStack, temp);
}

void    calcelse(LinkedStack *pStack, float value, int prec)
{
    Precedence type = prec;
    StackNode *first;
    StackNode *second;
    ExprToken temp;

    first = popLS(pStack);
    second = popLS(pStack);
    if (!first || !second)
        exit(1);
    if (first->data.value == 0.0000000 && first->data.type == divide)
        exit(1);
    switch (type)
    {
        case lparen:
            break;
        case rparen:
            break;
        case times:
            temp.value = first->data.value * second->data.value;
            break;
        case divide:
            temp.value = second->data.value / first->data.value;
            break;
        case plus:
            temp.value = second->data.value + first->data.value;
            break;
        case minus:
            temp.value = second->data.value - first->data.value;
            break;
        default :
            break;    
    }
    temp.type = operand;
    free(first);
    free(second);
    pushLSExprToken(pStack, temp);
}

void calcExpr(LinkedStack *pStack, float value, int prec)
{
    Precedence type = prec;

    if (type == operand)
        calcoperand(pStack ,value);
    else
        calcelse(pStack, value, type);
}
/*
int main(int ac , char **av)
{
    int i;
    LinkedStack *pStack;
    char **str;

    str = ft_split(av[1], ' ');
    pStack = createLinkedStack();
    i = 0;
    while (str[i])
    {
        if (!strcmp(str[i], "("))
            calcExpr(pStack, 0, 0);
        else if (!strcmp(str[i], ")"))
            calcExpr(pStack,0 ,1);
        else if (!strcmp(str[i], "*"))
            calcExpr(pStack,0, 2);
        else if (!strcmp(str[i], "\\"))
            calcExpr(pStack,0, 3);
        else if (!strcmp(str[i], "+"))
            calcExpr(pStack,0 ,4);
        else if (!strcmp(str[i], "-"))
            calcExpr(pStack,0 ,5);
        else if (str[i][0] != '0' && atof(str[i]) == 0.0000000)
            return (printf("input error"));
        else
            printf("%f",atof(str[i]));
        i++;
    }
    if (pStack->currentElementCount == 1)
        printToken(pStack->pTopElement->data);
    return (0);
}*/