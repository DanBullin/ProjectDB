#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include "Managers/ResourceManager.h"

/*! \file GameObject.h
* \brief Header file for GameObject
*
* Implementation for a GameObject
*/

/*! \class GameObject
\brief A GameObject
*/

class Game; // Forward declare Game

/*! A GameObject Class */
class GameObject : public sf::Drawable {
protected:
	std::string m_name = "Default"; //!< The name of the object
	bool m_draw = true; //!< Bool dictating whether to draw the object
	bool m_enabled = true; //!< Bool dictating whether to update the object
	bool m_markedDeletion = false; //!< Bool dictating whether to schedule the object for deletion
	bool m_animated = false; //!< Bool dictating whether to animate the object
	sf::Drawable* m_drawable; //!< The SFML shape of the object
public:
	GameObject(); //!< Constructor
	virtual ~GameObject(); //!< Destructor

	std::string getName() const; //!< Get the name of the object
	void setDraw(const bool draw); //!< Set whether the object is drawn
	bool getDraw() const; //!< Get whether the object is drawn
	bool getAnimated() const; //!< Get whether the object is animated
	void setEnabled(const bool enable); //!< Set whether the object is enabled
	bool getEnabled() const; //!< Get whether the object is enabled
	void scheduleForDeletion(const bool destroy); //!< Schedule the object for deletion
	bool getScheduleForDeletion() const; //!< Get whether the object is scheduled for deletion
	sf::Drawable* getDrawable(); //!< Get the SFML drawable component

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game object
	virtual bool contains(const sf::Vector2f pos) = 0; //!< Does the point lay within the bounds of the object
	virtual void mouseEnter(Game* game); //!< Action to run when the mouse enters. Must attach to the EventListener
	virtual void mouseLeave(Game* game); //!< Action to run when the mouse leaves. Must attach to the EventListener
	virtual void mousePress(Game* game); //!< Action to run when the mouse presses the object. Must attach to the EventListener
	virtual void mouseRelease(Game* game); //!< Action to run when the mouse releases the object. Must attach to the EventListener
	virtual void keyPress(Game* game, const int key); //!< Action to run when a key is pressed. Must attach to the EventListener
	virtual void keyRelease(Game* game, const int key); //!< Action to run when a key is released. Must attach to the EventListener
	virtual void animationUpdate(); //!< Animation update for the object
	virtual void update(Game* game) = 0; //!< Update the object
};
#endif