#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "Game.h"

TEST(GameInternals, WindowCreation) {
	Game game;
	// Game constructor calls initGame, which creates window
	void* addr = nullptr;
	void* windowAddr = game.m_window;
	// therefore, windowAddr shouldn't be a nullptr, check this
	EXPECT_NE(addr, windowAddr);
}

TEST(GameInternals, SceneCreation_NEW) {
	Game game;
	// Game constructor calls initGame, which creates a MainMenu Scene
	// However, if you call getCurrentScene, if the scene doesnt exist, it creates it for you
	// Level isn't created by default, so lets tests creating Level
	bool levelCreatedBefore = game.m_scenes.find("Level") != game.m_scenes.end();
	game.m_currentScene = "Level";
	game.getCurrentScene();
	bool levelCreatedAfter = game.m_scenes.find("Level") != game.m_scenes.end();
	// therefore, windowAddr shouldn't be a nullptr, check this
	EXPECT_NE(levelCreatedBefore, levelCreatedAfter);
}

TEST(GameInternals, SceneCreation_OLD) {
	Game game;
	// Game constructor calls initGame, which creates a MainMenu Scene
	// However, if you call getCurrentScene, if the scene doesnt exist, it creates it for you
	// Lets test that getCurrentScene doesn't create a scene that already exists
	// Main menu already exists, lets check scene list size
	int sceneSizeBefore = (int)game.m_scenes.size();
	game.m_currentScene = "MainMenu";
	game.getCurrentScene();
	int sceneSizeAfter = (int)game.m_scenes.size();
	// therefore, windowAddr shouldn't be a nullptr, check this	
	EXPECT_EQ(sceneSizeBefore, sceneSizeAfter);
}

TEST(GameInternals, ShowScene) {
	Game game;
	// Lets check showing scene is processing how it should
	// Requires scene name and whether old scene should be destroyed
	// Current scene is MainMenu

	int sizeBefore = (int)game.m_scenes.size();
	bool mainMenuExists = game.m_scenes.find("MainMenu") != game.m_scenes.end();
	std::string scene = game.m_currentScene;
	game.showScene("Level", true);
	// Scene size should remain at one because MainMenu is being deleted;
	int sizeAfter = (int)game.m_scenes.size();
	std::string sceneAfter = game.m_currentScene;
	bool mainMenuExistsAfter = game.m_scenes.find("MainMenu") != game.m_scenes.end();
	EXPECT_EQ(sizeBefore, sizeAfter);
	EXPECT_NE(scene, sceneAfter);
	EXPECT_NE(mainMenuExists, mainMenuExistsAfter);
}

TEST(GameInternals, DeleteScenes) {
	Game game;
	// Schedule scene for deletion and then delete
	bool mainMenuExists = game.m_scenes.find("MainMenu") != game.m_scenes.end();
	game.m_scenes["MainMenu"]->m_markedDeletion = true;
	game.destroyScheduledScenes();
	bool mainMenuExistsAfter = game.m_scenes.find("MainMenu") != game.m_scenes.end();
	EXPECT_NE(mainMenuExists, mainMenuExistsAfter);
}

TEST(GameInternals, GetValidObject) {
	Game game;
	void* testValue = nullptr;
	void* objectAddr = game.getObject("Logo");
	EXPECT_NE(testValue, objectAddr);
}

TEST(GameInternals, GetInvalidObject) {
	Game game;
	void* testValue = nullptr;
	// Object that doesn't exist should return a nullptr;
	void* objectAddr = game.getObject("Logo1");
	EXPECT_EQ(testValue, objectAddr);
}

TEST(GameInternals, GetCurrentScene) {
	Game game;
	std::string testValue1 = "Main Menu";
	std::string gameValue1 = game.getCurrentScene()->m_name;
	EXPECT_EQ(gameValue1, testValue1);
	std::string testValue2 = "Level";
	game.showScene("Level", true);
	std::string gameValue2 = game.getCurrentScene()->m_name;
	EXPECT_EQ(gameValue2, testValue2);
}

TEST(GameInternals, GetScene) {
	Game game;
	void* mainMenuAddr = game.getScene("MainMenu");
	void* mainMenuAddr2 = game.m_scenes["MainMenu"];
	EXPECT_EQ(mainMenuAddr, mainMenuAddr2);
}

TEST(GameInternals, UpdateView) {
	Game game;
	game.showScene("Level", true);
	// Player is centre screen
	// If player moves, view's centre must move
	sf::Vector2f posBefore = game.m_window->getView().getCenter();
	// Set player's velcity
	static_cast<PhysicsObject*>(game.getObject("Player"))->m_body->SetLinearVelocity(b2Vec2(100.f, 0.f));
	// Step the physics world
	game.getCurrentScene()->update(2.f);
	// Update view and set it to window
	game.updateView();
	game.m_window->setView(game.getWindow()->getGameView());
	sf::Vector2f posAfter = game.m_window->getView().getCenter();
	// Centre should change
	EXPECT_NE(posBefore, posAfter);
}

TEST(GameInternals, GameOverQuitTextPress) {
	Game game;
	game.showScene("Level", true);
	game.showScene("GameOver", false);
	std::string sceneNameBefore = game.getCurrentScene()->m_name;
	game.getObject("Quit")->mouseRelease(&game);
	std::string sceneNameAfter = game.getCurrentScene()->m_name;
	EXPECT_NE(sceneNameBefore, sceneNameAfter);
}

TEST(GameInternals, PauseResumeTextPress) {
	Game game;
	game.showScene("Level", true);
	game.showScene("Pause", false);
	std::string sceneNameBefore = game.getCurrentScene()->m_name;
	game.getObject("Resume")->mouseRelease(&game);
	std::string sceneNameAfter = game.getCurrentScene()->m_name;
	EXPECT_NE(sceneNameBefore, sceneNameAfter);
}