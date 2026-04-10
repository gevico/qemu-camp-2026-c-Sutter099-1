#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef enum {
    LEFT = 0,
    RIGHT,
    UP,
    DOWN
} direction;

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point pt;
    direction dir;
} stack;

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int visited[MAX_ROW][MAX_COL] = {
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
};

int in_bound(point pt)
{
    int x = pt.x, y = pt.y;

    return 0 <= x && x < MAX_ROW &&
           0 <= y && y < MAX_COL;
}

int is_wall(point pt)
{
    return maze[pt.x][pt.y];
}

int is_visited(point pt)
{
    return visited[pt.x][pt.y];
}

point move(point start, direction dir)
{
    switch(dir) {
    case UP:
            return (point){ start.x, start.y + 1 };
    case DOWN:
            return (point){ start.x, start.y - 1 };
    case LEFT:
            return (point){ start.x - 1, start.y };
    case RIGHT:
            return (point){ start.x + 1, start.y };
    default:
            return start;
    }
}

void printPath(stack *s, int top)
{
    for (int i = top; i >= 0; i--)
        printf("(%d, %d)\n", s[i].pt.x, s[i].pt.y);
}

int main(void)
{
    point start = { 0, 0 }, end_pt = { 4, 4 }, pt, next_pt;
    stack stk[64], tmp, item;
    direction dir;
    int top = -1;

    // init start point
    tmp.pt = start;
    tmp.dir = LEFT;
    stk[++top] = tmp;
    visited[start.x][start.y] = 1;

    while (top >= 0) {
        item = stk[top];
        pt   = item.pt;
        dir  = item.dir;

        if (pt.x == end_pt.x && pt.y == end_pt.y) {
            printPath(stk, top);
            return 0;
        }

        // skip unavailable points
        while (dir < 4) {
            next_pt = move(pt, dir);
            if (in_bound(next_pt) && !is_wall(next_pt) && !is_visited(next_pt))
                break;
            dir++;
        }

        // no point available, go backward
        if (dir >= 4) {
            visited[item.pt.x][item.pt.y] = 0;
            top--;
            continue;
        }

        // found next point
        stk[top].dir = dir + 1;
        tmp.pt = move(pt, dir);
        tmp.dir = LEFT;
        stk[++top] = tmp;
        visited[tmp.pt.x][tmp.pt.y] = 1;
    }

	return 0;
}
