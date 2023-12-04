#pragma once

enum class ECAMERAORDER
{
	MainPrev,
	Main,
	MainNext,
	UI,
};

enum class EPROJECTIONTYPE
{
	Perspective,
	Orthographic,
};


enum class ShaderType
{
	None = 0, // �Ǿտ� None�� �־��ִ� ����� ������ üũ�Ϸ��� ������� ���� ����.
	Vertex, // �ʼ�
	Hull,
	Tessellator,
	Domain,
	Geometry,
	Pixel, // �ʼ�<
	Compute,
	Max, // max�� for�������ų� �Ҷ� �ʿ��ϴϱ�.
};
