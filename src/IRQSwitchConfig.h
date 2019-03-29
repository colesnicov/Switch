/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitchconfig.h
 * Created on:	29.03.2019
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.5.1
 */

/** UPDATES **
 *
 * 29.03.2019 - 2.5.1
 *  - Definice jsou presunuty do samostatneho souboru 'IRQSwitchConfig.h'
 *
 */

#ifndef SRC_IRQSWITCHCONFIG_H_
#define SRC_IRQSWITCHCONFIG_H_

/**
 * Library version.
 */
#define IRQSwitch_Version "2.5.1"

/**
 * This set maximum of buttons to manage.
 * Defaults is 12.
 */
#ifndef IRQSWITCH_HANDLER_MAX_BUTTONS
#define IRQSWITCH_HANDLER_MAX_BUTTONS	12
#endif

/**
 * This indicate, if you want, to check buttons count in manage before added new one.
 */
#ifndef IRQSWITCH_HANDLER_CHECK_COUNT
#define IRQSWITCH_HANDLER_CHECK_COUNT	0
#endif

#ifndef IRQSWITCH_DEBUG
/**
 * Set to 1 if you have more memory!! See the code.
 */
#define IRQSWITCH_DEBUG					1
#endif

#ifndef IRQSWITCH_NAME_LENGTH
/**
 * Maximum count of characters in name string.
 */
#define IRQSWITCH_NAME_LENGTH			10
#endif

#ifndef IRQSWITCH_IMPLEMENT_CLICK_HELD
/**
 * Set 1 if you wanna have a hold BUTTON functionality, otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_HELD	1
#endif

#ifndef IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME
/**
 * Set 1 if you wanna have a time of hold BUTTON in milliseconds functionality, otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME	1
#endif

#ifndef IRQSWITCH_IMPLEMENT_CLICK_COUNT
/**
 * Set (nums of clicks) if you wanna have Click Counter functionality. otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_COUNT 100
#endif

#ifndef IRQSWITCH_HANDLER_DEFAULT_INPUT_type
/**
 * Default internal (in the MCU) pin matrix type. Eg. INPUT, INPUT_PULLUP.
 */
#define IRQSWITCH_DEFAULT_INPUT_TYPE	INPUT_PULLUP
#endif

/////////
///
/// Check configurations.
///
/////////

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME and !IRQSWITCH_IMPLEMENT_CLICK_HELD
#error "Not allowed, You must enable the 'Keep button pressed' (see IRQSWITCH_IMPLEMENT_CLICK_HELD) feature."
#endif

#endif /* SRC_IRQSWITCHCONFIG_H_ */
