#pragma once


class LevelManager
{
public:
	static LevelManager& Get() {
		static LevelManager s_instance;
		return s_instance;
	}
	virtual ~LevelManager() = default;

	void LoadLevel();
	void SaveLevel();

private:
	LevelManager() = default;

};

