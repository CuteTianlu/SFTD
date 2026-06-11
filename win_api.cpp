#include "h/win_api.h"
#include "h/game.h"

win_OpVk::win_OpVk() :
	win_OpVk::win_OpVk({ 800, 600, "OpenGL", game->OpenGLapi }) {
}

win_OpVk::win_OpVk(std::string title) :
	win_OpVk::win_OpVk({ 800, 600, title, game->OpenGLapi }) {
}

win_OpVk::win_OpVk(windowInfo window_info) :
	w_info(window_info),
	window(nullptr) {
	game = new Game();
	win_OpVk::initwindow();
	game->Init();
	win_OpVk::initRenderingapi();
}

win_OpVk::~win_OpVk() {
	delete game;
	cleanupAll();
}

void win_OpVk::initwindow() {
	if (!glfwInit()) {
		throw std::runtime_error("初始化GLFW失败");
	}

	if (w_info.Renderingapi == game->Vulkanapi) {
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}
	else if (w_info.Renderingapi == game->OpenGLapi) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	else {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	
	window = glfwCreateWindow(w_info.width, w_info.height, w_info.title.c_str(), nullptr, nullptr);

	if (glfwWindowShouldClose(window)) {
		glfwTerminate();
		throw std::runtime_error("窗口给我创建好了啊\n错误窗口(窗户(window))创建失败");
	}

	game->window = window;
	game->w_info = w_info;
}

void win_OpVk::initRenderingapi() {
	game->Renderingapi = w_info.Renderingapi;
	if (w_info.Renderingapi == game->Vulkanapi) {
		win_OpVk::initvulkan();
	} else if (w_info.Renderingapi == game->OpenGLapi) {
		win_OpVk::initOpenGL();
	} else {
		win_OpVk::initOpenGL();
	}
};

void win_OpVk::initvulkan() {
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VulkanWindow";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_4;
	appInfo.pEngineName = "TianLu天禄";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	VkResult results;
	if ((results = vkCreateInstance(&createInfo, nullptr, &instance)) != VK_SUCCESS) {
		switch (results) {
			case VK_ERROR_INCOMPATIBLE_DRIVER:
				std::cerr << "GPU不支持vulkan渲染api" << results << std::endl;
				break;
			case VK_ERROR_EXTENSION_NOT_PRESENT:
				std::cerr << "vulkan渲染api不支持扩展" << results << std::endl;
				break;
			default:
				std::cerr << "未知错误" << results << std::endl;
				break;
		};
		throw std::runtime_error("创建实例给我创建好了啊！");
	}
}

void win_OpVk::initOpenGL() {
	glfwSetWindowPos(window, 150, 150);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw std::runtime_error("初始化OpenGL失败");
	}

	std::cout << "OpenGL 版本: " << glGetString(GL_VERSION) << std::endl;

	game->reng.Shader();
	game->reng.initrer();
}

void win_OpVk::cleanupAll() {
	cleanupwindow();
}

void win_OpVk::cleanupwindow() {
	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void win_OpVk::pickupPhysicalDevice() {

}

void win_OpVk::Rendering() {
	try {
		while (Switch) {
			glfwPollEvents();
			game->draw();
			if (glfwWindowShouldClose(window)) {
				Switch = false;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(game->FPS));
		}
	} catch (const std::exception& e) {
		std::cerr << "[渲染主要线程异常] " << e.what() << std::endl;
		Switch = false;  // 通知其他线程退出
	}
};

void win_OpVk::Update() {
	try {
		while (Switch) {
			game->update();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	} catch (const std::exception& e) {
		std::cerr << "[更新线程异常] " << e.what() << std::endl;
		Switch = false;  // 通知其他线程退出
	}
};

void win_OpVk::Physics() {
	try {
		while (Switch) {
			game->physics();
			std::this_thread::sleep_for(std::chrono::milliseconds(32));
		}
	} catch (const std::exception& e) {
		std::cerr << "[物理线程异常] " << e.what() << std::endl;
		Switch = false;  // 通知其他线程退出
	}
};