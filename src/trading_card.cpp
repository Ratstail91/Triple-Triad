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
#include "trading_card.hpp"

TradingCard::TradingCard(SDL_Texture* tex, int index, type_t _top, type_t _left, type_t _right, type_t _bottom):
	index(index),
	top(_top),
	left(_left),
	right(_right),
	bottom(_bottom)
{
	cardSheet.SetTexture(tex, 2, 10); //TODO: this parameter will need changing
	cardSheet.SetIndexX(static_cast<int>(color) * cardSheet.GetClipW());
	cardSheet.SetIndexY(index * cardSheet.GetClipW());
}

TradingCard::~TradingCard() {
	//TODO: a memory leak warning
}

void TradingCard::DrawTo(SDL_Renderer* renderer) {
	cardSheet.DrawTo(renderer, posX, posY, .25, .25);
}

void TradingCard::SetColor(Color c) {
	color = c;
	cardSheet.SetIndexX(static_cast<int>(color) * cardSheet.GetClipW());
}

//define the sorting functor
int SortFunctor::Compare(TradingCard* lhs, TradingCard* rhs) {
	//unknown, just use a placeholder
	if (lhs->GetTop() < rhs->GetTop()) return -1;
	if (lhs->GetTop() > rhs->GetTop()) return 1;

	if (lhs->GetTop() < rhs->GetTop()) return -1;
	if (lhs->GetTop() > rhs->GetTop()) return 1;

	if (lhs->GetTop() < rhs->GetTop()) return -1;
	if (lhs->GetTop() > rhs->GetTop()) return 1;

	if (lhs->GetTop() < rhs->GetTop()) return -1;
	if (lhs->GetTop() > rhs->GetTop()) return 1;

	return 0;
}