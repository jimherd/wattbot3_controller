/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        main.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Controller Firmware
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "global.h"     
#include "delay.h"
#include "packetiser.h"

#include "init.h"       
#include "spi.h"
#include "sci.h"
#include "motor.h"
#include "pwm.h"
#include "cypusb.h"
#include "servo.h"
#include "psx.h"

//***********************************************************************
//** Function:      Main
//** Description:   Entry point of user code
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void main()
{
uint8_t   radio_id=0;
psx_map   psx_data;
  
  Init_mcu();
  Init_Dig_IO();
  init_sci();
  init_spi_norm();
  radio_channel = get_radio_channel();
  init_radio();
  init_psx();
  RED_LED_ON;
  GREEN_LED_OFF;

  send_msg("\033[2J\033[HBootstrap successful. AW60 ready...\r\n\r\n");
  send_msg("Schools Challenge Robot\r\n");
  send_msg("=======================\r\n");
  send_msg("Wireless chipset status: ");
  if(radio_get_id() == 0x07) send_msg("Pass\r\n\r\n");
  else{
    send_msg("Fail - Please contact vendor for repair\r\n");
    for(;;);  
  }
  send_msg("Ready...\r\n");
    
  for(;;){
    send_msg("Getting PSX status\r\n");
    /* Get PSX status */
    psx_get_stat(&psx_data);
    
    send_msg("Sending data\r\n");
    /* Send data */
    packet_tx(&psx_data, sizeof(psx_data));
    
    send_msg("Waiting...\r\n\r\n");    
    /* Wait for 100ms */
    delay_ms(100);
  }
}

