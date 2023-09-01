#pragma once

#include <GameEngineCore/GameEngineActor.h>

class MiniMapCharacter : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMapCharacter();
	~MiniMapCharacter();

	// delete Function
	MiniMapCharacter(const MiniMapCharacter& _Other) = delete;
	MiniMapCharacter(MiniMapCharacter&& _Other) noexcept = delete;
	MiniMapCharacter& operator=(const MiniMapCharacter& _Other) = delete;
	MiniMapCharacter& operator=(MiniMapCharacter&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSprite;

	void Start() override;
	void Update(float _Delta) override;
};