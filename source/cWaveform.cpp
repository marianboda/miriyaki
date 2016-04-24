#include "cWaveform.h"

cWaveform::cWaveform()
{
	double waveSize = WAVEFORM_SIZE;
	double saw_counter = 0.0;
	double saw_inc = 2/waveSize;
	double triangle_counter = 0.0;
	double triangle_inc = 4/waveSize;

	SHcounter = -1;

	// Inicializacia generatora bieleho sumu
	srand((unsigned int)time(0));
	VstInt32 q = 15;
	float c1 = (1 << q) - 1.f;
	float c2 = ((VstInt32)(c1 / 3.f)) + 1.f;
	float c3 = 1.f / c1;
	float random = 0.f;
	float noise = 0.f;

	for (VstInt32 i=0;i<waveSize;i++)
	{

		waveformSine[i] = (float)sin(i*2* M_PI /waveSize);
	    
		saw_counter += saw_inc;
		if (saw_counter >= 1.0001)
			saw_counter = -1.;
		if ((saw_counter < 1.0001) && (saw_counter > 0.9999))
			saw_counter = 1.;
		waveformSaw[i] = (float)saw_counter;

		triangle_counter += triangle_inc;
		if (triangle_counter > 0.9999)
			{
		        triangle_inc *= -1.;
				triangle_counter = 1.;
			}
		if (triangle_counter < -0.9999)
			{
				triangle_inc *= -1.;
				triangle_counter = -1.;
			}
		waveformTriangle[i] = (float)triangle_counter;
	}
	for (VstInt32 i=0;i<NOISEWAVE_SIZE;i++)
	{
	    random = ((float)rand() / (float)(RAND_MAX + 1));
		waveformNoise[i] = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;
    
	}
	tableSize = 0;
	readResources();

	double freq;
	VstInt32 counter = 0;
	if (tableSize == 67567)
	{
		for (int i = 0; i < 27; i++)
		{
			freq = 27.5 * pow(2, 4 * i / 12.0);
			VstInt32 samps = (VstInt32) floor(384000.0 / freq + 1.0);
			wavSizes[i] = samps;
			sawPointers[i] = &sawTable[counter];
			squarePointers[i] = &squareTable[counter];
			trianglePointers[i] = &triangleTable[counter];
			counter += samps;
		}
	}

};
cWaveform::~cWaveform()
{};

