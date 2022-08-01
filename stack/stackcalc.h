#ifndef _STACK_CALC_
#define _STACK_CALC_

#include "linkedstack.h"

int checkBracketMatching(char *expression);
void calcExpr(LinkedStack *pStack, float value, int type);
int pushLSExprToken(LinkedStack* pStack, ExprToken data);
//void convertInfixToPostfix(ExprToken *pExprTokens, int tokenCount);
int inStackPrecedence(Precedence oper);
int outStackPrecedence(Precedence oper);
void printToken(ExprToken element);
void    calcoperand(LinkedStack *pStack, float value);
void    calcelse(LinkedStack *pStack, float value, int prec);
#endif