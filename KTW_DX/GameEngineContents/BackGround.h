#pragma once

class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void BackGroundInit(std::string_view _FileName, int _Order = 0);
	void BackGroundInitAuto(std::string_view _FileName, int _Order = 0);
	void SetAutoScaleRatio(float _Value);

	void AnimationInit(std::string_view _AnimationName, std::string_view _FileName, float _Inter = 0.1f, bool _Loop = true, bool _SizeFixWindow = true, unsigned int _Start = -1, unsigned int _End = -1);
	bool AnimationEndCheck();

	void SetBackGroundRendererPivotType(PivotType _Pivot);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BackGroundRenderer;
};