#pragma once
#include "GameEngineInputLayOut.h"
// Input LayOut�̶� �� 1���� ��������.

// ���� : �ְ� ���� �߾˰� �־�� �մϴ�.
class GameEngineVertex2D
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

	// ���� �󸶵��� �ٲܼ� �ִ�.
public:
	float4 POSITION;
	float4 TEXCOORD;
};

//struct Vertex
//{
//    float4 Pos0 : POSITION0;
//    float4 Pos1 : POSITION1;
//    float4 COLOR : COLOR;
//    float4 COLOR : TEXCOORD;
//};

class GameEngine3DVertex
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};