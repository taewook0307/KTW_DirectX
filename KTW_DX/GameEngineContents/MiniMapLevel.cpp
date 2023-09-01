#include "PreCompile.h"
#include "MiniMapLevel.h"

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

	MiniMap = CreateActor<Map>(UpdateOrder::BackGround);
	MiniMap->MapInit("CupHead_MiniMap.png");
}

void MiniMapLevel::Update(float _Delta)
{

}