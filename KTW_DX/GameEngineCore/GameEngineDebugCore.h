#pragma once
#include "GameEngineCamera.h"

namespace GameEngineDebug
{
	void DrawBox2D(const GameEngineTransform& _Trans, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);

	void DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);

	class GameEngineDebugCore
	{
		friend class GameEngineLevel;
		// �Լ��� friend�ɼ� �ֽ��ϴ�.
		friend void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color, class GameEngineCamera* _Camera);

	private:
		static class GameEngineLevel* CurLevel;

		static void DebugInit();
		static void DebugRender();
	};
}
