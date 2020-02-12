#pragma once

/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitchArduino.hpp
 * Created on:	12.02.2020
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.8.0
 */

/**
 * @todo	Pridat definici poctu tlacitek do souboru s definicemi.
 * 			Pocet tlacitek by mel odpovidat maximalnimu mnozstvi pinu MCU + 1
 */

#include <stdint.h>

#include "IRQSwitchConfig.h"
#include "IRQSwitch.hpp"

class IRQSwitchArduino {
public:

	/**
	 * Constructor
	 * Do nothing.
	 */
	IRQSwitchArduino();

	/**
	 * Add button to manage.
	 *
	 * @param	b*	Pointer to button.
	 * @param	pin	Pin number, 0 ... max arduino pin number
	 *
	 */
	void AddButton(IRQSwitch *b, uint8_t pin);

	/**
	 * Update states.
	 *
	 * @param ms Current time in milliseconds.
	 */
	void Update(uint32_t ms);

	/**
	 * Get access to button.
	 * @param id	ID of button.
	 *
	 * @return	IRQSwitch*	Pointer to object.
	 */
	IRQSwitch* GetButton(uint8_t pin);

private:

	IRQSwitch *m_buttons[255] = { nullptr }; /*!< List of buttons. */
	uint8_t m_last_clicked = 255; /*!< ID of last clicket button */
};
