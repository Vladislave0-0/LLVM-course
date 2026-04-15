#ifndef __sim__
#define __sim__

#define SIM_X_SIZE 512
#define SIM_Y_SIZE 512

void simInit();
void app();
void simExit();

#ifdef __rus__
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
#endif // __rus__

#endif // __sim__
