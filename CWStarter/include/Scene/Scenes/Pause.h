#ifndef PAUSE_H
#define PAUSE_H
#pragma once

#include "Scene/Scene.h"
#include "GameObjects/Objects/StaticImage.h"
#include "GameObjects/Objects/UI/DynamicText.h"

/*! \file Pause.h
* \brief Header file for Pause
*
* Implementation for a Pause
* Inherits from Scene and creates the necassary objects
*/

/*! \class Pause
\brief A Pause
*/

/*! A Pause Class */
class Pause : public Scene {
public:
	Pause(Game* game); //!< Constructor requiring pointer to the game
	~Pause(); //! Destructor which overrides Scene
	void initScene() override; //!< Initialises the scene
	void update(const float& timestep) override; //!< Updates the scene
};
#endif