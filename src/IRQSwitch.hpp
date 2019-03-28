#pragma once

/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitch.hpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.5.0
 *
 * Note:		Attention! The getClickCount() method should only be used sensibly if you use external interruption to change the status of the buttons !!
 */

/** NOTES **
 *
 * - Nepouzivat 'setClick(...)' - Neni zrejmy koncept, k cemu je?
 */

/** UPDATES **
 *
 * 28.03.2019 - 2.5.0
 *  - Metody 'bind(...)' a 'unbind(...)' jiz jsou pouzitelne.
 *
 * 28.03.2019 - 2.4.2
 *  - Uzpusobene pro lepsi produktivitu.
 *  - Poupraveny komentare.
 *
 * 28.03.2019 - 2.4.0
 *  - Pridana metoda 'getHoldedTime()'
 *  - Pridana metoda 'getHoldedTimeWithReset()'
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
#include <stdint.h>

/**
 * Library version.
 */
#define IRQSwitch_Version "2.5.0"

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

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME and !IRQSWITCH_IMPLEMENT_CLICK_HELD
#error "Not allowed, You must enable the 'Keep button pressed' (see IRQSWITCH_IMPLEMENT_CLICK_HELD) feature."
#endif

#ifndef IRQSWITCH_HANDLER_DEFAULT_INPUT_type
/**
 * Default internal (in the MCU) pin matrix type. Eg. INPUT, INPUT_PULLUP.
 */
#define IRQSWITCH_DEFAULT_INPUT_TYPE	INPUT_PULLUP
#endif

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

	IRQSwitch(char name[10]);

	/**
	 * Destructor
	 * Do nothing
	 */
	~IRQSwitch();

	/**
	 * Bind a pin to physical output pad of MCU
	 * This step also will enabled PULL UP resistor on this pin
	 *
	 * @param name	Name of the Object. For DEBUG only. @see IRQSWITCH_DEBUG
	 * @param pin	Pin to bind to the switch functionality
	 */
	void bind(char name[10], uint8_t pin);

	/**
	 * Bind a pin to physical output pad of MCU
	 * This step also will enabled PULL UP resistor on this pin
	 *
	 * @param name	Name of the Object. For DEBUG only. @see IRQSWITCH_DEBUG
	 * @param pin	Pin to bind to the switch functionality
	 * @param mode	Mode of input pin (INPUT, INPUT_PULLUP)
	 */
	void bind(char name[10], uint8_t pin, uint8_t mode);

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

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME

	/**
	 * Returns the hold time of the button.
	 *
	 * @return uint32_t Time in milliseconds.
	 */
	uint32_t getHoldedTime();

	/**
	 * Returns the hold time of the button with reset hold counter.
	 *
	 * @return uint32_t Time in milliseconds.
	 */
	uint32_t getHoldedTimeWithReset();
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
	 * @param ms milliseconds.
	 *
	 * @note This method its a pure concept!
	 * @note Do not use this method. !
	 */
	void setClick(uint32_t ms);

	/**
	 * Returns a number of pin used for this Switch Button.
	 *
	 * @return uint8_t Pin number.
	 */
	uint8_t getPin();

#if IRQSWITCH_DEBUG
	/**
	 * Returns the name of object.
	 *
	 * @note	For DEBUG only! @see IRQSWITCH_DEBUG.
	 * @return	char*
	 */
	char* getName();
#endif

private:

	uint8_t m_pin = 0; /*!< The number a pin to bind a switch button. */

	bool m_is_clicked = false; /*!< The switch button has bin clicked for now?. */
	uint32_t m_start_click = 0; /*!< Time in milliseconds where the click/hold action is started. */
	uint32_t m_end_click = 0; /*!< Time in milliseconds where the click/hold action is ended. */
	uint16_t m_time_debounce = 300; /*!< Delay in milliseconds to prevent a debounced noise. */
	uint32_t m_time_hold; /*!< Delay in milliseconds to roll a held action. */

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT
	uint8_t m_click_count; /*!< Incremented value for store klicks count. */
#endif

#if IRQSWITCH_DEBUG
	char m_name[IRQSWITCH_NAME_LENGTH];
#endif

};

