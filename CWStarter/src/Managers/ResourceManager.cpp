#include "Managers/ResourceManager.h"

/*! \file ResourceManager.cpp
* \brief CPP file for ResourceManager
*
* Implementation for a ResourceManager
*
*/

// Initial values
bool ResourceManager::m_InstanceFlag = false;
ResourceManager* ResourceManager::m_resManager = nullptr;

//! Constructor()
ResourceManager::ResourceManager()
{

}

/*!
\return a ResourceManager* - A pointer to the resource manager instance
*/
ResourceManager* ResourceManager::getInstance()
{
	if (!m_InstanceFlag)
	{
		// If an instance hasn't been created, create one
		m_resManager = new ResourceManager();
		// Prevent making more
		m_InstanceFlag = true;
		return m_resManager;
	}
	return m_resManager;
}

//! Destructor()
ResourceManager::~ResourceManager()
{
	// Set all relevant pointers to null
	m_InstanceFlag = false;
	delete m_resManager;
	m_resManager = nullptr;
	// Delete all textures & fonts
	for (auto pair : m_textures) { delete pair.second; }
	for (auto pair : m_fonts) { delete pair.second; }
}

/*!
\param key a const std::string - The name of the texture
\param fileName a const std::string - The file path of the texture from the base asset directory
\return a bool - Was the texture added successfully
*/
bool ResourceManager::addTexture(const std::string key, const std::string fileName)
{
	// If the key already exists, return false
	if (m_textures.find(key) != m_textures.end()) { return false; }

	// Create texture and set it as repeated
	sf::Texture tmp;
	tmp.setRepeated(true);

	if (!tmp.loadFromFile(mk_resourceDirectory + fileName))
	{
		// If it couldn't load texture, return and send error message
		LOG("Couldn't load the texture from file: " + fileName);
		return false;
	}
	// Add texture
	m_textures[key] = new sf::Texture(tmp);
	return true;
}

/*!
\param key a const std::string - The name of the font
\param fileName a const std::string - The file path of the font from the base asset directory
\return a bool - Was the font added successfully
*/
bool ResourceManager::addFont(const std::string key, const std::string fileName)
{
	// If the key already exists, return false
	if (m_fonts.find(key) != m_fonts.end()) { return false; }

	// Create the font and load
	sf::Font tmp;
	if (!tmp.loadFromFile(mk_resourceDirectory + fileName))
	{
		// If it couldn't load font, return and send error message
		LOG("Couldn't load the font from file: " + fileName);
		return false;
	}
	// Add font
	m_fonts[key] = new sf::Font(tmp);
	return true;
}

/*!
\param name a const std::string - The name of the texture
\return a sf::Texture* - A pointer to the texture
*/
sf::Texture* ResourceManager::getTexture(const std::string name) const
{
	auto it = m_textures.find(name);
	// If it finds the texture, return it
	if (it != m_textures.end()) { return it->second; }
	return nullptr;
}

/*!
\param name a const std::string - The name of the font
\return a sf::Font* - A pointer to the font
*/
sf::Font* ResourceManager::getFont(const std::string name) const
{
	auto it = m_fonts.find(name);
	// If it finds the font, return it
	if (it != m_fonts.end()) { return it->second; }
	return nullptr;
}

//! loadAllAssets()
void ResourceManager::loadAllAssets()
{
	loadTextures();
	loadFonts();
}

//! loadTextures()
void ResourceManager::loadTextures()
{
	// Open up the texture list file
	std::ifstream stream(mk_resourceDirectory + "loadTextures.txt");
	std::string line;
	std::vector<std::string> textureFileNames;
	while (std::getline(stream, line))
	{
		// Go through each line and add the text to the vector of names
		textureFileNames.push_back(line);
	}
	// For all names, add the texture using the name as the filepath
	for (auto t : textureFileNames)
	{
		addTexture(t, "Textures/" + t + ".png");
	}
}

//! loadFonts()
void ResourceManager::loadFonts()
{
	// Open up the font list file
	std::ifstream stream(mk_resourceDirectory + "loadFonts.txt");
	std::string line;
	std::vector<std::string> fontFileNames;
	while (std::getline(stream, line))
	{
		// Go through each line and add the text to the vector of names
		fontFileNames.push_back(line);
	}
	// For all names, add the font using the name as the filepath
	for (auto f : fontFileNames)
	{
		addFont(f, "Fonts/" + f + ".ttf");
	}
}