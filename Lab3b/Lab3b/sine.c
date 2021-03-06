/*************************************************************************************
			       DEPARTMENT OF ELECTRICAL AND ELECTRONIC ENGINEERING
					   		     IMPERIAL COLLEGE LONDON 

 				      EE 3.19: Real Time Digital Signal Processing
					       Dr Paul Mitcheson and Daniel Harvey

				        LAB 2: Learning C and Sinewave Generation 

 				             ********* S I N E . C **********

             	Demonstrates outputing data from the DSK's audio port. 
   			  Used for extending knowledge of C and using look up tables.

 *************************************************************************************
  				Updated for use on 6713 DSK by Danny Harvey: May-Aug 06/Dec 07/Oct 09
				CCS V4 updates Sept 10
 ************************************************************************************/
/*
 *  Initialy this example uses the AIC23 codec module of the 6713 DSK Board Support
 *  Library to generate a 1KHz sine wave using a simple digital filter. 
 *	You should modify the code to generate a sine of variable frequency.
 */
/**************************** Pre-processor statements ******************************/

//  Included so program can make use of DSP/BIOS configuration tool.  
#include "dsp_bios_cfg.h"

/* The file dsk6713.h must be included in every program that uses the BSL.  This 
   example also includes dsk6713_aic23.h because it uses the 
   AIC23 codec module (audio interface). */
#include "dsk6713.h"
#include "dsk6713_aic23.h"

// math library (trig functions)
#include <math.h>

// Some functions to help with configuring hardware
#include <helper_functions_ISR.h>

// PI defined here for use in your code 
#define PI 3.141592653589793

// Define variable for size of look up table
#define SINE_TABLE_SIZE 256

/******************************* Global declarations ********************************/

/* Audio port configuration settings: these values set registers in the AIC23 audio 
   interface to configure it. See TI doc SLWS106D 3-3 to 3-10 for more info. */
DSK6713_AIC23_Config Config = { \
			 /**********************************************************************/
			 /*   REGISTER	            FUNCTION			      SETTINGS         */ 
			 /**********************************************************************/\
    0x0017,  /* 0 LEFTINVOL  Left line input channel volume  0dB                   */\
    0x0017,  /* 1 RIGHTINVOL Right line input channel volume 0dB                   */\
    0x01f9,  /* 2 LEFTHPVOL  Left channel headphone volume   0dB                   */\
    0x01f9,  /* 3 RIGHTHPVOL Right channel headphone volume  0dB                   */\
    0x0011,  /* 4 ANAPATH    Analog audio path control       DAC on, Mic boost 20dB*/\
    0x0000,  /* 5 DIGPATH    Digital audio path control      All Filters off       */\
    0x0000,  /* 6 DPOWERDOWN Power down control              All Hardware on       */\
    0x0043,  /* 7 DIGIF      Digital audio interface format  16 bit                */\
    0x008d,  /* 8 SAMPLERATE Sample rate control             8 KHZ                 */\
    0x0001   /* 9 DIGACT     Digital interface activation    On                    */\
			 /**********************************************************************/
};


// Codec handle:- a variable used to identify audio interface  
DSK6713_AIC23_CodecHandle H_Codec;

/* Sampling frequency in HZ. Must only be set to 8000, 16000, 24000
32000, 44100 (CD standard), 48000 or 96000  */ 
int sampling_freq = 8000;

// Keep track of which sample we're on
float sample_number = 0;

// Holds the value of the current sample 
float sample;
float wave;
int rectify = 0;

// Define Output Gain
#define GAIN 32000

/* Use this variable in your code to set the frequency of your sine wave 
   be carefull that you do not set it above the current nyquist frequency! */
float sine_freq = 1000.0;

//Create table to store sine values
float table[SINE_TABLE_SIZE];
     
/******************************* Function prototypes ********************************/
void init_hardware(void);
void init_HWI(void);
void init_sine(void);
void ISR_SINEOUT(void);  
//float sinegen(void);
/********************************** Main routine ************************************/
void main()
{

	// initialize board and the audio port
	init_hardware();
	
	init_HWI();
	
	// initialize the table of sine values
	init_sine();

    // Loop endlessley generating a sine wave 
   while(1){};

}

/******************************* init_sine() ****************************************/
void init_sine()
{
	/* Function to populate the values in the sine table */
	int i;
	for(i=0; i<=SINE_TABLE_SIZE; i++){
			table[i] = sin((2 * PI * i)/SINE_TABLE_SIZE);
	};
}


/******************************* init_hardware() ************************************/
void init_hardware()
{
    // Initialize the board support library, must be called first 
    DSK6713_init();
    
    // Start the codec using the settings defined above in config 
    H_Codec = DSK6713_AIC23_openCodec(0, &Config);

	/* Defines number of bits in word used by MSBSP for communications with AIC23
	 NOTE: this must match the bit resolution set in in the AIC23 */
	MCBSP_FSETS(XCR1, XWDLEN1, 32BIT);	
	MCBSP_FSETS(SPCR1, XINTM, FRM);

}

/********************************* init_HWI() ***************************************/
void init_HWI(void)
{
	IRQ_globalDisable();			// Globally disables interrupts
	IRQ_nmiEnable();				// Enables the NMI interrupt (used by the debugger)
	IRQ_map(IRQ_EVT_XINT1,4);		// Maps an event to a physical interrupt
	IRQ_enable(IRQ_EVT_XINT1);		// Enables the event
	IRQ_globalEnable();				// Globally enables interrupts

}

void ISR_SINEOUT(void)
{
	// Calculate number of samples per complete sine wave
	float sample_count = sampling_freq/sine_freq;
	
	// Calculate the next look up table element to be returned
	sample_number = ((sample_number + (SINE_TABLE_SIZE/sample_count)));
	
	if (sample_number > SINE_TABLE_SIZE) sample_number -= SINE_TABLE_SIZE;
	
	// Return sine table element corresponding to this sample
	wave = table[(int)sample_number] * GAIN;
	
	if (rectify) 
		{sample = abs(wave);}
	else
		{sample = wave;}
	
	mono_write_16Bit(sample);
	
}