float cWaveform::getSineSample(float pPos)
{
	return	waveformSine[lrint((pPos * WAVEFORM_SIZE))];
}
float cWaveform::getSawSample(float pPos, float exponent)
{
	if (tableSize > 0)
	{	
		float Exp = exponent * 3 - 5.25;
		double intPart, iWPos;

		if (Exp < 0.0f) Exp = 0.0f;
		if (Exp >= 26.0f)
		{
			if (Exp >28.5f)	return 0.0f;
			if (Exp > 27.5f)
				iWPos = 1.0f - (28.5f - Exp);
			else iWPos = 0.0f;
			intPart = 26.0;
		}
		else
			iWPos = modf(Exp, &intPart);

		VstInt32 wavID = (VstInt32) intPart;
		
		VstInt32 posIndex1, posIndex2;
		float posFraction;

		posFraction = modf((pPos * wavSizes[wavID]),&intPart);
		posIndex1 = lrint(intPart);
		posIndex2 = posIndex1 + 1;
		if (posIndex2 >= wavSizes[wavID]) posIndex2 = 0;

		float wav1Value =	sawPointers[wavID][posIndex1]	* (1-posFraction) + 
							sawPointers[wavID][posIndex2]	* posFraction;

		if (iWPos == 0.0f)	return wav1Value;
		else
		{
			wavID += 1;
			float wav2Value;
			if (wavID > 26)	
				wav2Value = 0.f;
			else
			{
				posFraction = modf((pPos * wavSizes[wavID]),&intPart);
				posIndex1 = lrint(intPart);
				posIndex2 = posIndex1 + 1;
				if (posIndex2 >= wavSizes[wavID]) posIndex2 = 0;
					wav2Value =	sawPointers[wavID][posIndex1]	* (1-posFraction) + 
								sawPointers[wavID][posIndex2]	* posFraction;
			}
			return wav1Value * (1 - iWPos) + wav2Value * iWPos;
		}
	}
	else return 0.f;
}
float cWaveform::getTriangleSample(float pPos, float exponent)
{
	if (tableSize > 0)
	{	
		float Exp = exponent * 3 - 5.25;
		double intPart, iWPos;

		if (Exp < 0.0f) Exp = 0.0f;
		if (Exp >= 26.0f)
		{
			if (Exp >28.5f)	return 0.0f;
			if (Exp > 27.5f)
				iWPos = 1.0f - (28.5f - Exp);
			else iWPos = 0.0f;
			intPart = 26.0;
		}
		else
			iWPos = modf(Exp, &intPart);

		VstInt32 wavID = (VstInt32) intPart;
		
		VstInt32 posIndex1, posIndex2;
		float posFraction;

		posFraction = modf((pPos * wavSizes[wavID]),&intPart);
		posIndex1 = lrint(intPart);
		posIndex2 = posIndex1 + 1;
		if (posIndex2 >= wavSizes[wavID]) posIndex2 = 0;

		float wav1Value =	trianglePointers[wavID][posIndex1]	* (1-posFraction) + 
							trianglePointers[wavID][posIndex2]	* posFraction;

		if (iWPos == 0.0f)	return wav1Value;
		else
		{
			wavID += 1;
			float wav2Value;
			if (wavID > 26)	
				wav2Value = 0.f;
			else
			{
				posFraction = modf((pPos * wavSizes[wavID]),&intPart);
				posIndex1 = lrint(intPart);
				posIndex2 = posIndex1 + 1;
				if (posIndex2 >= wavSizes[wavID]) posIndex2 = 0;
					wav2Value =	trianglePointers[wavID][posIndex1]	* (1-posFraction) + 
								trianglePointers[wavID][posIndex2]	* posFraction;
			}
			return wav1Value * (1 - iWPos) + wav2Value * iWPos;
		}
	}
	else return 0.f;
}
float cWaveform::getSquareSample(float pPos, float exponent)
{
	if (tableSize > 0)
	{	
		float Exp = exponent * 3 - 5.25;
		double intPart, iWPos;

		if (Exp < 0.0f) Exp = 0.0f;
		if (Exp >= 26.0f)
		{
			if (Exp >28.5f)	return 0.0f;
			if (Exp > 27.5f)
				iWPos = 1.0f - (28.5f - Exp);
			else iWPos = 0.0f;
			intPart = 26.0;
		}
		else
			iWPos = modf(Exp, &intPart);

		VstInt32 wavID = (VstInt32) intPart;
		
		VstInt32 posIndex1, posIndex2;
		float posFraction;

		posFraction = modf((pPos * wavSizes[wavID]),&intPart);
		posIndex1 = lrint(intPart);
		posIndex2 = posIndex1 + 1;
		if (posIndex2 >= wavSizes[wavID]) posIndex2 = 0;

		float wav1Value =	squarePointers[wavID][posIndex1]	* (1-posFraction) + 
							squarePointers[wavID][posIndex2]	* posFraction;

		if (iWPos == 0.0f)	return wav1Value;
		else
		{
			wavID += 1;
			float wav2Value;
			if (wavID > 26)	
				wav2Value = 0.f;
			else
			{
				posFraction = modf((pPos * wavSizes[wavID]),&intPart);
				posIndex1 = lrint(intPart);
				posIndex2 = posIndex1 + 1;
				if (posIndex2 >= wavSizes[wavID]) posIndex2 = 0;
					wav2Value =	squarePointers[wavID][posIndex1]	* (1-posFraction) + 
								squarePointers[wavID][posIndex2]	* posFraction;
			}
			return wav1Value * (1 - iWPos) + wav2Value * iWPos;
		}
	}
	else return 0.f;

}
float cWaveform::getNoiseSample(float pPos)
{
	return waveformNoise[(VstInt32)floor(pPos * NOISEWAVE_SIZE)];
}
float cWaveform::getLfoSineSample(float pPos)
{
	double v = tempValue;
	tempFraction = modf((pPos * WAVEFORM_SIZE),&v);
	tempValue = v;
	tempValue2 = tempValue+1;
	if (tempValue2 >= WAVEFORM_SIZE) tempValue2 = 0;

	return	waveformSine[lrint(tempValue)]	* (1-tempFraction) +
			waveformSine[lrint(tempValue2)]	* (tempFraction);
}
float cWaveform::getLfoSawSample(float pPos)
{
	return pPos*2.f-1.f;
}
float cWaveform::getLfoTriangleSample(float pPos)
{
	double v = tempValue;
	tempFraction = modf((pPos * WAVEFORM_SIZE),&v);
	tempValue = v;
	tempValue2 = tempValue+1;
	if (tempValue2 >= WAVEFORM_SIZE) tempValue2 = 0;

	return	waveformTriangle[lrint(tempValue)]	* (1-tempFraction) +
			waveformTriangle[lrint(tempValue2)]	* (tempFraction);
}
float cWaveform::getLfoSquareSample(float pPos)
{
	return (pPos < 0.5f) ? 1.f : -1.f;
}
float cWaveform::getLfoSHSample()
{
	SHcounter += 1;
	if (SHcounter >= NOISEWAVE_SIZE) SHcounter = 0;
	return waveformNoise[SHcounter];
}

float cWaveform::getLfoNoiseSample(float pPos)
{
	return waveformNoise[(VstInt32)floor(pPos * NOISEWAVE_SIZE)];
}


void cWaveform::readResources()
{
	
	HRSRC  rsrc = FindResource ((HINSTANCE)hInstance, MAKEINTRESOURCE (192), "WAVETABLE");
	tableSize = SizeofResource ((HINSTANCE)hInstance, rsrc)/4;
	sawTable = new float[tableSize];
	HGLOBAL resDataLoad = LoadResource ((HINSTANCE)hInstance, rsrc);
	    if (resDataLoad)
            {
               LPVOID resData = LockResource (resDataLoad);
               memcpy (sawTable,((void*)resData),tableSize*4);
            }
	FreeResource(resDataLoad);

	rsrc = FindResource ((HINSTANCE)hInstance, MAKEINTRESOURCE (193), "WAVETABLE");
	tableSize = SizeofResource ((HINSTANCE)hInstance, rsrc)/4;
	squareTable = new float[tableSize];
	resDataLoad = LoadResource ((HINSTANCE)hInstance, rsrc);
	    if (resDataLoad)
            {
               LPVOID resData = LockResource (resDataLoad);
               memcpy (squareTable,((void*)resData),tableSize*4);
            }
	FreeResource(resDataLoad);

	rsrc = FindResource ((HINSTANCE)hInstance, MAKEINTRESOURCE (194), "WAVETABLE");
	tableSize = SizeofResource ((HINSTANCE)hInstance, rsrc)/4;
	triangleTable = new float[tableSize];
	resDataLoad = LoadResource ((HINSTANCE)hInstance, rsrc);
	    if (resDataLoad)
            {
               LPVOID resData = LockResource (resDataLoad);
               memcpy (triangleTable,((void*)resData),tableSize*4);
            }
	FreeResource(resDataLoad);
}