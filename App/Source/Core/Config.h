#pragma once

#include <filesystem>

namespace config 
{
	// Loaded from config. All paths are absolute.
	inline std::filesystem::path projectPath = std::filesystem::current_path().parent_path().parent_path();
};

