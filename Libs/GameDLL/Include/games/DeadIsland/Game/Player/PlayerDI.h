//
// Created by Brendon on 1/18/2026.
//

#pragma once
#include <cstdint>

class PlayerDI {
public:
	char pad_0008[24]; //0x0008
	char *N00000EBB; //0x0030
	char pad_0038[1872]; //0x0038
	char *N000011AD; //0x07A0
	char pad_07A8[8]; //0x07A8
	float m_PlayerPosition; //0x07B0
	float N0000123B; //0x07B4
	float N000011B0; //0x07B8
	char pad_07BC[84]; //0x07BC
	char *N000011BB; //0x0810
	char pad_0818[96]; //0x0818
	class PlayerAddHeadGeom *m_PlayerAddHeadGeom; //0x0878
	char pad_0880[96]; //0x0880
	class InventoryContainerDI *m_InventoryContainerDI; //0x08E0
	class InventoryContainerDI *m_InventoryContainerDI_1; //0x08E8
	class InventoryContainerDI *m_InventoryContainerDI_2; //0x08F0
	class InventoryContainerDI *m_InventoryContainerDI_3; //0x08F8
	class InventoryContainerDI *m_InventoryContainerDI_4; //0x0900
	char pad_0908[576]; //0x0908
	class MoveController *m_MoveController; //0x0B48
	class DeadController *m_DeadController; //0x0B50
	class LookController *m_LookController; //0x0B58
	class N0000103F *m_GrabController; //0x0B60
	class VehicleController *m_VehicleController; //0x0B68
	class N00001067 *m_CinematicController; //0x0B70
	class TriggerController *m_TriggerController; //0x0B78
	class N0000108F *m_LadderController; //0x0B80
	class StationaryCannonController *m_StationaryCannonController; //0x0B88
	class N000010B7 *m_HealingController; //0x0B90
	class RepairWeaponController *m_RepairWeaponController; //0x0B98
	class KnockDownController *m_KnockDownController; //0x0BA0
	class N000010F3 *m_BreakDoorController; //0x0BA8
	class StompFinisherController *m_StompFinisherController; //0x0BB0
	class N0000111B *m_WeaponMeleeController; //0x0BB8
	class N00000FDB *m_WeaponFireControllerRight; //0x0BC0
	class WeaponFireControllerLeft *m_WeaponFireControllerLeft; //0x0BC8
	class WeaponThrowController *m_WeaponThrowController; //0x0BD0
	class WeaponBowController *m_WeaponBowController; //0x0BD8
	class InjectionController *m_InjectionController; //0x0BE0
	class ObjectsCarryController *m_ObjectsCarryController; //0x0BE8
	class DialogController *m_DialogController; //0x0BF0
	class EquipmentController *m_EquipmentController; //0x0BF8
	class DefensiveController *m_DefensiveController; //0x0C00
	class EdgeGrabController *m_EdgeGrabController; //0x0C08
	class InteractionController *m_InteractionController; //0x0C10
	class N00000EFF *m_SwimController; //0x0C18
	class LockpickController *m_LockpickController; //0x0C20
	class RopeLocomotionController *m_RopeLocomotionController; //0x0C28
	class PVPGrabController *m_PVPGrabController; //0x0C30
	class PlayerGrabAttackController *m_PlayerGrabAttackController; //0x0C38
	class ZombieAbilitiesController *m_ZombieAbilitiesController; //0x0C40
	class ChargeController *m_ChargeController; //0x0C48
	class ZipLineController *m_ZipLineController; //0x0C50
	class TutorialController *m_TutorialController; //0x0C58
	class InfectionController *m_InfectionController; //0x0C60
	class ReactionController *m_ReactionController; //0x0C68
	class LandingController *m_LandingController; //0x0C70
	class SpecialUseController *m_SpecialUseController; //0x0C78
	class ShieldController *m_ShieldController; //0x0C80
	class SpikesHitController *m_SpikesHitController; //0x0C88
	class ZombieVehicleAttackController *m_ZombieVehicleAttackController; //0x0C90
	class SelfieController *m_SelfieController; //0x0C98
	char pad_0CA0[24]; //0x0CA0
	char *N00001255; //0x0CB8
	char pad_0CC0[8]; //0x0CC0
	char *N00001257; //0x0CC8
	char pad_0CD0[24]; //0x0CD0
	char *N0000125B; //0x0CE8
	char pad_0CF0[72]; //0x0CF0
	char *N00001268; //0x0D38
	char pad_0D40[24]; //0x0D40
	char *N0000126C; //0x0D58
	char pad_0D60[8]; //0x0D60
	char *N0000126E; //0x0D68
	char pad_0D70[8]; //0x0D70
	char *N00001270; //0x0D78
	char pad_0D80[56]; //0x0D80
	char *N00001278; //0x0DB8
	char pad_0DC0[8]; //0x0DC0
	char *N0000127A; //0x0DC8
	char pad_0DD0[16]; //0x0DD0
	char *N0000127D; //0x0DE0
	char pad_0DE8[476]; //0x0DE8
	float N000013F8; //0x0FC4
	char pad_0FC8[328]; //0x0FC8
	float N000012E2; //0x1110
	float N0000131E; //0x1114
	float N00001316; //0x1118
	float N00001321; //0x111C
	float N000012E3; //0x1120
	char pad_1124[16]; //0x1124
	float N00001372; //0x1134
	float N000012E6; //0x1138
	float N00001326; //0x113C
	float N000012E7; //0x1140
	float N00001329; //0x1144
	float N000012E8; //0x1148
	char pad_114C[64]; //0x114C
	float N00001432; //0x118C
	float N000012F3; //0x1190
	float N00001339; //0x1194
	float N000012F4; //0x1198
	char pad_119C[4]; //0x119C
	float N000012F5; //0x11A0
	char pad_11A4[8]; //0x11A4
	float N0000132E; //0x11AC
	char pad_11B0[8]; //0x11B0
	float N00001439; //0x11B8
	float N00001331; //0x11BC
	float m_PlayerPosition_2; //0x11C0
	float N00001337; //0x11C4
	float N000012FA; //0x11C8
	float N00001341; //0x11CC
	float N000012FB; //0x11D0
	float N00001343; //0x11D4
	float N000012FC; //0x11D8
	float N00001345; //0x11DC
	float N000012FD; //0x11E0
	int32_t N00001347; //0x11E4
	int32_t N000012FE; //0x11E8
	float N00001349; //0x11EC
	float m_PlayerPosition_3; //0x11F0
	float N0000134B; //0x11F4
	float N00001300; //0x11F8
	int32_t m_BodyRotSynchroAnim; //0x11FC
	float m_BodyRotSynchroAnimTime; //0x1200
	float m_Health; //0x1204
	float m_LastHealth; //0x1208
	char pad_120C[1088]; //0x120C

	virtual void Function0();
};
