#pragma once

class Summon_Ball
{
public:
	// constrcuter destructer
	Summon_Ball();
	~Summon_Ball();

	// delete Function
	Summon_Ball(const Summon_Ball& _Other) = delete;
	Summon_Ball(Summon_Ball&& _Other) noexcept = delete;
	Summon_Ball& operator=(const Summon_Ball& _Other) = delete;
	Summon_Ball& operator=(Summon_Ball&& _Other) noexcept = delete;

protected:

private:

};