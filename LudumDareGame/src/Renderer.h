#pragma once

class Renderer {
private:

public:
	int width = 720;
	int height = 460;
	float mix = 0.2f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float lastX = 300, lastY = 400;
	float initialMouse = true;
};