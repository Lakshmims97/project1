/*============================================================================*/
/* System Controller                                                          */
/*============================================================================*/
/*!
* \file     SystemController.c
* \brief    This module provides the overall controll of the system. Dealing
*           with Massaging etc.
*
* \copyright    Datasol Innovative Labs
* \author       Rajath K S
* \date         25th Feburary 2019 (first created)
*=============================================================================*/

/*============================================================================*/
/* INCLUDES                                                                   */
/*============================================================================*/
#include "SYSTEMCONTROLLER.h"


/*============================================================================*/
/* LOCAL DEFINITIONS                                                          */
/*============================================================================*/

/*! The maximum number of steps in an experience*/

/*! The maximum number of valves in the system (including primary valve)*/



/*============================================================================*/
/* LOCAL TYPES                                                                */
/*============================================================================*/




/*! The possible operating states of the system controller */
enum IRSENSORSTATES
{
	IRSENSOR_PRESENCEDETECT,
	IRSENSOR_READSTATE,
	IRSENSOR_PROCESSSTATE,
	IRSENSOR_DEVICEIDLE,
};


/*============================================================================*/
/* LOCAL FUNCTION PROTOTYPES                                                  */
/*============================================================================*/




/*============================================================================*/
/* LOCAL VARIABLES                                                            */
/*============================================================================*/
static unsigned char IRSENSORSTATES;
static unsigned int power;
static unsigned int temp;
static unsigned int b;

sbit led=P0^1;
sbit buzzer=P0^2;
sbit reset=P0^3;


/*============================================================================*/
/* PUBLIC FUNCTIONS                                                           */
/*============================================================================*/

/*----------------------------------------------------------------------------*/
/* SystemControllerInit                                                       */
/*----------------------------------------------------------------------------*/
/*! Set up the module ready for use.
*
*
*-----------------------------------------------------------------------------*/
void SystemControllerInit(void)
{

}

void SystemControlHandler(void)
{
      switch(IRSENSORSTATES)
	{


		case(IRSENSOR_PRESENCEDETECT):
			    power=1;
		     if(power!=0)
		     {
			     IRSENSORSTATES=IRSENSOR_READSTATE;
		     }
		    else
		     {
			     IRSENSORSTATES=IRSENSOR_DEVICEIDLE;
		     }
	    break;

		case(IRSENSOR_READSTATE):
				temp=***;// value of temperature
		        b=temp;
		    if(b<=380)
		    {
			    IRSENSORSTATES=IRSENSOR_PROCESSSTATE;
		    }
		   else
		    {
			    IRSENSORSTATES=IRSENSOR_DEVICEIDLE;
		    }
		break;

		case(IRSENSOR_PROCESSSTATE):
				temp=***;
		        b=temp;
		   if(b<=380)
		   {
		 	    reset=1;
			    led=1;//green light indication
			    lcddata('###');//display actual temperature
			    reset=0;//reset temperature value
		   if(reset!=1)
		   {
			   IRSENSORSTATES=IRSENSOR_PRESENCEDETECT;
		   }
		   }
		else
		   {
		        reset=1;
		        led=0;// no light indication
		        lcddata('###');//display actual temperature
		        buzzer=1;//alarm indication and disallow entry of person
		        reset=0;
		        if(reset!=1)
		       		   {
		       			   IRSENSORSTATES=IRSENSOR_PRESENCEDETECT;
		       		   }
		   }
	    break;

		case(IRSENSOR_DEVICEIDLE):
			  power=0;
		   if(power!=1)
			{
			    IRSENSORSTATES=IRSENSOR_DEVICEIDLE;
		    }
		break;

		default:
			IRSENSORSTATES=IRSENSOR_DEVICEIDLE;
		break;
	}
}


