#include "fluid_emulator.h"

using namespace nvdb;

bool FluidEmulator::init(int numpnts)
{
	m_time = 0;
	m_simulate = true;
	m_use_color = true;
	m_frame = 0;
	m_sample = 0;
	m_origin = Vector3DF(0, 0, 0);
	m_radius = 1.0;
	m_rebuild_gpu = true;
	srand(6572);

	// Initialize 
	fluid.SetDebug(false);

	gvdb.SetDebug(false);
	gvdb.SetVerbose(false);
	gvdb.SetProfile(false, true);
	gvdb.SetCudaDevice(GVDB_DEV_FIRST);
	gvdb.Initialize();

	// Set volume params
	gvdb.getScene()->SetSteps(0.25f, 16, 0.25f);			// Set raycasting steps
	gvdb.getScene()->SetExtinct(-1.0f, 1.5f, 0.0f);		// Set volume extinction
	gvdb.getScene()->SetVolumeRange(0.0f, 3.0f, -1.0f);	// Set volume value range
	gvdb.getScene()->SetCutoff(0.005f, 0.01f, 0.0f);
	gvdb.getScene()->SetBackgroundClr(0.8f, 0.8f, 0.8f, 1.0f);

	// Configure volume
	reconfigure();

	// Initialize Fluid System
	m_numpnts = numpnts;

	fluid.Initialize();
	fluid.Start(m_numpnts);

	Vector3DF ctr = (fluid.GetGridMax() + fluid.GetGridMin()) * Vector3DF(0.5, 0.5, 0.5);

	// Create Camera 
	Camera3D* cam = new Camera3D;
	cam->setFov(50.0);
	cam->setOrbit(Vector3DF(50, 30, 0), ctr, 1200, 1.0);
	gvdb.getScene()->SetCamera(cam);

	// Create Light
	Light* lgt = new Light;
	lgt->setOrbit(Vector3DF(20, 60, 0), ctr, 1000, 1.0);
	gvdb.getScene()->SetLight(0, lgt);

	return true;
}

void FluidEmulator::reconfigure()
{
	// Configure new GVDB volume
	gvdb.Configure(3, 3, 3, 3, 5);

	gvdb.DestroyChannels();

	gvdb.SetChannelDefault(16, 16, 1);
	gvdb.AddChannel(0, T_FLOAT, 1);
	if (m_use_color) {
		gvdb.AddChannel(1, T_UCHAR4, 1);
		gvdb.SetColorChannel(1);
	}
}

Vector3DF* FluidEmulator::display()
{
	if (m_simulate)
	{
		simulate();
		m_frame++;
		m_sample = 0;
	}

	return fluid.TransferParticlePosition();
}

void FluidEmulator::simulate()
{
	m_time += 1.0;

	// Run fluid simulation
	PERF_PUSH("Simulate");
	fluid.Run();
	PERF_POP();

	// Setup GPU points for GVDB
	#ifdef USE_CPU_COPY
											//-- transfer point data from cpu
											// common use case: reading data from disk, import from a device
		gvdb.CommitData(m_pntpos, m_numpnts, (char*)fluid.getPos(0), 0, sizeof(Vector3DF));
		gvdb.CommitData(m_pntclr, m_numpnts, (char*)fluid.getClr(0), 0, sizeof(uint));
	#else 
											//-- assign data already on gpu
											// common use case: simulation already on gpu
		gvdb.SetDataGPU(m_pntpos, m_numpnts, fluid.getBufferGPU(FPOS), 0, sizeof(Vector3DF));
		gvdb.SetDataGPU(m_pntclr, m_numpnts, fluid.getBufferGPU(FCLR), 0, sizeof(uint));
	#endif

	DataPtr pntvel, clrpos;
	gvdb.SetPoints(m_pntpos, pntvel, m_use_color ? m_pntclr : clrpos);

	// Rebuild Topology
	PERF_PUSH("Topology");

	if (m_rebuild_gpu) {
		// GPU rebuild
		gvdb.RebuildTopology(m_numpnts, m_radius * 2.0f, m_origin);
		gvdb.FinishTopology(false, true);
	}
	else {
		// CPU rebuild
		Vector3DF* fpos = fluid.getPos(0);				// fluid positions
		uint* fclr = fluid.getClr(0);					// fluid colors
		Vector3DF p1;
		for (int n = 0; n < m_numpnts; n++) {
			p1 = (*fpos++) + m_origin;	// get fluid sim pos		
			if (n % 2 == 0) gvdb.ActivateSpace(p1);					// Activate GVDB topology
		}
		gvdb.FinishTopology();
	}
	PERF_POP();

	// Update and Clear Atlas	
	gvdb.UpdateAtlas();

	// Insert and Gather Points-to-Voxels
	int scPntLen = 0, subcell_size = 4;
	gvdb.InsertPointsSubcell(subcell_size, m_numpnts, m_radius * 2.0f, m_origin, scPntLen);
	gvdb.GatherLevelSet(subcell_size, m_numpnts, m_radius, m_origin, scPntLen, 0, 1);
	gvdb.UpdateApron(0, 3.0f);
	if (m_use_color) gvdb.UpdateApron(1, 0.0f);
}
