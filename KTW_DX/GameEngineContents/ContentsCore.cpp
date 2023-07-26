﻿#include "PreCompile.h"
#include "ContentsCore.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Start()
{
	// 회전방향을 외적으로 알아내는 방법
	float4 PlayerPos = { 3, 5 };
	float4 MonsterPos = { 5, 5 };

	float4 PlayerDir = { 0, 1, 0 };
	float4 PlayerLook = (PlayerPos - MonsterPos).NormalizeReturn();


	float4 Check = float4::Cross3D(PlayerDir, PlayerLook);

	// float4 Rev = float4::Cross3D({0, 10, 0}, { 0.01f, -10.0f, 0 });

	if (0 > Check.Z)
	{
		// 왼쪽으로 돌아라.
	}

	int a = 0;

}

void ContentsCore::Update(float _Delta)
{
	HDC DC;
	{
		// 윈도우 클리어
		DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Rectangle(DC, 0, 0, WinScale.iX(), WinScale.iY());
	}


	{
		// 로컬과 월드의 차이입니다.
		// 사각형을 만들기 위해서 점을 4개 만들었습니다.
		// 바로 월드로 바로만든것
		// 로컬이 존재하지 않는다.

		// 로컬상태
		std::vector<float4> Vertex;
		Vertex.resize(4 * 6);

		float4 BaseVertexs[4];

		BaseVertexs[0] = { -0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[1] = { 0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[2] = { 0.5f, 0.5f, -0.5f, 1.0f };
		BaseVertexs[3] = { -0.5f, 0.5f, -0.5f, 1.0f };

		// 앞면
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// 뒷면
		Vertex[4] = float4::VectorRotationToDegX(BaseVertexs[0], 180.0f);
		Vertex[5] = float4::VectorRotationToDegX(BaseVertexs[1], 180.0f);
		Vertex[6] = float4::VectorRotationToDegX(BaseVertexs[2], 180.0f);
		Vertex[7] = float4::VectorRotationToDegX(BaseVertexs[3], 180.0f);

		// 왼쪽이나 오른쪽
		Vertex[8] = float4::VectorRotationToDegY(BaseVertexs[0], 90.0f);
		Vertex[9] = float4::VectorRotationToDegY(BaseVertexs[1], 90.0f);
		Vertex[10] = float4::VectorRotationToDegY(BaseVertexs[2], 90.0f);
		Vertex[11] = float4::VectorRotationToDegY(BaseVertexs[3], 90.0f);

		// 왼쪽이나 오른쪽
		Vertex[12] = float4::VectorRotationToDegY(BaseVertexs[0], -90.0f);
		Vertex[13] = float4::VectorRotationToDegY(BaseVertexs[1], -90.0f);
		Vertex[14] = float4::VectorRotationToDegY(BaseVertexs[2], -90.0f);
		Vertex[15] = float4::VectorRotationToDegY(BaseVertexs[3], -90.0f);

		// 위거나 아래
		Vertex[16] = float4::VectorRotationToDegX(BaseVertexs[0], 90.0f);
		Vertex[17] = float4::VectorRotationToDegX(BaseVertexs[1], 90.0f);
		Vertex[18] = float4::VectorRotationToDegX(BaseVertexs[2], 90.0f);
		Vertex[19] = float4::VectorRotationToDegX(BaseVertexs[3], 90.0f);

		Vertex[20] = float4::VectorRotationToDegX(BaseVertexs[0], -90.0f);
		Vertex[21] = float4::VectorRotationToDegX(BaseVertexs[1], -90.0f);
		Vertex[22] = float4::VectorRotationToDegX(BaseVertexs[2], -90.0f);
		Vertex[23] = float4::VectorRotationToDegX(BaseVertexs[3], -90.0f);



		std::vector<int> Index =
		{
			0, 1, 2,
			0, 2, 3,
			0 + 4, 1 + 4, 2 + 4,
			0 + 4, 2 + 4, 3 + 4,
			0 + 8, 1 + 8, 2 + 8,
			0 + 8, 2 + 8, 3 + 8,
			0 + 12, 1 + 12, 2 + 12,
			0 + 12, 2 + 12, 3 + 12,
			0 + 16, 1 + 16, 2 + 16,
			0 + 16, 2 + 16, 3 + 16,
			0 + 20, 1 + 20, 2 + 20,
			0 + 20, 2 + 20, 3 + 20,
		};

		// 0   1
		// 3   2


		// 첫번째 방법
		// Vertex[0] = { -0.5f, -0.5f }; 16
		// Vertex[1] = { 0.5f, -0.5f }; 16
		// Vertex[2] = { 0.5f, 0.5f }; 16
		// 
		// Vertex1[0] = { -0.5f, -0.5f }; 16
		// Vertex1[1] = { 0.5f, -0.5f }; 16
		// Vertex1[2] = { 0.5f, 0.5f }; 16 
		// 
		// 두번째 방법
		// Vertex[0] = { -0.5f, -0.5f }; 16
		// Vertex[1] = { 0.5f, -0.5f }; 16
		// Vertex[2] = { 0.5f, 0.5f }; 16
		// Vertex[3] = { -0.5f, 0.5f }; 16
		// 
		// short Arr[2][3] = {{0, 1, 2}, {0, 2, 3}}; 24


		// 월드의 영역
		static float4 Scale = { 100.0f, 100.0f, 100.0f }; // 크기
		static float4 Rotation = { 0, 0, 0 }; // 회전
		static float4 Position = { 100.0f, 100.0f, 0.0f }; // 이동
		Rotation.X += 360.0f * _Delta;
		Rotation.Y += 360.0f * _Delta;
		Rotation.Z += 360.0f * _Delta;

		float4x4 Scale4x4;
		float4x4 Rotation4x4X;
		float4x4 Rotation4x4Y;
		float4x4 Rotation4x4Z;
		float4x4 Rotation4x4;
		float4x4 Position4x4;


		Scale4x4.Scale(Scale);

		Rotation4x4X.RotationXDegs(Rotation.X);
		Rotation4x4Y.RotationYDegs(Rotation.Y);
		Rotation4x4Z.RotationZDegs(Rotation.Z);
		Rotation4x4 = Rotation4x4X * Rotation4x4Y * Rotation4x4Z;

		Position4x4.Pos(Position);

		// 행렬의 곱샘은 교환법칙이 성립하지 않습니다.
		float4x4 World4x4 = Scale4x4 * Rotation4x4 * Position4x4;


		// 카메라의 영역

		float4x4 View4x4;
		float4 EyePos = { 0.0f, 0.0f, -1000.0f, 1.0f };
		float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
		// View4x4.LookToLH
		// float4 EyeLookPos = { 0.0f, 0.0f, 0.0f, 1.0f };
		// 내부에서 계산된다.
		// float4 EyeDir = EyePos - EyeLookPos;
		float4 EyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };

		View4x4.LookAtLH(EyePos, EyeDir, EyeUp);



		float4x4 WorldView4x4 = World4x4 * View4x4;

		for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		{
			int ArrIndex[3];
			ArrIndex[0] = Index[indexCount * 3 + 0];
			ArrIndex[1] = Index[indexCount * 3 + 1];
			ArrIndex[2] = Index[indexCount * 3 + 2];

			float4 Trifloat4[3];
			std::vector<POINT> Tri;
			Tri.resize(3);
			for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
			{
				// 위치를 더해줌으로해서 월드 상태로 이전시켰다고 한다.
				float4 WorldPoint = Vertex[ArrIndex[VertexCount]];

				//변환식은 이제 딱 한가지 인것.
				WorldPoint = WorldPoint * WorldView4x4;

				Trifloat4[VertexCount] = WorldPoint;
				Tri[VertexCount] = WorldPoint.WindowPOINT();
			}
			float4 Dir0 = Trifloat4[0] - Trifloat4[1];
			float4 Dir1 = Trifloat4[1] - Trifloat4[2];
			float4 Check = float4::Cross3D(Dir1, Dir0);
			if (Check.Z < 1.0f)
			{
				continue;
			}
			Polygon(DC, &Tri[0], Tri.size());
		}


		GameEngineCore::MainWindow.DoubleBuffering();
	}
}

void ContentsCore::Release()
{

}