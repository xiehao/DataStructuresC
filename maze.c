#include "maze.h"

#define WIDTH 8
#define HEIGHT 8
#define N_DIRECTIONS 8

typedef struct {
    int x, y;
} Direction;

/**
 * @brief Directional vectors to the next steps
 *
 */
static const Direction steps[N_DIRECTIONS] = {
    {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1},
};

/**
 * @brief The map of the maze
 * 0: the ground to visit
 * 1: the wall which is not allowed to visit
 * -1: the ground which is already visited
 */
static int map[HEIGHT + 2][WIDTH + 2] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 1, 1, 1}, {1, 1, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 0, 1, 1, 1, 1}, {1, 1, 1, 0, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, {1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct {
    int x, y, d;
} Cell;

/**
 * @brief Create a cell
 * The direction of the new cell is initiated 0
 * @param x the horizontal coordinate
 * @param y the vertical coordinate
 * @param d the next possible direction
 * @return Cell* the created cell
 */
static Cell *create_cell(int x, int y, int d) {
    Cell *c = malloc(sizeof(Cell));
    if (c) {
        c->x = x, c->y = y, c->d = d;
    }
    return c;
}

/**
 * @brief Create a next cell, according to the current direction
 * The direction of the new cell is initiated 0
 * @param c the current cell, with the next possible direction
 * @return Cell* the created next cell
 */
static Cell *create_next_cell(Cell *c) {
    assert(c);
    return create_cell(c->x + steps[c->d].x, c->y + steps[c->d].y, -1);
}

/**
 * @brief Try the next direction
 *
 * @param c the original cell
 * @return Cell* the cell with its direction changed
 */
static Cell *try_next_direction(Cell *c) {
    assert(c);
    c->d = (c->d + 1) % N_DIRECTIONS;
    return c;
}

static void mark_visited(Cell *c) {
    assert(c);
    map[c->y][c->x] = 2;
}

/**
 * @brief Check if the next possible step is blocked
 * A cell is blocked if it is a wall or visited.
 * @param c the cell, with the info of the next step direction
 * @return true is blocked
 * @return false is not blocked
 */
static bool is_blocked_next(Cell *c) {
    assert(c);
    return map[c->y + steps[c->d].y][c->x + steps[c->d].x];
}

/**
 * @brief Check if two cells have the same info
 *
 * @param lhs one cell
 * @param rhs another cell
 * @return true have the same info
 * @return false have different info
 */
static bool equal_cells(DataType lhs, DataType rhs) {
    assert(lhs && rhs);
    Cell *left = (Cell *)lhs;
    Cell *right = (Cell *)rhs;
    return left->x == right->x && left->y == right->y;
}

/**
 * @brief Print a path
 * Print the info of each and every cell from the path one by one
 * @param path the path to be printed
 */
static void print_path(SequenceStack *path) {
    assert(path);
    printf("[");
    for (int i = 0; i <= path->_->last; ++i) {
        Cell c = DATAVALUE(Cell, path->_->data[i]);
        printf("(%d, %d, %d) -> ", c.x, c.y, c.d);
    }
    printf("end]\n");
}

static void print_map() {
    for (int i = 0; i < HEIGHT + 2; ++i) {
        for (int j = 0; j < WIDTH + 2; ++j) {
            printf("%d\t", map[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Find a path from starting cell to ending cell in a maze.
 * The algorithm is implemented via a stack (storing the visited cells)
 * @param s the starting cell
 * @param e the ending cell
 * @return SequenceStack* the path, NULL if no path is found
 */
static SequenceStack *find_path(Cell *s, Cell *e, EqualType c) {
    SequenceStack *path = create_sequence_stack();
    push_sequence_stack(path, s);
    while (!empty_sequence_stack(path)) {
        pop_sequence_stack(path, (DataType *)(&s));
        for (int d = 0; d < N_DIRECTIONS; ++d, try_next_direction(s)) {
            if (!is_blocked_next(s)) {
                push_sequence_stack(path, s);
                s = create_next_cell(s);
                mark_visited(s);
                d = 0; // reset the counter
                if (c(s, e)) { // arrived the end
                    push_sequence_stack(path, e);
                    return path; // found the path
                }
            }
        }
        free(s); // free the popped cell
    }
    return path; // found no path
}

void solve_maze() {
    Cell *s = create_cell(2, 1, 0); // starting cell
    Cell *e = create_cell(7, 8, 0); // ending cell
    SequenceStack *path = find_path(s, e, equal_cells);
    print_path(path);
    print_map();
    destroy_sequence_stack(path);
}