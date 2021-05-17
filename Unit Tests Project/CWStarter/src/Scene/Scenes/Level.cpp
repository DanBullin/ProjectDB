#include "Scene/Scenes/Level.h"

/*! \file Level.cpp
* \brief CPP file for Level
*
* Implementation for Level
*
*/

/*!
\param game a Game* - A pointer to the game
*/
Level::Level(Game* game)
	: Scene(game)
{
	// Set the name
	m_name = "Level";
	// Set world to null
	m_world = nullptr;
	m_drawBodies = false;
}

//! Destructor()
Level::~Level()
{
	// Delete all heap allocated objects by clearing scene
	//LOG("Deleting scene: " + m_name);
	clearScene();
}

//! initScene()
void Level::initScene()
{
	// Enable the scene, create world and create objects
	m_enabled = true;
	m_world = new b2World(mk_gravity);
	// Give the SFMLDebugDraw the world
	m_physicsDraw.setWorld(m_world);
	// Set the contact listener
	m_world->SetContactListener(&m_contactListener);
	m_animationClock.restart();

	// Create some of the objects
	createEnvironment(); // StaticBlocks + Static Platforms
	createStatics(); // HUD + Background
	createGems(); // Collectables

	// The rest which are less duplicated
	m_gameObjects["Lava1"] = new Lava(m_world, sf::Vector2f(21.f, 1.84f), sf::Vector2f(4.f, 0.32f), 180);
	m_gameObjects["Lava2"] = new Lava(m_world, sf::Vector2f(36.5f, 1.84f), sf::Vector2f(8.f, 0.32f), 180);
	m_gameObjects["Lava3"] = new Lava(m_world, sf::Vector2f(46.f, -16.34f), sf::Vector2f(2.f, 0.32f), 180);
	m_gameObjects["Box1"] = new Box(m_world, sf::Vector2f(4.f, -0.33f), sf::Vector2f(0.64f, 0.64f));
	m_gameObjects["GravitySwitch1"] = new GravitySwitch(m_world, sf::Vector2f(49.f, -0.35f));
	m_gameObjects["GravitySwitch2"] = new GravitySwitch(m_world, sf::Vector2f(49.2f, -15.3f));
	m_gameObjects["Key"] = new Key(m_world, sf::Vector2f(63.2f, -6.8f));
	m_gameObjects["Door"] = new Door(m_world, sf::Vector2f(23.f, -5.32f));

	m_gameObjects["IronDoor1"] = new IronDoor(m_world, b2Vec2(61.f, -8.f), -1);
	m_gameObjects["IronDoor2"] = new IronDoor(m_world, b2Vec2(61.f, -7.f), 1);
	m_gameObjects["DoorSensor1"] = new DoorSensor(m_world, sf::Vector2f(59.f, -8.f), static_cast<IronDoor*>(m_gameObjects["IronDoor1"]), static_cast<IronDoor*>(m_gameObjects["IronDoor2"]));

	m_gameObjects["MovingPlatform1"] = new MovingPlatform(m_world, 21.f, 0.5f, b2Vec2(-1.f, 0.f), 100);
	m_gameObjects["MovingPlatform2"] = new MovingPlatform(m_world, 27.5f, -3.f, b2Vec2(0.f, -1.f), 200);
	m_gameObjects["MovingPlatform3"] = new MovingPlatform(m_world, 55.5f, -10.5f, b2Vec2(0.f, -1.f), 400);
	m_gameObjects["RevolvingPlatform1"] = new RevolvingPlatform(m_world, 39.f, -0.2f, 0);
	m_gameObjects["RevolvingPlatform2"] = new RevolvingPlatform(m_world, 34.f, 0.2f, 0);
	m_gameObjects["RevolvingPlatform3"] = new RevolvingPlatform(m_world, 36.5f, -1.f, 0);
	m_gameObjects["Enemy1"] = new Enemy(m_world, 27.5f, -0.24f, b2Vec2(1.f, 0.f), 300.f);
	m_gameObjects["Enemy2"] = new Enemy(m_world, 14.f, -0.24f, b2Vec2(1.f, 0.f), 300.f);
	m_gameObjects["Enemy3"] = new Enemy(m_world, 44.65f, -0.24f, b2Vec2(1.f, 0.f), 300.f);
	m_gameObjects["Enemy4"] = new Enemy(m_world, 50.9f, -13.68f, b2Vec2(1.f, 0.f), 200.f);
	m_gameObjects["Player"] = new Player(m_world);
}

