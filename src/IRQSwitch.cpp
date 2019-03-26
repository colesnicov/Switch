/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitch.cpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Verion:		2.3.5
 */


#include <IRQSwitch.hpp>

IRQSwitch::IRQSwitch() :
				m_pin(0),
				m_is_clicked(false),
				m_start_click(0),
				m_end_click(0),
				m_time_debounce(300)
#if IRQSWITCH_IMPLEMENT_CLICK_HELD
						,
				m_time_hold(450)
#endif
#if IRQSWITCH_IMPLEMENT_CLICK_COUNT
						,
				m_click_count(0)
#endif
{
}

IRQSwitch::~IRQSwitch()
{
}

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
bool IRQSwitch::isHolded()
{
	return m_is_clicked && millis() - m_start_click > m_time_hold; // || m_end_click < m_start_click;
}
#endif

void IRQSwitch::CleanClick()
{
	m_end_click = 0;
}

bool IRQSwitch::isClicked()
{
	if (!m_is_clicked && m_end_click > 0)
	{
		CleanClick();
		return true;
	} else
	{
		return false;
	}
}

void IRQSwitch::setClick(uint32_t ms)
{
	if (ms - m_end_click > m_time_debounce || m_end_click == 0)
	{
		m_end_click = ms;
		m_is_clicked = false;
	}
}

bool IRQSwitch::setClickUp(uint32_t ms)
{
	if (/*any_button_clicked && */(ms - m_end_click > m_time_debounce
			|| m_end_click == 0))
	{
		m_end_click = ms;
		m_is_clicked = false;
#if IRQSWITCH_IMPLEMENT_CLICK_HELD
		if (ms - m_start_click > m_time_hold)
		{
			m_end_click = 0;
		}
		//Button::any_button_clicked = false;

#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
		m_click_count++;
		if (m_click_count > IRQSWITCH_IMPLEMENT_CLICK_COUNT)
		{
			m_click_count = 0;
		}
#endif

		return true;
	}
	return false;
}

bool IRQSwitch::setClickDown(uint32_t ms)
{
	if (/*!any_button_clicked && */(ms - m_end_click) > m_time_debounce
			|| m_end_click == 0)
	{

		m_start_click = ms;
		m_is_clicked = true;
		//Button::any_button_clicked = true;
		return true;
	}
	return false;
}

void IRQSwitch::bind(uint8_t pin, uint8_t mode)
{
	m_pin = pin;
	pinMode(pin, mode);
}

void IRQSwitch::unbind()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, HIGH);
}

bool IRQSwitch::any_button_clicked = false;

uint8_t IRQSwitch::getClickCount()
{
	uint8_t click_count = m_click_count;
	cleanClickCount();
	return click_count;
}

void IRQSwitch::cleanClickCount()
{
	m_click_count = 0;
}

