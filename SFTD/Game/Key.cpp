#include "../h/Game/Key.h"

bool keW = false;
bool keA = false;
bool keS = false;
bool keD = false;

int GameCustomKey0 = GLFW_KEY_W;
int GameCustomKey1 = GLFW_KEY_A;
int GameCustomKey2 = GLFW_KEY_S;
int GameCustomKey3 = GLFW_KEY_D;
int GameCustomKey4 = GLFW_KEY_F;

void keyCallback(GLFWwindow * window) {
	keW = glfwGetKey(window, GameCustomKey0);
	keA = glfwGetKey(window, GameCustomKey1);
	keS = glfwGetKey(window, GameCustomKey2);
	keD = glfwGetKey(window, GameCustomKey3);
}