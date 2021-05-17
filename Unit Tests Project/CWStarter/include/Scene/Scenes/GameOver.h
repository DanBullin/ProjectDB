#ifndef GAMEOVER_H
#define GAMEOVER_H
#pragma once

#include "Scene/Scene.h"
#include "GameObjects/Objects/StaticImage.h"
#include "GameObjects/Objects/UI/StaticText.h"
#include "GameObjects/Objects/UI/DynamicText.h"

/*! \file GameOver.h
* \brief Header file for GameOver
*
* Implementation for a GameOver
* Inherits from Scene and creates the necassary objects
*/

/*! \class GameOver
\brief A GameOver
*/

/*! A GameOver Class */
class GameOver : public Scene {
public:
	GameOver(Game* game); //!< Constructor requiring pointer to the game
	~GameOver(); //! Destructor which overrides Scene
	void initScene() override; //!< Initialises the scene
	void update(const float& timestep) override; //!< Updates the scene
};
#endif