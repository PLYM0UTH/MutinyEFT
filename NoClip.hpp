#pragma once

#include "includes.hpp"
#include "Classes.hpp"
#include "Settings.hpp"
static float noclipspeed = 1.00001f;
static bool speed = false;
static bool nogravity = true;
namespace NoClip
{
	void Hook(void)
	{
		if (Settings::Player::NoClip)
		{





			hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
			if (!Nav)
				return;

			Vector3 ActualPos = LocalPlayer->GetCoordinate();

			if (LocalPlayer->IsInAVehicule() == true)
			{
				return;
			}
			if (LocalPlayer->GetHealth() < 100)return;
			/// Monter

			if (SAFE_CALL(GetAsyncKeyState)(VK_LSHIFT))
				speed = true;
			else
				speed = false;



			if (speed)
			{
				noclipspeed = 1.0f;
			}
			else
			{
				noclipspeed = 0.1f;

			}


			if (SAFE_CALL(GetAsyncKeyState)('L'))
			{
				Settings::Player::isNoclipWorking = !Settings::Player::isNoclipWorking;

			}

			if (Settings::Player::isNoclipWorking)
			{

		


				Nav->SetRotation(Vector4(0, 0, 0, 0));
			


				if (SAFE_CALL(GetAsyncKeyState)(Settings::Player::ForwardHotkey) & 0x8000)
				{


					LocalPlayer->SetVelocity();
				//	LocalPlayer->SetFreeze(true);

					DWORD64 addr = FiveM::GetCamera();
					Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
					Vector3 newpos = ActualPos;
					newpos.x += (TPSangles.x * noclipspeed);
					newpos.y += (TPSangles.y * noclipspeed);
					newpos.z += (TPSangles.z * noclipspeed);
					LocalPlayer->SetCoordinate(newpos);
					Nav->SetCoordinate(newpos);

				//	LocalPlayer->SetFreeze(false);

				}

				if (SAFE_CALL(GetAsyncKeyState)(Settings::Player::BackwardHotkey) & 0x8000)
				{
					LocalPlayer->SetVelocity();
	

				//	LocalPlayer->SetFreeze(true);
					DWORD64 addr = FiveM::GetCamera();
					Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
					Vector3 newpos = ActualPos;
					newpos.x -= (TPSangles.x * noclipspeed);
					newpos.y -= (TPSangles.y * noclipspeed);
					newpos.z -= (TPSangles.z * noclipspeed);
					LocalPlayer->SetCoordinate(newpos);
					Nav->SetCoordinate(newpos);

				//	LocalPlayer->SetFreeze(false);

				}

			}
		}
	}
}


	
