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

class TradingCard {
private:
	//define internal types
	typedef signed char type_t;

public:
	enum class Color {
		RED = 0, BLUE = 1
	};

	TradingCard() = delete;
	TradingCard(int index, type_t top, type_t left, type_t right, type_t bottom);
	~TradingCard();

	//controller
	void SetColor(Color c) { color = c; }
	Color GetColor() const { return color; }

	//attributes
	int GetTop() const { return top; }
	int GetLeft() const { return left; }
	int GetRight() const { return right; }
	int GetBottom() const { return bottom; }

	//linked list
	TradingCard* SetNext(TradingCard* n) { return next = n; }
	TradingCard* GetNext() const { return next; }

private:
	const int index = -1; //card identity
	Color color = Color::RED; //who controls the card

	//attributes of the card
	const type_t top = -1, left = -1, right = -1, bottom = -1;

	//linked list
	TradingCard* next = nullptr;
};

//define the sorting functor
class TradingCardSorter : public CardSorter<TradingCard> {
public:
	//EMPTY
protected:
	int Compare(TradingCard* lhs, TradingCard* rhs) override;
};
