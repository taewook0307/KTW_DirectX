#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader() 
{
}

GameEngineVertexShader::~GameEngineVertexShader() 
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEngineVertexShader::ShaderLoad(
	std::string_view _Path, 
	std::string_view _EntryPoint, 
	UINT _VersionHight, 
	UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);

	CreateVersion(ShaderType::Vertex, _VersionHight, _VersionLow);

	EntryName = _EntryPoint;

	int Flag = 0;

#ifdef _DEBUG
	// 11������ ����.
	// ���� 
	Flag = D3D10_SHADER_DEBUG;
#endif

	//std::string Include =
	//"float4 Value; \
	// float4 Pos; ";

	// ���� ������� �����ϸ鼭 �� �������
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// std::string*
	ID3DBlob* Error = nullptr;

	// ���̴��� ������ �ϴ� �Լ��Դϴ�.
	// 
	HRESULT Result = D3DCompileFromFile(
		UniPath.c_str(), // ���
		nullptr, // ���̴����� ����� ��ũ�� ��ũ�δ� �Ⱦ��ϴ�.
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // ���ο��� ����� #include �׳� �ڴ�. ���� ���� �ȳ־��ش�.
		EntryName.c_str(), // "ColorShader_VS"
		Version.c_str(), // "vs_5_0"
		Flag,
		0, // ���� ��.
		&BinaryCode,
		&Error);

	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}


	Result = GameEngineCore::GetDevice()->CreateVertexShader(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr);

	if (S_OK != Result)
	{
		MsgBoxAssert("���ؽ� ���̴� ������ �����߽��ϴ�.");
	}

	ShaderResCheck();
}

void GameEngineVertexShader::Setting()
{
	GameEngineCore::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}