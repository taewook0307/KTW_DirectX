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

	MainSprite = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Play);
	MainSprite->CreateAnimation("MiniCharacter_Idle", "MiniMap_Character.png", 0.1f, 67, 70);
	MainSprite->ChangeAnimation("MiniCharacter_Idle");
	MainSprite->AutoSpriteSizeOn();
}

void MiniMapCharacter::Update(float _Delta)
{
	float Speed = 200.0f;

	float4 MovePos = float4::ZERO;

	if (GameEngineInput::IsPress(VK_UP))
	{
		MovePos += float4::UP * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_DOWN))
	{
		MovePos += float4::DOWN * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		MovePos += float4::LEFT * _Delta * Speed;
	}

	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += float4::RIGHT * _Delta * Speed;
	}

	Transform.AddLocalPosition(MovePos);
}