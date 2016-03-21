/* Define SenseMe Bluetooth as HC_05 module 
   \author: Venus Shum
*/


#include <HC_05.h>
#include <SenseMe.h>

#ifndef SENSEMEBLUETOOTH
#define SENSEMEBLUETOOTH
HC_05 SenseMeBluetooth = HC_05(BTCMDPIN, BTSTATEPIN, BTRESETPIN, BTENABLE);
#endif