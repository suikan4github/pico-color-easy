/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// The original of this file is found at :
// https://github.com/raspberrypi/pico-examples/blob/master/blink/blink.c

#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "math.h"
#include "pico/stdlib.h"

// Initialize the PWM output.
// The gpio parameter is the number of the GPIO port.
// The period is 100cycles.
// The pre-scaler is set to 1/125.
void init_pwm(const uint gpio) {
  gpio_set_function(gpio, GPIO_FUNC_PWM);

  // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
  uint pwm_slice = pwm_gpio_to_slice_num(gpio);

  // set pre-scaler to 1/125. Running clock is 1MHz.
  pwm_set_clkdiv(pwm_slice, 125.0);

  // Set period of 100 cycles (0 to 99 inclusive)
  pwm_set_wrap(pwm_slice, 99);
}

// Set the duty cycle of the PWM.
// The gpio parameter is the number of the GPIO port.
// The threshold is the count which GPIO turns from 1 to 0.
void set_pwm_threshold(const uint gpio, const uint threshold) {
  // Find out which PWM slice is connected to gpio
  uint pwm_slice = pwm_gpio_to_slice_num(gpio);

  // Find out which PWM channel is connected to gpio.
  uint pwm_channel = pwm_gpio_to_channel(gpio);

  // Set the threshold to the given channel of the given slice.
  pwm_set_chan_level(pwm_slice, pwm_channel, threshold);
}

// Run the PWM from now.
// The gpio parameter is the number of the GPIO port.
void start_pwm(const uint gpio) {
  // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
  uint pwm_slice = pwm_gpio_to_slice_num(gpio);

  // Start PWM
  pwm_set_enabled(pwm_slice, true);
}

// Initialize the GPIO and assign it to ADC0.
// The gpio parameter is the number of the GPIO port.
void init_adc(const uint gpio) {
  adc_init();

  // Select GPIO.
  adc_gpio_init(gpio);

  // Select ADC0
  adc_select_input(0);
}

// Set up the GPIO as input with internal pull-up.
// The gpio parameter is the number of the GPIO port.
void init_switch(const uint gpio) {
  // Initialize the GPIO port.

  gpio_init(gpio);
  // Set it input.
  gpio_set_dir(gpio, false);

  // The input have to be pull up to handle when the SW is not pushed.
  gpio_pull_up(gpio);
}

int main() {
  // Declare the GPIO port of each peripheral.
  const uint RED_LED = 20;
  const uint GREEN_LED = 21;
  const uint BLUE_LED = 22;
  const uint ADC = 26;
  const uint SW1 = 11;
  const uint SW2 = 12;
  const uint SW3 = 13;

  init_pwm(RED_LED);
  init_pwm(GREEN_LED);
  init_pwm(BLUE_LED);

  set_pwm_threshold(RED_LED, 0);
  set_pwm_threshold(GREEN_LED, 0);
  set_pwm_threshold(BLUE_LED, 0);

  start_pwm(RED_LED);
  start_pwm(GREEN_LED);
  start_pwm(BLUE_LED);

  init_adc(ADC);

  init_switch(SW1);
  init_switch(SW2);
  init_switch(SW3);

  const uint max_phase = 300;
  uint phase = 0;

  while (true) {
    // update phase.
    phase++;
    if (phase >= max_phase) phase = 0;

    // calc current phase. Each LED has 1/3 phase shifted.
    const float red_phase = (phase) * (3.1415 * 2) / max_phase;
    const float green_phase =
        (phase + max_phase / 3) * (3.1415 * 2) / max_phase;
    const float blue_phase =
        (phase + 2 * max_phase / 3) * (3.1415 * 2) / max_phase;

    // Calc duty from phase.
    // duty is 0..99
    int red_duty = (sin(red_phase) + 1.0) * 50;
    int green_duty = (sin(green_phase) + 1.0) * 50;
    int blue_duty = (sin(blue_phase) + 1.0) * 50;

    // If SWx is pushed, turn off the relevant LED.
    if (gpio_get(SW1) == 0) red_duty = 0;
    if (gpio_get(SW2) == 0) green_duty = 0;
    if (gpio_get(SW3) == 0) blue_duty = 0;

    // set PWM threshold based on the current duty and threshold.
    set_pwm_threshold(RED_LED, red_duty);
    set_pwm_threshold(GREEN_LED, green_duty);
    set_pwm_threshold(BLUE_LED, blue_duty);

    // The value is 0..4095
    const uint adc_value = adc_read();

    // Set sleep duration from ADC value.
    const int sleep_duration = 33 - (adc_value * 32.0 / 4096.0);

    // sleep to give the appropriate period.
    sleep_ms(sleep_duration);
  }
}
