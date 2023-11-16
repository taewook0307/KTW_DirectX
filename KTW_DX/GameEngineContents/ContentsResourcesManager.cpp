#include "PreCompile.h"
#include "ContentsResourcesManager.h"

ContentsResourcesManager::ContentsResourcesManager()
{
}

ContentsResourcesManager::~ContentsResourcesManager()
{
}

void ContentsResourcesManager::ImageLoad(std::string_view _ImagePath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild(_ImagePath);
	GameEngineTexture::Load(Path.GetStringPath());
}

void ContentsResourcesManager::CreateFolderSpriteDir(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	GameEngineSprite::CreateFolder(Dir.GetStringPath());
}

void ContentsResourcesManager::CreateFolderSpriteAllDir(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	size_t DirSize = Directorys.size();

	for (size_t i = 0; i < DirSize; i++)
	{
		GameEngineDirectory& Dir = Directorys[i];

		std::string DirPath = Dir.GetStringPath();

		GameEngineSprite::CreateFolder(DirPath);
	}
}

void ContentsResourcesManager::CreateSingleSpriteImage(std::string_view _ImagePath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild(_ImagePath);
	GameEngineTexture::Load(Path.GetStringPath());
	GameEngineSprite::CreateSingle(Path.GetFileName());
}

void ContentsResourcesManager::CreateSingleSpriteDir(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	size_t FileSize = Files.size();

	for (size_t i = 0; i < FileSize; i++)
	{
		GameEngineFile& CurFile = Files[i];

		std::string FilePath = CurFile.GetStringPath();
		std::string FileName = CurFile.GetFileName();

		GameEngineTexture::Load(FilePath);
		GameEngineSprite::CreateSingle(FileName);
	}
}

void ContentsResourcesManager::SingleSpriteRelease(std::string_view _ImageName)
{
	GameEngineTexture::Release(_ImageName);
	GameEngineSprite::Release(_ImageName);
}

void ContentsResourcesManager::SingleSpriteInDirRelease(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	size_t FileSize = Files.size();

	for (size_t i = 0; i < FileSize; i++)
	{
		GameEngineFile& CurFile = Files[i];
		std::string FileName = CurFile.GetFileName();
		GameEngineTexture::Release(FileName);
		GameEngineSprite::Release(FileName);
	}
}

void ContentsResourcesManager::FolderSpriteRelease(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	
	std::string DirName = Dir.GetFileName();
	GameEngineSprite::Release(DirName);

	std::vector<GameEngineFile> Files = Dir.GetAllFile();
	size_t FileSize = Files.size();

	for (size_t i = 0; i < FileSize; i++)
	{
		GameEngineFile& CurFile = Files[i];
		std::string FileName = CurFile.GetFileName();
		GameEngineTexture::Release(FileName);
	}
}

void ContentsResourcesManager::SpriteAndTextureInAllDirRelease(std::string_view _DirPath)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("Resources");
	Dir.MoveChild(_DirPath);
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	size_t DirSize = Directorys.size();

	for (size_t i = 0; i < DirSize; i++)
	{
		GameEngineDirectory CurDirectory = Directorys[i];

		std::string DirectoryName = CurDirectory.GetFileName();
		GameEngineSprite::Release(DirectoryName);

		std::vector<GameEngineFile> Files = CurDirectory.GetAllFile();
		size_t FileSize = Files.size();

		for (size_t i = 0; i < FileSize; i++)
		{
			GameEngineFile CurFile = Files[i];
			std::string FileName = CurFile.GetFileName();
			GameEngineTexture::Release(FileName);
		}
	}
}

void ContentsResourcesManager::SoundLoad(std::string_view _SoundPath)
{
	GameEnginePath Path;
	Path.MoveParentToExistsChild("Resources");
	Path.MoveChild(_SoundPath);
	GameEngineSound::SoundLoad(Path.GetStringPath());
}