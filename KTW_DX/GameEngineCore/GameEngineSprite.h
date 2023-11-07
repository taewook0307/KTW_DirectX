#pragma once
#include "GameEngineTexture.h"


// �̹����� �ڸ��ٴ� ������ �����ų� �Ҽ� �ִ� �༮�̴�.

// �ڸ��� ����� ������ �ʰڴ�.
class SpriteData
{
public:
	std::shared_ptr<GameEngineTexture> Texture;
	// �̹����� �ڸ��� �뵵�� ���˴ϴ�.
	float4 SpritePivot;

	float4 GetScale();
};

// ���� :
class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	// ���� ��ġ �˷��ָ�
	// ���� ��ġ������ �ؽ�ó�� ���δ� �ε��ؼ� ��������Ʈ�� �����.

	static std::shared_ptr<GameEngineSprite> CreateFolder(std::string_view _Path)
	{
		GameEngineDirectory Dir = _Path;

		return CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	static std::shared_ptr<GameEngineSprite> CreateFolder(std::string_view _Name, std::string_view _Path)
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes(_Name);
		NewRes->ResCreateFolder(_Path);
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes(_Name);
		NewRes->ResCreateCut(_Name, _X, _Y);
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateSingle(std::string_view _Name)
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes(_Name);
		NewRes->ResCreateCut(_Name, 1, 1);
		return NewRes;
	}

	SpriteData GetSpriteData(unsigned int _Index);

	unsigned int GetSpriteCount() 
	{
		return static_cast<unsigned int>(SpriteDatas.size());
	}

protected:
	void ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y);
	void ResCreateFolder(std::string_view _Path);

private:
	std::vector<SpriteData> SpriteDatas;
};