//! createStatic()
void Level::createStatics()
{
	// Static background
	m_gameObjects["Background"] = new StaticImage(sf::Vector2f(-4.f, -3.f), sf::Vector2f(8.f, 6.f), sf::Vector2f(1.f, 1.f), "background");
	// HUD
	// Start with z because iterating through map is done alphabetically and HUD needs to be at the top of layer
	m_gameObjects["zPauseText"] = new DynamicText("II", sf::Vector2f(-1.f, -1.f), 40, 2);
	m_gameObjects["zGemIcon"] = new StaticImage(sf::Vector2f(0.f, -1.f), sf::Vector2f(0.32f, 0.32f), sf::Vector2f(1.f, 1.f), "gem");
	m_gameObjects["zLivesIcon"] = new StaticImage(sf::Vector2f(0.f, -1.f), sf::Vector2f(0.48f, 0.48f), sf::Vector2f(1.f, 1.f), "lives");
	m_gameObjects["zKeyIcon"] = new KeyIcon;
	m_gameObjects["zHUDInfoText"] = new StaticText("", sf::Vector2f(0.f, -1.f), 20, sf::Color::White);
	m_gameObjects["zIntro"] = new StaticText("Find the key to unlock the gated door. Pass through the door to win", sf::Vector2f(-3.8f, 2.4f), 24, sf::Color::White);
}

