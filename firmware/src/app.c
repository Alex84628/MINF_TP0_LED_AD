/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data*/
APP_DATA appData;

// definitions des LED pour le switch case du chenillard
#define LED0 0 //LED0
#define LED1 1 //LED1
#define LED2 2 //LED2
#define LED3 3 //LED3
#define LED4 4 //LED4
#define LED5 5 //LED5
#define LED6 6 //LED6
#define LED7 7 //LED7
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************
void APP_Initialize ( void )
{
    appData.state = APP_STATE_INIT;//le systeme passe en mode initialisation   
}
// *****************************************************************************
// *****************************************************************************
// fonction tasks qui realise les differente tache du programme
// *****************************************************************************
// *****************************************************************************

void APP_Tasks ( void )
{
    //déclaration des variables
    static uint32_t PremiereFois = 0;       //Cette variable se trouve dans un if qui permet au programme d'effectuer qu'une seule fois l'action
    static uint32_t compteurChenillard = 0; //Compteur du chennilard
    S_ADCResults adc;                       //Variables qui stocke les valeurs ADC
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        case APP_STATE_INIT: //Dans ce case on est en mode démarrage du proggrame et effectue differente initialisation
        {
            BSP_LEDInit();                  //Appelle de fonction d'initialisation des LED
            APP_initialize();               //Appelle la fonction d'initialisation de l'ADC et le LCD
            lcd_bl_on();                    //Allume l'ecran du LCD
            printf_lcd("Tp0 Led+AD 2026");  //Ecris sur le LCD 
            lcd_gotoxy(1,2);                //Change la position a la deuxieme ligne du LCD
            printf_lcd("Alexandre Rabald"); //Ecris sur le LCD            
            AllumerLed();                   //appel la fonction allumer LED                                                         
            DRV_TMR0_Start();               //Le timer demarre
            appData.state = APP_STATE_WAIT; //Le systeme passe en mode attante
            break;
        }
        case APP_STATE_WAIT: //Dans ce case le programme attend une interuption
        {
            //ne se passe rien, en attante de l'interuption   
            break;
        }              
        case APP_STATE_SERVICE_TASKS://Dans ce case le programme effectue ses differentes instructions
        {
            if (PremiereFois == 0)  //effectue ces instruction une seule fois
            {
                EteindreLed();      //Appelle la fonction qui eteint les LEDS
                PremiereFois = 1;   //La variable passe à 1 le programme ne retournera plus dans le IF
            }
            lcd_gotoxy(1,3);        //Change la position a la troisieme ligne du LCD
            adc = BSP_ReadAllADC(); //Lis les ADC et enregistre les valeur dans ADC
            printf_lcd("CH0=%4d CH1=%4d", adc.Chan0, adc.Chan1); //Affichie les valeur des ADC sur le LCD            
            if(compteurChenillard == 0)     //Si le compteur du chennillard est à 0
            {                
                compteurChenillard++;       //Incrémentation du compteur du chennillard
            }
            else //Sinon
            {
                chennilard();               //Appelle de la fonction chennillard
                compteurChenillard = 0;     //reset du compteur du chennillard
            }            
            appData.state = APP_STATE_WAIT; //Le systeme passe en mode attante
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
// *****************************************************************************
// *****************************************************************************
// Fonction call back : le systeme passe en mode service tasks
// *****************************************************************************
// *****************************************************************************
void APP_TMR_Callbck(void)
{
    appData.state = APP_STATE_SERVICE_TASKS;
}
// *****************************************************************************
// *****************************************************************************
// Fonction Initialisation : Initialise l'ADC et le LCD
// *****************************************************************************
// *****************************************************************************
void APP_initialize(void)
{
    lcd_init();      //Initialise l'LCD
    BSP_InitADC10(); //Initialise l'ADC   
}
// *****************************************************************************
// *****************************************************************************
// Fonction chennillard : Allume les LED de D6 à D13 une par une.
// *****************************************************************************
// *****************************************************************************
void chennilard(void)
{
    static uint32_t chillardLed = 0;
       
    switch (chillardLed)
    {
        case LED0:              
            BSP_LEDOff(BSP_LED_7); //Eteind la LED 7   
            BSP_LEDOn(BSP_LED_0);  //Allume la LED 0
            chillardLed++;         //Incrémente de 1 le compteur 
            break;
        case LED1:
            BSP_LEDOff(BSP_LED_0); //Eteind la LED 0  
            BSP_LEDOn(BSP_LED_1);  //Allume la LED 1
            chillardLed++;         //Incrémente de 1 le compteur 
           break;
        case LED2:
            BSP_LEDOff(BSP_LED_1); //Eteind la LED 1    
            BSP_LEDOn(BSP_LED_2);  //Allume la LED 2
            chillardLed++;         //Incrémente de 1 le compteur 
            break;
        case LED3:
            BSP_LEDOff(BSP_LED_2); //Eteind la LED 2    
            BSP_LEDOn(BSP_LED_3);  //Allume la LED 3
            chillardLed++;         //Incrémente de 1 le compteur 
           break;
        case LED4:
            BSP_LEDOff(BSP_LED_3); //Eteind la LED 3    
            BSP_LEDOn(BSP_LED_4);  //Allume la LED 4
            chillardLed++;         //Incrémente de 1 le compteur  
            break;
        case LED5:
            BSP_LEDOff(BSP_LED_4); //Eteind la LED 4    
            BSP_LEDOn(BSP_LED_5);  //Allume la LED 5
            chillardLed++;         //Incrémente de 1 le compteur 
            break;
        case LED6:
            BSP_LEDOff(BSP_LED_5); //Eteind la LED 5    
            BSP_LEDOn(BSP_LED_6);  //Allume la LED 6
            chillardLed++;         //Incrémente de 1 le compteur 
            break;
        case LED7:
            BSP_LEDOff(BSP_LED_6); //Eteind la LED 6    
            BSP_LEDOn(BSP_LED_7);  //Allume la LED 7
            chillardLed = 0;       //Remts à 0 le compteur
            break;
    }
}
// *****************************************************************************
// *****************************************************************************
// Fonction Eteindre LED : Elle permet d'eteindre les led de D6 à D13
// *****************************************************************************
// *****************************************************************************
void EteindreLed(void)
{
    BSP_LEDOff(BSP_LED_0); //Eteind la LED 0
    BSP_LEDOff(BSP_LED_1); //Eteind la LED 1
    BSP_LEDOff(BSP_LED_2); //Eteind la LED 2
    BSP_LEDOff(BSP_LED_3); //Eteind la LED 3
    BSP_LEDOff(BSP_LED_4); //Eteind la LED 4
    BSP_LEDOff(BSP_LED_5); //Eteind la LED 5
    BSP_LEDOff(BSP_LED_6); //Eteind la LED 6
    BSP_LEDOff(BSP_LED_7); //Eteind la LED 7 
}
// *****************************************************************************
// *****************************************************************************
// Fonction Allumer LED : Elle permet d'allumer les led de D6 à D13
// *****************************************************************************
// *****************************************************************************
void AllumerLed(void)
{
    BSP_LEDOn(BSP_LED_0); //Allume la LED 0
    BSP_LEDOn(BSP_LED_1); //Allume la LED 1
    BSP_LEDOn(BSP_LED_2); //Allume la LED 2
    BSP_LEDOn(BSP_LED_3); //Allume la LED 3
    BSP_LEDOn(BSP_LED_4); //Allume la LED 4
    BSP_LEDOn(BSP_LED_5); //Allume la LED 5
    BSP_LEDOn(BSP_LED_6); //Allume la LED 6
    BSP_LEDOn(BSP_LED_7); //Allume la LED 7  
}
/*******************************************************************************
 End of File
 */
