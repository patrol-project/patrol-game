#pragma once

#include <string>

using namespace std; 

/**
 * @brief Instead of changing all GameObject classes when a parameter changes
 * we use LoaderParams so that we change the parameters here only. And it is easier to 
 * read and maintain
 * 
 */
class LoaderParams
{
public:
	/**
	 * @brief 
	 * 
	 * @param x position on the screen corresponding to the X axis 
	 * @param y position on the screen corresponding to the Y axis
	 * @param width width of the object
	 * @param height height of the object
	 * @param textureID  the ID of the texture(picture) to 
	 */
	LoaderParams(int x, int y, int width, int height, string textureID) : 
		xpos(x), ypos(y), 
		m_width(width), 
		m_height(height), 
		m_textureID(textureID)
	{
	}

	/**
	 * @brief Returns the x position on the screen
	 * 
	 * @return int getX 
	 */
	int getX() const{ return xpos; }

	/**
	 * @brief Returns the y position on the screen
	 * 
	 * @return int getY 
	 */
	int getY() const { return ypos; }

	/**
	 * @brief Return the width of the game object
	 * 
	 * @return int getWidth 
	 */
	int getWidth() const { return m_width; }

	/**
	 * @brief Returns the height of the game object
	 * 
	 * @return int getHeight 
	 */
	int getHeight() const { return m_height; }

	/**
	 * @brief Returns the texture ID of the game object
	 * 
	 * @return string getTextureID 
	 */
	string getTextureID() const { return m_textureID; }
private:
	int xpos;
	int ypos;
	int m_width;
	int m_height;
	string m_textureID;
};
