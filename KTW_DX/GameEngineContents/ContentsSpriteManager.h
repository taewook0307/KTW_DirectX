#pragma once

class ContentsSpriteManager
{
public:
	// delete Function
	ContentsSpriteManager(const ContentsSpriteManager& _Other) = delete;
	ContentsSpriteManager(ContentsSpriteManager&& _Other) noexcept = delete;
	ContentsSpriteManager& operator=(const ContentsSpriteManager& _Other) = delete;
	ContentsSpriteManager& operator=(ContentsSpriteManager&& _Other) noexcept = delete;

	static void ImageLoad(std::string_view _ImagePath);
	static void CreateFolderSpriteDir(std::string_view _DirPath);
	static void CreateFolderSpriteAllDir(std::string_view _DirPath);
	static void CreateSingleSpriteImage(std::string_view _ImagePath);
	static void CreateSingleSpriteDir(std::string_view _DirPath);

	
	static void SingleSpriteRelease(std::string_view _ImageName);
	static void SingleSpriteInDirRelease(std::string_view _DirPath);
	static void FolderSpriteRelease(std::string_view _DirPath);
	static void SpriteAndTextureInAllDirRelease(std::string_view _DirPath);

protected:

private:
	// constrcuter destructer
	ContentsSpriteManager();
	~ContentsSpriteManager();
};