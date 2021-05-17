#include "Maths/VectorDistance.h"

/*! \file VectorDistance.cpp
* \brief CPP file for VectorDistance
*
* Implementation for VectorDistance
*
*/

/*!
\param a a const& b2Vec2 - Vector a
\param b a const& b2Vec2 - Vector b
\return a const float - The distance between the two vectors squared
*/
const float VectorDistance::operator()(const b2Vec2& a, const b2Vec2& b) const
{
	// Calculate the vector from a to b
	b2Vec2 vector = a - b;
	// Square both components and add them
	float result = pow(vector.x, 2) + pow(vector.y,2);
	// Removed the sqrt because its expensive
	return result;
}

/*!
\param a a const& sf::Vector2f - Vector a
\param b a const& sf::Vector2f - Vector b
\return a const float - The distance between the two vectors squared
*/
const float VectorDistance::operator()(const sf::Vector2f& a, const sf::Vector2f& b) const
{
	// Calculate the vector from a to b
	sf::Vector2f vector = a - b;
	// Square both components and add them
	float result = pow(vector.x, 2) + pow(vector.y, 2);
	// Removed the sqrt because its expensive
	return result;
}