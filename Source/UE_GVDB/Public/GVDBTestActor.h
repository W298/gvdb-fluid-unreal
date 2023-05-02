// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "gl/glew.h"
#include "gvdb.h"
#include "GameFramework/Actor.h"
#include "GVDBTestActor.generated.h"

UCLASS()
class UE_GVDB_API AGVDBTestActor : public AActor
{
	GENERATED_BODY()
	
public:
	FString logBuffer[100];
	FColor logColor[100];
	int logCursor = 0;
	FString lastErrorMsg;
	int updateIndex;

	int w, h;
	int gl_screen_tex;
	Vector3DF m_pretrans;
	Vector3DF m_scale;
	Vector3DF m_angs;
	Vector3DF m_trans;
	VolumeGVDB gvdb;

	// Sets default values for this actor's properties
	AGVDBTestActor();

	void PrintMsg(FString msg, FColor color)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0, color, msg);
	}

	int AddToBuffer(FString msg, FColor color)
	{
		logBuffer[logCursor] = msg;
		logColor[logCursor++] = color;
		return logCursor - 1;
	}

	void UpdateBuffer(int index, FString msg, FColor color)
	{
		logBuffer[index] = msg;
		logColor[index] = color;
	}

	bool GVDBInit()
	{
		const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		w = viewportSize.X;
		h = viewportSize.Y;

		m_pretrans.Set(-125, -160, -125);
		m_scale.Set(1, 1, 1);
		m_angs.Set(0, 0, 0);
		m_trans.Set(0, 0, 0);

		// Initialize GVDB
		gvdb.SetDebug(true);
		gvdb.SetVerbose(true);
		gvdb.SetCudaDevice(GVDB_DEV_FIRST);
		gvdb.Initialize();
		gvdb.AddPath("C:/Users/lutca/source/repos/gvdb-voxels/source/shared_assets/");

		// Load VBX
		char scnpath[1024];
		if (!gvdb.getScene()->FindFile("explosion.vbx", scnpath)) {
			lastErrorMsg = "Cannot find vbx file.";
			return false;
		}

		TCHAR scnpath_tchar[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, scnpath, strlen(scnpath), scnpath_tchar, 256);

		AddToBuffer(FString::Printf(TEXT("Load VBX from %s"), scnpath_tchar), FColor::Cyan);
		gvdb.SetChannelDefault(16, 16, 16);
		gvdb.LoadVBX(scnpath);
		AddToBuffer("Load VBX Success", FColor::Green);

		// Set volume params
		gvdb.SetTransform(m_pretrans, m_scale, m_angs, m_trans);
		gvdb.getScene()->SetSteps(.25f, 16, .25f);			// Set raycasting steps
		gvdb.getScene()->SetExtinct(-1.0f, 1.0f, 0.0f);		// Set volume extinction
		gvdb.getScene()->SetVolumeRange(0.1f, 0.0f, .5f);	// Set volume value range
		gvdb.getScene()->SetCutoff(0.005f, 0.005f, 0.0f);
		gvdb.getScene()->SetBackgroundClr(0.1f, 0.2f, 0.4f, 1.0);
		gvdb.getScene()->LinearTransferFunc(0.00f, 0.25f, Vector4DF(0, 0, 0, 0), Vector4DF(1, 0, 0, 0.05f));
		gvdb.getScene()->LinearTransferFunc(0.25f, 0.50f, Vector4DF(1, 0, 0, 0.05f), Vector4DF(1, .5f, 0, 0.1f));
		gvdb.getScene()->LinearTransferFunc(0.50f, 0.75f, Vector4DF(1, .5f, 0, 0.1f), Vector4DF(1, 1, 0, 0.15f));
		gvdb.getScene()->LinearTransferFunc(0.75f, 1.00f, Vector4DF(1, 1, 0, 0.15f), Vector4DF(1, 1, 1, 0.2f));
		gvdb.CommitTransferFunc();

		// Create Camera 
		Camera3D* cam = new Camera3D;
		cam->setFov(50.0);
		cam->setOrbit(Vector3DF(20, 30, 0), Vector3DF(0, 0, 0), 700, 1.0);
		gvdb.getScene()->SetCamera(cam);

		// Create Light
		Light* lgt = new Light;
		lgt->setOrbit(Vector3DF(299, 57.3f, 0), Vector3DF(132, -20, 50), 200, 1.0);
		gvdb.getScene()->SetLight(0, lgt);

		// Add render buffer
		AddToBuffer(FString::Printf(TEXT("Creating screen buffer. %d x %d"), w, h), FColor::Cyan);
		gvdb.AddRenderBuf(0, w, h, 4);

		gl_screen_tex = -1;

		glGenTextures(1, (GLuint*)(&gl_screen_tex));
		glBindTexture(GL_TEXTURE_2D, *(&gl_screen_tex));
		// checkGL("glBindTexture (createScreenQuadGL)");
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		// checkGL("glTexImage2D (createScreenQuadGL)");
		glBindTexture(GL_TEXTURE_2D, 0);

		gvdb.PrepareVDB();

		VDBInfo vdbInfo = gvdb.getVDBInfoStruct();
		const FColor vdbTextColor = FColor(255, 160, 130, 255);

		AddToBuffer("", vdbTextColor);
		AddToBuffer("[VDB Info]", vdbTextColor);

		FString res_str = "res                     ";
		for (int i = 0; i < MAXLEV; i++)
		{
			res_str += FString::Printf(TEXT("%d"), vdbInfo.res[i]);
			if (i < MAXLEV - 1) res_str += "  /  ";
		}
		res_str += "                         (Lateral resolution of each node per level)";
		AddToBuffer(res_str, vdbTextColor);

		FString nodecnt_str = "nodecnt                 ";
		for (int i = 0; i < MAXLEV; i++)
		{
			nodecnt_str += FString::Printf(TEXT("%d"), vdbInfo.nodecnt[i]);
			if (i < MAXLEV - 1) nodecnt_str += "  /  ";
		}
		nodecnt_str += "                        (Total number of allocated nodes per level)";
		AddToBuffer(nodecnt_str, vdbTextColor);

		FString nodewid_str = "nodewid                 ";
		for (int i = 0; i < MAXLEV; i++)
		{
			nodewid_str += FString::Printf(TEXT("%d"), vdbInfo.nodewid[i]);
			if (i < MAXLEV - 1) nodewid_str += "  /  ";
		}
		nodewid_str += "                 (Size of a node at each level in bytes)";
		AddToBuffer(nodewid_str, vdbTextColor);

		AddToBuffer(FString::Printf(TEXT("atlas_cnt               [%d, %d, %d]                        (Number of bricks on each axis of the atlas)"), vdbInfo.atlas_cnt.x, vdbInfo.atlas_cnt.y, vdbInfo.atlas_cnt.z), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("atlas_res               [%d, %d, %d]                     (Total resolution in voxels of the atlas)"), vdbInfo.atlas_res.x, vdbInfo.atlas_res.y, vdbInfo.atlas_res.z), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("atlas_apron             %d                                   (Apron size)"), vdbInfo.atlas_apron), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("brick_res               %d                                  (Resolution of a single brick)"), vdbInfo.brick_res), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("top_lev                 %d                                   (Top level)"), vdbInfo.top_lev), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("epsilon                 %.3f                               (Epsilon used for voxel ray tracing)"), vdbInfo.epsilon), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("bmin                    [%.3f, %.3f, %.3f]               (Inclusive minimum of axis-aligned bounding box in voxels)"), vdbInfo.bmin.x, vdbInfo.bmin.y, vdbInfo.bmin.z), vdbTextColor);
		AddToBuffer(FString::Printf(TEXT("bmax                    [%.3f, %.3f, %.3f]         (Inclusive maximum of axis-aligned bounding box in voxels)"), vdbInfo.bmax.x, vdbInfo.bmax.y, vdbInfo.bmax.z), vdbTextColor);

		AddToBuffer("", vdbTextColor);
		return true;
	}

	void GVDBRender()
	{
		gvdb.TimerStart();
		gvdb.Render(SHADE_VOLUME, 0, 0);
		float rtime = gvdb.TimerStop();
		UpdateBuffer(updateIndex, FString::Printf(TEXT("Render volume. %6.3f ms"), rtime), FColor::Magenta);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
