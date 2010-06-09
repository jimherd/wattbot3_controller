/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        psx.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Playstation controller driver
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#include "global.h"
#include "psx.h"
#include "spi.h"
#include "delay.h"

#define DEADMAN_MAX_COUNT 50

typedef struct {
  char cont_id;   //Controller ID 0x01 -> 0x04 valid
  char command;   //Command to send
  char filler;    //Always 0x00
  char byte1;     //Command payload byte 1
  char byte2;     //Command payload byte 2
  char byte3;     //Command payload byte 3
  char byte4;     //Command payload byte 4
  char byte5;     //Command payload byte 5
  char byte6;     //Command payload byte 6
} psx_packet;

static struct psx_motor_status{
  char motor1;
  char motor2;
} psx_motor_status;

char FAKE_PORT;

//***********************************************************************
//** Function:      init_psx
//** 
//** Description:   Initialises microcontroller and PSX controller
//**
//** Parameters:    None
//** Returns:       None
//***********************************************************************
void init_psx(void){
  /* Initialise additional pins for PSX controller */
  PSX_SS_D = 1;
  PSX_ACK_D = 0;
  PSX_SS = 1;
  
  /* Delay for PSX controller to boot */
  delay_250ms();
  delay_250ms();
    
  /* Initialise PSX controller */
  psx_config_mode(TRUE);            //Enter configuration mode
  psx_lock_en(PSX_LOCK_ANA, TRUE);  //Lock PSX controller into Analogue mode
  psx_vib_en(TRUE);                 //Enable vibration circuitry
  psx_config_mode(FALSE);           //Exit configuration mode
  psx_motor1_duty(0x00);            //Set rumble motor 1 to off (0x00)
  psx_motor2_duty(0x00);            //Set rumble motor 2 to off (0x00)
}

//***********************************************************************
//** Function:      psx_io
//** 
//** Description:   Low level PSX controller tranceiver function
//**                !!Not recommend for general purpose use!! 
//**
//** Parameters:    char tx   - Byte to send to PSX controller 
//**                char *ack - Pointer to acknowledge flag
//** Returns:       char      - Data received from PSX controller
//***********************************************************************
char psx_io(char tx, char *ack)
{
uint8_t  rx;
uint8_t  n;
  
    rx = spi_io(tx);
    *ack = FALSE;
  
    for (n = 0 ; (n < DEADMAN_MAX_COUNT) ; n++) {
        if (!PSX_ACK) {                                // PSX_ACK == 0
            *ack = TRUE;
            break;
        }
    }
    return(rx);
}

//***********************************************************************
//** Function:      psx_com
//** 
//** Description:   High level PSX controller transceiver function
//**
//** Parameters:    void *psx_tx - Pointer to array of void data to be Tx'ed to PSX controller 
//**                void *psx_rx - Pointer to array of void data to be Rx'ed to PSX controller
//**                char len     - Length of void arrays
//** Returns:       char         - Number of bytes received from PSX controller
//***********************************************************************
char psx_com(void *psx_tx, void *psx_rx, char len)
{
uint8_t   n=0;
uint8_t   ack=1;
//  
//  Set SPI module for PSX mode
//
    init_spi_psx();
//
// Activate PSX controller 
//
    PSX_SS = 0;
    delay_100us();
//  
// Wait for PSX to become ready
//
    while(!PSX_ACK) {        // PSX_ACK == 0
        NULL_STATEMENT;
    }
// 
// Transmit data packet - stop when PSX doesn't acknowledge SPI Xfer (1 fail = EOF notification)
// Deference psx_rx and psx_tx as char arrays and transceive new data  
// 
    for(n=0 ; (n < len) && ack ; n++){
        *(((char *)(psx_rx))+n) = psx_io( *(((char *)(psx_tx))+n), &ack);                                       
        delay_10us();  // 10us delay to emulate PSX operation (not strictly necessary)
    }
//  
// Disable PSX controller 
//
    PSX_SS = 1;
// 
// Set SPI module to normal mode
//
    init_spi_norm();
//  
// Delay to allow controller time to process command and return number of bytes
//
    delay_1ms();
    return(n);
}

//***********************************************************************
//** Function:      psx_config_mode
//** 
//** Description:   Set PSX controller to configuration mode
//**
//** Parameters:    char enable - 0x01 = Enable configuration mode
//**                              0x00 = Disable configuration mode
//** Returns:       None
//***********************************************************************
void psx_config_mode(char enable){
  psx_packet psx_packet1 = {0};
  char rx_buff[sizeof(psx_packet1)];
  
  psx_packet1.cont_id = 0x01;
  psx_packet1.command = PSX_CONFIG;
  psx_packet1.filler  = 0x00;
  psx_packet1.byte1 = enable;
  psx_packet1.byte3 = 0x00;
  psx_packet1.byte4 = 0x00;
  psx_packet1.byte5 = 0x00;
  psx_packet1.byte6 = 0x00;
 
  (void)psx_com(&psx_packet1, rx_buff, sizeof(psx_packet1));
}

