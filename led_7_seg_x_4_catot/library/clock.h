/*
 * clock.h
 *
 *  Created on: 27-09-2017
 *      Author: KILLER
 */
static char clk_sec = 0, clk_minu = 0, clk_hour = 11, dem_clk = 0;

#ifndef CLOCK_H_
#define CLOCK_H_

void config_clock_MHz(unsigned char CLOCK_CHOSE);
void config_timerA0(void);
void config_timerA1(void);


#endif /* CLOCK_H_ */