//! createEnvironment()
void Level::createEnvironment()
{
	// Just create a bunch of blocks
	m_gameObjects["StaticBlock1"] = new StaticBlock(m_world, sf::Vector2f(1.5f, 0.5f), sf::Vector2f(5, 1), 0.f, "ground");
	m_gameObjects["StaticBlock2"] = new StaticBlock(m_world, sf::Vector2f(-1.5f, 0.5f), sf::Vector2f(1, 1), 90.f, "ground-corner2");
	m_gameObjects["StaticBlock3"] = new StaticBlock(m_world, sf::Vector2f(-1.5f, -1.5f), sf::Vector2f(3, 1), 90.f, "ground");
	m_gameObjects["StaticBlock4"] = new StaticBlock(m_world, sf::Vector2f(-1.5f, -3.5f), sf::Vector2f(1, 1), 180.f, "ground-corner2");
	m_gameObjects["StaticBlock5"] = new StaticBlock(m_world, sf::Vector2f(3.f, -3.5f), sf::Vector2f(8, 1), 180.f, "ground");
	
	m_gameObjects["StaticBlock6"] = new StaticBlock(m_world, sf::Vector2f(4.5f, 0.5f), sf::Vector2f(1, 1), 90.f, "ground-corner");
	m_gameObjects["StaticBlock7"] = new StaticBlock(m_world, sf::Vector2f(4.5f, 1.5f), sf::Vector2f(1, 1), 90.f, "ground");
	m_gameObjects["StaticBlock8"] = new StaticBlock(m_world, sf::Vector2f(4.5f, 2.5f), sf::Vector2f(1, 1), 90.f, "ground-corner2");
	m_gameObjects["StaticBlock9"] = new StaticBlock(m_world, sf::Vector2f(7.f, 2.5f), sf::Vector2f(4, 1), 0.f, "ground");
	m_gameObjects["StaticBlock10"] = new StaticBlock(m_world, sf::Vector2f(9.5f, 0.5f), sf::Vector2f(1, 1), 0.f, "ground-corner");
	m_gameObjects["StaticBlock11"] = new StaticBlock(m_world, sf::Vector2f(9.5f, 1.5f), sf::Vector2f(1, 1), 270.f, "ground");
	m_gameObjects["StaticBlock12"] = new StaticBlock(m_world, sf::Vector2f(9.5f, 2.5f), sf::Vector2f(1, 1), 0.f, "ground-corner2");
	
	m_gameObjects["StaticBlock13"] = new StaticBlock(m_world, sf::Vector2f(14.f, 0.5f), sf::Vector2f(8, 1), 0.f, "ground");
	m_gameObjects["StaticBlock14"] = new StaticBlock(m_world, sf::Vector2f(7.5f, -4.5f), sf::Vector2f(1, 1), 90.f, "ground-corner");
	m_gameObjects["StaticBlock15"] = new StaticBlock(m_world, sf::Vector2f(7.5f, -3.5f), sf::Vector2f(1, 1), 180.f, "ground-corner");
	m_gameObjects["StaticBlock16"] = new StaticBlock(m_world, sf::Vector2f(3.f, -4.5f), sf::Vector2f(8, 1), 0.f, "ground");
	m_gameObjects["StaticBlock17"] = new StaticBlock(m_world, sf::Vector2f(-1.5f, -4.5f), sf::Vector2f(1, 1), 90.f, "ground-corner2");
	m_gameObjects["StaticBlock18"] = new StaticBlock(m_world, sf::Vector2f(-1.5f, -6.f), sf::Vector2f(2, 1), 90.f, "ground");
	m_gameObjects["StaticBlock19"] = new StaticBlock(m_world, sf::Vector2f(-1.5f, -7.f), sf::Vector2f(1, 1), 180.f, "ground-corner2");
	m_gameObjects["StaticBlock20"] = new StaticBlock(m_world, sf::Vector2f(4.f, -7.f), sf::Vector2f(10, 1), 180.f, "ground");
	m_gameObjects["StaticBlock21"] = new StaticBlock(m_world, sf::Vector2f(14.f, -7.f), sf::Vector2f(10, 1), 180.f, "ground");
	m_gameObjects["StaticBlock22"] = new StaticBlock(m_world, sf::Vector2f(24.f, -7.f), sf::Vector2f(10, 1), 180.f, "ground");

	m_gameObjects["StaticBlock23"] = new StaticBlock(m_world, sf::Vector2f(18.5f, 0.5f), sf::Vector2f(1, 1), 90.f, "ground-corner");
	m_gameObjects["StaticBlock24"] = new StaticBlock(m_world, sf::Vector2f(18.5f, 1.5f), sf::Vector2f(1, 1), 90.f, "ground");
	m_gameObjects["StaticBlock25"] = new StaticBlock(m_world, sf::Vector2f(18.5f, 2.5f), sf::Vector2f(1, 1), 90.f, "ground-corner2");
	m_gameObjects["StaticBlock26"] = new StaticBlock(m_world, sf::Vector2f(21.f, 2.5f), sf::Vector2f(4, 1), 0.f, "ground");
	m_gameObjects["StaticBlock27"] = new StaticBlock(m_world, sf::Vector2f(23.5f, 0.5f), sf::Vector2f(1, 1), 0.f, "ground-corner");
	m_gameObjects["StaticBlock28"] = new StaticBlock(m_world, sf::Vector2f(23.5f, 1.5f), sf::Vector2f(1, 1), 270.f, "ground");
	m_gameObjects["StaticBlock29"] = new StaticBlock(m_world, sf::Vector2f(23.5f, 2.5f), sf::Vector2f(1, 1), 0.f, "ground-corner2");
	m_gameObjects["StaticBlock30"] = new StaticBlock(m_world, sf::Vector2f(27.5f, 0.5f), sf::Vector2f(8, 1), 0.f, "ground");

	m_gameObjects["StaticBlock31"] = new StaticBlock(m_world, sf::Vector2f(32.f, 0.5f), sf::Vector2f(1, 1), 90.f, "ground-corner");
	m_gameObjects["StaticBlock32"] = new StaticBlock(m_world, sf::Vector2f(32.f, 1.5f), sf::Vector2f(1, 1), 90.f, "ground");
	m_gameObjects["StaticBlock33"] = new StaticBlock(m_world, sf::Vector2f(32.f, 2.5f), sf::Vector2f(1, 1), 90.f, "ground-corner2");
	m_gameObjects["StaticBlock34"] = new StaticBlock(m_world, sf::Vector2f(36.5f, 2.5f), sf::Vector2f(8, 1), 0.f, "ground");
	m_gameObjects["StaticBlock35"] = new StaticBlock(m_world, sf::Vector2f(41.f, 0.5f), sf::Vector2f(1, 1), 0.f, "ground-corner");
	m_gameObjects["StaticBlock36"] = new StaticBlock(m_world, sf::Vector2f(41.f, 1.5f), sf::Vector2f(1, 1), 270.f, "ground");
	m_gameObjects["StaticBlock37"] = new StaticBlock(m_world, sf::Vector2f(41.f, 2.5f), sf::Vector2f(1, 1), 0.f, "ground-corner2");
	m_gameObjects["StaticBlock38"] = new StaticBlock(m_world, sf::Vector2f(34.f, -7.f), sf::Vector2f(10, 1), 180.f, "ground");
	m_gameObjects["StaticBlock39"] = new StaticBlock(m_world, sf::Vector2f(41.5f, -7.f), sf::Vector2f(5, 1), 180.f, "ground");
	m_gameObjects["StaticBlock40"] = new StaticBlock(m_world, sf::Vector2f(45.5f, 0.5f), sf::Vector2f(8, 1), 0.f, "ground");

	m_gameObjects["StaticBlock41"] = new StaticBlock(m_world, sf::Vector2f(50.f, -7.f), sf::Vector2f(1, 1), 270.f, "ground-corner2");
	m_gameObjects["StaticBlock42"] = new StaticBlock(m_world, sf::Vector2f(50.f, -3.25f), sf::Vector2f(6.5, 1), 270.f, "ground");
	m_gameObjects["StaticBlock43"] = new StaticBlock(m_world, sf::Vector2f(50.f, 0.5f), sf::Vector2f(1, 1), 0.f, "ground-corner2");
	m_gameObjects["StaticBlock44"] = new StaticBlock(m_world, sf::Vector2f(48.5f, -7.f), sf::Vector2f(2, 1), 180.f, "ground");
	m_gameObjects["StaticBlock45"] = new StaticBlock(m_world, sf::Vector2f(44.5f, -7.f), sf::Vector2f(1, 1), 180.f, "ground-corner");
	m_gameObjects["StaticBlock46"] = new StaticBlock(m_world, sf::Vector2f(47.5f, -7.f), sf::Vector2f(1, 1), 270.f, "ground-corner");
	
	m_gameObjects["StaticBlock47"] = new StaticBlock(m_world, sf::Vector2f(44.5f, -12.f), sf::Vector2f(9, 1), 90.f, "ground");
	m_gameObjects["StaticBlock48"] = new StaticBlock(m_world, sf::Vector2f(47.5f, -10.f), sf::Vector2f(5, 1), 270.f, "ground");
	m_gameObjects["StaticBlock49"] = new StaticBlock(m_world, sf::Vector2f(47.5f, -13.f), sf::Vector2f(1, 1), 0.f, "ground-corner");
	m_gameObjects["StaticBlock50"] = new StaticBlock(m_world, sf::Vector2f(44.5f, -17.f), sf::Vector2f(1, 1), 180.f, "ground-corner2");
	m_gameObjects["StaticBlock51"] = new StaticBlock(m_world, sf::Vector2f(46.f, -17.f), sf::Vector2f(2, 1), 180.f, "ground");
	m_gameObjects["StaticBlock52"] = new StaticBlock(m_world, sf::Vector2f(47.5f, -17.f), sf::Vector2f(1, 1), 270.f, "ground-corner2");
	m_gameObjects["StaticBlock53"] = new StaticBlock(m_world, sf::Vector2f(47.5f, -16.f), sf::Vector2f(1, 1), 270.f, "ground-corner");

	m_gameObjects["StaticBlock54"] = new StaticBlock(m_world, sf::Vector2f(52.f, -16.f), sf::Vector2f(9, 1), 180.f, "ground");
	m_gameObjects["StaticBlock55"] = new StaticBlock(m_world, sf::Vector2f(50.5f, -13.f), sf::Vector2f(6, 1), 0.f, "ground");
	m_gameObjects["StaticBlock56"] = new StaticBlock(m_world, sf::Vector2f(54.f, -13.f), sf::Vector2f(1, 1), 90.f, "ground-corner");
	m_gameObjects["StaticBlock57"] = new StaticBlock(m_world, sf::Vector2f(57.f, -16.f), sf::Vector2f(1, 1), 270.f, "ground-corner2");
	m_gameObjects["StaticBlock58"] = new StaticBlock(m_world, sf::Vector2f(57.f, -12.5f), sf::Vector2f(6, 1), 270.f, "ground");

	m_gameObjects["StaticBlock59"] = new StaticBlock(m_world, sf::Vector2f(57.f, -9.f), sf::Vector2f(1, 1), 270.f, "ground-corner");
	m_gameObjects["StaticBlock60"] = new StaticBlock(m_world, sf::Vector2f(54.f, -9.5f), sf::Vector2f(6, 1), 90.f, "ground");
	m_gameObjects["StaticBlock61"] = new StaticBlock(m_world, sf::Vector2f(54.f, -6.f), sf::Vector2f(1, 1), 90.f, "ground-corner2");
	m_gameObjects["StaticBlock62"] = new StaticBlock(m_world, sf::Vector2f(59.f, -6.f), sf::Vector2f(9, 1), 0.f, "ground");
	m_gameObjects["StaticBlock63"] = new StaticBlock(m_world, sf::Vector2f(64.f, -6.f), sf::Vector2f(1, 1), 0.f, "ground-corner2");
	m_gameObjects["StaticBlock64"] = new StaticBlock(m_world, sf::Vector2f(64.f, -9.f), sf::Vector2f(1, 1), 270.f, "ground-corner2");
	m_gameObjects["StaticBlock65"] = new StaticBlock(m_world, sf::Vector2f(64.f, -7.5f), sf::Vector2f(2, 1), 270.f, "ground");
	m_gameObjects["StaticBlock66"] = new StaticBlock(m_world, sf::Vector2f(60.5f, -9.f), sf::Vector2f(6, 1), 180.f, "ground");

	m_gameObjects["StaticPlatform1"] = new StaticBlock(m_world, sf::Vector2f(14.f, -1.25f), sf::Vector2f(2, 0.5), 0.f, "platform");
	m_gameObjects["StaticPlatform2"] = new StaticBlock(m_world, sf::Vector2f(10.5f, -2.75f), sf::Vector2f(2, 0.5), 0.f, "platform");
	m_gameObjects["StaticPlatform3"] = new StaticBlock(m_world, sf::Vector2f(14.f, -4.f), sf::Vector2f(2, 0.5), 0.f, "platform");
	m_gameObjects["StaticPlatform4"] = new StaticBlock(m_world, sf::Vector2f(10.5f, -4.75f), sf::Vector2f(2, 0.5), 0.f, "platform");
	m_gameObjects["StaticPlatform5"] = new StaticBlock(m_world, sf::Vector2f(24.f, -4.75f), sf::Vector2f(3, 0.5), 0.f, "platform");
}

