#include "stackcalc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char	**ft_split(char const *s, char c);
int pushLSExprToken(LinkedStack* pStack, ExprToken data);

//int inStackPrecedence(Precedence oper)
//int outStackPrecedence(Precedence oper)
static void printToken(ExprToken element)
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

void    calcoperand(LinkedStack *pStack, float value)
{
    ExprToken temp;

    temp.value = value;
    temp.type = operand;
    pushLSExprToken(pStack, temp);
}