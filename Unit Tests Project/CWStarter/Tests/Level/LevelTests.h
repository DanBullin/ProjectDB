#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "Game.h"
#include "Scene/Scenes/Level.h"
#include "GameObjects/GameObject.h"

TEST(LevelInternals, PlayerMoveRight) {
	Game game;
	game.showScene("Level", true);
	Player* player = static_cast<Player*>(game.getObject("Player"));
	float playerPositionBefore = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition().x;
	game.getObject("Player")->keyPress(&game, sf::Keyboard::D);
	game.getCurrentScene()->update(2.f);
	float playerPositionAfter = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition().x;
	// Before should be less than After in x axis
	EXPECT_LT(playerPositionBefore, playerPositionAfter);
}

TEST(LevelInternals, PlayerMoveLeft) {
	Game game;
	game.showScene("Level", true);
	Player* player = static_cast<Player*>(game.getObject("Player"));
	float playerPositionBefore = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition().x;
	game.getObject("Player")->keyPress(&game, sf::Keyboard::A);
	game.getCurrentScene()->update(2.f);
	float playerPositionAfter = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition().x;
	// Before should be greater than After in x axis
	EXPECT_GT(playerPositionBefore, playerPositionAfter);
}

TEST(LevelInternals, PlayerJump) {
	Game game;
	game.showScene("Level", true);
	Player* player = static_cast<Player*>(game.getObject("Player"));
	float playerPositionBefore = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition().y;
	game.getObject("Player")->keyRelease(&game, sf::Keyboard::Space);
	game.getCurrentScene()->update(2.f);
	float playerPositionAfter = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition().y;
	// Before should be greater than After in y axis because up is heading in -y direction
	EXPECT_GT(playerPositionBefore, playerPositionAfter);
}

TEST(LevelInternals, PlayerJumpRight) {
	Game game;
	game.showScene("Level", true);
	Player* player = static_cast<Player*>(game.getObject("Player"));
	sf::Vector2f playerPositionBefore = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition();
	game.getObject("Player")->keyPress(&game, sf::Keyboard::D);
	game.getObject("Player")->keyRelease(&game, sf::Keyboard::Space);
	game.getCurrentScene()->update(2.f);
	sf::Vector2f  playerPositionAfter = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition();
	// x Axis should increase, so expect before to be less than after
	// y axis should decrease, so expect before to be greater than after
	EXPECT_LT(playerPositionBefore.x, playerPositionAfter.x);
	EXPECT_GT(playerPositionBefore.y, playerPositionAfter.y);
}

TEST(LevelInternals, PlayerJumpLeft) {
	Game game;
	game.showScene("Level", true);
	Player* player = static_cast<Player*>(game.getObject("Player"));
	sf::Vector2f playerPositionBefore = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition();
	game.getObject("Player")->keyPress(&game, sf::Keyboard::A);
	game.getObject("Player")->keyRelease(&game, sf::Keyboard::Space);
	game.getCurrentScene()->update(2.f);
	sf::Vector2f  playerPositionAfter = static_cast<sf::RectangleShape*>(player->m_drawable)->getPosition();
	// x Axis should increase, so expect before to be greater than after
	// y axis should decrease, so expect before to be greater than after
	EXPECT_GT(playerPositionBefore.x, playerPositionAfter.x);
	EXPECT_GT(playerPositionBefore.y, playerPositionAfter.y);
}

TEST(LevelInternals, ClearLevel) {
	Game game;
	game.showScene("Level", true);
	int objectCountBefore = (int)game.getCurrentScene()->getObjects().size();
	game.getCurrentScene()->clearScene();
	int objectCountAfter = (int)game.getCurrentScene()->getObjects().size();
	int expectedValue = 0;
	EXPECT_NE(objectCountBefore, objectCountAfter);
	EXPECT_EQ(objectCountAfter, expectedValue);
}

