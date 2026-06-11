#include <iostream>
#include <string>
#include <thread>
#include <stdexcept>
#include <cstdlib>

#include "h/win_api.h"

int main(void) {

	win_OpVk SFTD({ 800, 600, "SFTD", Game::OpenGLapi });

	try {
		std::thread Update_thread(&win_OpVk::Update, &SFTD);
		std::thread Physics_thread(&win_OpVk::Physics, &SFTD);
		SFTD.Rendering();
		Update_thread.join();
		Physics_thread.join();
	}
		catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}