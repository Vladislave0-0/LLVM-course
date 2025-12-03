#include "./include/sim.h"

// Colors.
#define DEAD_CLR 0xFFFFFFFF  // white
#define ALIVE_CLR 0x808080FF // blue
#define GRID_CLR 0x696969    // dark grey

static inline int validCell(int x, int y) {
  if (x < 0 || x >= 32 || y < 0 || y >= 32)
    return 0;

  return 1;
}

// The function was used to count the number of living neighbors.
static int countNeighbors(int x, int y, int grid[][32]) {
  int count = 0;

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      // Skip the cell itself, for which we count the neighbors.
      if (dx == 0 && dy == 0)
        continue;

      int nx = x + dx;
      int ny = y + dy;

      nx = (nx + 32) % 32;
      ny = (ny + 32) % 32;

      count += grid[ny][nx];
    }
  }

  return count;
}

// A function that renders a live cell.
static void drawLiveCell(int grid_x, int grid_y, int color) {
  if (!validCell(grid_x, grid_y))
    return;

  int start_x = grid_x * 16;
  int start_y = grid_y * 16;

  for (int y = 0; y < 16; ++y) {
    for (int x = 0; x < 16; ++x)
      simPutPixel(start_x + x, start_y + y, color);
  }
}

// The function that renders the grid lines.
static void drawGrid() {
  for (int x = 0; x < 32; ++x) {
    int line_x = x * 16;

    for (int y = 0; y < SIM_Y_SIZE; ++y)
      simPutPixel(line_x, y, GRID_CLR);
  }

  for (int y = 0; y < 32; ++y) {
    int line_y = y * 16;

    for (int x = 0; x < SIM_X_SIZE; ++x)
      simPutPixel(x, line_y, GRID_CLR);
  }
}

void app() {
  int grid[32][32] = {0};
  int tmp_grid[32][32] = {0};

  for (int i = 0; i < 32; ++i) {
    for (int j = 0; j < 32; ++j)
      grid[i][j] = simRand() % 2;
  }

  for (int step = 0; step < 10000; ++step) {
    // Building the next generation.
    for (int i = 0; i < 32; ++i) {
      for (int j = 0; j < 32; ++j) {
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
    for (int i = 0; i < 32; ++i) {
      for (int j = 0; j < 32; ++j)
        grid[i][j] = tmp_grid[i][j];
    }

    // Cleaning the screen from the previous generation.
    for (int i = 0; i < SIM_Y_SIZE; ++i) {
      for (int j = 0; j < SIM_X_SIZE; ++j)
        simPutPixel(j, i, DEAD_CLR);
    }

    // Drawing live cells.
    for (int i = 0; i < 32; ++i) {
      for (int j = 0; j < 32; ++j) {
        if (grid[i][j])
          drawLiveCell(j, i, ALIVE_CLR);
      }
    }

    drawGrid();
    simFlush();
  }
}

// void app() {
//   int grid[32][32];
//   int tmp_grid[32][32];

//   for (int i = 0; i < 32; ++i) {
//     for (int j = 0; j < 32; ++j)
//       grid[i][j] = simRand() % 2;
//   }

//   for (int step = 0; step < 10000; ++step) {
//     // Building the next generation.
//     for (int i = 0; i < 32; ++i) {
//       for (int j = 0; j < 32; ++j) {
//         int neighbors = 0;

//         for (int dx = -1; dx <= 1; ++dx) {
//           for (int dy = -1; dy <= 1; ++dy) {
//             // Skip the cell itself, for which we count the neighbors.
//             if (dx == 0 && dy == 0)
//               continue;

//             neighbors += grid[(i + dy + 32) % 32][(j + dx + 32) % 32];
//           }
//         }

//         int cell = grid[i][j];

//         // The rules of the "game of life".
//         if (cell) {
//           // The cell continues to live.
//           tmp_grid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
//         } else {
//           // The cell is dying.
//           tmp_grid[i][j] = (neighbors == 3) ? 1 : 0;
//         }
//       }
//     }

//     // Making the tmp_grid the main one.
//     for (int i = 0; i < 32; ++i) {
//       for (int j = 0; j < 32; ++j)
//         grid[i][j] = tmp_grid[i][j];
//     }

//     // Cleaning the screen from the previous generation.
//     for (int i = 0; i < 512; ++i) {
//       for (int j = 0; j < 512; ++j)
//         simPutPixel(j, i, 0xFFFFFFFF);
//     }

//     // Drawing live cells.
//     for (int i = 0; i < 32; ++i) {
//       for (int j = 0; j < 32; ++j) {
//         if (grid[i][j]) {

//           if (j > 0 && j <= 32 && i > 0 && i <= 32) {

//             for (int y = 0; y < 16; ++y) {
//               for (int x = 0; x < 16; ++x)
//                 simPutPixel(j * 16 + x, i * 16 + y, 0x808080FF);
//             }
//           }
//         }
//       }
//     }

//     // Draw grid.
//     for (int x = 0; x < 32; ++x) {
//       int line_x = x * 16;

//       for (int y = 0; y < 512; ++y)
//         simPutPixel(line_x, y, 0x696969);
//     }

//     for (int y = 0; y < 32; ++y) {
//       int line_y = y * 16;

//       for (int x = 0; x < 512; ++x)
//         simPutPixel(x, line_y, 0x696969);
//     }

//     simFlush();
//   }
// }
