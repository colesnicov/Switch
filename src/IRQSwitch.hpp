#pragma once

/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitch.hpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Verion:		2.3.6
 *
 * Note:		Attention! The getClickCount() method should only be used sensibly if you use external interruption to change the status of the buttons !!
 */

/** NOTES **
 *
 * - Nepouzivat '(un)bind(...)' - Neni zrejmy koncept, jak metody pouzivat.
 * - Nepouzivat 'any_button_clicked' - Neni zrejmy koncept, k cemu je?
 * - Nepouzivat 'setClick(...)' - Neni zrejmy koncept, k cemu je?
 */

/** UPDATES **
 *
 * 26.03.2019 - 2.3.6
 *  - Prejmenovana metoda 'setClickDown()' na setClickStart().
 *  - Prejmenovana metoda 'setClickUp()' na setClickEnd().
 *  - Upravena metoda 'getClickCount()' uz automaticky neresetuje svoje pocitadlo.
 *  - Pridana metoda 'getClickCountWithReset()' ktera automaticky resetuje svoje pocitadlo.
 *  - Odstranena staicka promena 'any_button_clicked'.
 *  - Oprava chyby ktera se tezko popisuje.
 *  - Oprava detekce dlouheho stisku tlacitka a inkrementace pocitadla.
 *    Drive se pocitadlo zvysovalo i pri dlouhem stisku tlacitka a to je spatne.
 *    Pokud je potreba puvodni funkcionalita, snadno se da implementovat v kodu.
 *
 * 26.03.2019 - 2.3.5
 *  - Pridana metoda pro zaznamenavani poctu kliknuti na tlacitko.
 *
 */

#include <Arduino.h>

#ifndef IRQSWITCH_IMPLEMENT_CLICK_HELD
/**
 * Set 1 if you wanna have a hold BUTTON functionality, otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_HELD	1
#endif

#ifndef IRQSWITCH_IMPLEMENT_CLICK_COUNT
/**
 * Set (nums of clicks) if you wanna have Click Counter functionality. otherwise 0.
 */
#define IRQSWITCH_IMPLEMENT_CLICK_COUNT 100
#endif

#define IRQSwitch_Version "2.3.5"

/**
 * Simulate a Tactile Switch Button interface.
 */
class IRQSwitch
{
public:

	/**
	 * Constructor
	 * Do nothing
	 */
	IRQSwitch();

	/**
	 * Destructor
	 * Do nothing
	 */
	~IRQSwitch();

	/**
	 * Bind a pin to physical output pad of MCU
	 * This step also will enabled PULL UP resistor on this pin
	 *
	 * @param pin	Pin to bind to the switch functionality
	 * @param mode	Mode of input pin (INPUT, INPUT_PULLUP)
	 */
	void bind(uint8_t pin, uint8_t mode);

	/**
	 * UnBind a physical pin of MCU from a switch functionality
	 */
	void unbind();

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
	/**
	 * Is the switch has helded?
	 *
	 * @return bool TRUE if is helded, otherwise FALSE
	 *
	 * @note See IRQSWITCH_IMPLEMENT_CLICK_HELD definition
	 */
	bool isHolded();

#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
	/**
	 * Get Click Count on the button
	 *
	 * @return uint8_t Count of clicks
	 *
	 * @note @see IRQSWITCH_IMPLEMENT_CLICK_COUNT
	 */
	uint8_t getClickCount();

	/**
	 * Get click count on the Button with reset clicks counter.
	 *
	 * @return uint8_t Count of clicks
	 *
	 * @note @see IRQSWITCH_IMPLEMENT_CLICK_COUNT
	 */
	uint8_t getClickCountWithReset();

	/**
	 * Reset clicks counter.
	 */
	void cleanClickCount();

#endif

	/**
	 * Is the switch has clicked?
	 *
	 * @return bool TRUE if has clicked, otherwise FALSE
	 */
	bool isClicked();

	/**
	 * Reset Click state
	 */
	inline void CleanClick();

	/**
	 * Set Indicies to switch un press down state
	 *
	 * @param ms Time in milliseconds, typically call millis()...
	 *
	 * @note Pro volani uvnitr metody zpracovavajici stisk tlacitka nebo preruseni
	 */
	bool setClickEnd(uint32_t ms);

	/**
	 * Set Indicies to switch press down state
	 *
	 * @param ms Time in milliseconds, typically call millis()...
	 *
	 * @note Pro volani uvnitr metody zpracovavajici stisk tlacitka nebo preruseni
	 */
	bool setClickStart(uint32_t ms);

	/**
	 * Simulate the Click on the button.
	 * @param ms milliseconds
	 *
	 * @note This method its a pure concept!
	 * @note Do not use this method. !
	 */
	void setClick(uint32_t ms);

	/**
	 * Returns a number of used pin for this Switch Button
	 *
	 * @return uint8_t Pin number
	 */
	uint8_t getPin()
	{
		return m_pin;
	}

private:

	uint8_t m_pin = 0; /*!< The number a pin to bind a switch button */

	bool m_is_clicked = false; /*!< The switch button has bin clicked for now? */
	uint32_t m_start_click = 0; /*!< Time in milliseconds where the click/hold action is started */
	uint32_t m_end_click = 0; /*!< Time in milliseconds where the click/hold action is ended */
	uint16_t m_time_debounce = 300; /*!< Delay in milliseconds to prevent a debounced noise */
	uint32_t m_time_hold; /*!< Delay in milliseconds to roll a held action */

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT
	uint8_t m_click_count; /*!< Incremented value for store klicks count */
#endif

};



























