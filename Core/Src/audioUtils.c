#include "audioUtils.h"
#include <math.h>


int32_t swap_half_word(int32_t sample)
{
    uint32_t u = (uint32_t)sample;
    u = ((u & 0xFFFF) << 16) | (uint16_t)(u >> 16);
    return (int32_t)u;
}



float quantize(float x, float step)
{
    return roundf(x / step) * step;
}



float peakDetect (const float *data, size_t bufferLength)
{
	float max = 0.0f;

	for(size_t i = 0; i < bufferLength; i++)
	{
		float absSample = fabsf(data[i]);
		if(absSample > max)
					max = absSample;
	}

	return max;
}



float rmsDetection(const float *data, size_t bufferLength)
{
	float sum = 0.0f;

	for(size_t i = 0; i < bufferLength; i++)
			sum += data[i] * data[i];

	float rmsValue = sqrtf(sum / bufferLength);

	return rmsValue;

}



void applyGain(float *data, size_t bufferLength, float gain)
{
	for(size_t i = 0; i < bufferLength; i++)
		data[i] *= gain;
}
