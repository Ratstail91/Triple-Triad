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
	//graphics
	cardSheet.Load(GetRenderer(), "../rsc/level1.png");
	cardSheet.SetClipW(512);
	cardSheet.SetClipH(512);
	frame.Load(GetRenderer(), "../rsc/framing.png");

	//cards
	LoadCards();
	DealCards();
}

ExampleScene::~ExampleScene() {
	CollectCards();
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
	frame.DrawTo(renderer, 0, 0);
	RenderHand(renderer, &leftHand, 0, 0);
	RenderHand(renderer, &rightHand, 672, 0);
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
		case SDLK_r:
			SetSceneSignal(SceneSignal::EXAMPLE_SCENE);
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
	//load the text file
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

void ExampleScene::DealCards() {
	masterList.Shuffle();
	leftHand.Push(masterList.Pop(0, 5));
	rightHand.Push(masterList.Pop(0, 5));
}

void ExampleScene::CollectCards() {
	//return all cards to the master list
	masterList.Push(leftHand.Pop(0, leftHand.Size()));
	masterList.Push(rightHand.Pop(0, rightHand.Size()));
}

void ExampleScene::UnloadCards() {
	//clear the cards from memory
	while (masterList.Peek()) {
		delete masterList.Pop();
	}
	cardSheet.Free();
}

void ExampleScene::RenderHand(SDL_Renderer* renderer, TradingCardList* list, int posX, int posY) {
	//for each card
	for (TradingCard* it = list->Peek(); it != nullptr; it = it->GetNext()) {
		//for the clip
		cardSheet.SetClipX(cardSheet.GetClipW() * static_cast<int>(it->GetColor()) );
		cardSheet.SetClipY(cardSheet.GetClipH() * it->GetIndex());

		//draw to
		cardSheet.DrawTo(renderer, posX, posY, .25, .25);

		//shift the y pos
		posY += cardSheet.GetClipH() * .25 * .5;
	}
}