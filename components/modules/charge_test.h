/*
 * charge_test.h
 *
 *  Created on: Aug 19, 2019
 *      Author: wt
 */

#ifndef MODULES_CHARGE_TEST_H_
#define MODULES_CHARGE_TEST_H_

#include "gpio.h"
#include "package.h"

#define CHARGE_STATUS 0x34

typedef enum{
	no_charge = 0,
	charging = 1,
}charge_status_e;


void charge_test(void);

#endif /* MODULES_CHARGE_TEST_H_ */
