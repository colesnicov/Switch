/**
 * This file is a part of IRQSwitch library for embedded devices.
 *
 * File:		IRQSwitch.cpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.9.0
 */

#include "IRQSwitch.hpp"

IRQSwitch::IRQSwitch() {
}

IRQSwitch::~IRQSwitch() {
}

#if IRQSWITCH_IMPLEMENT_CLICK_HELD

bool IRQSwitch::isHolded(uint32_t ms) {
	bool _is_clicked;
	uint32_t _start_click;

	IRQSWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
		_start_click = m_start_click;
	IRQSWITCH_ATOMIC_END

	return _is_clicked && ms - _start_click > m_time_hold;
}
#endif

void IRQSwitch::CleanClick() {
	IRQSWITCH_ATOMIC_START
		m_end_click = 0;
	IRQSWITCH_ATOMIC_END
}

bool IRQSwitch::isClicked() {
	bool _is_clicked;
	uint32_t _end_click;

	IRQSWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
		_end_click = m_end_click;
	IRQSWITCH_ATOMIC_END

	if (!_is_clicked && _end_click > 0) {
		CleanClick();
		return true;
	} else {
		return false;
	}
}

/**
 * @note Metoda je volana v rutine preruseni. ATOMIC_BLOCK neumistovat!
 */
void IRQSwitch::setClick(uint32_t ms) {
	if (ms - m_end_click > m_time_debounce || m_end_click == 0) {
		m_end_click = ms;
		m_is_clicked = false;
	}
}

/**
 * @note Metoda je volana v rutine preruseni. ATOMIC_BLOCK neumistovat!
 */
bool IRQSwitch::setClickEnd(uint32_t ms) {
	if ((ms - m_end_click > m_time_debounce || m_end_click == 0)) {
		m_end_click = ms;
		m_is_clicked = false;

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
		if (ms - m_start_click > m_time_hold) {
			m_end_click = 0;
		}
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
		if (m_end_click > 0 && m_click_count < IRQSWITCH_IMPLEMENT_CLICK_COUNT) {
			m_click_count++;
		}
#endif

		return true;
	}
	return false;
}

/**
 * @note Metoda je volana v rutine preruseni. ATOMIC_BLOCK neumistovat!
 */
bool IRQSwitch::setClickStart(uint32_t ms) {
	if ((ms - m_end_click) > m_time_debounce || m_end_click == 0) {
		m_start_click = ms;
		m_is_clicked = true;
		return true;
	}
	return false;
}

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT

uint8_t IRQSwitch::getClickCount() {
	uint8_t _click_count;

	IRQSWITCH_ATOMIC_START
		_click_count = m_click_count;
	IRQSWITCH_ATOMIC_END

	return _click_count;
}

uint8_t IRQSwitch::getClickCountWithReset() {
	uint8_t _click_count;

	IRQSWITCH_ATOMIC_START
		_click_count = m_click_count;
		m_click_count = 0;
	IRQSWITCH_ATOMIC_END

	return _click_count;
}

void IRQSwitch::cleanClickCount() {
	IRQSWITCH_ATOMIC_START
		m_click_count = 0;
	IRQSWITCH_ATOMIC_END
}

#endif

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME

uint32_t IRQSwitch::getHoldedTime(uint32_t _ms) {
	bool _is_clicked;
	uint32_t _start_click;

	IRQSWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
		_start_click = m_start_click;
	IRQSWITCH_ATOMIC_END

	if (_is_clicked) {
		return _ms - _start_click;
	} else {
		return 0;
	}
}

uint32_t IRQSwitch::getHoldedTimeWithReset(uint32_t _ms) {
	uint32_t t = 0;

	return t;
}

bool IRQSwitch::isPressed() {
	bool _is_clicked;

	IRQSWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
	IRQSWITCH_ATOMIC_END

	return _is_clicked;
}

#endif