TEST(LevelInternals, DisableObjectRender) {
	Game game;
	game.showScene("Level", true);
	// Player is at (0,0)
	// Range is sqrt(90)
	Level* level = static_cast<Level*>(game.getCurrentScene());
	game.getCurrentScene()->m_gameObjects["TestObj"] = new Gem(level->m_world, sf::Vector2f(20.f, 0.f));
	game.getObject("TestObj")->m_draw = true;
	bool expectedValue = false;
	game.getCurrentScene()->update(0.6f);
	// Update calls private disableObjectRender, running update should switch bool to false
	bool result = game.getObject("TestObj")->m_draw;
	EXPECT_EQ(result, expectedValue);
}

TEST(LevelInternals, HUDPositionUpdate) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	sf::Vector2f posBefore = static_cast<sf::RectangleShape*>(level->m_gameObjects["Background"]->m_drawable)->getPosition();
	game.getObject("Player")->keyPress(&game, sf::Keyboard::D);
	game.getCurrentScene()->update(2.f);
	sf::Vector2f posAfter = static_cast<sf::RectangleShape*>(level->m_gameObjects["Background"]->m_drawable)->getPosition();
	EXPECT_NE(posBefore, posAfter);
}

TEST(LevelInternals, InitLevel) {
	Game game;
	Level level(&game);
	int sizeBefore = level.m_gameObjects.size();
	level.initScene();
	int sizeAfter = level.m_gameObjects.size();
	EXPECT_NE(sizeBefore, sizeAfter);
}

TEST(LevelInternals, SceneEnabled) {
	Game game;
	Level level(&game);
	level.setEnabled(false);
	bool before = level.getEnabled();
	level.setEnabled(true);
	bool after = level.getEnabled();
	EXPECT_NE(before, after);
}

TEST(LevelInternals, KeyHUDTextureChange) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(game.getObject("Player"));
	player->m_collectedKey = true;
	const sf::Texture* textureBefore = (static_cast<sf::RectangleShape*>(game.getObject("zKeyIcon")->m_drawable))->getTexture();
	level->updateObjects();
	const sf::Texture* textureAfter = (static_cast<sf::RectangleShape*>(game.getObject("zKeyIcon")->m_drawable))->getTexture();
	EXPECT_NE(textureBefore, textureAfter);
}

TEST(LevelInternals, LevelPauseTextPress) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	std::string sceneNameBefore = game.getCurrentScene()->m_name;
	game.getObject("zPauseText")->mouseRelease(&game);
	std::string sceneNameAfter = game.getCurrentScene()->m_name;
	EXPECT_NE(sceneNameBefore, sceneNameAfter);
}

TEST(LevelInternals, GemTextCountChange) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(game.getObject("Player"));
	sf::Text* text = static_cast<sf::Text*>(game.getObject("zHUDInfoText")->m_drawable);
	level->update(0.6f);
	std::string textBefore = text->getString();
	player->m_gemsCollected = 10;
	level->update(0.6f);
	std::string textAfter = text->getString();
	EXPECT_NE(textBefore, textAfter);
}

TEST(LevelInternals, LivesTextCountChange) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(game.getObject("Player"));
	sf::Text* text = static_cast<sf::Text*>(game.getObject("zHUDInfoText")->m_drawable);
	level->update(0.6f);
	std::string textBefore = text->getString();
	player->m_lives = 1;
	level->update(0.6f);
	std::string textAfter = text->getString();
	EXPECT_NE(textBefore, textAfter);
}

TEST(LevelInternals, GameOverGemsText) {
	Game game;
	game.showScene("Level", true);
	Player* player = static_cast<Player*>(game.getObject("Player"));
	player->m_gemsCollected = 7;
	game.showScene("GameOver", false);
	sf::Text* text = static_cast<sf::Text*>(game.getObject("GemsCollected")->m_drawable);

	std::string gemsText = text->getString();
	bool actualValue = gemsText.find(std::to_string(player->m_gemsCollected)) != std::string::npos;
	bool containsExpectedValue = true;
	EXPECT_EQ(actualValue, containsExpectedValue);
}