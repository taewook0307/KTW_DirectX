#include "PreCompile.h"
#include "MiniMapCharacter.h"

MiniMapCharacter::MiniMapCharacter()
{
}

MiniMapCharacter::~MiniMapCharacter()
{
}

void MiniMapCharacter::Start()
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild("Resources\\Texture\\Character");

	GameEngineFile File = Path.PlusFilePath("MiniMap_Character.png");

	GameEngineTexture::Load(File.GetStringPath());

	GameEngineSprite::CreateCut("MiniMap_Character.png", 10, 11);

	MainSprite = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::Play));
	MainSprite->CreateAnimation("MiniCharacter_Idle", "MiniMap_Character.png", 0.1f, 67, 70);
	MainSprite->ChangeAnimation("MiniCharacter_Idle");
	MainSprite->AutoSpriteSizeOn();
}

void MiniMapCharacter::Update(float _Delta)
{

}