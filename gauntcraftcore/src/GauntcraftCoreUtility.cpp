#include "../inc/GauntcraftCoreUtility.h"
namespace gauntcraftcore {

	void GauntcraftCoreUtility::clearPtr(void * pt) {
		if(pt) {
			delete pt;
			pt = NULL;
		}
	}

	bool GauntcraftCoreUtility::failed(CORE_INT status) {
		return (status < 0);
	}
}