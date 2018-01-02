#pragma once

#include <string>

using namespace std; 

// easier to change in one place the parameters we pass
// in game objects instead of changing all classes 

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, string textureID) : 
		xpos(x), ypos(y), 
		m_width(width), 
		m_height(height), 
		m_textureID(textureID)
	{
	}

	int getX() const{ return xpos; }
	int getY() const { return ypos; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	string getTextureID() const { return m_textureID; }
private:
	int xpos;
	int ypos;
	int m_width;
	int m_height;
	string m_textureID;
};
