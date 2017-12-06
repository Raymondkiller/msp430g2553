#include <msp430g2553.h>

#include "uart.h"
#define WDT_meas_setting    (WDT_MDLY_8)        // watchdog interval = 0.5 ms

int base_cap[4];                                // Baseline capacitance for each pad

struct Element{                                    // This structure contains informations of sensor pad
    unsigned char *Pxsel;                        // Pointer to Pxsel register
    unsigned char *Pxsel2;                        // Pointer to Pxsel2 register
    unsigned char *Pxdir;                        // Pointer to Pxdir register
    unsigned char *Pxout;                        // Pointer to Pxout register
    unsigned char inputBits;                    // Input bit
    int *baseline;                                // Pointer to baseline capacitance
};
//*************************************************************************
// Define sensor pad element
//*************************************************************************
const struct Element KEY_1 = {
        .Pxsel = (unsigned char *)&P1SEL,
        .Pxsel2 = (unsigned char *)&P1SEL2,
        .Pxdir = (unsigned char *)&P1DIR,
        .inputBits = BIT3,
        .baseline = &base_cap[0]
};

const struct Element KEY_2 = {
        .Pxsel = (unsigned char *)&P1SEL,
        .Pxsel2 = (unsigned char *)&P1SEL2,
        .Pxdir = (unsigned char *)&P1DIR,
        .inputBits = BIT4,
        .baseline = &base_cap[1]
};

const struct Element KEY_3 = {
        .Pxsel = (unsigned char *)&P1SEL,
        .Pxsel2 = (unsigned char *)&P1SEL2,
        .Pxdir = (unsigned char *)&P1DIR,
        .inputBits = BIT5,
        .baseline = &base_cap[2]
};

const struct Element KEY_4 = {
        .Pxsel = (unsigned char *)&P1SEL,
        .Pxsel2 = (unsigned char *)&P1SEL2,
        .Pxdir = (unsigned char *)&P1DIR,
        .inputBits = BIT6,
        .baseline = &base_cap[3]
};

const struct Element KEY_5 = {
        .Pxsel = (unsigned char *)&P1SEL,
        .Pxsel2 = (unsigned char *)&P1SEL2,
        .Pxdir = (unsigned char *)&P1DIR,
        .inputBits = BIT7,
        .baseline = &base_cap[3]
};

const struct Element *KEY[] = {&KEY_1, &KEY_2, &KEY_3, &KEY_4, &KEY_5};    // Define Element pointer array

//*************************************************************************
// Program subroutines
//*************************************************************************
void base_calib(void){                        // Measure the baseline capacitance each pad
    char i;
    for(i = 0; i < 5; i++){
        base_cap[i] = measure_count(*KEY[i]);
    }
}
//------------------------------------------------------------------------
int measure_count(struct Element pad){        // Measure raw capacitance
    int meas_cnt;
    TA0CTL = TASSEL_3 + MC_2;              // TACLK, continous mode
    TA0CCTL1 = CM_3 + CCIS_2 + CAP;        // Pos & Neg, GND, capture mode

    *(pad.Pxsel) &= ~pad.inputBits;            // TACLK input
    *(pad.Pxsel2) |= pad.inputBits;
    *(pad.Pxdir) &= ~pad.inputBits;            // input pins

    /*Setup Gate Timer*/
    WDTCTL = WDT_meas_setting;              // WDT, SMCLK, interval timer
    TA0CTL |= TACLR;                        // Clear Timer_A TAR
    __bis_SR_register(LPM0_bits+GIE);      // Wait for WDT interrupt
    meas_cnt = TA0CCR1;                    // Save result
    WDTCTL = WDTPW + WDTHOLD;              // Stop watchdog timer
    TA0CTL = MC_0;                            // Stop timer0
    *(pad.Pxsel2) &= ~pad.inputBits;
    return meas_cnt;
}
//------------------------------------------------------------------------
//*************************************************************************
// Main Program
//*************************************************************************
int main(void) {
    int delta_count;
    WDTCTL = WDTPW | WDTHOLD;                // Stop watchdog timer
    BCSCTL1 = CALBC1_16MHZ;                // Set DCO to 1MHz
    DCOCTL =  CALDCO_16MHZ;
    UART_Init();
    UART_Write_String("tuan");

    IE1 |= WDTIE;                          // Enable WDT interrupt
    base_calib();
    while(1){
    	__delay_cycles(500000);

        delta_count = *(KEY_1.baseline) - measure_count(KEY_1);
        if(delta_count > 100){                // If Key 2 is touched -> turned on LED 1
        	UART_Write_String("3");
        	__delay_cycles(100000);
        }
        delta_count = *(KEY_2.baseline) - measure_count(KEY_2);
        if(delta_count > 100){                // If Key 2 is touched -> turned on LED 1
        	UART_Write_String("4");
        	__delay_cycles(200000);
        }

        delta_count = *(KEY_3.baseline) - measure_count(KEY_3);
        if(delta_count > 100){                // If Key 2 is touched -> turned on LED 1
        	UART_Write_String("5");
        	__delay_cycles(200000);
        }

        delta_count = *(KEY_4.baseline) - measure_count(KEY_4);
        if(delta_count > 100){                // If Key 2 is touched -> turned on LED 1
        	UART_Write_String("6");
        	__delay_cycles(200000);
        }

        delta_count = *(KEY_5.baseline) - measure_count(KEY_5);
        if(delta_count > 100){                // If Key 2 is touched -> turned on LED 1
        	UART_Write_String("7");
        	__delay_cycles(200000);
        }

    }
    return 0;
}

//*************************************************************************
// Interrupt service routine
//*************************************************************************
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
    TA0CCTL1 ^= CCIS0;                        // Toggle CM0 to initiate capture
    __bic_SR_register_on_exit(LPM3_bits);  // Exit LPM3 on reti
}
