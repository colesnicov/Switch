/**
 * This file is a part of IRQSwitch Arduino library.
 *
 * File:		IRQSwitchHandler.cpp
 * Created on:	28.03.2019
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Version:		2.5.0
 */

#include <IRQSwitchHandler.hpp>

uint8_t IRQSwitchHandler::CreateButton(char name[10], uint8_t pin)
{
	return CreateButton(name, pin, IRQSWITCH_DEFAULT_INPUT_TYPE);
}

uint8_t IRQSwitchHandler::CreateButton(char name[10], uint8_t pin, uint8_t type)
{
	IRQSwitch button;
	uint8_t id = AddButton(&button);
	if (id > 0)
	{
		button.bind(name, pin, type);
	}
	return id;
}

uint8_t IRQSwitchHandler::AddButton(IRQSwitch* b)

{
#if IRQSWITCH_HANDLER_CHECK_COUNT
	if(m_count == MAX_BUTTONS)
	{
		return 0;
	}
#endif

	m_buttons[m_count] = b;
	m_count++;

	return m_count;
}

IRQSwitch* IRQSwitchHandler::GetButton(uint8_t id)
{
	if (id > m_count)
	{
		return nullptr;
	} else
	{
		return m_buttons[id - 1];
	}
}

IRQSwitchHandler::IRQSwitchHandler() :
				m_count(0),
				m_last_clicked(0)
{
}

void IRQSwitchHandler::Update(uint32_t ms)

{
	for (uint8_t i = 0; i < m_count; i++)
	// Tlacitko je stisknute.
	{
		if (digitalRead(m_buttons[i]->getPin()) == LOW)
		{
			if (m_last_clicked == 0)
			// Zadne jine tlacitko stisknute neni.
			{
				m_buttons[i]->setClickStart(ms); // Nastaveni tlacitka jako "PRESSED".
				m_last_clicked = m_buttons[i]->getPin(); // Zapamatovani ID stisknuteho tlacitka.
			}

		} else if (m_last_clicked == m_buttons[i]->getPin())
		// Tlacitko neni stisknute,
		// ale naposledy stisknute tlacitko ma stejne ID.
		{
			m_buttons[i]->setClickEnd(ms); // Nastaveni tlacitka jako "RELEASED".
			m_last_clicked = 0; // Nulovani ID naposledy stisknuteho tlacitka.
		}
	}

}

IRQSwitchHandler::~IRQSwitchHandler()
{
	for (uint8_t i = m_count; i > 0; i--)
	{
		m_buttons[i] = nullptr;
	}
}

