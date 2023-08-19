/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
   dsPIC33CH + Curiosity board - Timers demos

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33  MCUs - 1.171.3
        DFP: dsPIC33CH-MP_DFP v1.12.352
        Device            :  dsPIC33CH512MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05 (actual 6.10 + Updates)
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
// definition of __delay32() __delay_us(), __delay_ms()
// requires proper macro FCY, we use _XTAL_FREQ from mcc_generated_files/system.h
#define FCY (_XTAL_FREQ/2UL)
#include <libpic30.h>
#include <stdio.h> // printf(3) to UART

// Application version times 100: 123 => Version 1.23
#define HP_APP_VERSION 101

// counter/divider by 100
volatile uint16_t gCounter100 = 0;
volatile uint16_t gCounter = 0; 

// Timer1 callback, called at 1 kHz rate
void TMR1_CallBack(void)
{
    TMR1_OVFLOW_Toggle(); // RB11
    gCounter++;
    gCounter100++;
    if (gCounter100 >= 100){
        // NOTE: We don't use just if(gCounter%100 == 0){ ... }
        // because it will work incorrectly on value wrap 65535 -> 0
        gCounter100 = 0;
        RED_LED1_Toggle(); // toggle RED LED1 at 10 Hz rate => frequency 5 Hz
    }
}

// value must be known at compile time
#define HP_MAIN_DELAY_MS 1000
/*
                         Main application
 */
int main(void)
{
    unsigned i=0;
    unsigned oldMs=0,nowMs=0;
    // initialize the device
    SYSTEM_Initialize();
    //Remember to setup USB CDC with these parameters:
    // BaudRate: 115'200, 8-data bits, Odd parity, flow-control: None
    printf("MASTER: startup %s:%d %s(): v%d:%02d %s\r\n",
            __FILE__,__LINE__,__func__,HP_APP_VERSION/100,HP_APP_VERSION%100,
            __DATE__);
    // loop forever
    for(i=0;;i++)
    {
        nowMs = gCounter;
        printf("  i=%u Total=%u [ms] Delta=%u [ms]\r\n",
                i,nowMs,nowMs-oldMs);
        oldMs = nowMs;
        // rotate LEDs at 1s rate: Red -> Green -> Blue -> All off
        RGB_RED_SetHigh();
        __delay_ms(HP_MAIN_DELAY_MS);
        RGB_RED_SetLow();RGB_GREEN_SetHigh();
        __delay_ms(HP_MAIN_DELAY_MS);
        RGB_GREEN_SetLow();RGB_BLUE_SetHigh();
        __delay_ms(HP_MAIN_DELAY_MS);
        RGB_BLUE_SetLow();
        __delay_ms(HP_MAIN_DELAY_MS);
    }
    return 1; 
}
/**
 End of File
*/

