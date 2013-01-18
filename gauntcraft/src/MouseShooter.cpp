#include "../inc/MouseShooter.h"

namespace gauntcraft {

	MouseShooter::MouseShooter() {

	}

	MouseShooter::~MouseShooter() {

	}

	CORE_BOOL MouseShooter::registerTarget(IMouseTarget * target) {
		m_target = target;
		return true;
	}

	void MouseShooter::unregisterTarget(IMouseTarget * target) {

	}

	CORE_BOOL MouseShooter::shootMouse(SDL_Event * event) {
		// Need to fire a mouse down event
		if(event->type == SDL_MOUSEBUTTONDOWN) {

		}
		if(event->type == SDL_MOUSEBUTTONUP) {

		}
		// Just need to pull off a mouse motion event
		if(event->type == SDL_MOUSEMOTION) {

			m_target->targetHit(event);
		}
		return true;
	}

}