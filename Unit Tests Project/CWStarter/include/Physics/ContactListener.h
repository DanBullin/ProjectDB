#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H
#pragma once

#include <Box2D\Box2D.h>

/*! \file ContactListener.h
* \brief Header file for ContactListener
*
* Implementation for a ContactListener
*/

/*! \class ContactListener
\brief A ContactListener
*/

/*! A Contact Listener */
class ContactListener : public b2ContactListener
{
public:
	ContactListener(); //!< Constructor
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};
#endif