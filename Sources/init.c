/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        init.c
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Micontroller initialisation functions
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/
 
#include "global.h"


//***********************************************************************
//** Function:      init_mcu
//** Description:   
//** Parameters:    None
//** Returns:       None
//*********************************************************************** 
void Init_mcu(void){
  /* Common initialization of the write once registers */
  /* SOPT: COPE=0,COPT=1,STOPE=0 */
  SOPT = 0x53;                                      
 
  /* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=0,BGBE=0 */
  SPMSC1 = 0x18;                                      
  /* SPMSC2: LVWF=0,LVWACK=0,LVDV=0,LVWV=0,PPDF=0,PPDACK=0,PPDC=0 */
  SPMSC2 = 0x00;                                      
  /* SMCLK: MPE=0,MCSEL=0 */
  SMCLK &= (unsigned char)~0x17;                     
  
  /*  System clock initialization */
  /* ICGC1: HGO=0,RANGE=1,REFS=0,CLKS1=0,CLKS0=1,OSCSTEN=1,LOCD=1 */
  ICGC1 = 0x4E;                                      
  /* ICGC2: LOLRE=1,MFD2=1,MFD1=1,MFD0=1,LOCRE=0,RFD2=0,RFD1=0,RFD0=0 */
  ICGC2 = 0xF0;                                      
  
  ICGTRM = *(unsigned char*far)0xFFBE; /* Initialize ICGTRM register from a non volatile memory */
  while(!ICGS1_LOCK);                  /* Wait */
  
  EnableInterrupts;
}

//----------------------------------------------------------------------------
// Init_Dig_IO : configure digital I/O lines
// ===========
//
// Parameters
//      None
//
// Notes
//      the bit patterns for the initialisation are in file "pindef,h"
//
void Init_Dig_IO(void) {
//
// set data direction registers
//
    setReg8(PTADD, PORTA_DIR);
    setReg8(PTBDD, PORTB_DIR);
    setReg8(PTCDD, PORTC_DIR);
    setReg8(PTEDD, PORTE_DIR);
    setReg8(PTFDD, PORTF_DIR);  
    setReg8(PTGDD, PORTG_DIR);
//
// set pull-up registers
//
    setReg8(PTAPE, PORTA_PULLUP);
    setReg8(PTBPE, PORTB_PULLUP);
    setReg8(PTCPE, PORTC_PULLUP);
    setReg8(PTEPE, PORTE_PULLUP);
    setReg8(PTFPE, PORTF_PULLUP);  
    setReg8(PTGPE, PORTG_PULLUP);
//
// set slewrate control registers
//
    setReg8(PTASE, PORTA_SLEWRATE);
    setReg8(PTBSE, PORTB_SLEWRATE);
    setReg8(PTCSE, PORTC_SLEWRATE);
    setReg8(PTDSE, PORTD_SLEWRATE);
    setReg8(PTESE, PORTE_SLEWRATE);
    setReg8(PTFSE, PORTF_SLEWRATE);  
    setReg8(PTGSE, PORTG_SLEWRATE);
//
// set output drive control registers
//
    setReg8(PTADS, PORTA_OUT_DRIVE);
    setReg8(PTBDS, PORTB_OUT_DRIVE);
    setReg8(PTCDS, PORTC_OUT_DRIVE);
    setReg8(PTDDS, PORTD_OUT_DRIVE);
    setReg8(PTEDS, PORTE_OUT_DRIVE);
    setReg8(PTFDS, PORTF_OUT_DRIVE);  
    setReg8(PTGDS, PORTG_OUT_DRIVE);
//
// initialise outputs
// 
    setReg8(PTAD, PORTA_INIT);
    setReg8(PTBD, PORTB_INIT);
    setReg8(PTCD, PORTC_INIT);
    setReg8(PTED, PORTE_INIT);
    setReg8(PTFD, PORTF_INIT);  
    setReg8(PTGD, PORTG_INIT);       
}

//----------------------------------------------------------------------------
// get_radio_channel : read RED/BLUE switches to define radio channel
// =================
//
// Notes
//      Data is input from PORTA and is inverted.
//
// Parameters
//      None
//
// Values returned
//      radio channel number : uint8_t
//
uint8_t  get_radio_channel(void) 
{
uint8_t   temp, red_digit, blue_digit;

    temp = PTCD;  temp = ~temp;
    red_digit = temp & 0x0F;
    temp = PTDD;  temp = ~temp;
    blue_digit = temp & 0x0F;
    
    return  ((red_digit * 10) + blue_digit);
}
                                                                     