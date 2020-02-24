/**
 *
 * This file is a part of examples of a Switch library.
 *
 * Created on:  	22.02.2020
 * Updated on:  		24.02.2020
 * Author:    		Denis Colesnicov <eugustus@gmail.com>
 * Licence:   		MIT
 * Home:    		https://github.com/colesnicov/Switch
 * Description:		Priklad pouziti na ESP8266 s ESP-RTOS-SDK.
 *
 */

/**
 * Pouzite piny:
 * GPIO4 = D2 on Wemos D1 mini
 * GPIO5 = D1 on Wemos D1 mini
 */

/**
 * @note POZOR! Musite definovat makra pro atomicke prace uvnitr knihovny.
 * Viz SwitchConfig.hpp file.
 *
 * #include "SimplyAtomic/esp8266.h"
 * #define SWITCH_ATOMIC_START	ATOMIC(){
 * #define SWITCH_ATOMIC_END	}
 * 
 * @note POZOR! Musite nastavit cestu ke knihovne 'Switch' v souboru component.mk
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/portmacro.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"

#include "Switch/SwitchConfig.hpp"
#include "Switch/Switch.hpp"

#define TAG_MAIN	(char*)"USER_MAIN"
#define TAG_LOOP	(char*)"TASK_LOOP"

#define GPIO_INPUT_IO_0     GPIO_NUM_4
#define GPIO_INPUT_IO_1     GPIO_NUM_5
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))

#define BTN_NONE	0
#define BTN_ONE		1
#define BTN_TWO		2

#define millis()	(uint32_t) (xTaskGetTickCount() * portTICK_RATE_MS)


static xQueueHandle switch_evt_queue = NULL;

// Slouzi k prevenci proti kliknuti na nekolik tlacitek soucasne
static uint8_t btn_last = BTN_NONE;

// Objekty predstavujici tlacitka
Switch btn_one;
Switch btn_two;

/**
 * Rutina obsluhy preruseni.
 * Odesle cislo zmacknuteho/uvolneneho tlacitka do 'task_switch'
 * @param arg	Cislo zmacknuteho/uvolneneho tlacitka
 */
static void gpio_isr_handler(void *arg)
{
	uint32_t gpio_num = (uint32_t) arg;

	xQueueSendFromISR(switch_evt_queue, &gpio_num, NULL);
}


/**
 * Smycka nastavuji stavy tlacitek.
 * Prijima cislo zmacknuteho/uvolneneho tlacitka  od 'gpio_isr_handler'
 *  a podle toho se chova (viz implementaci)
 *
 * @param arg
 */
static void task_switch(void *arg)
{
	uint32_t io_num;
	for (;;)
	{
		if (xQueueReceive(switch_evt_queue, &io_num, portMAX_DELAY))
		{

			if (io_num == GPIO_NUM_4) // Cislo pinu == 4
			{
				if (gpio_get_level((gpio_num_t) io_num) == 0) // Tlacitko je zmacknute
				{
					if (btn_last == BTN_NONE) // Jine tlacitko nebylo stisknute
					{
						btn_one.setClickStart(millis()); // Nastavuji jako stisknute
						btn_last = BTN_ONE; // Ukladam ID tlacitka, jako stisknute
					}
				} else // Tlacitko je uvolnene
				{
					if (btn_last == BTN_ONE) // ID posledniho tlacitka se schoduje s timto
					{
						btn_one.setClickEnd(millis()); // Nastavuji jako uvolnene
						btn_last = BTN_NONE; // Nuluji posledni ID tlacitka
					}
				}
			} else if (io_num == GPIO_NUM_5)
			{
				if (gpio_get_level((gpio_num_t) io_num) == 0)
				{
					if (btn_last == BTN_NONE)
					{
						btn_two.setClickStart(millis());
						btn_last = BTN_TWO;
					}
				} else
				{
					if (btn_last == BTN_TWO)
					{
						btn_two.setClickEnd(millis());
						btn_last = BTN_NONE;
					}
				}
			}

		}
	}
}

/**
 * Hlavni smycka.
 * Zde zjistuji stav objektu predstavujicich tlacitka a
 *  provadim nejakou akci podle jejich stavu.
 *
 * @param arg
 */
