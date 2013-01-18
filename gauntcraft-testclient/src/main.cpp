#include <cstdio>

#include "GauntcraftCore.h"
#include <glog/logging.h>

int main(int argc, char ** argv) {
	google::InitGoogleLogging(argv[0]);

	google::LogToStderr();
	LOG(INFO) << "Starting gauntcraft";
	random_function();
	return 0;
}