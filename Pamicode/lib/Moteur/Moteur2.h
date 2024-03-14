//#include "moteur.h"
//#include <CRAC_utility.h>

void moteur_init(void);
//void setupPWM(int PWMpin, int PWMChannel);
void moteur_avance_D(int PWM);
void moteur_avance_G(int PWM);
void moteur_stop_G(void);
void moteur_stop_D(void);