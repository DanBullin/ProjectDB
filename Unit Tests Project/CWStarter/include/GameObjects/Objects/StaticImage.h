#ifndef STATICIMAGE_H
#define STATICIMAGE_H
#pragma once

#include "GameObjects/GameObject.h"

/*! \file StaticImage.h
* \brief Header file for StaticImage
*
* Implementation for a StaticImage
*/

/*! \class StaticImage
\brief A StaticImage
*/

/*! A StaticImage Class */
class StaticImage : public GameObject {
public:
	StaticImage(const sf::Vector2f pos, const sf::Vector2f size, const sf::Vector2f scale, const std::string textureName); //!< Constructor
	bool contains(const sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif