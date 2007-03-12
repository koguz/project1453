#ifndef SDLFONT__H
#define SDLFONT__H

#include <iostream>
#include <string>
#include "Headers.h"

using namespace std;

/** \brief Temporary class for handling fonts
 * 
 * This class handles fonts... It will be replaced 
 * by a more advanced class soon. Simply this class generates
 * a surface with the given string. 
 * 
 * As a result, this class is not well documented...
 * \author Kaya Oguz
 * \date 2007.02
 */
class SDLFont
{
	public:
	/**
	 * Constructor for creating a SDL_Surface with 
	 * given parameters
	 * \param str is the string to be created
	 * \param size is the size of the font
	 * \param color is the color of the font
	 */
	SDLFont(string str, int size, SDL_Color color);
	
	/// \return The surface created with the string given
	SDL_Surface* getString() { return s; }
	
	/// \return returns the width of the surface
	int getWidth() { return w; }
	
	/// \return returns the height of the surface
	int getHeight() { return h; }
	
	/// draws the font on surface
	/// \param screen is the pointer to the main screen surface
	/// \param x is the x-coordinate to be drawn
	/// \param y is the y-coordinate to be drawn
	void drawMe(SDL_Surface* screen, int x, int y);
	
	static TTF_Font* font;
	
	private:
	int w; 
	int h;
	SDL_Surface *s;
	
};


#endif

