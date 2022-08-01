#include "stackcalc.h"
#include "linkedstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int Levelcheck(char c, int *level)
{
    if ((c == '[' && *level >= -1) || c == ']')
    {
        *level = -1;
        return (TRUE);
    }
    else if ((c == '{' && *level >= -2) || c == '}')
    {
        *level = -2;
        return (TRUE);
    }
    else if ((c == '(' && *level >= -3) || c == ')')
    {
        *level = -3;
        return (TRUE);
    }
    return (FALSE);
}

void ft_makenode(char data, LinkedStack *pStack)
{
    StackNode   temp;

    if (data == '(')
        data = ')';
    else if (data == '{')
        data = '}';
    else
        data = ']';
    temp.data = data;
    temp.pLink = NULL;
    pushLS(pStack, temp);
}

int checkBracketMatching(char *expression)
{
    LinkedStack *pStack;
    int level;
    int i;

    level = 0;
    if (!expression)
        return (FALSE);
    pStack = createLinkedStack();
    while (expression[i])
    {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
        {
            if (!Levelcheck(expression[i], &level))
                return (FALSE);
            ft_makenode(expression[i], pStack);
        }
        else if ((expression[i] == ')' || expression[i] == '}' || expression[i] == ']') \
                && (pStack->pTopElement && peekLS(pStack)->data == expression[i]))
                {
                    popLS(pStack);
                    if (pStack->pTopElement)
                        Levelcheck(peekLS(pStack)->data, &level);
                    else
                        level = 0;
                }
        i++;
    }
    if (isLinkedStackEmpty(pStack))
        return (TRUE);
    return (FALSE);
}

int main(int ac, char **av)
{
    (void)ac;
    if (checkBracketMatching(av[1]))
        printf("ok\n");
    else
        printf("no\n");
}