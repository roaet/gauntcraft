#ifndef class_sdlgauntcraft_mouseshooter
#define class_sdlgauntcraft_mouseshooter
#include "ClientCore.h"
#include "IMouseTarget.h"

namespace gauntcraft {
	class MouseShooter {
	private:
		IMouseTarget * m_target;
	public:
		MouseShooter();
		~MouseShooter();

		CORE_BOOL registerTarget(IMouseTarget * target);
		void unregisterTarget(IMouseTarget * target);
		CORE_BOOL shootMouse(SDL_Event * event);
	};
}

#endif // class_sdlgauntcraft_mouseshooter