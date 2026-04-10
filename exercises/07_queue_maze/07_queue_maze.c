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
} item;

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

// for backward path printing
point pre_pt[MAX_ROW][MAX_COL] = {
    { { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, },
    { { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, },
    { { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, },
    { { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, },
    { { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, { -2, -2 }, },
};

#define Q_SIZE 1024

item q[Q_SIZE] = {};
int q_left = 0;
int q_right = 0;
int q_len = 0;

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

int enqueue(item it)
{
    if (q_len == Q_SIZE) {
        fprintf(stderr, "no space in queue\n");
        return -1;
    }

    q[q_right] = it;
    q_right = (q_right + 1) % Q_SIZE;
    q_len++;

    return 0;
}

item dequeue(void)
{
    item it;

    if (q_len <= 0)
        fprintf(stderr, "no obj in queue\n");

    it = q[q_left];
    q_left = (q_left + 1) % Q_SIZE;
    --q_len;

    return it;
}

int queue_len(void)
{
    return q_len;
}

int print_path(point curr, point stop)
{
    int counter = 100;
    point next_pt = curr;

    while (counter-- > 0 && 
           (next_pt.x != stop.x || next_pt.y != stop.y)) {
        printf("(%d, %d)\n", next_pt.x, next_pt.y);
        next_pt = pre_pt[next_pt.x][next_pt.y];
        if (next_pt.x < -1 || next_pt.y < -1)
            fprintf(stderr, "out of bound!\n");
    }
    // printf("(%d, %d)\n", next_pt.x, next_pt.y);

    return 0;
}

int main(void)
{
    point start = { 0, 0 }, end = { 4, 4 }, stop = { -1, -1 }, pt;
    direction dir;

    pre_pt[start.x][start.y] = stop;
    visited[start.x][start.y] = 1;
    enqueue((item){ start, LEFT });

    while (queue_len() > 0) {
        item it = dequeue();

        pt = it.pt;
        dir = LEFT;
        // visited[pt.x][pt.y] = 0; // no flag clear in BFS as it never goes backward

        if (pt.x == end.x && pt.y == end.y) {
            // success
            print_path(pt, stop);
            return 0;
        }

        point next_pt;
        for (direction dir = LEFT; dir < 4; ++dir) {
            next_pt = move(pt, dir);
            if (in_bound(next_pt) && !is_wall(next_pt) && !is_visited(next_pt)) {
                pre_pt[next_pt.x][next_pt.y] = pt;
                visited[next_pt.x][next_pt.y] = 1;
                enqueue((item){ next_pt, LEFT });
            }
        }
    }

    printf("No path\n");
	return 0;
}
