#pragma once

#include "includes.hpp"
#include "Classes.hpp"
#include "native.hpp"
namespace Players
{
	void Hook(void)
	{
	
			hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
			if (!World)
				return;

			hk_Ped* LocalPlayer = World->LocalPlayer();
			if (!LocalPlayer)
				return;

			hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
			if (!LocalPlayer)
				return;


			if (Settings::Player::Semi_Godmod)
			{
				if (LocalPlayer->GetHealth() < 200)
					LocalPlayer->SetMaxHealth();
			}
			if (Settings::Player::Infinite_Armor)
			{
				LocalPlayer->SetArmor(Settings::Player::ArmorToSet);

			}

			if (Settings::Player::Godmod)
			{
				*(bool*)(LocalPlayer + 0x189) = true;
			}

			if (Settings::Player::SetArmor)
			{
				LocalPlayer->SetArmor(Settings::Player::ArmorToSet);
				Settings::Player::SetArmor = false;
			}
			if (Settings::Player::SetHealth)
			{
				LocalPlayer->SetHealth(100 + Settings::Player::HealthToSet);

				Settings::Player::SetHealth = false;
			}
			/*
			if (Settings::Player::NoRagDoll)
			{
				LocalPlayer->Set_Ragdoll(true);
			}
			else 
			{
				LocalPlayer->Set_Ragdoll(false);
			}*/

				
			if (Settings::Player::fastrun)
			{
			//	auto player = PLAYER::PLAYER_PED_ID();
				//NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(player);
				Settings::Player::fastrun = false;

			}
			if (Settings::Player::EnableFovChange)
			{
				DWORD64 addr = FiveM::GetCamera();
				uintptr_t CameraData = *(uintptr_t*)(addr + 0x10);
				*(float*)(CameraData + 0x30) = Settings::Player::FovValue;
				Settings::Player::EnableFovChange = false;
			//	std::cout << *(float*)(CameraData + 0x30);

			//	FiveM::SetFOVZoom(Settings::Player::FovValue);
			}



		

		/*void OnlinePlayerHook()
		{
			ImGui::SetNextWindowSize(ImVec2(600, 300));

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
			ImGui::SetNextWindowBgAlpha(1.0f);
			if (ImGui::Begin("Player MENU", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
			{
				hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
				if (!World)
					return;

				hk_Ped* LocalPlayer = World->LocalPlayer();
				if (!LocalPlayer)
					return;

				hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(FiveM::ReplayInterface);
				if (!ReplayInterface)
					return;

				hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
				if (!PedInterface)
					return;

				for (int index = 0; index < PedInterface->PedMaximum(); index++)
				{
					hk_Ped* Peds = PedInterface->PedList()->Ped(index);
					if (!Peds) continue;

					bool IsPed = false;

					auto ped_type = Peds->GetPedType();
					if (!ped_type)
					{
						continue;
					}
					ped_type = ped_type << 11 >> 25;

					if (ped_type != 2) {
						IsPed = true;

					}

					if (IsPed)
					{
						continue;
					}


					ImVec2 Ped_Location = FiveM::WorldToScreen(Peds->GetCoordinate());
					if (!IsOnScreen(Ped_Location)) continue;

					ImVec2 LocalPlayer_Location = FiveM::WorldToScreen(LocalPlayer->GetCoordinate());
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
					ImGui::SetCursorPosX( 10);
					const char* PlayerID = "Player ID : " + index;

					ImGui::Text(PlayerID);


				}

				ImGui::PopStyleVar(4);
				ImGui::End();
			}
		}
		*/
		
	}
}