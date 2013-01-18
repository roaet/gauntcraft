#ifndef class_gauntcraft_coreutility
#define class_gauntcraft_coreutility

#include <algorithm>

#include "GauntcraftCore.h"
namespace gauntcraftcore {
	class GauntcraftCoreUtility {

	public:
		// TODO: clearPtr is not implemented properly.
		static void clearPtr(void *);
		static bool failed(CORE_INT);
	};
}
#endif // class_sdlgauntcraft_coreutility
