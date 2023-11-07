#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteData::GetScale()
{
	return Texture->GetScale() * float4( SpritePivot.Scale2DX, SpritePivot.Scale2DY, 1.0f, 0.0f);
}

GameEngineSprite::GameEngineSprite() 
{
}

GameEngineSprite::~GameEngineSprite() 
{
}

// �̹����� 1�� �ִµ� �� �̹����� �߶� �������ϴ� 
void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
	// �⺻�����ڰ� �ִ� �ڷ����� ���ο��� �����.
	// std::vector

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ��������Ʈ�� ������� �߽��ϴ�.");
		return;
	}

	SpriteDatas.resize(_X * _Y);

	float4 Start;
	Start.Pos2DX = 0.0f;
	Start.Pos2DY = 0.0f;
	Start.Scale2DX = 1.0f / _X;
	Start.Scale2DY = 1.0f / _Y;

	for (size_t y = 0; y < _Y; ++y)
	{
		for (size_t x = 0; x < _X; x++)
		{
			unsigned int index = static_cast<unsigned int>((y * _X) + x);
			SpriteDatas[index].Texture = Texture;
			SpriteDatas[index].SpritePivot = Start;
			Start.Pos2DX += Start.Scale2DX;
		}

		Start.Pos2DX = 0.0f;
		Start.Pos2DY += Start.Scale2DY;
	}
	

	// GameEngineTexture::Find(_Name);


}

SpriteData GameEngineSprite::GetSpriteData(unsigned int _Index)
{
	if (_Index >= SpriteDatas.size())
	{
		MsgBoxAssert("�ε����� �����ؼ� ��������Ʈ �����͸� ���������� �߽��ϴ�.");
		return SpriteData();
	}

	return SpriteDatas[_Index];
}

void GameEngineSprite::ResCreateFolder(std::string_view _Path)
{
	GameEngineDirectory Dir = _Path;

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	SpriteDatas.resize(Files.size());

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(File.GetStringPath());

		SpriteDatas[i].Texture = Texture;
		SpriteDatas[i].SpritePivot = float4(0, 0, 1.0f, 1.0f);
	}
}