//! createGems()
void Level::createGems()
{
	// Create gems
	m_gameObjects["Gem1"] = new Gem(m_world, sf::Vector2f(0.f, -5.5f));
	m_gameObjects["Gem2"] = new Gem(m_world, sf::Vector2f(0.f, -6.f));
	m_gameObjects["Gem3"] = new Gem(m_world, sf::Vector2f(-0.7f, -5.5f));
	m_gameObjects["Gem4"] = new Gem(m_world, sf::Vector2f(-0.7f, -6.f));

	m_gameObjects["Gem5"] = new Gem(m_world, sf::Vector2f(14.f, -1.75f));
	m_gameObjects["Gem6"] = new Gem(m_world, sf::Vector2f(10.5f, -3.25f));
	m_gameObjects["Gem7"] = new Gem(m_world, sf::Vector2f(14.f, -4.5f));
	m_gameObjects["Gem8"] = new Gem(m_world, sf::Vector2f(10.5f, -5.25f));

	m_gameObjects["Gem9"] = new Gem(m_world, sf::Vector2f(21.f, -1.f));
	m_gameObjects["Gem10"] = new Gem(m_world, sf::Vector2f(19.f, -1.f));
	m_gameObjects["Gem11"] = new Gem(m_world, sf::Vector2f(23.f, -1.f));

	m_gameObjects["Gem12"] = new Gem(m_world, sf::Vector2f(45.2f, -11.45f));
	m_gameObjects["Gem13"] = new Gem(m_world, sf::Vector2f(45.2f, -9.45f));
	m_gameObjects["Gem14"] = new Gem(m_world, sf::Vector2f(45.2f, -7.45f));
}

