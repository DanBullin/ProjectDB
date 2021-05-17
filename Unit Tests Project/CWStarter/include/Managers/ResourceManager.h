#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#define LOG(x) std::cout << x << std::endl;

/*! \file ResourceManager.h
* \brief Header file for ResourceManager
*
* Implementation for a ResourceManager
*/

/*! \class ResourceManager
\brief A ResourceManager
*/

/*! A ResourceManager Class */
class ResourceManager {
private:
	ResourceManager(); //!< Constructor
	static bool m_InstanceFlag; //!< Static flag tracking if an instance has been created
	static ResourceManager* m_resManager; //!< Pointer to the resource manager
	const std::string mk_resourceDirectory = "assets/"; //!< The assets directory from the working directory
	std::ifstream infile; //!< FileIO to read/write to files
	std::map<std::string, sf::Texture*> m_textures; //!< Map containing texture pointers with a string name mapped to each
	std::map<std::string, sf::Font*> m_fonts; //!< Map containing font pointers with a string name mapped to each
	bool addTexture(const std::string key, const std::string fileName); //!< Add a texture with the key and fileName passed
	bool addFont(const std::string key, const std::string fileName); //!< Add a font with the key and fileName passed
	void loadTextures(); //!< Load all textures
	void loadFonts(); //!< Load all fonts
public:
	~ResourceManager(); //!< Destructor
	ResourceManager(const ResourceManager&) = delete; // Delete the copy
	static ResourceManager* getInstance(); //!< Returns a pointer to the single resource manager

	sf::Texture* getTexture(const std::string name) const; //!< Get the texture with named name
	sf::Font* getFont(const std::string name) const; //!< Get the font with named name
	void loadAllAssets(); //!< Load all assets
};
#endif