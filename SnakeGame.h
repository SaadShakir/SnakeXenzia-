#include <SFML/Graphics.hpp>
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
void loadGameOverImage();
void drawGameOver(RenderWindow& window, Font& font);
bool isGameOver();
void loadAppleTexture();
void loadInstructionsBackground();
void drawInstructions(RenderWindow& window);
void loadHighScore();
void saveHighScore();
void checkHighScore();
void loadSnakeTextures();
void setSelectedSkin(int skin);
void loadSkinMenuBackground();
void drawSkinPreview(RenderWindow& window);
