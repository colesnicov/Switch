#pragma once

/**
 * This file is a part of IRQSwitch library for embedded devices.
 *
 * File:		IRQSwitch.hpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.8.0
 *
 * Note:		Attention! The getClickCount() method should only be used
 * 				sensibly if you use external interruption to change the
 * 				status of the buttons !!
 */

/** NOTES **
 *
 * - Nepouzivat 'setClick(...)' - Neni zrejmy koncept, k cemu je?
 */

/** UPDATES **
 *
 * 29.03.2019 - 2.5.1
 *  - Definice jsou presunuty do samostatneho souboru 'IRQSwitchConfig.h'
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
 * 03.02.2020 - 2.6.1
 *  - Metoda 'isHolded()' nyni jako argument prijima cas v milisekundach.
 *  	Je tomu tak kvuli prenositelnosti mezi ruznymi platformami.
 *  	Driv tato metoda volala interne funkci 'millis()' coz omezovalo prenositelnost..
 *    
 * 05.03.2020 - 2.7.0
 *  Kvuli prenositelnosti mezi jinymi platformami..
 *  - Odstraneny metody:
 *    - uint8_t IRQSwitch::getPin()
 *    - void IRQSwitch::bind(uint8_t pin)
 *    - void IRQSwitch::bind(uint8_t pin, uint8_t mode)
 *    - void IRQSwitch::unbind()
 *  - Odstranena promena:
 *    - m_pin
 *  - Metoda 'getHoldedTime()' nyni jako argument prijima cas v milisekundach.
 *  - Metoda 'getHoldedTimeWithReset()' nyni jako argument prijima cas v milisekundach.
 *    Je tomu tak kvuli prenositelnosti mezi ruznymi platformami.
 *    Driv tato metoda volala interne funkci 'millis()' coz omezovalo prenositelnost..
 *
 * 12.02.2020 - 2.8.0
 *	- Vychozi hodnoty pro clenske promene jsou nastaveny v definici tridy.
 *	- Metoda IRQSwitch::getHoldedTimeWithReset(uint32_t _ms) vraci 0.
 *
 */

/**
 * @todo Budouci upravy:
 * 			- Implementovat ATOMICke operace.
 * 				Je to dulezite pri pouziti preruseni,
 * 				jinak metody 'getHoldedTime(...)' a 'isHolded(...)'
 * 				pachaji neplechu!!
 */

#include <stdint.h>

#include "IRQSwitchConfig.h"

class IRQSwitch {
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

#if IRQSWITCH_IMPLEMENT_CLICK_HELD

	/**
	 * Is the switch has helded?
	 *
	 * @return bool TRUE if is helded, otherwise FALSE
	 *
	 * @note See IRQSWITCH_IMPLEMENT_CLICK_HELD definition
	 */
	bool isHolded(uint32_t ms);

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
	 * @param ms Time in milliseconds, typically call millis()...
	 *
	 * @return uint32_t Time in milliseconds.
	 */
	uint32_t getHoldedTime(uint32_t _ms);

	/**
	 * Returns the hold time of the button with reset hold counter.
	 *
	 * @param ms Time in milliseconds, typically call millis()...
	 *
	 * @return uint32_t Time in milliseconds.
	 *
	 * @note Not implemented!
	 */
	uint32_t getHoldedTimeWithReset(uint32_t _ms);

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
	 * @return True if success otherwise FALSE
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

private:

	bool m_is_clicked = false; /*!< The switch button has bin clicked for now?. */
	uint32_t m_start_click = 0; /*!< Time in milliseconds where the click/hold action is started. */
	uint32_t m_end_click = 0; /*!< Time in milliseconds where the click/hold action is ended. */
	uint16_t m_time_debounce = IRQSWITCH_TIME_DEBOUNCE; /*!< Delay in milliseconds to prevent a debounced noise. */

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
	uint32_t m_time_hold = 450; /*!< Delay in milliseconds to roll a held action. */
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT
	uint8_t m_click_count = 0; /*!< Incremented value for store klicks count. */
#endif

};
