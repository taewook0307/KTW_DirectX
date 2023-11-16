#pragma once

class ContentsResourcesManager
{
public:
	// delete Function
	ContentsResourcesManager(const ContentsResourcesManager& _Other) = delete;
	ContentsResourcesManager(ContentsResourcesManager&& _Other) noexcept = delete;
	ContentsResourcesManager& operator=(const ContentsResourcesManager& _Other) = delete;
	ContentsResourcesManager& operator=(ContentsResourcesManager&& _Other) noexcept = delete;

	static void ImageLoad(std::string_view _ImagePath);
	static void CreateFolderSpriteDir(std::string_view _DirPath);
	static void CreateFolderSpriteAllDir(std::string_view _DirPath);
	static void CreateSingleSpriteImage(std::string_view _ImagePath);
	static void CreateSingleSpriteDir(std::string_view _DirPath);

	
	static void SingleSpriteRelease(std::string_view _ImageName);
	static void SingleSpriteInDirRelease(std::string_view _DirPath);
	static void FolderSpriteRelease(std::string_view _DirPath);
	static void SpriteAndTextureInAllDirRelease(std::string_view _DirPath);

	static void SoundLoad(std::string_view _SoundPath);

protected:

private:
	// constrcuter destructer
	ContentsResourcesManager();
	~ContentsResourcesManager();
};