#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <gol.h>

int DIM_LIMIT = D - 1;
bool grid[D][D] = { false };
int grid_size = sizeof(grid);

int min(int a, int b)
{
    return ( a > b ) ? b : a;
}

int max(int a, int b)
{
    return ( a > b ) ? a : b;
}

void clear()
{
    printf("\e[1;1H\e[2J");
}

void render()
{
    int i, j;
    for (i = 0; i < D; i++) {
        for (j = 0; j < D; j++) {
            if (grid[i][j]) {
                printf(BWHITE "%c " RESET, ALIVE);
            } else {
                printf(GREEN "%c " RESET, DEAD);
            }
        }
        printf("\n");
    }
}

int get_neighbours(int i, int j)
{
    int result = 0;

    for (int x = max(0, i-1); x <= min(i+1, DIM_LIMIT); x++) {
        for (int y = max(0, j-1); y <= min(j+1, DIM_LIMIT); y++) {
            if (x != i || y != j) {
                if (grid[x][y]) {
                    result += 1;
                }
            }
        }
    }
    return result;
}

void update()
{
    bool new_grid[D][D]; // buffer holding a new frame
    memcpy(new_grid, grid, grid_size);

    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {

            int alive_cnt = get_neighbours(i, j);
            bool cur = grid[i][j];

            // rules
            if (cur && alive_cnt < 2) {
                // lonely die
                new_grid[i][j] = false;
            }
            else if (cur && alive_cnt > 3) {
                // overpopulated die
                new_grid[i][j] = false;
            }
            else if (!cur && alive_cnt == 3) {
                // new cells are born
                new_grid[i][j] = true;
            }
            else {
                // else stay the same
                new_grid[i][j] = cur;
            }
        }
    }
    memcpy(grid, new_grid, grid_size);
}

void set_alive(int i, int j)
{
    grid[i][j] = true;
}

void init_glider()
{
    set_alive(1, 0);
    set_alive(0, 2);
    set_alive(1, 2);
    set_alive(2, 2);
    set_alive(2, 1);
}

void init_blinker()
{
    set_alive(3, 4);
    set_alive(4, 4);
    set_alive(5, 4);
}

void init_toad()
{
    set_alive(3, 4);
    set_alive(4, 4);
    set_alive(5, 4);

    set_alive(2, 5);
    set_alive(3, 5);
    set_alive(4, 5);
}

int main()
{
    init_glider();
    render();

    while (true) {
        sleep(DELAY);
        clear();
        update();
        render();
    }

    return 0;
}