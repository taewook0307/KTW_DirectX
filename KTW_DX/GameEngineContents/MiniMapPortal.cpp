#include "PreCompile.h"
#include "MiniMapPortal.h"

MiniMapPortal::MiniMapPortal()
{
}

MiniMapPortal::~MiniMapPortal()
{
}

void MiniMapPortal::Start()
{
	PortalRenderer = CreateComponent<GameEngineSpriteRenderer>(ERENDERORDER::Map);
	PortalRenderer->CreateAnimation("Portal_Create", "Portal_Create", 0.1f, -1, -1, false);
	PortalRenderer->CreateAnimation("Portal_Idle", "Portal_Idle");

	PortalRenderer->SetEndEvent("Portal_Create",
		[=](GameEngineSpriteRenderer* _Renderer)
		{
			PortalRenderer->ChangeAnimation("Portal_Idle");
		}
	);
	PortalRenderer->AutoSpriteSizeOn();
	PortalRenderer->SetAutoScaleRatio(0.8f);

	PortalCollision = CreateComponent<GameEngineCollision>(ECOLLISIONORDER::Portal);
	PortalCollision->Transform.SetLocalScale(PORTALCOLLISIONSCALE);

	PortalRenderer->ChangeAnimation("Portal_Create");
}