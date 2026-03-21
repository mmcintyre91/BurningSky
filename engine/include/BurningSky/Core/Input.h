#pragma once

#include "BurningSky/Core/KeyCodes.h"

namespace BurningSky {
	
	class Window;

	class Input {
	public:

		//tell input whic window to poll from
		static void SetWindow(Window* window);

		//true as long as key held down
		static bool IsKeyDown(Key key);

	private:
		static int ToGLFWKey(Key key);

	private:
		static Window* s_Window;
	};



}