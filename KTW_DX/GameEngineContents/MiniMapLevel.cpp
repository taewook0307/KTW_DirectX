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
	float4 WinScaleHalf = GameEngineCore::MainWindow.GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y, -500 });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

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

	GameEngineSprite::CreateSingle("MiniMap.png");

	MiniMap = CreateActor<Map>(UpdateOrder::BackGround);
	MiniMap->MapInit("MiniMap.png");
	MiniMap->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });

	Character = CreateActor<MiniMapCharacter>(UpdateOrder::Player);
	Character->Transform.SetLocalPosition({ WinScaleHalf.X, -WinScaleHalf.Y });
}

void MiniMapLevel::Update(float _Delta)
{

}