#include "sim.h"

// The size of the playing field in cells.
#define GRID_WIDTH 16
#define GRID_HEIGHT 16

// The size of one cell in pixels (512 / 32 = 16).
#define CELL_SIZE ((SIM_X_SIZE) / (GRID_WIDTH))

// Field mode:
//    TOROIDAL == 0 --- the finite field.
//    TOROIDAL == 1 --- a closed field in a torus.
#define TOROIDAL 1

// Type of initializing the initial position:
//    RANDOM_INIT == 0 --- The points on the field are set according to the
//                        pattern in the initStartingPosition() function.
//    RANDOM_INIT == 1 --- The points on the field are set randomly.
#define RANDOM_INIT 0

// Maximum number of frames.
#define MAX_STEPS 10000

// Colors.
#define DEAD_CLR 0xFFFFFFFF  // white
#define ALIVE_CLR 0x808080FF // blue
#define GRID_CLR 0x696969    // dark grey

static inline int validCell(int x, int y) {
  if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT)
    return 0;

  return 1;
}

// The function was used to count the number of living neighbors.
static int countNeighbors(int x, int y, int grid[][GRID_WIDTH]) {
  int count = 0;

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      // Skip the cell itself, for which we count the neighbors.
      if (dx == 0 && dy == 0)
        continue;

      int nx = x + dx;
      int ny = y + dy;

      if (TOROIDAL) {
        nx = (nx + GRID_WIDTH) % GRID_WIDTH;
        ny = (ny + GRID_HEIGHT) % GRID_HEIGHT;
      } else { // The finite field.
        if (!validCell(nx, ny)) {
          continue;
        }
      }

      count += grid[ny][nx];
    }
  }

  return count;
}

static void initStartingPosition(int grid[][GRID_WIDTH]) {

#if RANDOM_INIT
  for (int i = 0; i < GRID_WIDTH; ++i) {
    for (int j = 0; j < GRID_HEIGHT; ++j)
      grid[i][j] = simRand() % 2;
  }

#else  // TEMPLATE_INIT
  for (int i = 0; i < GRID_WIDTH; ++i) {
    for (int j = 0; j < GRID_HEIGHT; ++j)
      grid[i][j] = 0;
  }

  // Pattern of glider
  int x = GRID_WIDTH / 2;
  int y = GRID_HEIGHT / 2;
  grid[y - 1][x] = 1;
  grid[y][x + 1] = 1;
  grid[y + 1][x - 1] = 1;
  grid[y + 1][x] = 1;
  grid[y + 1][x + 1] = 1;
#endif // RANDOM_INIT
}

// A function that renders a live cell.
static void drawLiveCell(int grid_x, int grid_y, int color) {
  if (!validCell(grid_x, grid_y))
    return;

  int start_x = grid_x * CELL_SIZE;
  int start_y = grid_y * CELL_SIZE;

  for (int y = 0; y < CELL_SIZE; ++y) {
    for (int x = 0; x < CELL_SIZE; ++x) {
      simPutPixel(start_x + x, start_y + y, color);
    }
  }
}

// The function that renders the grid lines.
static void drawGrid() {
  for (int x = 0; x < GRID_WIDTH; ++x) {
    int line_x = x * CELL_SIZE;

    for (int y = 0; y < SIM_Y_SIZE; ++y)
      simPutPixel(line_x, y, GRID_CLR);
  }

  for (int y = 0; y < GRID_HEIGHT; ++y) {
    int line_y = y * CELL_SIZE;

    for (int x = 0; x < SIM_X_SIZE; ++x)
      simPutPixel(x, line_y, GRID_CLR);
  }
}

void app() {
  int grid[GRID_HEIGHT][GRID_WIDTH] = {0};
  int tmp_grid[GRID_HEIGHT][GRID_WIDTH];

  initStartingPosition(grid);

  for (int step = 0; step < MAX_STEPS; ++step) {
    // Building the next generation.
    for (int i = 0; i < GRID_HEIGHT; ++i) {
      for (int j = 0; j < GRID_WIDTH; ++j) {
        int neighbors = countNeighbors(j, i, grid);
        int cell = grid[i][j];

        // The rules of the "game of life".
        if (cell) {
          // The cell continues to live.
          tmp_grid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
        } else {
          // The cell is dying.
          tmp_grid[i][j] = (neighbors == 3) ? 1 : 0;
        }
      }
    }

    // Making the tmp_grid the main one.
    for (int i = 0; i < GRID_HEIGHT; ++i) {
      for (int j = 0; j < GRID_WIDTH; ++j)
        grid[i][j] = tmp_grid[i][j];
    }

    // Cleaning the screen from the previous generation.
    for (int i = 0; i < SIM_Y_SIZE; ++i) {
      for (int j = 0; j < SIM_X_SIZE; ++j)
        simPutPixel(j, i, DEAD_CLR);
    }

    // Drawing live cells.
    for (int i = 0; i < GRID_HEIGHT; ++i) {
      for (int j = 0; j < GRID_WIDTH; ++j) {
        if (grid[i][j])
          drawLiveCell(j, i, ALIVE_CLR);
      }
    }

    drawGrid();
    simFlush();
  }
}
