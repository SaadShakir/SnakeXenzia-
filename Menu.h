#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

// Numbers returned to main.cpp for the selected menu option.
const int MENU_NOTHING = 0;
const int MENU_PLAY = 1;
const int MENU_SKINS = 2;
const int MENU_MAPS = 3;
const int MENU_INSTRUCTIONS = 4;
const int MENU_EXIT = 5;

int handleMenuInput(Event event, RenderWindow& window);//adjscreen
void drawMenu(RenderWindow& window, Font& font);
int handleSkinInput(Event event);
void drawSkinMenu(RenderWindow& window, Font& font);
int handleMapInput(Event event);
void drawMapMenu(RenderWindow& window, Font& font);
void loadMenuImage();
void loadMenuSounds();
extern Sound escapeSound;
extern SoundBuffer escapeSoundBuffer;
extern  SoundBuffer restartSoundBuffer;
extern Sound restartSound;
extern Sound playSound;
