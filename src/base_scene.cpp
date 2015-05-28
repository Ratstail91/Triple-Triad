/* Copyright: (c) Kayne Ruse 2015
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "base_scene.hpp"

BaseScene::BaseScene() {
	//EMPTY
}

BaseScene::~BaseScene() {
	//EMPTY
}

void BaseScene::RunFrame() {
	FrameStart();
	ProcessEvents();
	Update();
	FrameEnd();
}

void BaseScene::RenderFrame(SDL_Renderer* renderer) {
	//EMPTY
}

SceneSignal BaseScene::GetSceneSignal() {
	return sceneSignal;
}

void BaseScene::SetSceneSignal(SceneSignal signal) {
	sceneSignal = signal;
}

//-------------------------
//frame phases
//-------------------------

void BaseScene::FrameStart() {
	//EMPTY
}

void BaseScene::ProcessEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				QuitEvent();
			break;

			case SDL_MOUSEMOTION:
				MouseMotion(event.motion);
			break;

			case SDL_MOUSEBUTTONDOWN:
				MouseButtonDown(event.button);
			break;

			case SDL_MOUSEBUTTONUP:
				MouseButtonUp(event.button);
			break;

			case SDL_KEYDOWN:
				KeyDown(event.key);
			break;

			case SDL_KEYUP:
				KeyUp(event.key);
			break;

			//TODO: joystick and controller events
		}
	}
}

void BaseScene::Update() {
	//EMPTY
}

void BaseScene::FrameEnd() {
	//EMPTY
}

//-------------------------
//input events
//-------------------------

void BaseScene::QuitEvent() {
	sceneSignal = SceneSignal::QUIT;
}

void BaseScene::MouseMotion(SDL_MouseMotionEvent const& event) {
	//EMPTY
}

void BaseScene::MouseButtonDown(SDL_MouseButtonEvent const& event) {
	//EMPTY
}

void BaseScene::MouseButtonUp(SDL_MouseButtonEvent const& event) {
	//EMPTY
}

void BaseScene::MouseWheel(SDL_MouseWheelEvent const& event) {
	//EMPTY
}

void BaseScene::KeyDown(SDL_KeyboardEvent const& event) {
	//preference as a default
	switch(event.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;
	}
}

void BaseScene::KeyUp(SDL_KeyboardEvent const& event) {
	//EMPTY
}
