#pragma once

namespace Settings
{
	namespace Player
	{
		inline bool enable = false;

		inline bool Godmod = false;
		inline bool Semi_Godmod = false;
		inline bool Infinite_Armor = false;
		inline bool SetHealth = false;
		inline bool fastrun = false;
		inline bool SetArmor = false; 
		inline int RunSpeedToSet = 1;

		inline int HealthToSet = 100;
		inline int ArmorToSet = 100;
		inline bool NoClip = false; 
		inline int noclipspeed = false;
		inline int isNoclipWorking = true;


		inline int ForwardHotkey = 90;
		inline int BackwardHotkey = 0x53;

		inline bool EnableFovChange = false;
		inline bool SuperJump = false;
		inline bool TpToWaypoint = false;
		inline bool NoRagDoll = false;
		inline float FovValue = 50;

		

	}
	namespace Weapon
	{
		inline bool enable = false;

		inline bool No_Recoil = false;
		inline bool No_Spread = false;
		inline bool InfiniteAmmo = false;
		inline bool NoRangeLimit = false;
		inline bool SetAmmo = false;
		inline bool ExplosiveAmmo = false;
		inline bool NoReload = false;
		inline int AmmoToSet = 30;
		inline bool GiveWeapon = false;
		inline bool GiveAllWeapon = false;
		inline bool NoShot = false;

	}
	namespace Aimbot
	{
		inline bool Aimbot = false;
		inline bool Draw_Fov = false;
		inline bool PreviewTarget = false;
		inline int AimbotFov = 30;
		inline int AimbotSmooth = 1;
		inline int TypeOfTarget = 0;
		inline const char *AimbotTarget[]{ "All", "Only Player", "Only Ped" };
		inline int DistanceAimbotLimit = 150;
		inline int AimbotBone = 0;
		inline const char* AimbotBones[]{ "Head", "Body", "Leg left", "Leg right", "Arm right", "Arm left" };
		inline int AimbotTypes = 0;

		inline const char* AimbotType[]{ "Mouse aim", "Memory aim" };

		inline int Hotkey = 2;
		inline bool rapidfire = false;
		inline bool crosshair = false;
		inline bool silentaim = false;
		inline bool Check_Fov = false;

		inline bool magic = false;
		inline bool aimmousewhilesilent = false;

	}

	namespace Visuals
	{

		inline bool enable = false;
		inline bool Box = false;
		inline bool Filled = false;
		inline bool Corner = false; 
		inline bool TroiDBox = false;
		inline bool Skeleton = false;
		inline bool Snapline = false;
		inline bool HealthBar = false;
		inline bool ArmorBar = false;
		inline bool Weapon = false;
		inline bool DistanceESP = false;
		inline bool NameEsp = false;
		inline bool PreviewEsp = false;
		inline bool tpped = false;
		inline bool invisibleped = false; 
		inline bool killped = false;
		inline bool PlayerName = false;
		inline bool VisibleCheck = false;

		inline bool Draw_LocalPlayer = false;
		inline bool Draw_Dead = false;
		inline bool Draw_Ped = false; 

		inline int Distance = 250;
		inline int FillBoxAlpha = 100;

		inline ImColor BoxColor = ImColor(255, 255, 255, 255);
		inline ImColor CornerColor = ImColor(33, 140, 176, 255);
		inline ImColor SkelColor = ImColor(255, 255, 255, 255);
	}

	namespace vehicle
	{
		inline bool enable = false;

		inline bool godmode = false;
		inline bool fastspeed = false; 
		inline bool nogravity = false; 
		inline bool setmaxhealth = false;
		inline int Speed = 10; 
	}

	namespace misc
	{
		inline int Menu_Hotkey = 33;
	}

	namespace TempColor
	{
		inline float Box[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float Corner[4] = { 33.f, 140.f, 176.f, 255.f };

		inline float Skeleton[4] = { 255.f, 255.f, 255.f, 255.f };


	}
}