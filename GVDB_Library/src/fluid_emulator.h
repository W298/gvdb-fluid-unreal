#pragma once

#include "gvdb.h"
#include "fluid_system.h"

class FluidEmulator
{
public:
	bool init(int numpnts, float3* obsMinAry, float3* obsMaxAry, int obsCnt);
	void reconfigure();
	Vector3DF* display();
	void simulate();

	VolumeGVDB	gvdb;
	FluidSystem	fluid;

	DataPtr		m_pntpos;
	DataPtr		m_pntclr;

	bool		m_rebuild_gpu;
	bool		m_use_color;
	bool		m_simulate;
	int			m_numpnts;
	float		m_time;
	int			m_frame;
	int			m_sample;
	float		m_radius;
	Vector3DF	m_origin;
};