/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        init.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2404
 * Company:         MEng dissertation
 *************************************************************************
 * File description:
 *  Header for microcontroller initialisation code
 *************************************************************************
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 ************************************************************************/

#ifndef __init_H
#define __init_H
 
void Init_mcu(void);
void Init_Dig_IO(void);
uint8_t  get_radio_channel(void);

#endif