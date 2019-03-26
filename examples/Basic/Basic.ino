/**
 * This file is a part of examples of a IRQSwitch Arduino library.
 *
 * File:		examples/Basic/Basic.ino
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Description:	Priklad pouziti ve smycce loop. Jsou zde ukazany vsechny schopnosti knihovny.
 * Note:		Pozor! Metoda ClockCount() ma smysl, je pouzitelna, pouze v pripade pouziti exxterniho preruseni pro zmenu stavu tlacitka!!
 */


#include <Arduino.h>
#include <IRQSwitch.hpp>

// Definice pinu
#define BTN_one	A1
#define BTN_two	A2

// Objekty predstavujici tlacitka
IRQSwitch btn_one;
IRQSwitch btn_two;

void buttonProccess()
{
	// Prevent before clicking on multiple buttons at once. It must be static!!
	static uint8_t last_btn_clicked = 0;
	// Milliseconds to detect a long press of a button
	uint32_t ms = millis();

	// Test button 1
	if (digitalRead(BTN_one) == LOW)
	{ // The button is pressed
		if (last_btn_clicked == 0)
		{ // The other button is not pressed
			btn_one.setClickDown(ms); // Set to clicked
			last_btn_clicked = BTN_one; // Remember the ID of the pressed button
		}
	} else if (last_btn_clicked == BTN_one)
	{ // The last pressed button ID is the same
		btn_one.setClickUp(ms); // Set to released
		last_btn_clicked = 0; // Set the ID of the pressed button to 0
	}

	// Test button 2
	if (digitalRead(BTN_two) == LOW)
	{
		if (last_btn_clicked == 0)
		{
			btn_two.setClickDown(ms);
			last_btn_clicked = BTN_two;
		}
	} else if (last_btn_clicked == BTN_two)
	{
		btn_two.setClickUp(ms);
		last_btn_clicked = 0;
	}
}

void setup()
{
	Serial.begin(9600);

	Serial.print("IRQSwitch version ");
	Serial.println(IRQSwitch_Version);

	Serial.println("Preparing...");

	pinMode(BTN_one, INPUT);
	pinMode(BTN_two, INPUT);

	digitalWrite(BTN_one, HIGH);
	digitalWrite(BTN_two, HIGH);

	Serial.println("Ready!\n\n");

}

void loop()
{
	buttonProccess();

	if (btn_one.isClicked())
	{
		Serial.println("Button 1 clicked!");
	}

	if (btn_two.isClicked())
	{
		Serial.println("Button 2 clicked!");
	}

	if (IRQSWITCH_IMPLEMENT_CLICK_HELD)
	{
		if (btn_one.isHolded())
		{
			Serial.println("Button 1 holded!");
		}

		if (btn_two.isHolded())
		{
			Serial.println("Button 2 holded!");
		}
	}

	delay(1000);
	if (IRQSWITCH_IMPLEMENT_CLICK_COUNT)
	{
		Serial.print("Button 1 has ");
		Serial.print(btn_one.getClickCount());
		Serial.println(" clicks");

		Serial.print("Button 2 has ");
		Serial.print(btn_two.getClickCount());
		Serial.println(" clicks");
	}

}




































