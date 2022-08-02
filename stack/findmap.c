#include "linkedstack.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int pushLSMapPosition(LinkedStack* pStack, int x, int y, int direction)
{
    StackNode temp;
    MapPosition data;

    data.x = x;
    data.y = y;
    data.direction = direction;
    temp.data = data;
    temp.pLink = NULL;
    return (pushLS(pStack, temp));
}

void    get_enter(LinkedStack *pStack, int map[HEIGHT][WIDTH])
{
    int x = 0;
    int y = 0;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (map[y][x] == 3)
            {
                pStack->enter[0] = x;
                pStack->enter[1] = y;
                return ;
            }
            x++;
        }
        y++;
    }
    exit(printf("enter error"));
}

void    get_out(LinkedStack *pStack, int map[HEIGHT][WIDTH])
{
    int x = 0;
    int y = 0;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (map[y][x] == 4)
            {
                pStack->out[0] = x;
                pStack->out[1] = y;
                return ;
            }
            x++;
        }
        y++;
    }
    exit(printf("out error"));
}

void    get_map(int map[HEIGHT][WIDTH])
{
    int x = 0;
    int y = 0;
    char c[1];
    int fd;

    fd = open("stack_map", O_RDONLY);
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            read(fd, c, 1);
            map[y][x] = *c - 48;
            x++;
        }
        y++;
    }
    close(fd);
}

void    ft_print_map(int map[HEIGHT][WIDTH], int x, int y)
{
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            printf("%d ",map[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
}

int direc_check(int x, int y, int direc, int map[HEIGHT][WIDTH])
{
    if (y + DIRECTION_OFFSETS[direc][1] >= 0 && \
        x + DIRECTION_OFFSETS[direc][0] >= 0 && \
        x + DIRECTION_OFFSETS[direc][0] < WIDTH && \
        y + DIRECTION_OFFSETS[direc][1] < HEIGHT && \
        (map[y + DIRECTION_OFFSETS[direc][1]][x + DIRECTION_OFFSETS[direc][0]] == 0 || \
        map[y + DIRECTION_OFFSETS[direc][1]][x + DIRECTION_OFFSETS[direc][0]] == 4 || \
        map[y + DIRECTION_OFFSETS[direc][1]][x + DIRECTION_OFFSETS[direc][0]] == 3))
        return (1);
    return (0);
}

int find_direction(int x, int y, int map[HEIGHT][WIDTH])
{
    if (direc_check(x, y, up, map))
        return (up);
    else if (direc_check(x, y, right, map))
        return (right);
    else if (direc_check(x, y, down, map))
        return (down);
    else if (direc_check(x, y, left, map))
        return (left);
    return (-1);
}

void    wall_marking(LinkedStack *pStack, int map[HEIGHT][WIDTH])
{
    map[pStack->pTopElement->data.y + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][1]]\
    [pStack->pTopElement->data.x + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][0]] = 1;
    free(popLS(pStack));
}

void    visit_marking(LinkedStack *pStack, int map[HEIGHT][WIDTH], int type)
{
    map[pStack->pTopElement->data.y + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][1]]\
    [pStack->pTopElement->data.x + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][0]] = 2;
    pushLSMapPosition(pStack, pStack->pTopElement->data.x + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][0],\
    pStack->pTopElement->data.y + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][1], type);
}

int    find_out(LinkedStack *pStack, int map[HEIGHT][WIDTH])
{
    int direc = 0;

    pushLSMapPosition(pStack, pStack->enter[0], pStack->enter[1], \
    find_direction(pStack->enter[0], pStack->enter[1], map));
    if (pStack->pTopElement->data.direction == -1)
        return (printf("no way\n"));
    while (1)
    {
        if (direc == -1 && pStack->currentElementCount == 0)
            return (printf("no way\n"));
        if (map[pStack->pTopElement->data.y + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][1]]\
            [pStack->pTopElement->data.x + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][0]] == 4)
            return (printf("found_door\n"));
        direc = find_direction(pStack->pTopElement->data.x + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][0] \
                         ,pStack->pTopElement->data.y + DIRECTION_OFFSETS[pStack->pTopElement->data.direction][1], map);
        if (direc == -1)
            wall_marking(pStack ,map);
        else
            visit_marking(pStack, map, direc);
        printf("\n");
        usleep(100000);
        ft_print_map(map, 0 ,0);
    }
}

void    print_move_map(LinkedStack *pStack, int map[HEIGHT][WIDTH])
{
    StackNode *temp;

    while (pStack->currentElementCount != 0)
        {
            temp = popLS(pStack);
            printf("x : %d, y : %d\n",temp->data.x, temp->data.y);
            free(temp);
        }
}

int main(int ac, char **av)
{
    int map[HEIGHT][WIDTH];
    LinkedStack *pStack;

    pStack = createLinkedStack();
    get_map(map);
    get_enter(pStack, map);
    get_out(pStack, map);
    find_out(pStack, map);
    print_move_map(pStack ,map);
}