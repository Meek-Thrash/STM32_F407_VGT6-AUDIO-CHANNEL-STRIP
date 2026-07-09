A real-time stereo audio processor running on an **STM32F407** microcontroller.
The project demonstrates low-latency digital audio processing using **I2S + DMA double buffering**, while analog controls are acquired through **ADC + DMA**.

The application processes stereo audio in real time at **96 kHz**, providing input gain, stereo panning, output level control, peak detection and a dual-channel LED VU meter.



## Project Scope

This project is intentionally focused on the software architecture of a real-time embedded audio processing system.

To keep the scope focused on embedded software development, several hardware design aspects that are essential for production-quality audio hardware have intentionally been left out, including:

* Separation of analog and digital ground planes
* Separate analog and digital power supplies
* PCB layout considerations for low-noise audio performance
* Analog front-end optimization

The objective is to demonstrate the embedded software techniques rather than complete hardware design.

---

## Intended Purpose

This project is intended as a software demonstration rather than a complete audio product.

Instead, it serves as a practical demonstration of how to integrate multiple STM32 peripherals into a real-time application, including:

I2S full-duplex communication using DMA
ADC-based real-time parameter control
Interrupt-driven processing
Buffer management for low-latency audio streaming
Basic digital signal processing techniques

Its primary purpose is educational and demonstrative, showcasing common embedded software design patterns used in real-time audio applications.

---

## Features

* Stereo audio pass-through
* Adjustable input gain
* Constant-power stereo panning
* Master output level
* Peak detection with clipping indication LEDs
* Dual-channel LED VU meter (RMS-based)
* Mute control with software debounce
* Low-latency DMA-based audio processing

---

## Real-Time Performance

- Sampling frequency: **96 kHz**
- Stereo processing
- Floating-point DSP
- DMA double buffering
- Cortex-M4F hardware FPU
- Block size: **256 frames**

---

## Hardware

* STM32F407VGT6
* External audio codec composed of a PCM1808 ADC and a PCM5102 DAC connected via I2S.
* Input Gain potentiometer
* Stereo Pan potentiometer
* Output Level slider
* Push button for mute/unmute
* Dual 5-LED VU meters
* Peak indication LEDs

---

## Software Architecture

The application uses DMA double buffering to achieve continuous audio streaming without blocking the CPU.

### Audio path


I2S RX DMA
      │
      ▼
Convert to float
      │
      ▼
Input Gain
      │
      ▼
Peak Detection
      │
      ▼
Constant-Power Panning
      │
      ▼
Output Gain
      │
      ▼
RMS Measurement
      │
      ▼
VU Meter Update
      │
      ▼
Convert to 24-bit
      │
      ▼
I2S TX DMA


The DMA interrupt callbacks only signal buffer availability by setting synchronization flags.

All DSP processing is executed inside the main loop, where each half of the DMA buffer is processed as soon as it becomes available.

---

## Audio Processing

The processing chain consists of:

1. Conversion of 24-bit I2S samples to normalized floating-point values.
2. Adjustable input gain.
3. Peak detection for clipping indication.
4. Constant-power stereo panning using square-root coefficients.
5. Master output gain.
6. RMS level computation with exponential smoothing.
7. Conversion back to 24-bit samples for transmission.

---

## ADC Processing

The analog controls are periodically sampled using **ADC + DMA**.

Each control value is:

* Low-pass filtered to reduce noise
* Quantized for smoother parameter updates
* Rounded near the limits where appropriate


* Only the panning control is stabilized around the center position using a configurable dead zone

---

## VU Meter

The VU meter is based on the RMS level of each audio channel.

The measured RMS amplitude is converted into dBFS using:

```text
dB = 20 · log10(A)
```

where `A` is the normalized signal amplitude.

Five logarithmic thresholds drive the LED bars independently for the left and right channels.

---

## Project Structure

```text
Core/
 ├── Inc/
 ├── Src/
 │    ├── main.c
 │    ├── audioUtils.c
 │    └── ...
Drivers/
STM32CubeIDE project files
```

The majority of the DSP logic is implemented in `main.c`, while reusable audio utility functions are placed inside `audioUtils`.

---

## Development Environment

* STM32CubeIDE
* STM32 HAL Drivers
* GCC ARM Embedded Toolchain

---

## Notes

This project was developed as a learning exercise in real-time embedded DSP and demonstrates:

* DMA double buffering
* Real-time audio processing
* Embedded floating-point DSP on Cortex-M4F
* ADC and I2S peripheral integration
* Low-latency software architecture

---

## Future Improvements

Possible future extensions include:

* Parametric EQ
* Compressor/Limiter
* High-pass filter
* Delay effects
* Any other audio effects inserted between the pre-gain and master output stages.
* OLED display
* UART or USB parameter control

---

## System Schematic

The following schematic shows the hardware connections between the STM32F407, the audio codec devices and the user interface.

<p align="center">
  <img src="images/system_schematic.png" width="900">
</p>

---

## Prototype

The audio processor was developed and tested using a breadboard-based prototype.
