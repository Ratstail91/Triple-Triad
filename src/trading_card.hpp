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
#pragma once

#include "card_list.hpp"
#include "card_shuffler.hpp"
#include "card_sorter.hpp"
#include "sprite_sheet.hpp"

#include "SDL2/SDL.h"

class TradingCard {
private:
	//define internal types
	typedef signed char type_t;

public:
	enum class Color {
		RED = 0, BLUE = 1
	};

	TradingCard() = delete;
	TradingCard(SDL_Texture*, int index, type_t top, type_t left, type_t right, type_t bottom);
	~TradingCard();

	void DrawTo(SDL_Renderer*);

	//controller
	void SetColor(Color);
	Color GetColor() const { return color; }

	//position
	void SetX(int i) { posX = i; }
	void SetY(int i) { posY = i; }
	int GetX() { return posX; }
	int GetY() { return posY; }

	//attributes
	int GetTop() const { return top; }
	int GetLeft() const { return left; }
	int GetRight() const { return right; }
	int GetBottom() const { return bottom; }

	//linked list
	TradingCard* SetNext(TradingCard* n) { return next = n; }
	TradingCard* GetNext() const { return next; }

private:
	SpriteSheet cardSheet;
	const int index = -1; //index on the spritesheet
	Color color = Color::RED; //also an index
	int posX = 0, posY = 0; //screenpos

	//attributes of the card
	const type_t top = -1, left = -1, right = -1, bottom = -1;

	//linked list
	TradingCard* next = nullptr;
};

//define the sorting functor
class SortFunctor : public CardSorter<TradingCard> {
public:
	//EMPTY
protected:
	int Compare(TradingCard* lhs, TradingCard* rhs) override;
};

//define the list type
typedef CardList<TradingCard, SortFunctor> TradingCardList;
