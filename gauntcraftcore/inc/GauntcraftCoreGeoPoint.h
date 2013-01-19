#ifndef class_sdlgauntcraft_coregeometrypoint
#define class_sdlgauntcraft_coregeometrypoint

#include "GauntcraftCoreTypes.h"

namespace gauntcraft {
	class GauntcraftCoreGeoPoint {
	public:
		GauntcraftCoreGeoPoint(CORE_INT x, CORE_INT y): x(x), y(y) {

		}
		GauntcraftCoreGeoPoint(): x(0), y(0) {

		}
		CORE_INT x;
		CORE_INT y;
	};
}
#endif // class_sdlgauntcraft_coregeometrypoint