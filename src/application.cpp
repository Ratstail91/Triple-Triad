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
#include "application.hpp"

#include <chrono>
#include <sstream>
#include <stdexcept>

void Application::Init(int argc, char* argv[]) {
	//create and check the window
	window = SDL_CreateWindow(
		"Triple Triad",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_RESIZABLE);

	if (!window) {
		std::ostringstream msg;
		msg << "Failed to create the window: " << SDL_GetError();
		throw(std::runtime_error(msg.str()));
	}

	//create and check the renderer
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		std::ostringstream msg;
		msg << "Failed to create the renderer: " << SDL_GetError();
		throw(std::runtime_error(msg.str()));
	}

	//screen scaling
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	SDL_RenderSetLogicalSize(renderer, 800, 600);

	//set the hook for the renderer
	BaseScene::SetRenderer(renderer);
}

void Application::Proc() {
	//load the first scene
	ProcessSceneSignal(SceneSignal::FIRST);

	//fixed frame rate
	typedef std::chrono::steady_clock Clock;

	Clock::time_point simTime = Clock::now();
	Clock::time_point realTime;
	constexpr std::chrono::duration<int, std::milli> frameDelay(16); //~60FPS

	//the game loop continues until the scenes signal QUIT
	while(activeScene->GetSceneSignal() != SceneSignal::QUIT) {
		//switch scenes if necessary
		if(activeScene->GetSceneSignal() != SceneSignal::CONTINUE) {
			ProcessSceneSignal(activeScene->GetSceneSignal());
			continue;
		}

		//update the current time
		realTime = Clock::now();

		//simulate the game or give the machine a break
		if (simTime < realTime) {
			while(simTime < realTime) {
				//call the user defined functions
				activeScene->RunFrame();
				//step to the next frame
				simTime += frameDelay;
			}
		}
		else {
			SDL_Delay(1);
		}

		SDL_RenderClear(renderer);
		activeScene->RenderFrame(renderer);
		SDL_RenderPresent(renderer);
	}

	//cleanup
	ClearScene();
}

void Application::Quit() {
	//cleran up after the program
	BaseScene::SetRenderer(nullptr);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//TODO: is this necessary?
//	SDL_Quit();
}

//-------------------------
//Scene management
//-------------------------

//Add the custom scene headers here
#include "example_scene.hpp"

void Application::ProcessSceneSignal(SceneSignal signal) {
	ClearScene();

	switch(signal) {
		case SceneSignal::FIRST:
		case SceneSignal::EXAMPLE_SCENE:
			activeScene = new ExampleScene();
		break;
		default: {
			std::ostringstream msg;
			msg << "Failed to recognize the scene signal: " << signal;
			throw(std::logic_error(msg.str()));
		}
	}
}

void Application::ClearScene() {
	delete activeScene;
	activeScene = nullptr;
}