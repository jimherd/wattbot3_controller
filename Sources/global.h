#include "derivative.h"
#include "hidef.h"
#include "pindef.h"
#include "PE_Types.h"

#define   NULL_STATEMENT      ;

#define RED_LED_ON     PTBD_PTBD1 = 1;
#define RED_LED_OFF    PTBD_PTBD1 = 0;

#define GREEN_LED_ON   PTBD_PTBD2 = 1;
#define GREEN_LED_OFF  PTBD_PTBD2 = 0;

extern  uint8_t     radio_channel;