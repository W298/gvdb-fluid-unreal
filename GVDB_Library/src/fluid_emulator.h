#pragma once

#include "gvdb.h"
#include "fluid_system.h"

class FluidEmulator
{
public:
	bool init(int numpnts = 1500000);
	void reconfigure();
	const char* display(int p = 20);
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