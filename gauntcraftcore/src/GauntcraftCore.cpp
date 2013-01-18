#include "../inc/GauntcraftCore.h"
#include <glog/logging.h>

void random_function() {
	
	google::LogToStderr();
	LOG(INFO) << "Calling random function from GauntcraftCore";
	return;
}