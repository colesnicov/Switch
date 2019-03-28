/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitch.cpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Verion:		2.4.0
 */

#include <Arduino.h>
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
	return m_is_clicked && millis() - m_start_click > m_time_hold;
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

bool IRQSwitch::setClickEnd(uint32_t ms)
{
	if ((ms - m_end_click > m_time_debounce || m_end_click == 0))
	{
		m_end_click = ms;
		m_is_clicked = false;
#if IRQSWITCH_IMPLEMENT_CLICK_HELD
		if (ms - m_start_click > m_time_hold)
		{
			m_end_click = 0;
		}

#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
		if (m_end_click > 0)
		{
			m_click_count++;
			if (m_click_count > IRQSWITCH_IMPLEMENT_CLICK_COUNT)
			{
				m_click_count = 0;
			}
		}
#endif

		return true;
	}
	return false;
}

bool IRQSwitch::setClickStart(uint32_t ms)
{
	if ((ms - m_end_click) > m_time_debounce || m_end_click == 0)
	{

		m_start_click = ms;
		m_is_clicked = true;
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

uint8_t IRQSwitch::getClickCount()
{
	uint8_t click_count = m_click_count;
	return click_count;
}

uint8_t IRQSwitch::getClickCountWithReset()
{
	uint8_t click_count = m_click_count;
	cleanClickCount();
	return click_count;
}

void IRQSwitch::cleanClickCount()
{
	m_click_count = 0;
}

uint32_t IRQSwitch::getHoldedTime()
{
	if(m_is_clicked){
		return millis() - m_start_click;
	}else{
		return 0;
	}
}

uint32_t IRQSwitch::getHoldedTimeWithReset()
{
	uint32_t t;

	return t;
}

uint8_t IRQSwitch::getPin()
{
	return m_pin;
}
