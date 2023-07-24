﻿// App.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <iostream>
#include <Windows.h>
#include <memory>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	/*float4x4 Left;
	float4x4 Right;

	Left.Scale({ 5, 2, 4 });

	Right.Pos({ 120, 130, 140 });

	float4x4 Result = Left * Right;*/

	GameEngineCore::EngineStart<ContentsCore>(hInstance);
}

