#ifndef STATICTEXT_H
#define STATICTEXT_H
#pragma once

#include "GameObjects/GameObject.h"
#include "Game.h"
#include "Events/EventListener.h"

/*! \file StaticText.h
* \brief Header file for StaticText
*
* Implementation for a StaticText
*/

/*! \class StaticText
\brief A StaticText
*/

/*! A StaticText Class */
class StaticText : public GameObject {
public:
	StaticText(const std::string text, const sf::Vector2f pos, const unsigned int characterSize, const sf::Color& colour); //!< Constructor
	bool contains(sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
};
#endif