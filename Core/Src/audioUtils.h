/*
 * audioUtils.h
 *
 * Lightweight DSP utility layer for STM32 real-time audio processing.
 *
 * This module is part of a DMA-based audio pipeline running at 96 kHz,
 * designed for embedded systems with limited computational resources.
 *
 * It implements basic signal processing operations such as:
 * - Fixed-point / integer sample manipulation
 * - Nonlinear quantization
 * - Gain staging
 * - Peak and RMS level detection
 *
 * All functions are designed to be:
 * - Real-time safe (no dynamic allocation)
 * - Low latency
 * - Deterministic in execution time
 *
 * Intended use: audio effect processing, metering, and signal control
 * in embedded STM32 audio applications.
 *
 *  Created on: Jun 23, 2026
 *      Author: Meek
 */
#include <stdint.h>
#include <stddef.h>

#ifndef AUDIO_UTILS_H
#define AUDIO_UTILS_H

int32_t swap_half_word(int32_t sample);
float quantize(float x, float step);
float peakDetect (const float *data, size_t bufferLength);
float rmsDetection(const float *data, size_t bufferLength);
void applyGain(float *data, size_t bufferLength, float gain);

#endif

