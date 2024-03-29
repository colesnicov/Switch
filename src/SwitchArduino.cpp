/**
 This file is a part of Switch Arduino library.

 File:			SwitchArduino.cpp
 Created on:	12.02.2020
 Author:		Denis Colesnicov <eugustus@gmail.com>
 Licence:		MIT
 Home:			https://github.com/colesnicov/Switch
 Version:		3.0.1
 */

#include "switch/SwitchConfig.hpp"

#if SWITCH_ARDUINO

#include "switch/SwitchArduino.hpp"

#include "Arduino.h"

void SwitchArduino::AddButton(Switch *b, uint8_t pin) {
	m_buttons[pin] = b;
}

Switch* SwitchArduino::GetButton(uint8_t pin) {
	return m_buttons[pin];
}

SwitchArduino::SwitchArduino() {
}

void SwitchArduino::Update(uint32_t ms) {
	for (uint8_t i = 0; i < 255; i++) {
		// Tlacitko je stisknute.
		if (m_buttons[i] == nullptr) {
			continue;
		}

		if (digitalRead(i) == SWITCH_CLICK) {
			if (m_last_clicked == 255) {
				// Zadne jine tlacitko stisknute neni.
				m_buttons[i]->setClickStart(ms); // Nastaveni tlacitka jako "PRESSED".
				m_last_clicked = i; // Zapamatovani ID stisknuteho tlacitka.
			}

		} else if (m_last_clicked == i) {
			// Tlacitko bylo uvolnene
			// a naposledy stisknute tlacitko ma stejne ID.
			m_buttons[i]->setClickEnd(ms); // Nastaveni tlacitka jako "RELEASED".
			m_last_clicked = 255; // Nulovani ID naposledy stisknuteho tlacitka.
		}
	}

}


#endif
