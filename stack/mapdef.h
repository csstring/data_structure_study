#ifndef _MAP_DEF_
#define _MAP_DEF_

#define WIDTH 10
#define HEIGHT 10
#define up 0
#define right 1
#define down 2
#define left 3
#define NUM_DIRECTIONS 4
// offset: x, y
static int DIRECTION_OFFSETS[NUM_DIRECTIONS][2] = {
	{0, -1},		// up
	{1, 0},			// right
	{0, 1},			// down
	{-1, 0}			// left
};

enum PosStatus { NOT_VISIT = 0, WALL = 1 , VISIT = 2 , enter = 3 , out};

typedef struct MapPositionType
{
	int x;				// current x_point
	int y;				// current y_point
	int direction;		// moved next direction;
} MapPosition;

#endif