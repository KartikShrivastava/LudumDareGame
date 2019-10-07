#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Text.h"
#include "Shader.h"

SpriteRenderer* renderer;
Text* textRenderer;
Shader* textShaderObj;

Game::Game(GLuint w, GLuint h) : state(GAME_ACTIVE), width(w), height(h), keys(){
}

Game::~Game(){
	delete renderer;
	delete textRenderer;
	delete textShaderObj;
}

void Game::Init(){
	ResourceManager::LoadShader("src/shaders/SpriteVS.glsl", "src/shaders/SpriteFS.glsl", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Bind().SetInteger("u_image", 0);
	ResourceManager::GetShader("sprite").Bind().SetMatrix4f("u_projection", projection);

	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	ResourceManager::LoadTexture("res/textures/avocado1.png", GL_TRUE, "avocado0");
	ResourceManager::LoadTexture("res/textures/avocado2.png", GL_TRUE, "avocado1");
	ResourceManager::LoadTexture("res/textures/avocado3.png", GL_TRUE, "avocado2");
	ResourceManager::LoadTexture("res/textures/avocado2.png", GL_TRUE, "avocado3");

	ResourceManager::LoadTexture("res/textures/level1BG.png", GL_TRUE, "level1BG");
	
	ResourceManager::LoadTexture("res/textures/level1ThunderCloud.png", GL_TRUE, "level1ThunderCloud");
	ResourceManager::LoadTexture("res/textures/level1Thunder1.png", GL_TRUE, "level1Thunder1");
	ResourceManager::LoadTexture("res/textures/level1Thunder2.png", GL_TRUE, "level1Thunder2");

	ResourceManager::LoadTexture("res/textures/level1WaterCloud.png", GL_TRUE, "level1WaterCloud");
	ResourceManager::LoadTexture("res/textures/level1WaterDrop.png", GL_TRUE, "level1WaterDrop");

	avocadoPosition = glm::vec2(60, 440);
	avocadoSize = glm::vec2(80, 80);
	waterDropPos = 150;
	
	textRenderer = new Text("res/fonts/pixel.ttf", 48);
	textShaderObj = new Shader("src/shaders/textVS.glsl", "src/shaders/textFS.glsl");
	textShaderObj->Bind();
	glm::mat4 projectionText = glm::ortho(0.0f, 1.0f * width, 0.0f, 1.0f * height);

	textShaderObj->SetUniformMat4fv("u_projection", glm::value_ptr(projectionText));
}

void Game::ProcessInput(GLfloat dt){

	if (this->keys[GLFW_KEY_LEFT])
	{
		if (avocadoPosition.x >= 0)
			avocadoPosition.x -= 0.25f;
		moving = true;
	}
	else if (this->keys[GLFW_KEY_RIGHT])
	{
		if (avocadoPosition.x <= width - avocadoSize.x)
			avocadoPosition.x += 0.25f;
		moving = true;
	}
	else
		moving = false;
}

void Game::Update(GLfloat dt){
}

void Game::Render(){
	renderer->DrawSprite(ResourceManager::GetTexture("level1BG"), glm::vec2(0, 0), glm::vec2(800, 600));

	if (frame > 3.0f) {
		renderer->DrawSprite(ResourceManager::GetTexture("level1Thunder1"), glm::vec2(200, 300), glm::vec2(80, 80));
		if(thunderCount > 30)
			renderer->DrawSprite(ResourceManager::GetTexture("level1Thunder2"), glm::vec2(250, 380), glm::vec2(80, 80));
		thunderCount = (thunderCount + 1) % 100;
	}
	renderer->DrawSprite(ResourceManager::GetTexture("level1ThunderCloud"), glm::vec2(180, 180), glm::vec2(200, 200));

	waterDropPos = (waterDropPos + 1) % 470;
	if (frame < 1.0f && waterDropPos>150) {
		renderer->DrawSprite(ResourceManager::GetTexture("level1WaterDrop"), glm::vec2(550,waterDropPos), glm::vec2(30, 30));
	}
	renderer->DrawSprite(ResourceManager::GetTexture("level1WaterCloud"), glm::vec2(400, -50), glm::vec2(380, 380));

	if (moving) {
		frame = std::fmod(frame + 0.005f, 4.0f);
		renderer->DrawSprite(ResourceManager::GetTexture("avocado" + std::to_string(int(frame))), avocadoPosition, avocadoSize);
	}
	else
		renderer->DrawSprite(ResourceManager::GetTexture("avocado1"), avocadoPosition, avocadoSize);

	textRenderer->Draw(*textShaderObj, "An Avocado", 25.0f, 500.0f, 1.0f, glm::vec3(0.0f,0.0f,0.0f));
}