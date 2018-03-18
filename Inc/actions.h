/**
 * @file    actions.h
 * @author  Jeremy ROULLAND
 * @date    13 mar. 2018
 * @brief   Actions (Simple, Complex, Control, ...)
 */

/**
 *    CMD     | OPCOD | / | L | DATA0   DATA1   DATA2   DATA3      |    Comments
 * Get Inputs	0x05	R	16	Input 1	Input 2	Input 3	Input 4			Ana : 0 à 255	TOR : 0 ou 255
 * Set angle	0x10	W	2	unit	angle					        0 : 1ms  255 : 2ms
 *
 */

#ifndef INC_ACTIONS_H_
#define INC_ACTIONS_H_

#include "stdint.h"

void Actions_Process(void);

void EmergencyStop(uint8_t len, uint8_t *buff);



#endif /* INC_ACTIONS_H_ */
