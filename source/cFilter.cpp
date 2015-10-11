#include "cFilter.h"

cFilter:: cFilter(VstInt32 pId, float *pCutOff, float *pQ, float *pKeyFollow, float *pMix, VstInt32 *pType, VstInt32 *pNote)
{
	cutOff = pCutOff;
	q = pQ;
	keyFollow = pKeyFollow;
	mix = pMix;
	type = pType;
	note = pNote;
	rCutOff = 2000.0;
	reset();

	modCutOff = 0.f;
	modQ = 0.f;
	modKeyFlw = 0.f;
	modMix = 0.f;

};
cFilter::~cFilter()
{};
void cFilter::process(float *signal)
{
	setCoefficients();
	float output_add, output0, output1;

	killDenormal(signal[0]);
	killDenormal(signal[1]);

	output0 = b0*(signal[0]) + b1*inL1 + b2*inL2 - a1*outL1 - a2*outL2;
	output1 = b0*(signal[1]) + b1*inR1 + b2*inR2 - a1*outR1 - a2*outR2;
	killDenormal(output0);
	killDenormal(output1);

	inL2 = inL1;
	inL1 = signal[0];
	outL2 = outL1;
	outL1 = output0;

	inR2 = inR1;
	inR1 = signal[1];
	outR2 = outR1;
	outR1 = output1;

	float realMix = max(min(*mix + modMix,1.0),0.0);

	signal[0] = (output0 * realMix) + (signal[0] * (1.0-realMix));
	signal[1] = (output1 * realMix) + (signal[1] * (1.0-realMix));
}
void cFilter::setCoefficients()
{
	double da0;
	double sinh01;
	double realQ = 0.707+ (max(min(*q + modQ,1.0),0.0)*9.293);
	
	double newCutOff = max(min(*cutOff + modCutOff,1.0),0.0);
	double newKeyFlw = (*note-69)* ((*keyFollow + modKeyFlw)*2.0-1.0);

	if ((newCutOff != oldCutOff) || (newKeyFlw != oldKeyFlw))
	{
		fCutOff = ( 20 + pow(newCutOff,4) * 19980.f) * pow(2.0, newKeyFlw / 12.0);
		oldKeyFlw = newKeyFlw;
		oldCutOff = newCutOff;
	}

	double cut = fCutOff;
					
	if (cut > rCutOff)
	{
		rCutOff *= 1.005;
		if (cut < rCutOff)
			rCutOff = cut;
	}
	else if (cut < rCutOff)
	{
		rCutOff *= 0.99502487;
		if (cut > rCutOff)
			rCutOff = cut;
	}

	cut = rCutOff;
	
	if (cut > 20000.0) cut = 20000.0;	
	w0 = 2*M_PI * cut *Glob->sampleTime;
	cos_w0 = cos(w0);
	sin_w0 = sin(w0);
	switch (*type)
	{
	case 0: // Dolnopriepustny
		alpha = sin_w0 / (2.0 * realQ);
		da0 = 1.0/(1.0 + alpha);
		b0 = ((1.0 - cos_w0)/2.0) * da0;
		b1 = (1.0 - cos_w0) * da0;
		b2 = ((1.0 - cos_w0)/2.0) * da0;
		a1 =  (0-2.0*cos_w0) * da0;
		a2 =  (1.0 - alpha) * da0;
		break;
	case 1: // Hornopriepustny
		alpha = sin_w0 / (2.0 * realQ);
		da0 = 1.0/(1.0 + alpha);
		b0 = ((1.0 + cos_w0)/2.0) * da0;
		b1 = ( 0.0-(1.0 + cos_w0)) * da0;
		b2 = ((1.0 + cos_w0)/2.0) * da0;
		a1 =  (0.0 -2.0*cos_w0) * da0;
		a2 =  (1.0 - alpha) * da0;
		break;
	case 2: // Pasmovopriepustny
		sinh01 = sinh( (log(2.0) * realQ * w0)/(sin_w0*2.0) );
		alpha = sin_w0 * sinh01;
		da0 = 1.0/(1 + alpha);

		b0 = alpha * da0;
		b1 = 0.0;
		b2 = (0.0-alpha) * da0;
		a1 = (-2.0)*cos_w0 * da0;
		a2 = (1 - alpha) * da0;
		break;
	case 3: // Pasmo-stop
		sinh01 = sinh( (log(2.0) * realQ * w0)/(sin_w0*2.0) );
		alpha = sin_w0 * sinh01;
		da0 = 1.0/(1 + alpha);

		b0 = da0;
		b1 = (-2.0 * cos_w0) * da0;
		b2 = da0;
		a1 = (-2.0 * cos_w0) * da0;
		a2 = (1 - alpha) * da0;

		break;

	}
}
void cFilter::reset()
{
	oldCutOff = max(min(*cutOff + modCutOff,1.0),0.0);
	oldKeyFlw = (*note-69)* ((*keyFollow + modKeyFlw)*2.0-1.0);
	fCutOff = rCutOff = ( 20 + pow(oldCutOff,4) * 19980.f) * pow(2.0, oldKeyFlw / 12.0);

	inL1 = 0.f;
	inL2 = 0.f;
	outL1 = 0.f;
	outL2 = 0.f;
	inR1 = 0.f;
	inR2 = 0.f;
	outR1 = 0.f;
	outR2 = 0.f;
}
float cFilter::getBuffSum()
{
	return	abs(inL1) + abs(inL2) + abs(inR1) + abs(inR1) + 
			abs(outL1) + abs(outL2) + abs(outR1) + abs(outR1);
}
void cFilter::killDenormal(double &val)
{
	double anti_denormal = 1e-18;
	val += anti_denormal;
	val -= anti_denormal;
}
void cFilter::killDenormal(float &val)
{
	float anti_denormal = 1e-18;
	val += anti_denormal;
	val -= anti_denormal;
}