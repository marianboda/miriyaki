#include "cGlobFilter.h"

cGlobFilter:: cGlobFilter()
{
	reset();
	setCoefficients(20.0,0.707,1);
};
cGlobFilter::~cGlobFilter()
{};
void cGlobFilter::process(float *signal)
{
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

	signal[0] = output0;
	signal[1] = output1;
}
void cGlobFilter::setCoefficients(double pCutOff, double pQ, VstInt32 pType)
{
	double da0;
	double sinh01;
	double cut = pCutOff;
	if (cut > 20000.0) cut = 20000.0;	
	w0 = 2*M_PI * cut *Glob->sampleTime;
	cos_w0 = cos(w0);
	sin_w0 = sin(w0);
	switch (pType)
	{
	case 0: // Dolnopriepustny
		alpha = sin_w0 / (2.0 * pQ);
		da0 = 1.0/(1.0 + alpha);
		b0 = ((1.0 - cos_w0)/2.0) * da0;
		b1 = (1.0 - cos_w0) * da0;
		b2 = ((1.0 - cos_w0)/2.0) * da0;
		a1 =  (0-2.0*cos_w0) * da0;
		a2 =  (1.0 - alpha) * da0;
		break;
	case 1: // Hornopriepustny
		alpha = sin_w0 / (2.0 * pQ);
		da0 = 1.0/(1.0 + alpha);
		b0 = ((1.0 + cos_w0)/2.0) * da0;
		b1 = ( 0.0-(1.0 + cos_w0)) * da0;
		b2 = ((1.0 + cos_w0)/2.0) * da0;
		a1 =  (0.0 -2.0*cos_w0) * da0;
		a2 =  (1.0 - alpha) * da0;
		break;
	case 2: // Pasmovopriepustny
		sinh01 = sinh( (log(2.0) * pQ * w0)/(sin_w0*2.0) );
		alpha = sin_w0 * sinh01;
		da0 = 1.0/(1 + alpha);

		b0 = alpha * da0;
		b1 = 0.0;
		b2 = (0.0-alpha) * da0;
		a1 = (-2.0)*cos_w0 * da0;
		a2 = (1 - alpha) * da0;
		break;
	case 3: // Pasmo-stop
		sinh01 = sinh( (log(2.0) * pQ * w0)/(sin_w0*2.0) );
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
void cGlobFilter::reset()
{
	inL1 = 0.f;
	inL2 = 0.f;
	outL1 = 0.f;
	outL2 = 0.f;
	inR1 = 0.f;
	inR2 = 0.f;
	outR1 = 0.f;
	outR2 = 0.f;
}
void cGlobFilter::killDenormal(double &val)
{
	double anti_denormal = 1e-18;
	val += anti_denormal;
	val -= anti_denormal;
}
void cGlobFilter::killDenormal(float &val)
{
	float anti_denormal = 1e-18;
	val += anti_denormal;
	val -= anti_denormal;
}