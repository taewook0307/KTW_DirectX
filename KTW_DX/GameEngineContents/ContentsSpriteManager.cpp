#include "PreCompile.h"
#include "ContentsSpriteManager.h"

ContentsSpriteManager::ContentsSpriteManager()
{
}

ContentsSpriteManager::~ContentsSpriteManager()
{
}

void ContentsSpriteManager::ImageLoad(std::string_view _ImagePath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild(_ImagePath);
	GameEngineTexture::Load(Path.GetStringPath());
}

void ContentsSpriteManager::CreateFolderSpriteDir(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	GameEngineSprite::CreateFolder(Dir.GetStringPath());
}

void ContentsSpriteManager::CreateFolderSpriteAllDir(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		GameEngineSprite::CreateFolder(Dir.GetStringPath());
	}
}

void ContentsSpriteManager::CreateSingleSpriteImage(std::string_view _ImagePath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild(_ImagePath);
	GameEngineTexture::Load(Path.GetStringPath());
	GameEngineSprite::CreateSingle(Path.GetFileName());
}

void ContentsSpriteManager::CreateSingleSpriteDir(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];

		std::string PathCheck = File.GetStringPath();
		std::string FileNameCheck = File.GetFileName();

		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}
}