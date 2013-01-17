#include "../inc/ClientCoreUtility.h"
namespace gauntcraftcore {
	SDL_Rect ClientCoreUtility::IntersectRect(SDL_Rect * a, SDL_Rect *b) {
		bool intersecting = !( a->x > b->x + b->w ||
							   a->x + a->w < b->x ||
							   a->y > b->y + b->h ||
							   a->y + a->h < b->y);
	
		if(intersecting) {
			SDL_Rect ret = { std::max(b->x, a->x),
							 std::max(b->y, a->y),
							 std::min(b->x + b->w, a->x + a->w),
							 std::min(b->y + b->h, a->y + a->h) };
			return ret;
		}
		SDL_Rect ret = {0, 0, 0, 0};
		return ret;
	}

	void ClientCoreUtility::clearPtr(void * pt) {
		if(pt) {
			delete pt;
			pt = NULL;
		}
	}

	bool ClientCoreUtility::failed(CORE_INT status) {
		return (status < 0);
	}
}