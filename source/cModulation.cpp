#include "cModulation.h"

cModulation::cModulation()
{
	for (int i=0;i<jMS_total;i++)
		source[i] = NULL;
	for (int i=0;i<jMD_total;i++)
		destination[i] = NULL;

};
cModulation::~cModulation()
{};
void cModulation::modulate()
{
	float ampVolumeSum = 1.f;
	float ampVolumeEnvs = 1.0f;

	float osc1LevelSum = 1.f;
	float osc2LevelSum = 1.f;
	float osc3LevelSum = 1.f;
	float osc4LevelSum = 1.f;
	float osc1LevelEnvs = 1.f;
	float osc2LevelEnvs = 1.f;
	float osc3LevelEnvs = 1.f;
	float osc4LevelEnvs = 1.f;

	for (int i=0;i<jMD_total;i++)
	{
		if (i == jMD_ampVolume)
			{if (destination[i] != NULL) *destination[i] = 1.f;}
		else
			if (destination[i] != NULL) *destination[i] = 0.f;
	}
	
	for (int i=0;i<32;i++)
	{
		if ((Glob->iSrc[i] != 0) && (Glob->iDst[i] != 0))
		{
			if ((source[Glob->iSrc[i]] != NULL) && (destination[Glob->iDst[i]] != NULL))
			{

				if (Glob->iDst[i] == jMD_ampVolume)
				{
					if ( ((Glob->iSrc[i] >= jMS_env1) && (Glob->iSrc[i] <= jMS_env4)) ||
						 ((Glob->iSrc[i] >= jMS_c1)   && (Glob->iSrc[i] <= jMS_c16))  ||
						 (Glob->iSrc[i] == jMS_velocity) || 
						 (Glob->iSrc[i] == jMS_modWheel) )
						{
							if (Glob->rAmt[i] >= 0)
								ampVolumeEnvs *= *source[Glob->iSrc[i]] * Glob->rAmt[i] + (1.f - Glob->rAmt[i]);
							else
							{
								float invAmt = 0.f - Glob->rAmt[i];
								ampVolumeEnvs *= (1.f - *source[Glob->iSrc[i]]) * invAmt + (1.f - invAmt);
							}
						}
					else
						ampVolumeSum += *source[Glob->iSrc[i]] * Glob->rAmt[i];
				}
				else if (Glob->iDst[i] == jMD_osc1Level)
				{
					if ( ((Glob->iSrc[i] >= jMS_env1) && (Glob->iSrc[i] <= jMS_env4)) ||
						 ((Glob->iSrc[i] >= jMS_c1)   && (Glob->iSrc[i] <= jMS_c16))  ||
						 (Glob->iSrc[i] == jMS_velocity) || 
						 (Glob->iSrc[i] == jMS_modWheel) )
						{
							if (Glob->rAmt[i] >= 0)
								osc1LevelEnvs *= *source[Glob->iSrc[i]] * Glob->rAmt[i] + (1.f - Glob->rAmt[i]);
							else
							{
								float invAmt = 0.f - Glob->rAmt[i];
								osc1LevelEnvs *= (1.f - *source[Glob->iSrc[i]]) * invAmt + (1.f - invAmt);
							}
						}
					else
						osc1LevelSum += *source[Glob->iSrc[i]] * Glob->rAmt[i];
				}
				else if (Glob->iDst[i] == jMD_osc2Level)
				{
					if ( ((Glob->iSrc[i] >= jMS_env1) && (Glob->iSrc[i] <= jMS_env4)) ||
						 ((Glob->iSrc[i] >= jMS_c1)   && (Glob->iSrc[i] <= jMS_c16))  ||
						 (Glob->iSrc[i] == jMS_velocity) || 
						 (Glob->iSrc[i] == jMS_modWheel) )
						{
							if (Glob->rAmt[i] >= 0)
								osc2LevelEnvs *= *source[Glob->iSrc[i]] * Glob->rAmt[i] + (1.f - Glob->rAmt[i]);
							else
							{
								float invAmt = 0.f - Glob->rAmt[i];
								osc2LevelEnvs *= (1.f - *source[Glob->iSrc[i]]) * invAmt + (1.f - invAmt);
							}
						}
					else
						osc2LevelSum += *source[Glob->iSrc[i]] * Glob->rAmt[i];
				}
				else if (Glob->iDst[i] == jMD_osc3Level)
				{
					if ( ((Glob->iSrc[i] >= jMS_env1) && (Glob->iSrc[i] <= jMS_env4)) ||
						 ((Glob->iSrc[i] >= jMS_c1)   && (Glob->iSrc[i] <= jMS_c16))  ||
						 (Glob->iSrc[i] == jMS_velocity) || 
						 (Glob->iSrc[i] == jMS_modWheel) )
						{
							if (Glob->rAmt[i] >= 0)
								osc3LevelEnvs *= *source[Glob->iSrc[i]] * Glob->rAmt[i] + (1.f - Glob->rAmt[i]);
							else
							{
								float invAmt = 0.f - Glob->rAmt[i];
								osc3LevelEnvs *= (1.f - *source[Glob->iSrc[i]]) * invAmt + (1.f - invAmt);
							}
						}
					else
						osc3LevelSum += *source[Glob->iSrc[i]] * Glob->rAmt[i];
				}
				else if (Glob->iDst[i] == jMD_osc4Level)
				{
					if ( ((Glob->iSrc[i] >= jMS_env1) && (Glob->iSrc[i] <= jMS_env4)) ||
						 ((Glob->iSrc[i] >= jMS_c1)   && (Glob->iSrc[i] <= jMS_c16))  ||
						 (Glob->iSrc[i] == jMS_velocity) || 
						 (Glob->iSrc[i] == jMS_modWheel) )
						{
							if (Glob->rAmt[i] >= 0)
								osc4LevelEnvs *= *source[Glob->iSrc[i]] * Glob->rAmt[i] + (1.f - Glob->rAmt[i]);
							else
							{
								float invAmt = 0.f - Glob->rAmt[i];
								osc4LevelEnvs *= (1.f - *source[Glob->iSrc[i]]) * invAmt + (1.f - invAmt);
							}
						}
					else
						osc4LevelSum += *source[Glob->iSrc[i]] * Glob->rAmt[i];
				}
				else
					*destination[Glob->iDst[i]] += *source[Glob->iSrc[i]] * Glob->rAmt[i];
			}
		}
	}

	*destination[jMD_ampVolume] = ampVolumeSum * ampVolumeEnvs;
	*destination[jMD_osc1Level] = osc1LevelSum * osc1LevelEnvs;
	*destination[jMD_osc2Level] = osc2LevelSum * osc2LevelEnvs;
	*destination[jMD_osc3Level] = osc3LevelSum * osc3LevelEnvs;
	*destination[jMD_osc4Level] = osc4LevelSum * osc4LevelEnvs;
}
