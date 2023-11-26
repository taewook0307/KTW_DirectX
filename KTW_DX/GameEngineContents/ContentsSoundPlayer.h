#pragma once

class ContentsSoundPlayer
{
public:
	// constrcuter destructer
	ContentsSoundPlayer();
	~ContentsSoundPlayer();

	// delete Function
	ContentsSoundPlayer(const ContentsSoundPlayer& _Other) = delete;
	ContentsSoundPlayer(ContentsSoundPlayer&& _Other) noexcept = delete;
	ContentsSoundPlayer& operator=(const ContentsSoundPlayer& _Other) = delete;
	ContentsSoundPlayer& operator=(ContentsSoundPlayer&& _Other) noexcept = delete;

	void AddSoundList(std::string_view _SoundFileName);

	void RandomSoundPlay();
protected:

private:
	std::vector<std::string> SoundList;
};

