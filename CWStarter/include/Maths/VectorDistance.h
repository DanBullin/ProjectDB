#ifndef VECTORDISTANCE_H
#define VECTORDISTANCE_H
#pragma once

#include <cmath>
#include "Box2D/Common/b2Math.h"
#include <SFML/System/Vector2.hpp>

/*! \file VectorDistance.h
* \brief Header file for VectorDistance
*
* Implementation for VectorDistance
*/

/*! \class VectorDistance
\brief A VectorDistance class
*/

/*! A VectorDistance Class */
class VectorDistance {
public:
	const float operator()(const b2Vec2& a, const b2Vec2& b) const; // Calculate the distance between two b2Vec2 squared
	const float operator()(const sf::Vector2f& a, const sf::Vector2f& b) const; // Calculate the distance between two sf::Vector2f squared
};
#endif