//***********************************************************************
//** Function:      psx_lock_en
//** 
//** Description:   Enables PSX controller to be locked into a particular mode
//**
//** Parameters:    char mode   - 0x00 = Digital mode
//**                            - 0x01 = Analogue mode
//**                char enable - 0x03 = Enable lock
//**                            - 0x00 = Disable lock
//** Returns:       None
//***********************************************************************
void psx_lock_en(char mode, char enable){
  psx_packet psx_packet1 = {0};
  char rx_buff[sizeof(psx_packet1)];
  
  psx_packet1.cont_id = 0x01;
  psx_packet1.command = PSX_MODE_LOCK;
  psx_packet1.filler  = 0x00;
  psx_packet1.byte1 = mode;
  if (enable) {
    psx_packet1.byte2 = 0x03;
  }
  else {
    psx_packet1.byte2 = 0x00;
  }
  psx_packet1.byte3 = 0x00;
  psx_packet1.byte4 = 0x00;
  psx_packet1.byte5 = 0x00;
  psx_packet1.byte6 = 0x00;
 
  (void)psx_com(&psx_packet1, rx_buff, sizeof(psx_packet1));
}

//***********************************************************************
//** Function:      psx_vib_en
//** 
//** Description:   Enables vibrate
//**
//** Parameters:    char enable - 0x01 = Enable vibration function
//**                              0x00 = Disable vibration function
//** Returns:       None
//***********************************************************************
void psx_vib_en(char enable){
  psx_packet psx_packet1 = {0};
  char rx_buff[sizeof(psx_packet1)];
  
  psx_packet1.cont_id = 0x01;
  psx_packet1.command = PSX_VIBRATE_EN;
  psx_packet1.filler  = 0x00;
  psx_packet1.byte1 = enable;
  psx_packet1.byte2 = enable;
  psx_packet1.byte3 = 0xFF;
  psx_packet1.byte4 = 0xFF;
  psx_packet1.byte5 = 0xFF;
  psx_packet1.byte6 = 0xFF;
 
  (void)psx_com(&psx_packet1, rx_buff, sizeof(psx_packet1));
}

//***********************************************************************
//** Function:      psx_motor1_duty
//** 
//** Description:   Sets vibration effort of motor1
//**
//** Parameters:    char duty - Vibration level (0x00 [min] -> 0xFF [max])  
//** Returns:       None
//***********************************************************************
void psx_motor1_duty(char duty){
  psx_packet psx_packet1 = {0};
  char rx_buff[sizeof(psx_packet1)];
    
  psx_motor_status.motor1 = duty;
  
  psx_packet1.cont_id = 0x01;
  psx_packet1.command = PSX_STATUS;
  psx_packet1.filler  = 0x00;  
  psx_packet1.byte1 = duty;
  psx_packet1.byte2 = psx_motor_status.motor2;
  psx_packet1.byte3 = 0x00;
  psx_packet1.byte4 = 0x00;
  psx_packet1.byte5 = 0x00;
  psx_packet1.byte6 = 0x00;
 
  (void)psx_com(&psx_packet1, rx_buff, sizeof(psx_packet1));
}

//***********************************************************************
//** Function:      psx_motor2_duty
//** 
//** Description:   Sets vibration effort of motor2 
//**
//** Parameters:    char duty - Vibration level (0x00 [min] -> 0xFF [max]) 
//** Returns:       None
//***********************************************************************
void psx_motor2_duty(char duty){
  psx_packet psx_packet1 = {0};
  char rx_buff[sizeof(psx_packet1)];
    
  psx_motor_status.motor2 = duty;
  
  psx_packet1.cont_id = 0x01;
  psx_packet1.command = PSX_STATUS;
  psx_packet1.filler  = 0x00;  
  psx_packet1.byte1 = psx_motor_status.motor1;
  psx_packet1.byte2 = duty;
  psx_packet1.byte3 = 0x00;
  psx_packet1.byte4 = 0x00;
  psx_packet1.byte5 = 0x00;
  psx_packet1.byte6 = 0x00;  
 
  (void)psx_com(&psx_packet1, rx_buff, sizeof(psx_packet1));
}

//***********************************************************************
//** Function:      psx_stat
//** 
//** Description:   Gets PSX status 
//**
//** Parameters:    void *rx_buff - Array to store PSX data (must be >= 9bytes)                               
//** Returns:       None
//***********************************************************************
void psx_get_stat(void *rx_buff){
  psx_packet psx_packet1 = {0};
  
  psx_packet1.cont_id = 0x01;
  psx_packet1.command = PSX_STATUS;
  psx_packet1.filler  = 0x00;  
  psx_packet1.byte1 = psx_motor_status.motor1;
  psx_packet1.byte2 = psx_motor_status.motor2;
  psx_packet1.byte3 = 0x00;
  psx_packet1.byte4 = 0x00;
  psx_packet1.byte5 = 0x00;
  psx_packet1.byte6 = 0x00;  
   
  (void)psx_com(&psx_packet1, rx_buff, sizeof(psx_packet1));
}