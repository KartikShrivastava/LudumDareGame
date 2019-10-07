#include "GameObject.h"

GameObject::GameObject() 
	: position(0, 0), size(1, 1), velocity(0.0f), color(1.0f), rotation(0.0f), sprite() {
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D spr, glm::vec3 col, glm::vec2 vel)
	: position(pos), size(size), velocity(vel), color(col), rotation(0.0f), sprite(spr) {
}

void GameObject::Draw(SpriteRenderer & renderer){
	renderer.DrawSprite(sprite, position, size, rotation, color);
}
