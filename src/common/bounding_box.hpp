/* Copyright: (c) Kayne Ruse 2013-2015
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

class BoundingBox {
public:
	//This is explicitly a POD
	int x, y;
	int w, h;

	BoundingBox() = default;
	BoundingBox(BoundingBox const&) = default;
	BoundingBox(BoundingBox&&) = default;
	BoundingBox(int i, int j);
	BoundingBox(int i, int j, int k, int l);
	~BoundingBox() = default;

	BoundingBox& operator=(BoundingBox const&) = default;
	BoundingBox& operator=(BoundingBox&&) = default;

	int Area();

	//TODO: collision needs improving
	bool CheckOverlap(BoundingBox rhs);
	BoundingBox CalcOverlap(BoundingBox rhs);
};

#include "vector2.hpp"

//operators
inline BoundingBox operator+(BoundingBox b, Vector2 v) {
	return {b.x + (int)v.x, b.y + (int)v.y, b.w, b.h};
}
inline BoundingBox operator+(Vector2 v, BoundingBox b) {
	return b + v;
}