/*!
\param draw a bool - Draw the physical components
*/
void Level::setPhysicsDraw(const bool draw)
{
	m_drawBodies = draw;
}

/*!
\return a bool - Whether to draw the physical components
*/
bool Level::getPhysicsDraw() const
{
	return m_drawBodies;
}

//! clearScene()
void Level::clearScene()
{
	//LOG("Clearing scene: " + m_name);
	// Delete all objects
	for (auto& g : m_gameObjects)
	{
		delete g.second;
	}
	m_gameObjects.clear();
	//LOG("Deleting physics world...");
	// If world exists, delete it
	if (m_world != nullptr)
	{
		delete m_world;
		m_world = nullptr;
	}
}

//! restartClocks()
void Level::restartClocks()
{
	// Restart animation clock
	m_animationClock.restart();
}

//! updateStatics()
void Level::updateStatics()
{
	// Disable drawing for any objects out of render view
	disableObjectRender();
	// Calculate the view's top left visible coordinate
	sf::Vector2f viewTopLeft = getSceneCentre() - (m_game->getWindow()->getGameView().getSize() * 0.5f);

	// Get the SFML shape of the HUD elements and set its position, this is done repeatedly to move HUD as player moves
	sf::RectangleShape* tmp = static_cast<sf::RectangleShape*>(m_gameObjects["Background"]->getDrawable());
	tmp->setPosition(viewTopLeft);

	tmp = static_cast<sf::RectangleShape*>(m_gameObjects["zPauseText"]->getDrawable());
	tmp->setPosition(viewTopLeft + sf::Vector2f(0.1f, 0.05f));

	tmp = static_cast<sf::RectangleShape*>(m_gameObjects["zGemIcon"]->getDrawable());
	tmp->setPosition(viewTopLeft + sf::Vector2f(0.5f, 0.15f));

	sf::Text* HUDInfotmp = static_cast<sf::Text*>(m_gameObjects["zHUDInfoText"]->getDrawable());
	HUDInfotmp->setPosition(viewTopLeft  + sf::Vector2f(0.8f, 0.25f));

	// Updates the lives and gems count
	HUDInfotmp->setString("x" + std::to_string(static_cast<Player*>(m_gameObjects["Player"])->getGemsCollected()) + "        " + "x" + std::to_string(static_cast<Player*>(m_gameObjects["Player"])->getLives()));

	tmp = static_cast<sf::RectangleShape*>(m_gameObjects["zLivesIcon"]->getDrawable());
	tmp->setPosition(viewTopLeft + sf::Vector2f(1.1f, 0.07f));

	tmp = static_cast<sf::RectangleShape*>(m_gameObjects["zKeyIcon"]->getDrawable());
	tmp->setPosition(viewTopLeft + sf::Vector2f(1.88f, 0.15f));

	tmp = static_cast<sf::RectangleShape*>(m_gameObjects["zIntro"]->getDrawable());
	tmp->setPosition(viewTopLeft + sf::Vector2f(0.2f, 5.6f));
}

