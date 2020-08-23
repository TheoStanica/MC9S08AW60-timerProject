#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#define VNTimer 11 /* Interrupt vector for Timer */ 

typedef	unsigned char	uint8;
typedef	unsigned short	uint16;
typedef	unsigned long	uint32;

typedef	char			int8;
typedef	short			int16;
typedef	long			int32;

// To Clear or Set single bits in a byte variable.
#define	b_SetBit(bit_ID, varID)		(varID |= (uint8)(1<<bit_ID))
#define	b_ClearBit(bit_ID, varID)	(varID &= ~(uint8)(1<<bit_ID))
#define	b_XorBit(bit_ID, varID)		(varID ^= (uint8)(1<<bit_ID))

// To Clear or Set single bits in a word(16-bit) variable.
#define	w_SetBit(bit_ID, varID)		(varID |= (uint16)(1<<bit_ID))
#define	w_ClearBit(bit_ID, varID)	(varID &= ~(uint16)(1<<bit_ID))
#define	w_XorBit(bit_ID, varID)		(varID ^= (uint16)(1<<bit_ID))

// To check single bit status in a given variable in ZERO PAGE
#define	b_CheckBit(varID, bit_ID)	((varID & (uint8)(1<<bit_ID))?1:0)
//#define	b_CheckBit(varID, bit_ID)	(varID & (muint8)(1<<bit_ID))
#define	w_CheckBit(varID, bit_ID) ((varID & (uint16)(1<<bit_ID))?1:0)

// To check single bit status in a given variable in ZERO PAGE
#define		DummyRead(varID)			{__asm lda varID;}

int led_no=0;


void init(void);

void main(void) {
  EnableInterrupts;
  /* include your code here */
  init();
  

  while(1) {
//    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

interrupt VNTimer void TPM1_overflow()
{ 
	//i use a global variable to turn on specific LEDs depending on the variable value. I update the variable before finishing the
	//interrupt to have the variable ready for the next interrupt.
		
	byte varTOF; 
	varTOF = TPM1SC_TOF; // clear TOF; first read and then write 0 to the flag
	TPM1SC_TOF = 0;
	if(led_no == 0){
			PTFD = 0x0;
			PTFD_PTFD0=1;
		}
		if(led_no == 1){
			PTFD = 0x0;
			PTFD_PTFD1=1;
			}
		if(led_no == 2){
			PTFD = 0x0;
			PTFD_PTFD2=1;
			}
		if(led_no == 3){
			PTFD = 0x0;
			PTFD_PTFD3=1;
			}
		if(led_no == 4){
			PTFD = 0x0;
			PTFD_PTFD4=1;
			}
		if(led_no == 5){
			PTFD = 0x0;
			PTFD_PTFD5=1;
			}
		if(led_no == 6){
			PTFD = 0x0;
			PTFD_PTFD6=1;
			}
		if(led_no == 7){
			PTFD = 0x0;
			PTFD_PTFD7=1;
			}
		
		// if last LED has been turned on, I "reset" the animation to start again
		if(led_no == 7){
			led_no = 0;
		}
		else{
			led_no += 1;
		}
	
	
}

void init(){
	
	SOPT = 0x00;   			//disable watchdog
		
	
	
//	ICGC2 = 0b00000000; // Set up ICG control register 2
//	ICGC1 = 0X78; // Set up ICG for FEE, 4MHz external crystal
		 //0111 1000   // busclk = 8MHz
	// even when setting this, on the chip it still says 4MHz busclk. I tried different settings,
	//clock speed does not seem to change. I do not know why this is not working.


	TPM1SC = 0b01001011;	//b7- 0 
							//b6 - 1
							//b5 - 0
							//b4:3 = 01 (select bus rate clock)
							//b2:0 = 011 (in the course example we used 111 to simulate 1 second(62500 counter overflow) 
							//            but in the simulator, same config results in aprox 16seconds simulated
							//			 So i decided to use a smaller divisor.(128/16 = 8 ->b2:0= 011) 
			
	
	//set overflow value to 62500
	TPM1MODH = 0xF4;
	TPM1MODL = 0x24;
	
	
	PTFDD = 0xFF;  			//set all port F pins as output
		PTFD = 0x0; 			//turn off all LEDs
	
}
