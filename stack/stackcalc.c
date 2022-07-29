#include "stackcalc.h"
#include "linkedstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int Levelcheck(char c)
{
    static int level;

    if (c == '[' && level >= -1)
    {
        level = -1;
        return (TRUE);
    }
    else if (c == '{' && level >= -2)
    {
        level = -2;
        return (TRUE);
    }
    else if (c == '(' && level >= -3)
    {
        level = -3;
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
    int i;

    if (!expression)
        return (FALSE);
    i = 0;
    pStack = createLinkedStack();
    while (expression[i])
    {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
        {
            if (!Levelcheck(expression[i]))
                return (FALSE);
            ft_makenode(expression[i], pStack);
        }
        else if ((expression[i] == ')' || expression[i] == '}' || expression[i] == ']') \
                && peekLS(pStack)->data == expression[i])
                    popLS(pStack);
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