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
		// 물체로서의 크기 회전 위치
		static float4 Scale = { 100.0f, 100.0f, 100.0f }; // 크기
		static float4 Rotation = { 0, 0, 0 }; // 회전
		static float4 Position = { 100.0f, 100.0f, 100.0f }; // 이동

		//static float Dir = 1.0f;

		//Scale -= float4(100.0f, 100.0f, 100.0f) * _Delta * Dir;

		//if (100.0f <= abs(Scale.X))
		//{
		//	Dir *= -1.0f;
		//}


		Rotation.X += 90.0f * _Delta;
		Rotation.Y += 90.0f * _Delta;
		Rotation.Z += 90.0f * _Delta;


		// 로컬과 월드의 차이입니다.
		// 사각형을 만들기 위해서 점을 4개 만들었습니다.
		// 바로 월드로 바로만든것
		// 로컬이 존재하지 않는다.

		// 로컬상태
		std::vector<float4> Vertex;
		Vertex.resize(4 * 6);

		float4 BaseVertexs[4];

		BaseVertexs[0] = { -0.5f, -0.5f, -0.5f };
		BaseVertexs[1] = { 0.5f, -0.5f, -0.5f };
		BaseVertexs[2] = { 0.5f, 0.5f, -0.5f };
		BaseVertexs[3] = { -0.5f, 0.5f, -0.5f };

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

				// 위치 크기 회전을 적용시킬때 수학적으로 증명된
				// 절대적인 기준이 있습니다.
				// 크기 회전 위치 순서대로 적용시켜야 합니다.

				// 모든걸 다 행렬이라는 것으로 처리합니다.
				// 이렇게 벡터식으로 처리하지 않고 
				// 전부다 행렬이라는것을 사용해서 복잡한 변환을 수행합니다.
				// 그럼 행렬은 뭐냐?
				// x열 y행의 숫자가 모여있는 2차원 배열입니다.
				// 우리가 사용하는 float4 4열 1행 행렬이다.
				// 행렬의 기준으로 본다면 행렬이 아닌게 없다.
				// 1 <= 숫자하나가 덩그러니 있으면 1행 1열짜리 행렬일 것이다.

				// 당연히 float4 행렬이 다른 행렬끼리 연산이 되므로
				// 더 큰 행렬도 이에 사용될수 있을 것이다.

				// 보통은 4x4 행렬을 사용해서
				// 크기 회전 위치를 표현하는 변환행렬을 만듭니다.

				// 로컬 => 월드 => 뷰 => 투영 => 뷰포트 => 모니터

				// 일단 연산량의 차이.
				// 행렬이 훨씬 연산이 작아요.
				// 다양한 변환을 한번에 할수가 있다.

				// WorldPoint *= World;

				WorldPoint *= Scale;
				WorldPoint = WorldPoint.VectorRotationToDegX(Rotation.X);
				WorldPoint = WorldPoint.VectorRotationToDegY(Rotation.Y);
				WorldPoint = WorldPoint.VectorRotationToDegZ(Rotation.Z);
				WorldPoint += Position;

				Trifloat4[VertexCount] = WorldPoint;
				Tri[VertexCount] = WorldPoint.WindowPOINT();
			}
			float4 Dir0 = Trifloat4[0] - Trifloat4[1];
			float4 Dir1 = Trifloat4[1] - Trifloat4[2];
			float4 Check = float4::Cross3D(Dir0, Dir1);
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