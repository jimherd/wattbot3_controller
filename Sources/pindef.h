/*************************************************************************
 *
 *                  SCHOOLS CHALLENGE ROBOT
 *
 *************************************************************************
 * FileName:        pindef.h
 * Processor:       HCS08
 * Compiler:        Code Warrior 5.9 Build 2830
 * Company:         MEng dissertation
 *
 * Author                Date          Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * James Courtier        21/05/2008    Original.
 * Jim Herd              28/05/2009    Update for new PCB board
 ************************************************************************/

char __isflag_int(void);

#define PSX_ACK         PTCD_PTCD4
#define PSX_ACK_D       PTCDD_PTCDD4
#define PSX_SS          PTAD_PTAD1
#define PSX_SS_D        PTADD_PTADD1

#define CYP_RADIO_RST   PTGD_PTGD2
#define CYP_RADIO_RST_D PTGDD_PTGDD2
#define CYP_RADIO_SS    PTAD_PTAD0
#define CYP_RADIO_SS_D  PTADD_PTADD0
#define CYP_RADIO_IRQ   __isflag_int()

//
// Pin names

#define BATTERY_VOLTS_PIN   PTB0_AD1P0          // [34][analogue]


#define RED_SWITCH_1        PTCD_PTCD0
#define RED_SWITCH_2        PTCD_PTCD1
#define RED_SWITCH_4        PTCD_PTCD2
#define RED_SWITCH_8        PTCD_PTCD3

#define BLUE_SWITCH_1       PTDD_PTDD0
#define BLUE_SWITCH_2       PTDD_PTDD1
#define BLUE_SWITCH_4       PTDD_PTDD2
#define BLUE_SWITCH_8       PTDD_PTDD3

#define RED_LED             PTBD_PTBD1
#define GREEN_LED           PTBD_PTBD2



