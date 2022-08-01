#include "stackcalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	**ft_split(char const *s, char c);

int inStackPrecedence(Precedence type)
{
    if (type == rparen)
        return (3);
    else if (type == times || type == divide)
        return (2);
    else if (type == plus || type == minus)
        return (1);
    else if (type == lparen)
        return (0);
    else
        exit(1);
}

int outStackPrecedence(Precedence type)
{
    if (type == rparen || type == lparen)
        return (3);
    else if (type == times || type == divide)
        return (2);
    else if (type == plus || type == minus)
        return (1);
    else
        exit(1);
}

static void printprec(ExprToken element)
{
    switch (element.type)
    {
        case lparen:
            printf("(");
            break;
        case rparen:
            printf(")");
            break;
        case times:
            printf("*");
            break;
        case divide:
            printf("/");
            break;
        case plus:
            printf("+");
            break;
        case minus:
            printf("-");
            break;
        case operand:
            printf("%f", element.value);
            break;
        default :
            break;    
    }
}

static void    add_prec(LinkedStack *pStack, Precedence prec)
{
    ExprToken temp;

    temp.value = 0;
    temp.type = prec;
    pushLSExprToken(pStack, temp);
}

void    precedence_check(LinkedStack *pStack, Precedence prec)
{
    StackNode   *temp;

    if (pStack->currentElementCount == 0)
        add_prec(pStack, prec);
    else if (prec == rparen)
    {
        while (pStack->pTopElement->data.type != lparen)
            {
                temp = popLS(pStack);
                printprec(temp->data);
                free(temp);
            }
        temp = popLS(pStack);
        free(temp);
    }
    else if (outStackPrecedence(prec) > inStackPrecedence(pStack->pTopElement->data.type))
        add_prec(pStack, prec);
    else
    {
        temp = popLS(pStack);
        printprec(temp->data);
        free(temp);
        add_prec(pStack, prec);
    }
}

int main(int ac , char **av)
{
    int i;
    LinkedStack *pStack;
    char **str;
    StackNode   *temp;

    str = ft_split(av[1], ' ');
    pStack = createLinkedStack();
    i = 0;
    while (str[i])
    {
        if (!strcmp(str[i], "("))
            precedence_check(pStack, 0);
        else if (!strcmp(str[i], ")"))
            precedence_check(pStack, 1);
        else if (!strcmp(str[i], "*"))
            precedence_check(pStack, 2);
        else if (!strcmp(str[i], "\\"))
            precedence_check(pStack, 3);
        else if (!strcmp(str[i], "+"))
            precedence_check(pStack, 4);
        else if (!strcmp(str[i], "-"))
            precedence_check(pStack, 5);
        else if (str[i][0] != '0' && atof(str[i]) == 0.0000000)
            return (printf("input error"));
        else
            printf("%.0f",atof(str[i]));
        i++;
    }
    while (pStack->currentElementCount != 0)
        {
            temp = popLS(pStack);
            printprec(temp->data);
            free(temp);
        }
    return (0);
}