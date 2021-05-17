#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H
#pragma once

#include "Scene/Scenes/Level.h"

/*! \file EventListener.h
* \brief Header file for EventListener
*
* Implementation for an Event Listener
*/

/*! \class EventListener
\brief An EventListener
*/

class Game; // Forward declared Game class

/*! An EventListener Class */
class EventListener {
private:
	EventListener(); //!< Constructor which is private to prevent initialisations
	static bool m_InstanceFlag; //!< Static flag tracking if an instance has been created
	static EventListener* m_eventListener; //!< Pointer to the event listener

	std::vector<int> m_keysActive; //!< A vector of all keys currently held
	GameObject* m_activeObject = nullptr; //!< A pointer to the selected game object
	std::vector<GameObject*> m_subscribedObjects; //!< A vector of pointers to all subscribing game objects listening for input notifications
	bool keyAlreadyExists(const int key); //!< Checks if key already is pressed
	void eraseKey(const int key); //!< Erases the key from the active keys list
public:
	~EventListener(); //!< Destructor
	EventListener(const EventListener&) = delete; // Copy is deleted
	static EventListener* getInstance(); //!< Returns a pointer to the single event listener

	void attach(GameObject* object); //!< Subscribe the gameobject passed to the event listener
	void detach(GameObject* object); //!< Unsubscribe the gameobject passed to the event listener
	void notify(Game* game, const int eventType, const sf::Vector2f mousePos); //!< Notify all subscribing objects of the mouse event
	void notify(Game* game, const int eventType, const int key); //!< Notify all subscribing objects of the key event
	void update(Game* game); //!< Update all subscribing objects for repeated events
	void clearSubscriptions(); //!< Remove all subscribing objects
};
#endif