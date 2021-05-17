#pragma once
#include <gtest/gtest.h>

#define private public
#define protected public
#include "Game.h"

TEST(Collisions, PlayerGem) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	int gemCountBefore = player->getGemsCollected();
	level->getObjects()["GemTest"] = new Gem(level->m_world, sf::Vector2f(0.f, 0.f));
	game.getCurrentScene()->update(0.6f);
	int gemCountAfter = player->getGemsCollected();
	// Count after should be greater than Count before
	EXPECT_LT(gemCountBefore, gemCountAfter);
}

TEST(Collisions, PlayerGemDeleted) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	level->getObjects()["GemTest"] = new Gem(level->m_world, sf::Vector2f(0.f, 0.f));
	bool gemExistsBefore = level->getObjects().find("GemTest") != level->getObjects().end();
	game.getCurrentScene()->update(0.6f);
	bool gemExistsAfter = level->getObjects().find("GemTest") != level->getObjects().end();
	// Before shouldn't reach the end therefore bool will be true
	// After should reach the end so the bool should be false
	EXPECT_NE(gemExistsBefore, gemExistsAfter);
}

TEST(Collisions, PlayerLava) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	int livesCountBefore = player->getLives();
	level->getObjects()["LavaTest"] = new Lava(level->m_world, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.32f, 0.32f), 0);
	game.getCurrentScene()->update(0.6f);
	int livesCountAfter = player->getLives();
	// Count after should be greater than Count before
	EXPECT_GT(livesCountBefore, livesCountAfter);
}

TEST(Collisions, PlayerEnemy) {
	Game game;
	game.showScene("Level", true);

	Player* player = static_cast<Player*>(game.getObject("Player"));
	player->mk_spawnPoint = sf::Vector2f(10.f, 10.f);
	game.getCurrentScene()->update(0.6f);
	int livesCountBefore = player->getLives();
	game.getCurrentScene()->getObjects()["EnemyTest"] = new Enemy(static_cast<Level*>(game.getCurrentScene())->m_world, 0.f, -0.5f, b2Vec2(0.f, 0.f), 200.f);
	game.getCurrentScene()->update(0.6f);
	int livesCountAfter = player->getLives();
	// Count after should be greater than Count before
	EXPECT_GT(livesCountBefore, livesCountAfter);
}

TEST(Collisions, PlayerKey) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	bool keyCollectedBefore = player->getKeyCollected();
	level->getObjects()["KeyTest"] = new Key(level->m_world, sf::Vector2f(0.f, 0.f));
	game.getCurrentScene()->update(0.6f);
	bool keyCollectedAfter = player->getKeyCollected();
	// Count after should be greater than Count before
	EXPECT_NE(keyCollectedBefore, keyCollectedAfter);
}

TEST(Collisions, PlayerDoorWithNoKey) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	player->m_collectedKey = false;

	std::string sceneName = game.m_currentScene;
	level->getObjects()["DoorTest"] = new Door(level->m_world, sf::Vector2f(0.f, 0.f));
	game.getCurrentScene()->update(0.6f);
	std::string sceneNameAfter = game.m_currentScene;

	EXPECT_EQ(sceneName, sceneNameAfter);
}

TEST(Collisions, PlayerDoorWithKey) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	player->m_collectedKey = true;

	std::string sceneName = game.m_currentScene;
	level->getObjects()["DoorTest"] = new Door(level->m_world, sf::Vector2f(0.f, 0.f));
	game.getCurrentScene()->update(0.6f);
	std::string sceneNameAfter = game.m_currentScene;

	EXPECT_NE(sceneName, sceneNameAfter);
}

TEST(Collisions, PlayerGravitySwitch) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	player->m_applyReverseGravity = false;

	bool before = player->m_applyReverseGravity;
	level->getObjects()["GSTest"] = new GravitySwitch(level->m_world, sf::Vector2f(0.f, 0.f));
	game.getCurrentScene()->update(0.6f);
	bool after = player->m_applyReverseGravity;

	EXPECT_NE(before, after);
}

TEST(Collisions, PlayerFootStaticBlock) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	game.getCurrentScene()->update(0.6f);
	int footCollisionsBefore = player->m_footCollisions;
	player->keyRelease(&game, sf::Keyboard::Space);
	game.getCurrentScene()->update(0.6f);
	int footCollisionsAfter = player->m_footCollisions;

	EXPECT_GT(footCollisionsBefore, footCollisionsAfter);
}

TEST(Collisions, PlayerDoorSensor) {
	Game game;
	game.showScene("Level", true);
	Level* level = static_cast<Level*>(game.getCurrentScene());
	Player* player = static_cast<Player*>(level->m_gameObjects["Player"]);
	level->getObjects()["SensorTest"] = new DoorSensor(level->m_world, sf::Vector2f(0.f, 0.f), (IronDoor*)level->m_gameObjects["IronDoor1"], (IronDoor*)level->m_gameObjects["IronDoor2"]);
	game.getCurrentScene()->update(0.6f);
	b2Vec2 door1PosBefore = ((IronDoor*)level->m_gameObjects["IronDoor1"])->m_body->GetPosition();
	b2Vec2 door2PosBefore = ((IronDoor*)level->m_gameObjects["IronDoor2"])->m_body->GetPosition();
	game.getCurrentScene()->update(0.6f);
	b2Vec2 door1PosAfter = ((IronDoor*)level->m_gameObjects["IronDoor1"])->m_body->GetPosition();
	b2Vec2 door2PosAfter = ((IronDoor*)level->m_gameObjects["IronDoor2"])->m_body->GetPosition();
	EXPECT_NE(door1PosBefore, door1PosAfter);
	EXPECT_NE(door2PosBefore, door2PosAfter);
}