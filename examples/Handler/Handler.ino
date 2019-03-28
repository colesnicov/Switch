/**
 * This file is a part of examples of a IRQSwitch Arduino library.
 *
 * File:		examples/Handler/Handler.ino
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Description:	Priklad Handleru pouziti ve smycce loop. Jsou zde ukazany vsechny schopnosti knihovny.
 * Note:		Pozor! Metoda getClickCount() ma smysl, je pouzitelna pouze, v pripade pouziti externiho preruseni pro zmenu stavu tlacitka!!
 */

#include <Arduino.h>

#define IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME 	1
//#define IRQSWITCH_IMPLEMENT_CLICK_HELD			0 // Odkomentovat pro zabraneni teto funkcionality!
#define IRQSWITCH_IMPLEMENT_CLICK_COUNT			4 // Maximalni pocet pocitanych kliknuti na tlacitko!
#include <IRQSwitch.hpp>
#include <IRQSwitchHandler.hpp>

// Definice pinu
#define BTN_one	A1
#define BTN_two	A2

// ID tlacitka v Handleru.
uint8_t btn_one;

// Objekt predstavujici tlacitka
IRQSwitch btn_two;

// Handler.
IRQSwitchHandler buttons;


#if IRQSWITCH_DEBUG
uint32_t delta = 0;
#endif

void setup()
{
	Serial.begin(9600);

	Serial.print("IRQSwitch version ");
	Serial.println(IRQSwitch_Version);

	Serial.println("Preparing...");

	{
		btn_one = buttons.CreateButton((char*) "btn_one", BTN_one);
		if (btn_one)
		{
			Serial.print("Doslo k chybe behem vytvareni tlacitka: ");
			Serial.println(buttons.GetButton(btn_one)->getName());
			while (1)
			{
			}
		}
	}

	{
		if (!buttons.AddButton(&btn_two))
		{
			btn_two.bind((char*) "btn_two", BTN_two, INPUT_PULLUP);
			Serial.print("Doslo k chybe behem vytvareni tlacitka: ");
			Serial.print(btn_two.getName());
			Serial.println("!");
			while (1)
			{
			}
		}
	}

	Serial.println("Ready!\n\n");

}

void loop()
{
	// Volani funkce pro zpracovani stavu tlacitek.
	buttons.Update(millis());

	// Vypis stavu tlacitek.
	if (buttons.GetButton(btn_one)->isClicked())
	{
		Serial.println("Button 1 clicked!");
	}

	if (btn_two.isClicked())
	{
		Serial.println("Button 2 clicked!");
	}

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
	{
		if (buttons.GetButton(btn_one)->isHolded())
		{
			Serial.println("Button 1 holded!");
		}

		if (btn_two.isHolded())
		{
			Serial.println("Button 2 holded!");
		}
	}
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
	{
		// Prvni tlacitko je bez automatickeho resetovani pocitadla
		// stisku tlacitka.
		uint8_t count1 = buttons.GetButton(btn_one)->getClickCount();

		// Druhe tlacitko s automatickym resetovanim pocitadla
		// stisknuti tlacitka.
		uint8_t count2 = btn_two.getClickCountWithReset();

		if (count1 > 0)
		{
			Serial.print("Button 1 has ");
			Serial.print(count1);
			Serial.println(" clicks");
		}

		if (count2 > 0)
		{
			Serial.print("Button 2 has ");
			Serial.print(count2);
			Serial.println(" clicks");
		}

		if (count1 >= IRQSWITCH_IMPLEMENT_CLICK_COUNT)
		// Pokud je dosazen limit poctu stisknuti,
		// proved reset pocitadla stisku tlacitka.
		{
			buttons.GetButton(btn_one)->cleanClickCount();
			Serial.println("Reset clicks counter.");
		}
	}
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME
	if (buttons.GetButton(btn_one)->isHolded())
	{
		Serial.print("Button 1 has holded state: ");
		Serial.print(buttons.GetButton(btn_one)->getHoldedTime());
		Serial.println(" ms");
	}

	if (btn_two.isHolded())
	{
		Serial.print("Button 2 has holded state: ");
		Serial.print(btn_two.getHoldedTime());
		Serial.println(" ms");
	}

#endif

#if IRQSWITCH_DEBUG
	if (delta > 0)
	{
		Serial.print("buttonProccess = ");
		Serial.print(delta);
		Serial.println(" ms");
	}
#endif

}

