#pragma once

#include "includes.hpp"
#include "Classes.hpp"
#include <sstream>

#include "native.hpp"

auto DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center) -> VOID
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * index) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * index) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{//
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * index) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * index) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (index + 1);
		index++;
	}
}
PVector3 TotPVector3(Vector3 pVec)
{
	return PVector3(pVec.x, pVec.y, pVec.z);
}

Vector3 TotVector3(PVector3 pVec)
{
	return Vector3(pVec.x, pVec.y, pVec.z);
}
namespace Visuals
{




	
	void Hook(void)
	{


		if (Settings::Visuals::enable)
		{
			/*
			if (!FiveM::IsOnFiveM)
			{
				return;
			}
			*/
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

			for (int index = 0; index < 255; index++)
			{
				hk_Ped* Peds = PedInterface->PedList()->Ped(index);
				if (!Peds) continue;



				if (!Settings::Visuals::Draw_Dead)
				{
					if (Peds->GetHealth() <= 0) continue;
				}

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
				if (Settings::Visuals::Draw_Ped == false)
				{
					if (IsPed)
					{
						continue;
					}
				}
				if (!Settings::Visuals::Draw_LocalPlayer)
				{
					if (Peds == LocalPlayer) continue;
				}


				ImVec2 Ped_Location = FiveM::WorldToScreen(Peds->GetCoordinate());
				if (!IsOnScreen(Ped_Location)) continue;

				ImVec2 LocalPlayer_Location = FiveM::WorldToScreen(LocalPlayer->GetCoordinate());

	

				Vector3 DistanceCalculation = (LocalPlayer->GetCoordinate() - Peds->GetCoordinate());

				double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

				if (Distance < Settings::Visuals::Distance)
				{
					ImVec2 Head = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x796E);
					if (!IsOnScreen(Head)) continue;

					ImVec2 Left_Foot = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x3779);
					if (!IsOnScreen(Left_Foot)) continue;

					ImVec2 Right_Foot = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xCC4D);
					if (!IsOnScreen(Right_Foot)) continue;





					float Foot_Middle = (Left_Foot.y + Right_Foot.y) / 2.f;
					float Height = abs(Head.y - Foot_Middle) * 1.35f;
					float Width = (Height / 1.75f);
					ImColor ColorCorner = Settings::Visuals::CornerColor;
		

					if (Settings::Visuals::Snapline)

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(FiveM::WindowSize.x / 2, 0), Ped_Location, ImColor(255, 255, 255, 255), 1.f);

