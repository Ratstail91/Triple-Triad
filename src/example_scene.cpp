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
#include "example_scene.hpp"

#include <iostream>
#include <fstream>

ExampleScene::ExampleScene() {
	LoadCards();

	//debugging
	std::cout << "card count: " << masterList.Size() << std::endl;
}

ExampleScene::~ExampleScene() {
	UnloadCards();
}

//-------------------------
//frame phases
//-------------------------

void ExampleScene::FrameStart() {
	//
}

void ExampleScene::Update() {
	//
}

void ExampleScene::FrameEnd() {
	//
}

void ExampleScene::RenderFrame(SDL_Renderer* renderer) {
	cardSheet.DrawTo(renderer, 0, 0, .25, .25);
}

//-------------------------
//input events
//-------------------------

void ExampleScene::MouseMotion(SDL_MouseMotionEvent const& event) {
	//
}

void ExampleScene::MouseButtonDown(SDL_MouseButtonEvent const& event) {
	//
}

void ExampleScene::MouseButtonUp(SDL_MouseButtonEvent const& event) {
	//
}

void ExampleScene::MouseWheel(SDL_MouseWheelEvent const& event) {
	//
}

void ExampleScene::KeyDown(SDL_KeyboardEvent const& event) {
	//preference as a default
	switch(event.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;
	}
}

void ExampleScene::KeyUp(SDL_KeyboardEvent const& event) {
	//
}

//-------------------------
//misc
//-------------------------

void ExampleScene::LoadCards() {
	//open the image & text files
	cardSheet.Load(GetRenderer(), "../rsc/level1.png");
	std::ifstream is("../rsc/level1.txt");
	int index;
	int top, left, right, bottom;

	//TODO: parsing error checks
	while (!is.eof()) {
		//read the card data
		is >> index;
		is >> top;
		is >> left;
		is >> right;
		is >> bottom;

		masterList.Push(new TradingCard(index, top, left, right, bottom));
	}

	//close the text file
	is.close();
}

void ExampleScene::UnloadCards() {
	//clear the cards from memory
	while (masterList.Peek()) {
		delete masterList.Pop();
	}
	cardSheet.Free();
}
