#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

// A Point stores the position of one square on the game board.
struct Point {
    int x;
    int y;
};

void resetGame();
void handleGameInput(Event event);
void updateGame();
void drawGame(RenderWindow& window, Font& font);
void loadHighScore();
void saveHighScore();
void checkHighScore();
void loadSnakeTextures();
void setSelectedSkin(int skin);
void loadGameOverImage();
void drawGameOver(RenderWindow& window, Font& font);
bool isGameOver();
void setSelectedMap(int map);
void loadSkinMenuBackground();
void drawSkinPreview(RenderWindow& window);
void loadMapMenuBackground();
void loadMapPreviewImages();
void drawMapPreview(RenderWindow& window);
void loadCollectibles();//
void loadInstructionsBackground();
void drawInstructions(RenderWindow& window);
void placePoison();
void placeShield();
void loadGameOverSounds();
void Death();
void loadBackgroundMusic();
void backgroundMusicControl();
extern Music backgroundMusic;
