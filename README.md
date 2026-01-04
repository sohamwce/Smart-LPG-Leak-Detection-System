# Smart LPG Leak Detection System

ESP32-Based IoT & GSM Safety Monitoring Solution

## Overview

The Smart LPG Leak Detection System is a real-time safety monitoring solution designed to detect LPG gas leaks and provide immediate local and remote alerts. The system combines embedded sensing, GSM-based notifications, and IoT cloud monitoring to minimize the risk of fire, explosion, and health hazards in residential and industrial environments.

The project continuously monitors LPG concentration using an MQ-series gas sensor. When gas levels exceed a predefined safety threshold, the system triggers:

An audible local alarm

SMS alerts via GSM (independent of internet availability)

Real-time cloud updates visible on a dashboard

This hybrid alert mechanism ensures reliability even in environments with unstable internet connectivity.

## System Architecture

High-Level Components

Sensor Layer: MQ-6 gas sensor for LPG detection

Processing Layer: ESP32 microcontroller

Communication Layer:

Wi-Fi → Cloud backend

GSM (SIM900A) → SMS alerts

Alert Layer:

Buzzer / LED (local)

SMS + Dashboard (remote)

Hardware Components
Component	Description
ESP32 WROOM-32D	Main controller with Wi-Fi and multiple peripherals
MQ-6 Gas Sensor	Detects LPG, propane, butane (200–10,000 ppm)
SIM900A GSM Module	Sends SMS alerts using AT commands
Buzzer & LEDs	Immediate local alert
Power Supply	5V regulated supply

Estimated Cost: ~₹1385

## Software Stack
Firmware (ESP32)

Language: Embedded C / Arduino Framework

Interfaces:

ADC → Gas sensor readings

UART → GSM communication

Wi-Fi → Cloud connectivity

Logic:

Threshold-based detection

Multi-channel alert triggering

Backend

Spring Boot REST API

Stores gas readings and alert events

Exposes APIs for real-time updates

Frontend

React-based dashboard

Live gas level visualization

Alert history and status indicators

## Working Principle
1. System Initialization

ESP32 boots and initializes:

Wi-Fi connection

MQ-6 sensor ADC

GSM UART interface

Buzzer/LED outputs

2. Continuous Gas Monitoring

MQ-6 outputs analog voltage proportional to gas concentration

ESP32 converts ADC values into approximate PPM readings

Readings are continuously sampled

3. Threshold Evaluation

If Gas Level < Threshold

Data sent to backend as SAFE

If Gas Level ≥ Threshold

Buzzer and LED activated

SMS alert sent via GSM

Alert pushed to backend and dashboard

4. GSM Alert (AT Command Flow)
AT+CMGF=1
AT+CMGS="+91XXXXXXXXXX"
GAS LEAK DETECTED! Level: XXX PPM

5. Cloud & Dashboard Update

Backend logs event

Frontend updates gas level graph and alert panel in real time

## Key Features

Real-time LPG detection

Internet-independent SMS alerts

Cloud-based monitoring dashboard

Low-cost and scalable design

Modular hardware and software architecture

## Advantages

Faster response than manual detection

Works even without Wi-Fi (via GSM)

Suitable for homes, kitchens, and small industries

Easy integration with future automation systems

## Limitations

MQ sensors require warm-up and calibration

Threshold-based detection may cause false alarms in extreme conditions

GSM modules add power consumption

## Future Enhancements

Automatic gas shut-off valve integration

Adaptive thresholding based on environment

Edge analytics to reduce false positives

Mobile app notifications with push alerts

ML-based leak prediction for industrial setups

## Applications

Residential kitchens

Restaurants and food stalls

Industrial LPG storage areas

Educational laboratories

Smart home safety systems
