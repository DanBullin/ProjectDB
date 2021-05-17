#ifndef DYNAMICTEXT_H
#define DYNAMICTEXT_H
#pragma once

#include "GameObjects/GameObject.h"
#include "Game.h"
#include "Events/EventListener.h"

/*! \file DynamicText.h
* \brief Header file for DynamicText
*
* Implementation for a DynamicText
*/

/*! \class DynamicText
\brief A DynamicText
*/

/*! A DynamicText Class */
class DynamicText : public GameObject {
private:
	unsigned int m_releaseAction = 0; //!< The action index of the actions to run when mouse is released
public:
	DynamicText(const std::string text, const sf::Vector2f pos, const unsigned int characterSize, const unsigned int releaseAction); //!< Constructor
	bool contains(sf::Vector2f pos) override; //!< Does this object contain the point passed
	void update(Game* game) override; //!< Update the object
	void mouseEnter(Game* game) override; //!< Action to run when the mouse enters. Must attach to the EventListener
	void mouseLeave(Game* game) override; //!< Action to run when the mouse leaves. Must attach to the EventListener
	void mouseRelease(Game* game) override; //!< Action to run when the mouse releases. Must attach to the EventListener
};
#endif