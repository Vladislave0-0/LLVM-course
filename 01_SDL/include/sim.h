#ifndef __sim__
#define __sim__

#define SIM_X_SIZE 128
#define SIM_Y_SIZE 128

void simInit();
void app();
void simExit();
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();

#endif // __sim__
