#ifndef __sim__
#define __sim__

#define SIM_X_SIZE 512
#define SIM_Y_SIZE 512

void simInit();
void app();
void simExit();
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
void dumpReg(long long reg_num, long long reg_val);
void dumpGrid(int *grid);

#endif // __sim__