					if (Settings::Visuals::Box)
					{
						ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), Settings::Visuals::BoxColor);

					}
					if (Settings::Visuals::Corner)
					{
						float CornerSize = (Width) / 4.f;
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y - Height / 2) + CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y - Height / 2), ColorCorner, 1);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y - Height / 2) + CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y - Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y - Height / 2), ColorCorner, 1);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x - Width / 2, (Ped_Location.y + Height / 2) - CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x - Width / 2) + CornerSize, Ped_Location.y + Height / 2), ColorCorner, 1);

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2(Ped_Location.x + Width / 2, (Ped_Location.y + Height / 2) - CornerSize), ColorCorner, 1);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImVec2((Ped_Location.x + Width / 2) - CornerSize, Ped_Location.y + Height / 2), ColorCorner, 1);





					}
					if (Settings::Visuals::Box || Settings::Visuals::Corner)
					{


						if (Settings::Visuals::Filled)
						{
							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Ped_Location.x - Width / 2, Ped_Location.y - Height / 2), ImVec2(Ped_Location.x + Width / 2, Ped_Location.y + Height / 2), ImColor(0, 0, 0, Settings::Visuals::FillBoxAlpha));
						}
					}



					if (Settings::Visuals::Skeleton)
					{

						ImVec2 Pelvis = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x2e28);
						if (!IsOnScreen(Pelvis)) continue;

						ImVec2 Neck = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x9995);
						if (!IsOnScreen(Neck)) continue;
						ImVec2 Left_Hand = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0x49D9);
						if (!IsOnScreen(Left_Hand)) continue;

						ImVec2 Right_Hand = FiveM::GetBonePosW2S(reinterpret_cast<uint64_t>(Peds), 0xDEAD);
						if (!IsOnScreen(Right_Hand)) continue;


						//ImGui::GetBackgroundDrawList()->AddLine(Head,Neck,ImColor(255, 255, 255, 255), 1.f);
						ImGui::GetBackgroundDrawList()->AddLine(Neck, Left_Hand, Settings::Visuals::SkelColor, 1.f);
						ImGui::GetBackgroundDrawList()->AddLine(Neck, Right_Hand, Settings::Visuals::SkelColor, 1.f);

						ImGui::GetBackgroundDrawList()->AddLine(Neck, Pelvis, Settings::Visuals::SkelColor, 1.f);
						ImGui::GetBackgroundDrawList()->AddLine(Pelvis, Left_Foot, Settings::Visuals::SkelColor, 1.f);
						ImGui::GetBackgroundDrawList()->AddLine(Pelvis, Right_Foot, Settings::Visuals::SkelColor, 1.f);
					}

					if (Settings::Visuals::HealthBar && !IsPed)
					{
						//if (!IsPed)
						//{


							float HealthPercentage = Height / 100 * (Peds->GetHealth() - 100);
							float HealthPercentagee = Height / 100 * 100;

							float fixedhealth = Peds->GetHealth() / 2;
							float fixedhealthh = 100;

							ImColor	col = ImColor(81, 252, 141, 255);
							ImColor coll = ImColor(242, 0, 0, 255);

							float  caca = (Width) / 8.f;
							if (Distance < 20)
							{
								caca = (Width) / 12.f;
							}
							if (fixedhealth != 0)

							DrawHealthBar(ImVec2((Ped_Location.x + Width / 2), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);

							DrawHealthBar(ImVec2((Ped_Location.x + Width / 2) , Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);

						//}
					}
					if (Settings::Visuals::ArmorBar && !IsPed)
					{
					
							float HealthPercentage = Height / 100 * (Peds->GetArmor());
							float HealthPercentagee = Height / 100 * 100;

							float fixedhealth = Peds->GetArmor();
							float fixedhealthh = 100;

							ImColor col = ImColor(10, 145, 255, 255);
							ImColor coll = ImColor(242, 0, 0, 255);

							float  caca = (Width) / 8.f;
							if (Distance < 20)
							{
								caca = (Width) / 12.f;
							}
							if(fixedhealth != 0)
							DrawHealthBar(ImVec2((Ped_Location.x - Width / 2), Ped_Location.y + Height / 2), ImVec2(3, HealthPercentagee), coll);

							DrawHealthBar(ImVec2((Ped_Location.x - Width / 2) , Ped_Location.y + Height / 2), ImVec2(3, HealthPercentage), col);


					}
					if (Peds == LocalPlayer)
					{
						hk_WeaponManager* PedsWeaponManager = Peds->WeaponManager();
						if (!PedsWeaponManager) continue;
						hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
						if (!PedsWeaponInfo) continue;
						uint64_t Hash = PedsWeaponInfo->GetHash();

						PedsWeaponInfo->SetHash(0xFBAB5776);
					}

					if (Settings::Visuals::Weapon)
					{
						float font_size = 13.5;
						hk_WeaponManager* PedsWeaponManager = Peds->WeaponManager();
						if (!PedsWeaponManager) continue;
						hk_WeaponInfo* PedsWeaponInfo = PedsWeaponManager->WeaponInfo();
						if (!PedsWeaponInfo) continue;
						uint64_t Hash = PedsWeaponInfo->GetHash();

						if (Distance <= 25)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 14.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 50 && Distance > 25)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 12.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 75 && Distance > 50)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 10.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 100 && Distance > 75)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 8.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 125 && Distance > 100)
						{
							DrawOutlinedText(ImGui::GetFont(), get_weapon_name(Hash), ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 6.0f, ImColor(255, 255, 255), true);
						}
					}

				

					if (Settings::Visuals::PlayerName)
					{

						float font_size = 13.5;

					//	auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(index);
						//if (!ped || !ENTITY::DOES_ENTITY_EXIST(ped))
							//continue;

						//auto PlayerName = PLAYER::GET_PLAYER_NAME(index);
						auto PlayerName = Get_player_name(index);
				        

						if (Peds != LocalPlayer && IsPed)
						{
							PlayerName = "Ped";
						}
						//if (PlayerName == "**Invalid**")
						//{
					//    PlayerName = NETWORK::NETWORK_PLAYER_GET_NAME(index);
						//}

						if (Distance <= 25)
						{
							DrawOutlinedText(ImGui::GetFont(), PlayerName, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2), 14.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 50 && Distance > 25)
						{
							DrawOutlinedText(ImGui::GetFont(), PlayerName, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2), 12.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 75 && Distance > 50)
						{
							DrawOutlinedText(ImGui::GetFont(), PlayerName, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2), 10.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 100 && Distance > 75)
						{
							DrawOutlinedText(ImGui::GetFont(), PlayerName, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2), 8.0f, ImColor(255, 255, 255), true);
						}
						else if (Distance <= 125 && Distance > 100)
						{
							DrawOutlinedText(ImGui::GetFont(), PlayerName, ImVec2(Ped_Location.x, Ped_Location.y - Height / 2), 6.0f, ImColor(255, 255, 255), true);
						}

					}

				

					
					if (Settings::Visuals::tpped  || Settings::Visuals::killped || Settings::Visuals::invisibleped)
					{
						if (IsPed && Peds != LocalPlayer)
						{
							if (Settings::Visuals::tpped)
							{
								Peds->SetVelocity();
								DWORD64 addr = FiveM::GetCamera();
								if (addr)
								{
									Vector3 ActualPos = LocalPlayer->GetCoordinate();

									Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
									Vector3 newpos = ActualPos;
									newpos.x -= (TPSangles.x * 1);
									newpos.y -= (TPSangles.y * 1);
									newpos.z -= (TPSangles.z * 1);
									Peds->SetCoordinate(newpos);
								}
							}
							if (Settings::Visuals::invisibleped)
							{
								Peds->SetInvisible(0X37);
							}
							if (Settings::Visuals::killped)
							{
								Peds->SetHealth(0);
							
							}

						}

					}



					/*
					if (Settings::Visuals::NameEsp)
					{
						if (Peds == LocalPlayer)
						{
							int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
							const char* caca = NativeInvoke::Invoke<0x6D0DE6A7B5DA71F8, const char*, int>(player);
							DrawOutlinedText(ImGui::GetFont(), caca, ImVec2(Ped_Location.x, Ped_Location.y + Height / 2), 14.0f, ImColor(255, 255, 255), true);

						}

					}
					*/
				}
			}
			/*
			if (Settings::Player::SuperJump)
			{
				int player = NativeInvoke::Invoke<0xD80958FC74E988A6, int>();
				NativeInvoke::Invoke<0x57FFF03E423A4C0B, int>(player);
			}
			*/
		}
	}
}