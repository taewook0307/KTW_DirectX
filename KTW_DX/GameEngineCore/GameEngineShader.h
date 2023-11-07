#pragma once
#include "GameEngineShaderResHelper.h"

enum class ShaderType
{
	None = 0, // �Ǿտ� None�� �־��ִ� ����� ������ üũ�Ϸ��� ������� ���� ����.
	Vertex, // �ʼ�
	Hull,
	Tessellator,
	Domain,
	Geometry,
	Pixel, // �ʼ�
	Max, // max�� for�������ų� �Ҷ� �ʿ��ϴϱ�.
};

// ���� :
class GameEngineShader
{
public:
	static bool AutoCompile(GameEngineFile& _File);

	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	GameEngineShaderResHelper ResHelper;

	ShaderType GetShaderType() 
	{
		return ShaderTypeValue;
	}
	
protected:
	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);
	std::string Version;

	// ���̴��� ���̳ʸ� �ڵ忡 ���� ������
	// ���̴� �ڵ带 �����ϱ� ���� ������ �������̴�.
	ID3DBlob* BinaryCode = nullptr;
	std::string EntryName = "";

	void ShaderResCheck();

private:
	ShaderType ShaderTypeValue = ShaderType::None;

};

