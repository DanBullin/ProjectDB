#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include "Scene/Scene.h"
#include "GameObjects/Objects/StaticImage.h"
#include "GameObjects/Objects/UI/DynamicText.h"
#include "GameObjects/Objects/UI/StaticText.h"

/*! \file MainMenu.h
* \brief Header file for MainMenu
*
* Implementation for a MainMenu
* Inherits from Scene and creates the necassary objects
*/

/*! \class MainMenu
\brief A MainMenu
*/

/*! A MainMenu Class */
class MainMenu : public Scene {
public:
	MainMenu(Game* game); //!< Constructor requiring pointer to the game
	~MainMenu() override; //! Destructor which overrides Scene
	void initScene() override; //!< Initialises the scene
	void update(const float& timestep) override; //!< Updates the scene
};
#endif