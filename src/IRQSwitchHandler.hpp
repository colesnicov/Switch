#pragma once

/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitchHandler.hpp
 * Created on:	28.03.2019
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.5.0
 */

/** UPDATES **
 * 28.03.2019 - 2.5.0
 *  - Pridani tridy 'IRQSwitchHandler'.
 *
 */

#include <IRQSwitch.hpp>
#include <stdint.h>


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

/**
 * Manage button to automatically changed states.
 */
class IRQSwitchHandler
{
public:

	/**
	 * Constructor
	 * Do nothing.
	 */
	IRQSwitchHandler();

	/**
	 * Destructor
	 * Destroy managed buttons!
	 */
	~IRQSwitchHandler();

	/**
	 * Add next button to manage.
	 *
	 * @param	b*	Pointer to button.
	 *
	 * @return	uint8_t	New ID of button. Or 0 if fail.
	 */
	uint8_t AddButton(IRQSwitch* b);

	/**
	 * Update states.
	 *
	 * @param ms Current time in milliseconds.
	 */
	void Update(uint32_t ms);

	/**
	 * Create new button to manage.
	 *
	 * @param name	Name of button. For DEBUG only. @see IRQSWITCH_DEBUG
	 * @param pin	Pin number.
	 *
	 * @return	uint8_t	New ID of button. Or 0 if fail.
	 */
	uint8_t CreateButton(char name[10], uint8_t pin);

	/**
	 * Create new button to manage.
	 *
	 * @param name	Name of button. For DEBUG only. @see IRQSWITCH_DEBUG
	 * @param pin	Pin number.
	 * @param type	INPUT or INPUT_PULLUP.
	 *
	 * @return	uin8_t	New ID of button. Or 0 if fail.
	 */
	uint8_t CreateButton(char name[10], uint8_t pin, uint8_t type);

	/**
	 * Get access to button.
	 * @param id	ID of button.
	 *
	 * @return	IRQSwitch*	Pointer to object.
	 */
	IRQSwitch* GetButton(uint8_t id);

private:

	IRQSwitch* m_buttons[IRQSWITCH_HANDLER_MAX_BUTTONS] = { nullptr }; /*!< List of buttons. */

	uint8_t m_count = 0; /*!< Buttons count in manage. */
	uint8_t m_last_clicked = 0; /*!< ID of last clicket button */
};

