/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <XMC1100.h>

//****************************************************************************
// @Defines
//****************************************************************************

#define NUM_DIGITAL_PINS    12
#define NUM_ANALOG_INPUTS   2
#define NUM_PWM             1
#define NUM_LEDS            2
#define NUM_INTERRUPT       1
#define NUM_SERIAL          1

#define PWM4_TIMER_PERIOD (2041U)  // Generate 490Hz @fCCU=1MHz

#define PIN_RX        (7)
#define PIN_TX        (6)
#define PIN_SPI_SS    (3)
#define PIN_SPI_MOSI  (0)
#define PIN_SPI_MISO  (1)
#define PIN_SPI_SCK   (2)

#define PIN_WIRE_SDA        (11)
#define PIN_WIRE_SCL        (10)

static const uint8_t RX   = 7;
static const uint8_t TX   = 6;

static const uint8_t SS   = 3;
static const uint8_t MOSI = 0;
static const uint8_t MISO = 1;
static const uint8_t SCK  = 2;

static const uint8_t SDA = 11;
static const uint8_t SCL = 10;

#define A0   12
#define A1   13

#define LED_BUILTIN 14 //Standard Arduino LED: Used LED1
#define LED1    14  // Extended Leds
#define LED2    15  // Extended Leds
#define GND     32  // GND

#define digitalPinToInterrupt(p)    (((p) == 13) ? 0 : NOT_AN_INTERRUPT)
#define isanalogPin(p)              (((p == A0) || (p == A1)) ? (1) :0)
#define analogPinToADCNum(p)        ((p == A0) ? (0) : (p == A1) ? (1) : -1)
#define digitalPinHasPWM4(p)        ((p) == 8 )
#define digitalPinToPWM4Num(p)      (((p) == 8) ? (0) : (-1))


#ifdef ARDUINO_MAIN

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT0, 6},    // SPI-MOSI                         P0.6
    /* 1  */    {XMC_GPIO_PORT0 , 7},   // SPI-MISO                         P0.7
    /* 2  */    {XMC_GPIO_PORT0 , 8},   // SPI-SCK                          P0.8
    /* 3  */    {XMC_GPIO_PORT0 , 9},   // SPI-SS                           P0.9
    /* 4  */    {XMC_GPIO_PORT0 , 14},  // GPIO                             P0.14
    /* 5  */    {XMC_GPIO_PORT0 , 15},  // GPIO                             P0.15
    /* 6  */    {XMC_GPIO_PORT2 , 0},   // PIN_TX                           P2.0
    /* 7  */    {XMC_GPIO_PORT2 , 6},   // PIN_RX                           P2.6
    /* 8  */    {XMC_GPIO_PORT0 , 5},   // PWM output                       P0.5
    /* 9  */    {XMC_GPIO_PORT0 , 0},   // External interrupt               P0.0
    /* 10  */   {XMC_GPIO_PORT2 , 11},  // I2C Clock SCL                    P2.11
    /* 11  */   {XMC_GPIO_PORT2 , 10},  // I2C Data / Address SDA           P2.10
    /* 12  */   {XMC_GPIO_PORT2 , 9},   // A0 / ADC Input                   P2.9
    /* 13  */   {XMC_GPIO_PORT2 , 7},   // A1                               P2.7
    /* 14  */   {XMC_GPIO_PORT1 , 1},   // LED output                       P1.1
    /* 15  */   {XMC_GPIO_PORT1 , 0},   // LED output                       P1.0
    /* 16  */   {XMC_GPIO_PORT2 , 1},   // DEBUG_TX                         P2.1
    /* 17  */   {XMC_GPIO_PORT2 , 2}    // DEBUG_RX                         P2.2
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_P0_0}
};

XMC_PWM4_t mapping_pwm4[] =
{
    {CCU40, CCU40_CC40, 0, mapping_port_pin[8], P0_0_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}  // PWM disabled      8                   P0.5
};

XMC_ADC_t mapping_adc[] =
{
    {VADC, 2, DISABLED},
    {VADC, 1, DISABLED}
};

/*
 * UART objects
 */
RingBuffer rx_buffer_debug;
RingBuffer tx_buffer_debug;
RingBuffer rx_buffer_on_board;
RingBuffer tx_buffer_on_board;

XMC_UART_t XMC_UART_debug =
{
    .channel              = XMC_UART0_CH0,
    .rx                   = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)2
    },
    .rx_config            = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .tx                   = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)1
    },
    .tx_config            = {
        .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
    .input_source_dx1     = XMC_INPUT_INVALID,
    .input_source_dx2     = XMC_INPUT_INVALID,
    .input_source_dx3     = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_2,
    .irq_num              = USIC0_0_IRQn,
    .irq_service_request  = 0
};

XMC_UART_t XMC_UART_on_board =
{
    .channel              = XMC_UART0_CH0,
    .rx                   = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)6
    },
    .rx_config            = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .tx                   = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)0
    },
    .tx_config            = {
        .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
    .input_source_dx1     = XMC_INPUT_INVALID,
    .input_source_dx2     = XMC_INPUT_INVALID,
    .input_source_dx3     = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_6,
    .irq_num              = USIC0_0_IRQn,
    .irq_service_request  = 0
};

HardwareSerial Serial(&XMC_UART_debug, &rx_buffer_debug, &tx_buffer_debug);
//HardwareSerial Serial(&XMC_UART_on_board, &rx_buffer_on_board, &tx_buffer_on_board);


#endif


#endif
