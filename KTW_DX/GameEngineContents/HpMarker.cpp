#include "PreCompile.h"
#include "HpMarker.h"

#include "BaseCharacter.h"

HpMarker::HpMarker()
{
}

HpMarker::~HpMarker()
{
}

void HpMarker::Start()
{
	HpRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::UI);
	HpRenderer->CreateAnimation("Hp_1", "Hp_1", 0.05f);
	HpRenderer->CreateAnimation("Hp_2", "Hp_2");
	HpRenderer->CreateAnimation("Hp_3", "Hp_3");
	HpRenderer->CreateAnimation("Hp_0", "Hp_0");

	HpRenderer->AutoSpriteSizeOn();
	HpRenderer->SetPivotType(PivotType::Bottom);

	HpRenderer->ChangeAnimation("Hp_3");
}

void HpMarker::Update(float _Delta)
{
	if (nullptr != BaseCharacter::MainCharacter)
	{
		int CharacterHp = BaseCharacter::MainCharacter->GetHp();

		HpCheck(CharacterHp);
	}
}

void HpMarker::HpCheck(int _Hp)
{
	int Hp = _Hp;

	if (0 > Hp)
	{
		Hp = 0;
	}

	if (3 < Hp)
	{
		Hp = 3;
	}

	std::string AnimationName = "Hp_";

	std::string HpString = std::to_string(Hp);

	AnimationName += HpString;

	HpRenderer->ChangeAnimation(AnimationName);
}