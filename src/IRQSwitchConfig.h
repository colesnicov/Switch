/**
 * This file is a part of IRQSwitch library for embedded devices.
 *
 * File:		IRQSwitchconfig.h
 * Created on:	29.03.2019
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 */

/** UPDATES **
 *
 * 29.03.2019 - 2.5.1
 *  - Definice jsou presunuty do samostatneho souboru 'IRQSwitchConfig.h'
 *
 * 05.02.2020 - 2.7.0
 *  - Ve vychozim nastaveni jsou vsechny moznosti zapnute.
 *
 * 12.02.2020 - 2.8.0
 *	- Nove definice pro arduino handler
 *  - Odstranene definice:
 *    - IRQSWITCH_DEBUG
 *    - IRQSWITCH_NAME_LENGTH
 *    - IRQSWITCH_HANDLER_CHECK_COUNT
 *    - IRQSWITCH_HANDLER_MAX_BUTTONS
 *  - Zmenena hodnota definice IRQSWITCH_IMPLEMENT_CLICK_COUNT ze 100 na 3
 */

#ifndef SRC_IRQSWITCHCONFIG_H_
#define SRC_IRQSWITCHCONFIG_H_

/**
 * Library version.
 */
#define IRQSwitch_Version "2.8.0"

#define IRQSWITCH_ARDUINO	1

#ifdef IRQSWITCH_ARDUINO

#include "Arduino.h"

#define IRQSWITCH_CLICK	LOW

#endif

/**
 * Maximum count of characters in name string.
 */
#define IRQSWITCH_TIME_DEBOUNCE			40


/**
 * Set 1 if you wanna have a hold BUTTON functionality, otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_HELD	1

/**
 * Set 1 if you wanna have a time of hold BUTTON in milliseconds functionality, otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME	1

/**
 * Set (nums of clicks) if you wanna have Click Counter functionality. otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_COUNT 3


/////////
///
/// Check configurations.
///
/////////

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME and !IRQSWITCH_IMPLEMENT_CLICK_HELD
#error "Not allowed, You must enable the 'Keep button pressed' (see IRQSWITCH_IMPLEMENT_CLICK_HELD) feature."
#endif

#endif /* SRC_IRQSWITCHCONFIG_H_ */








