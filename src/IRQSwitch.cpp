/**
 * This file is a part of IRQSwitch library for embedded devices.
 *
 * File:		IRQSwitch.cpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.8.1
 */

#include "IRQSwitch.hpp"

IRQSwitch::IRQSwitch()
{
}

IRQSwitch::~IRQSwitch() {
}

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
bool IRQSwitch::isHolded(uint32_t ms) {
	return isPressed() && ms - m_start_click > m_time_hold;
}
#endif

void IRQSwitch::CleanClick() {
	m_end_click = 0;
}

bool IRQSwitch::isClicked() {
	if (!isPressed() && m_end_click > 0) {
		CleanClick();
		return true;
	} else {
		return false;
	}
}

void IRQSwitch::setClick(uint32_t ms) {
	if (ms - m_end_click > m_time_debounce || m_end_click == 0) {
		m_end_click = ms;
		m_is_clicked = false;
	}
}

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
	uint8_t click_count = m_click_count;
	return click_count;
}

uint8_t IRQSwitch::getClickCountWithReset() {
	uint8_t click_count = m_click_count;
	cleanClickCount();
	return click_count;
}

void IRQSwitch::cleanClickCount() {
	m_click_count = 0;
}

#endif

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME

uint32_t IRQSwitch::getHoldedTime(uint32_t _ms) {
	if (isPressed()) {
		return _ms - m_start_click;
	} else {
		return 0;
	}
}

uint32_t IRQSwitch::getHoldedTimeWithReset(uint32_t _ms) {
	uint32_t t = 0;

	return t;
}

bool IRQSwitch::isPressed() {
	return m_is_clicked;
}


#endif
























