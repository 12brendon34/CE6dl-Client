//
// Created by Brendon on 1/18/2026.
//

#pragma once
#include "engine/engine/Levels/CLevel.h"
#include "games/DeadIsland/Game/Camera/CameraFPPDI.h"
class LevelDI
{
public:
	CLevel *N0000099D; //0x0008
	char pad_0028[8]; //0x0028
	CLevel *N000009A2; //0x0030
	char pad_0038[112]; //0x0038
	char *N000009B2; //0x00B0
	char pad_00B8[96]; //0x00B8
	class UIScreen *m_UIScreen; //0x0118
	char pad_0120[2176]; //0x0120
	class N00001548 *N00001438; //0x09A0
	class N0000155C *N00001439; //0x09A8
	class N00001570 *N0000143A; //0x09B0
	class N00001584 *N0000143D; //0x09C8
	class N00001598 *m_MusicManager; //0x09D0
	class AISpawnSystem_Manager *N0000143F; //0x09D8 //class AISpawnSystem::Manager *N0000143F; //0x09D8
	class Crowd_Manager *N00001440; //0x09E0 //class Crowd::Manager *N00001440; //0x09E0
	class ActionDirector *N00001441; //0x09E8
	class N000015E8 *m_AIManager; //0x09F0
	char pad_09F8[40]; //0x09F8
	class AIDataManager *m_AIDataManager; //0x0A20
	char pad_0A28[8]; //0x0A28
	class ForceFeedback_Manager *N0000164D; //0x0A30 //class ForceFeedback::Manager *N0000164D; //0x0A30
	char pad_0A38[16]; //0x0A38
	class N000016BE *m_LootingManager; //0x0A48
	char pad_0A50[40]; //0x0A50
	class N000016D2 *m_Bloodbaths_Manager; //0x0A78
	char pad_0A80[24]; //0x0A80
	class Dialogs_Manager *m_Dialogs_Manager; //0x0A98//class Dialogs::Manager *m_Dialogs_Manager; //0x0A98
	class N000016FA *m_DynamicObjectsManager; //0x0AA0
	class ChunkObjectsManager *m_ChunkObjectsManager; //0x0AA8
	class N00001722 *m_ChunkObjectsController; //0x0AB0
	class N00001736 *m_StepsSoundManager; //0x0AB8
	char pad_0AC0[8]; //0x0AC0
	class N0000175E *N0000145A; //0x0AC8
	class N00001772 *m_PlayableAreaManager; //0x0AD0
	char pad_0AD8[24]; //0x0AD8
	class N000017C2 *N0000145F; //0x0AF0
	class N000017D6 *m_AIGroupManager; //0x0AF8
	class N000017EA *m_ClimaticMusicManager; //0x0B00
	class N000017FE *m_ClimaticMusicPlayer; //0x0B08
	char pad_0B10[40]; //0x0B10
	class N00001876 *m_MeshLodStateManager; //0x0B38
	char pad_0B40[8]; //0x0B40
	class N0000189E *N0000146A; //0x0B48
	class N000018B2 *N0000146B; //0x0B50
	class N000018C6 *N0000146C; //0x0B58
	char pad_0B60[8]; //0x0B60
	LevelDI *N0000146E; //0x0B68
	char pad_0B70[208]; //0x0B70
	char *N00001489; //0x0C40
	char pad_0C48[8]; //0x0C48
	char *N0000148B; //0x0C50
	char pad_0C58[8]; //0x0C58
	char *N0000148D; //0x0C60
	char pad_0C68[544]; //0x0C68
	class N0000194D *m_AmbientSoundManager; //0x0E88
	char pad_0E90[8]; //0x0E90
	class N00001975 *m_MultisampleSoundManager; //0x0E98
	class N00001939 *m_ParamsReplicator; //0x0EA0
	char pad_0EA8[16]; //0x0EA8
	CameraFPPDI *m_CameraFPPDI; //0x0EB8
	char pad_0EC0[200]; //0x0EC0
	class N0000198A *N000014F2; //0x0F88
	class N0000199E *N000014F3; //0x0F90
	class N000019B2 *N000014F4; //0x0F98
	class N000019C6 *N000014F5; //0x0FA0
	class N000019DA *N000014F6; //0x0FA8
	class N000019EE *N000014F7; //0x0FB0
	class N00001A02 *N000014F8; //0x0FB8
	class N00001A16 *N000014F9; //0x0FC0
	class N00001A2A *N000014FA; //0x0FC8
	class N00001A3E *N000014FB; //0x0FD0
	class N00001A52 *N000014FC; //0x0FD8
	class N00001A66 *N000014FD; //0x0FE0
	char pad_0FE8[64]; //0x0FE8
	class N00001AA3 *m_ConcentrationModeManager; //0x1028
	class N00001A8F *m_NightAggressionManager; //0x1030
	class N00001AB7 *m_NpcAggressionManager; //0x1038
	class N00001ACB *m_PursuitBreakerManager; //0x1040
	char pad_1048[8]; //0x1048
	class N00001AF3 *m_PatrolManager; //0x1050
	class N00001B07 *m_FakeTargetManager; //0x1058
	char pad_1060[8]; //0x1060
	class N00001B1C *m_BulletManager; //0x1068
	char pad_1070[72]; //0x1070
	class N00001B30 *m_StateSaveManager; //0x10B8

	virtual void Function0();
};