//----------------------------------------------------------------------------
// Pin listing
//
//  Pin  Name               Used     Feature         Description
//  ===  ====               ====     =======         ===========
//   1   PTC4                Y         PTC4          PSX ack
//   2   IRQ                 Y         IRQ           Cypress IRQ
//   3   ~RESET              *
//   4   PTF0/TPM1CH2        N         
//   5   PTF1/TPM1CH3        N         
//   6   PTF4/TPM2CH0        N          
//   7   PTF5/TPM2CH1        N
//   8   PTE0/TxD1           Y         TxD1          serial port transmit
//   9   PTE1/RxD1           Y         RxD1          serial port receive
//  10   PTE2/TPM1CH0        N
//  11   PTE3/TPM1CH1        N
//  12   PTE4/~SS1           Y                       SPI system select
//  13   PTE5/MISO1          Y                       SPI input
//  14   PTE6/MOSI1          Y                       SPI output
//  15   PTE7/SPSCK          Y                       SPI clock
//  16   Vss                 *
//  17   Vdd                 *
//  18   PTG0/KBI1P0         N                  
//  19   PTG1/KBI1P1         N                 
//  20   PTG2/KBI1P2         Y         PTG2          Cypress reset          
//  21   PTA0                Y         PTA0          Cypress slave select (SPI SS)       
//  22   PTA1                Y         PTA1          PSX slave select (SPI SS)        
//  23   PTB0/AD1P0          Y         AD1P0         battery voltage
//  24   PTB1/AD1P1          Y         PTB1          RED_LED
//  25   PTB2/AD1P2          Y         PTB2          GREEN_LED
//  26   PTB3/AD1P3          N         
//  27   PTD0/AD1P8          Y         PTD0          BLUE_SWITCH_1
//  28   PTD1/AD1P9          Y         PTD1          BLUE_SWITCH_2
//  29   Vddad               *
//  30   Vssad               *
//  31   PTD2/KBI1P5/AD1P10  Y         PTD2          BLUE_SWITCH_4
//  32   PTD3/KBI1P6/AD1P11  Y         PTD3          BLUE_SWITCH_8
//  33   PTG3/KBI1P3         N
//  34   Vrefh               *
//  35   Vrefl               *
//  36   BKGD/MS             *
//  37   PTG5/XTAL           -
//  38   PTG6/EXTAL          -
//  39   Vss                 *
//  40   PTC0/SCL1           Y         SCL1          RED_SWITCH_1
//  41   PTC1/SDA1           Y         SDA1          RED_SWITCH_2
//  42   PTC2/MCLK           Y         PTC2          RED_SWITCH_4
//  43   PTC3/TxD2           Y         PTC3          RED_SWITCH_8
//  44   PTC5/RxD2           N        
//
//----------------------------------------------------------------------------
// Current spare lines
// ===================
//
//  Pin  Name               Used     Feature         Description
//   4   PTF0/TPM1CH2        N         
//   5   PTF1/TPM1CH3        N         
//   6   PTF4/TPM2CH0        N          
//   7   PTF5/TPM2CH1        N
//  10   PTE2/TPM1CH0        N
//  11   PTE3/TPM1CH1        N
//  18   PTG0/KBI1P0         N                  
//  19   PTG1/KBI1P1         N      
//  26   PTB3/AD1P3          N         
//  33   PTG3/KBI1P3         N
//  44   PTC5/RxD2           N        
//
//----------------------------------------------------------------------------
// Analogue channel listing
// ========================
//
//   Channel     Name               Pin      Description
//   =======     ====               ===      ===========
//      0      PTB0/AD1P0            23      Battery voltage
//
//----------------------------------------------------------------------------
// Pin assignment for each of the digital I/O ports
//
// PTDA   0     Cypress SS          PTA0                // [21][Output]    
//        1     PSX SS              PTA1                // [22][Output]
//        - 
//        - 
//        - 
//        - 
//        - 
//        - 
//
#define     PORTA_DIR       0b11111111 
#define     PORTA_PULLUP    0b00000000
#define     PORTA_SLEWRATE  0b00000000
#define     PORTA_OUT_DRIVE 0b11111111 
#define     PORTA_INIT      0b00000011 
//----------------------------------------------------------------------------
// PTDB   0     BATTERY_VOLTS       PTB0_AD1P0          // [23][analogue]
//        1     RED_LED             PTB1_AD1P1          // [24][Output]
//        2     GREEN_LED           PTB2_AD1P2          // [25][Output]
//        3     ---
//        - 
//        - 
//        - 
//        -  
//
#define     PORTB_DIR           0b00000110
#define     PORTB_PULLUP        0b00000000
#define     PORTB_SLEWRATE      0b00000000
#define     PORTB_OUT_DRIVE     0b11111111  
#define     PORTB_INIT          0b00000000 
#define     PORTB_AD_CHAN_0_7   0b00000001 
//----------------------------------------------------------------------------
// PTDC   0     RED_SWITCH_1        PTC0_SCL1           // [40][Input]
//        1     RED_SWITCH_2        PTC2_SDA1           // [41][Input]
//        2     RED_SWITCH_4        PTC2_MCLK           // [42][Input]
//        3     RED_SWITCH_8        PTC3_TxD2           // [43][Input]
//        -                        
//        5 
//        - 
//        -     
//
#define     PORTC_DIR       0b01000000
#define     PORTC_PULLUP    0b00111100
#define     PORTC_SLEWRATE  0b00000000
#define     PORTC_OUT_DRIVE 0b11111111   
#define     PORTC_INIT      0b00000000
//----------------------------------------------------------------------------
// PTDD   0     BLUE_SWITCH_1       PTD0_AD1P8          // [27][Input]
//        1     BLUE_SWITCH_2       PTD1_AD1P9          // [28][Input]
//        2     BLUE_SWITCH_4       PTD2_KBI1P5_AD1P10  // [31][Input]
//        3     BLUE_SWITCH_8       PTD3_KBI1P6_AD1P11  // [32][Input]
//        -     
//        -                        
//        -                        
//        -                        
//
#define     PORTD_DIR           0b00000000
#define     PORTD_PULLUP        0b00000000
#define     PORTD_SLEWRATE      0b00000000
#define     PORTD_OUT_DRIVE     0b11111111 
#define     PORTD_INIT          0b00000000
#define     PORTD_AD_CHAN_8_15  0b00000000   
//----------------------------------------------------------------------------
// PTDE   0                         PTE0/TxD1           // [ 8][Serial Tx]
//        1                         PTE1/RxD1           // [ 9][Serial Rx]
//        2                         PTE2_TPM1CH0        // [10][Input]
//        3                         PTE3_TPM1CH1        // [11][Input]  
//        -
//        -
//        -
//        -
//
#define     PORTE_DIR       0b00000000
#define     PORTE_PULLUP    0b00000000
#define     PORTE_SLEWRATE  0b00000000
#define     PORTE_OUT_DRIVE 0b11111111 
#define     PORTE_INIT      0b00000000  
//----------------------------------------------------------------------------
// PTDF   0                         PTF0_TPM1CH2        // [ 4][Input]    
//        1                         PTF1_TPM1CH3        // [ 5][Input]
//        -
//        -
//        4                         PTF4_TPM2CH0        // [ 6][Input]
//        5                         PTF4_TPM2CH1        // [ 7][Input]
//        -
//        -      
//
#define     PORTF_DIR       0b00000000
#define     PORTF_PULLUP    0b00000000
#define     PORTF_SLEWRATE  0b00000000
#define     PORTF_OUT_DRIVE 0b11111111   
#define     PORTF_INIT      0b00000000
//----------------------------------------------------------------------------
// PTDG   0                         PTG0_KBI1P0         // [18][Input]     
//        1                         PTG1_KBI1P1         // [19][Input]
//        2                         PTG2_KBI1P2         // [20][Input]
//        3                         PTG3_KBI1P3         // [33][Input]
//        -                                            
//        5                         PTG5_XTAL           // [37][Input]
//        6                         PTG6_EXTAL          // [38][Input]
//        -                                             
//
#define     PORTG_DIR       0b00000000
#define     PORTG_PULLUP    0b00000000
#define     PORTG_SLEWRATE  0b00000000
#define     PORTG_OUT_DRIVE 0b11111111 
#define     PORTG_INIT      0b00000000  