static void task_loop(void *arg)
{

	for (;;)
	{
		// Vypis stavu tlacitek.
		if (btn_one.isClicked(millis()))
		{
			ESP_LOGI(TAG_LOOP, (char* ) "Button 1 clicked!\n");
		}

		if (btn_two.isClicked(millis()))
		{
			ESP_LOGI(TAG_LOOP, (char* ) "Button 2 clicked!\n");
		}

#if SWITCH_IMPLEMENT_DOUBLE_CLICK

		if (btn_one.isDoubleClicked(millis()))
		{
			ESP_LOGI(TAG_LOOP, (char* ) "Button 1 is double clicked!\n");
		}

		if (btn_two.isDoubleClicked(millis()))
		{
			ESP_LOGI(TAG_LOOP, (char* ) "Button 2 is double clicked!\n");
		}

#endif

#if SWITCH_IMPLEMENT_CLICK_HELD
		{
			if (btn_one.isHolded(millis()))
			{
				ESP_LOGI(TAG_LOOP, (char* ) "Button 1 holded!\n");
			}

			if (btn_two.isHolded(millis()))
			{
				ESP_LOGI(TAG_LOOP, (char* ) "Button 2 holded!\n");
			}
		}
#endif

#if SWITCH_IMPLEMENT_CLICK_HELD_TIME
		{
			if (btn_one.isHolded(millis()))
			{
				ESP_LOGI(TAG_LOOP,
						(char* ) "Button 1 has holded state: '%u', %s\n",
						btn_one.getHoldedTime(millis()), (char* ) "ms");
			}

			if (btn_two.isHolded(millis()))
			{
				ESP_LOGI(TAG_LOOP,
						(char* ) "Button 2 has holded state: '%u' %s\n",
						btn_two.getHoldedTime(millis()), (char* ) "ms");
			}
		}
#endif

#if !SWITCH_IMPLEMENT_DOUBLE_CLICK &&  SWITCH_IMPLEMENT_CLICK_COUNT > 0
		{
			// Prvni tlacitko je bez automatickeho resetovani pocitadla stisku tlacitka.
			uint8_t count1 = btn_one.getClickCount();
			//			uint8_t count1 = 0;

			// Druhe tlacitko s automatickym resetovanim pocitadla stisknuti tlacitka.
			uint8_t count2 = btn_two.getClickCount(); //WithReset();
			//			uint8_t count2 = 0;

			if (count1 > 0)
			{
				ESP_LOGI(TAG_LOOP, (char* ) "Button 1 has '%u' %s\n", count1,
						(char* ) "clicks");
			}

			if (count1 >= SWITCH_IMPLEMENT_CLICK_COUNT)
			// Pokud je dosazen limit poctu stisknuti, proved reset pocitadla stisku tlacitka
			{
				btn_one.cleanClickCount();
				ESP_LOGI(TAG_LOOP, (char* ) "Reset clicks counter.\n");
			}

			if (count2 > 0)
			{
				ESP_LOGI(TAG_LOOP, (char* ) "Button 2 has '%u' %s\n", count2,
						(char* ) "clicks");
			}
		}
#endif

		// smycka musi predat rizeni OS, jinak selze WATCHDOG!
		vTaskDelay((uint32_t) (10 / portTICK_RATE_MS));

	}
}

extern "C" void app_main(void)
{
	// Nastaveni vstupu
	gpio_config_t io_conf;

	// Preruseni na oba stavy, LOW i HIGH
	io_conf.intr_type = GPIO_INTR_ANYEDGE;
	// Bitova maska cisel pinu
	io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
	// Mod vstup
	io_conf.mode = GPIO_MODE_INPUT;
	// Odkomentujte pokud nepouzivate externi PULLUP odpory
	// Zapinam interni PULLUP odpory
	io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
	gpio_config(&io_conf);

	// Vytvarim frontu pri indikaci stisku tlacitka
	switch_evt_queue = xQueueCreate(10, sizeof(uint32_t));

	// Startuji smycku obsluhujici knihovnu Switch
	xTaskCreate(task_switch, (char*) "task_switch", 2048, NULL, 10, NULL);

	// Startuji hlavni smycku
	xTaskCreate(task_loop, (char*) "gpio_task_example", 2048, NULL, 10,
	NULL);

	// Inicializuji sluzbu preruseni na GPIO
	gpio_install_isr_service(0);

	// Navesuji sluzbu preruseni a rutinu preruseni na piny
	gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler,
			(void*) GPIO_INPUT_IO_0);
	gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler,
			(void*) GPIO_INPUT_IO_1);

	ESP_LOGI(TAG_MAIN, "Switch Version %s\n\n", (char*) Switch_Version);

}

