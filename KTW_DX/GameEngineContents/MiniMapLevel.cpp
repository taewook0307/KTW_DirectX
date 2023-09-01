﻿#include "PreCompile.h"
#include "MiniMapLevel.h"
#include "MiniMapCharacter.h"

#include "Map.h"

MiniMapLevel::MiniMapLevel()
{
}

MiniMapLevel::~MiniMapLevel()
{
}

void MiniMapLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild("Resources\\Texture\\Map");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	size_t FileSize = Files.size();

	for (size_t i = 0; i < FileSize; i++)
	{
		GameEngineFile& File = Files[i];
		GameEngineTexture::Load(File.GetStringPath());
	}

	GameEngineSprite::CreateSingle("CupHead_MiniMap.png");
	
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });

	/*MiniMap = CreateActor<Map>(UpdateOrder::BackGround);
	MiniMap->MapInit("CupHead_MiniMap.png");*/

	Character = CreateActor<MiniMapCharacter>(UpdateOrder::Player);
}

void MiniMapLevel::Update(float _Delta)
{

}