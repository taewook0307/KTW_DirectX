#include "PreCompile.h"
#include "SelectMenu.h"

SelectMenu::SelectMenu()
{
}

SelectMenu::~SelectMenu()
{
}

void SelectMenu::Start()
{
	OnRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::Play);
	OffRenderer = CreateComponent<GameEngineUIRenderer>(ERENDERORDER::Play);
}

void SelectMenu::Update(float _Delta)
{
	if (true == IsSelect)
	{
		OnRenderer->On();
		OffRenderer->Off();
	}
	else
	{
		OnRenderer->Off();
		OffRenderer->On();
	}
}

void SelectMenu::SelectMenuInit(std::string_view _SelectFileName, std::string_view _UnSelectFileName)
{
	OnRenderer->SetSprite(_SelectFileName);
	OffRenderer->SetSprite(_UnSelectFileName);
	OnRenderer->Off();
}

void SelectMenu::OnRendererInit(std::string_view _FileName, int _Order /*= 0*/)
{
	OnRenderer->SetSprite(_FileName, _Order);
	OnRenderer->Off();
}

void SelectMenu::OffRendererInit(std::string_view _FileName, int _Order /*= 0*/)
{
	OffRenderer->SetSprite(_FileName, _Order);
}