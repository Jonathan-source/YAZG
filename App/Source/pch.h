#pragma once

// Include Lua, assumes it is local to this file
extern "C"
{
#include "../../ThirdParty/lua542/include/lua.h"
#include "../../ThirdParty/lua542/include/lauxlib.h"
#include "../../ThirdParty/lua542/include/lualib.h"
}

// Link to lua library
#ifdef _WIN32
#pragma comment(lib, "../../ThirdParty/lua542/liblua54.a")
#endif

// RayLib.
#include <raylib.h>
#include <raymath.h>

// Standard
#include <string>
#include <string_view>
#include <exception>
#include <chrono>
#include <iostream>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <memory>
#include <cassert> 
#include <unordered_map>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <condition_variable>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <functional>
#include <math.h>

#define TEXTURE_PATH(name) "../../App/Assets/Textures/" ## name
#define MESH_PATH(name) "../../App/Assets/Meshes/" ## name
#define SOUND_PATH(name) "../../App/Assets/Sounds/" ## name
#define MUSIC_PATH(name) "../../App/Assets/Music/" ## name
#define SCRIPT_PATH(name) "../../App/Assets/Scripts/" ## name