/*!
\return a sf::Vector2f - The updated position of the view's centre (Player is centre frame)
*/
sf::Vector2f Level::getSceneCentre()
{
	// If the player doesn't exist
	if (m_gameObjects.find("Player") == m_gameObjects.end())
	{
		// Return as 0,0
		return sf::Vector2f(0.f, 0.f);
	}
	// Otherwise, get the player's position
	sf::RectangleShape* tmp = static_cast<sf::RectangleShape*>(m_gameObjects["Player"]->getDrawable());
	return tmp->getPosition();
}

//! disableObjectRender()
void Level::disableObjectRender()
{
	// Get the players position, we can piggy back off the getSceneCentre to get it
	sf::Vector2f playerPos = getSceneCentre();

	for (auto& g : m_gameObjects)
	{
		// Check for all objects if it's position is within 9 units
		sf::Vector2f tmp = static_cast<sf::RectangleShape*>(g.second->getDrawable())->getPosition();
		// Answer is squared because squareroot is expensive
		if (VectorDistance()(tmp, playerPos) > 90.f)
		{
			// Object is too far away, don't try drawing it
			g.second->setDraw(false);
		}
		else
		{
			g.second->setDraw(true);
		}
	}
}

/*!
\param timestep a const float& - The game update timestep
*/
void Level::update(const float& timestep)
{
	// If level isn't enabled, skip
	if (!m_enabled) { return; }

	// Advance the physics world
	m_world->Step(timestep, mk_iVelIterations, mk_iVelIterations);
	// Update all enabled objects
	updateObjects();
	// Update HUD
	updateStatics();
	// Destroy any scheduled for deletion objects
	destroyScheduledObjects();

	// Clear the physics draw if its enabled
	if (m_drawBodies) m_physicsDraw.clear();

	// Check if animation update needs to run
	float fElapsedTime = m_animationClock.getElapsedTime().asSeconds();
	if (fElapsedTime > mk_AnimationTime)
	{
		for (auto& g : m_gameObjects)
		{
			if (g.second->getAnimated())
			{
				// only if the object is animated
				g.second->animationUpdate();
			}
		}
		m_animationClock.restart();
	}
}

/*!
\param target a sf::RenderTarget & - A reference to the RenderTarget
\param states a sf::RenderStates - A render state
*/
void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// If we want to draw physics components, disable SFML object visuals
	if (m_drawBodies)
	{
		target.draw(m_physicsDraw);
	}
	else
	{
		// Draw all objects that need to be drawn
		for (auto& g : m_gameObjects)
		{
			if (g.second->getDraw())
			{
				target.draw(*g.second);
			}
		}
	}
}