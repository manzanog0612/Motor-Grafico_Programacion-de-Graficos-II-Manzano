#pragma once

#include "glew.h"
#include "glfw3.h"

namespace engine
{
	#ifdef ENGINE_EXPORTS
	#define ENGINE_API __declspec(dllexport)
	#else
	#define ENGINE_API __declspec(dllimport)
	#endif
}