#pragma once
#include "GameEngineResources.h"
#include "GameEngineSampler.h"
#include "..\\GameEngineCore\\ThirdParty\\DirectXTex\\inc\\DirectXTex.h"

class GameEngineColor
{
public:
	static const GameEngineColor RED;

	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char A = 0;

	bool operator==(const GameEngineColor& _Other) const
	{
		return memcmp(this, &_Other, sizeof(GameEngineColor)) == 0;
	}
};

// ���� :
class GameEngineTexture : public GameEngineResources<GameEngineTexture>
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineTexture> Create(ID3D11Texture2D* _Res)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes();
		NewRes->Texture2D = _Res;
		return NewRes;
	}

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path,
		D3D11_FILTER _Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_TEXTURE_ADDRESS_MODE _Address = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP)
	{
		GameEnginePath Path = _Path;

		return Load(Path.GetStringPath(), Path.GetFileName());
	}

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path, std::string_view _Name,
		D3D11_FILTER _Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_TEXTURE_ADDRESS_MODE _Address = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes(_Name);
		NewRes->ResLoad(_Path);
		NewRes->Sampler = GameEngineSampler::Create(_Filter, _Address);
		return NewRes;
	}

	inline ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	void CreateRenderTargetView();

	inline float4 GetScale()
	{
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height), 1.0f, 0.0f };
	}

	inline ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor)
	{
		return GetColor(_Pos.iX(), _Pos.iY(), _DefaultColor);
	}

	GameEngineColor GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor);

	std::shared_ptr<GameEngineSampler> GetBaseSampler()
	{
		return Sampler;
	}

protected:

private:
	D3D11_TEXTURE2D_DESC Desc; // �ؽ�ó�� Create�Ҷ� �����ε�. �׳� load�Ҷ��� ����Ұ��̴�.

	ID3D11Texture2D* Texture2D = nullptr;

	ID3D11RenderTargetView* RTV = nullptr; // �� �ؽ�ó�� ����������� ��ų� �����Ҽ� �ִ� ����.
	ID3D11ShaderResourceView* SRV = nullptr; // ���̴��� �������ټ� �ִ� ���Ѵ�.

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	std::shared_ptr<GameEngineSampler> Sampler;

	void ResLoad(std::string_view _Path);
};

