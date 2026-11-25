#include "SnakeGame.h"
#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;


const int cellSize = 20;
const int columns = 40;
const int rows = 28;
const int maximumLength = columns * rows;

Point snake[1120];
int snakeLength = 3;
int directionX = 1;
int directionY = 0;
Point food;
Point poison;
Point shield;
int score = 0;
int highScore = 0;
bool gameOver = false;
bool gameOverScreenReady = false;
bool gameOverZoom = false;
Clock movementClock;
Clock shieldClock;//
Clock poisonSpawnClock;
Clock shieldSpawnClock;
Clock poisonLifeClock;
Clock shieldLifeClock;
Clock deathClock;
Clock gameOverZoomClock;
float poisonSpawnTime = 20;
float shieldSpawnTime = 25;
//instructions
Texture instructionsTexture;
Sprite instructionsBackground;
//instructions
//collectibles
Texture appleTexture;
Sprite appleSprite;
Texture poisonTexture;
Sprite poisonSprite;
Texture shieldTexture;
Sprite shieldSprite;
bool poisonPresent = false;
bool shieldPresent = false;
bool shieldActive = false;
float nextPoisonSpawn = 0;
float nextShieldSpawn = 0;

// sounds 

SoundBuffer appleSoundBuffer;
SoundBuffer poisonSoundBuffer;
SoundBuffer shieldSoundBuffer;
SoundBuffer deathSoundBuffer;
SoundBuffer transitionSoundBuffer;
Music backgroundMusic;

Sound appleSound;
Sound poisonSound;
Sound shieldSound;
Sound deathSound;
Sound transitionSound;
const float itemLifetime = 8.0f;
//skins
Texture snakeHeadTexture;
Texture snakeBodyTexture;
Texture skinMenuTexture;
Sprite skinMenuBackground;
//skins
//gameover screen
Texture gameOverTexture;
Sprite gameOverSprite;
//gameover screen
//maps
Texture backgroundTexture;
//maps
//mapmenu
Texture mapMenuTexture;
Sprite mapMenuBackground;
Texture grassPreviewTexture;
Texture desertPreviewTexture;
Texture retroPreviewTexture;
Sprite mapPreviewSprite;
int selectedMap = 0;
//mapmenu
void loadBackgroundMusic()
{
    if (!backgroundMusic.openFromFile("assets/gamemusic.mp3"))
    {
        cout << "Failed to load background music!" << endl;
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(30);
}
void backgroundMusicControl()
{
    if (!gameOver)
    {
        if (backgroundMusic.getStatus() != Music::Playing)
        {
            backgroundMusic.play();
        }
    }
    else
    {
        backgroundMusic.stop();
    }
}


void Death()
{
    if (!gameOver)
    {
        gameOver = true;

        deathClock.restart();

        gameOverZoom = false;
        backgroundMusic.stop();

        deathSound.play();

        checkHighScore();
    }
}
void loadGameOverSounds()
{
    if (!deathSoundBuffer.loadFromFile("assets/snakedeathb.mp3.mpeg"))
        cout << "Failed to load snake death sound!" << endl;

    if (!transitionSoundBuffer.loadFromFile("assets/gameover.mp3"))
        cout << "Failed to load Game Over transition sound!" << endl;

    deathSound.setBuffer(deathSoundBuffer);
    transitionSound.setBuffer(transitionSoundBuffer);
}

void loadInstructionsBackground()
{
    if (!instructionsTexture.loadFromFile("assets/Instructions.png"))
    {
        cout << "Failed to load Instructions image!" << endl;
    }
    else
    {
        instructionsBackground.setTexture(instructionsTexture);

        instructionsBackground.setScale(
            800.0f / instructionsTexture.getSize().x,
            600.0f / instructionsTexture.getSize().y
        );
    }
}
void drawInstructions(RenderWindow& window)
{
    window.clear();

    window.draw(instructionsBackground);

    window.display();
}
void loadCollectibles()
{
    if (!appleTexture.loadFromFile("assets/RedApple.png"))
    {
        cout << "Apple image failed to load!" << endl;
    }
    appleSprite.setTexture(appleTexture);
    
    if (!poisonTexture.loadFromFile("assets/PoisonApple.png"))
    {
        cout << "Poison apple image failed to load!" << endl;
    }
    poisonSprite.setTexture(poisonTexture);
    
    if (!shieldTexture.loadFromFile("assets/Shield.png"))
    {
        cout << "Shield image failed to load!" << endl;
    }
    shieldSprite.setTexture(shieldTexture);


    if (!appleSoundBuffer.loadFromFile("assets/eatingfood1.mp3"))
    cout << "Failed to load apple sound!" << endl;

    if (!poisonSoundBuffer.loadFromFile("assets/poison.wav"))
    cout << "Failed to load poison sound!" << endl;

if (!shieldSoundBuffer.loadFromFile("assets/shield.mp3"))
    cout << "Failed to load shield sound!" << endl;
    appleSound.setBuffer(appleSoundBuffer);
poisonSound.setBuffer(poisonSoundBuffer);
shieldSound.setBuffer(shieldSoundBuffer);

}
void loadMapMenuBackground()
{
    mapMenuTexture.loadFromFile("assets/mapmenu.png");

    mapMenuBackground.setTexture(mapMenuTexture);

    mapMenuBackground.setScale(
        800.0f / mapMenuTexture.getSize().x,
        600.0f / mapMenuTexture.getSize().y
    );
}
void loadMapPreviewImages()
{
    grassPreviewTexture.loadFromFile("assets/grassmap.png");

    desertPreviewTexture.loadFromFile("assets/desertmap.png");

    retroPreviewTexture.loadFromFile("assets/retromap.png");
}
void drawMapPreview(RenderWindow& window)
{
  window.clear();

    // Draw map selection background
    window.draw(mapMenuBackground);

    // Select the appropriate map image
    if (selectedMap == 0)
    {
        mapPreviewSprite.setTexture(grassPreviewTexture);
    }
    else if (selectedMap == 1)
    {
        mapPreviewSprite.setTexture(desertPreviewTexture);
    }
    else if (selectedMap == 2)
    {
        mapPreviewSprite.setTexture(retroPreviewTexture);
    }

    // Reset the sprite scale
    mapPreviewSprite.setScale(1.0f, 1.0f);

    // Get the original image dimensions
    float imageWidth = mapPreviewSprite.getTexture()->getSize().x;
    float imageHeight = mapPreviewSprite.getTexture()->getSize().y;

    // Preview box dimensions
    float previewWidth = 400;
    float previewHeight = 240;

    // Scale image to fit the preview box
    mapPreviewSprite.setScale(
        previewWidth / imageWidth,
        previewHeight / imageHeight
    );

    // Position the preview image
    mapPreviewSprite.setPosition(200, 177);

    // Draw the image
    window.draw(mapPreviewSprite);

    window.display();
}
void drawSkinPreview(RenderWindow& window)
{ window.clear();

    // Draw the skin menu background
    window.draw(skinMenuBackground);

    Sprite previewSnake;

    // Draw body segments
    previewSnake.setTexture(snakeBodyTexture);
    previewSnake.setScale(3.0f, 3.0f);

    previewSnake.setPosition(280, 270);
    window.draw(previewSnake);

    previewSnake.setPosition(340, 270);
    window.draw(previewSnake);

    previewSnake.setPosition(400, 270);
    window.draw(previewSnake);

    // Draw head
    previewSnake.setTexture(snakeHeadTexture);
    previewSnake.setScale(3.0f, 3.0f);
    previewSnake.setPosition(460, 270);
    window.draw(previewSnake);

    window.display();
}

void loadSkinMenuBackground()
{
    skinMenuTexture.loadFromFile("assets/skinmenu.png");

    skinMenuBackground.setTexture(skinMenuTexture);

    skinMenuBackground.setScale(
        800.0f / skinMenuTexture.getSize().x,
        600.0f / skinMenuTexture.getSize().y
    );
}

void loadGameOverImage(){
    if (!gameOverTexture.loadFromFile("assets/gameover.png")){
        cout << "Failed to load Game Over image" << endl;
    }
    else
    {
        gameOverSprite.setTexture(gameOverTexture);

        gameOverSprite.setScale(
            800.0f / gameOverTexture.getSize().x,
            600.0f / gameOverTexture.getSize().y
        );
    }
}
void drawGameOver(RenderWindow& window, Font& font)
{
    if (!gameOverZoom)
    {
        gameOverZoom = true;

        gameOverZoomClock.restart();

        transitionSound.play();
    }

    float elapsed = gameOverZoomClock.getElapsedTime().asSeconds();

    float duration = 0.7f;

    float progress = elapsed / duration;

    if (progress > 1.0f)
        progress = 1.0f;

    // Smooth easing
    float eased = 1.0f - (1.0f - progress) * (1.0f - progress);

    window.clear(Color::Black);

    if (progress < 1.0f)
    {
        float scale = 0.08f + 0.92f * eased;

        gameOverSprite.setScale(
            (800.0f / gameOverTexture.getSize().x) * scale,
            (600.0f / gameOverTexture.getSize().y) * scale
        );

        gameOverSprite.setPosition(
            400.0f - gameOverTexture.getSize().x * gameOverSprite.getScale().x / 2.0f,
            300.0f - gameOverTexture.getSize().y * gameOverSprite.getScale().y / 2.0f
        );
    }
    else
    {
        gameOverSprite.setScale(
            800.0f / gameOverTexture.getSize().x,
            600.0f / gameOverTexture.getSize().y
        );

        gameOverSprite.setPosition(0, 0);
    }

    window.draw(gameOverSprite);

    if (progress >= 1.0f)
    {
        Text scoreText;

        scoreText.setFont(font);
        scoreText.setString(to_string(score));
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(480, 218);

        window.draw(scoreText);

        Text highScoreText;

        highScoreText.setFont(font);
        highScoreText.setString(to_string(highScore));
        highScoreText.setCharacterSize(30);
        highScoreText.setFillColor(Color::White);
        highScoreText.setPosition(507, 276);

        window.draw(highScoreText);
    }

    window.display();
}
bool isGameOver()
{
    return gameOver &&
           deathClock.getElapsedTime().asSeconds() >= 1.5f;
}
//
int selectedSkin = 0;
void setSelectedSkin(int skin) {
    selectedSkin = skin;
}

void setSelectedMap(int map)
{
    selectedMap = map;
}

void loadSnakeTextures() {   
    if (selectedSkin == 0)
    {
        snakeHeadTexture.loadFromFile("assets/head.png");
        snakeBodyTexture.loadFromFile("assets/body.png");
    }
    else if (selectedSkin == 1)
    {
        snakeHeadTexture.loadFromFile("assets/orangehead.png");
        snakeBodyTexture.loadFromFile("assets/orangebody.png");
    }
    else if (selectedSkin == 2)
    {
        snakeHeadTexture.loadFromFile("assets/bluesnakehead.png");
        snakeBodyTexture.loadFromFile("assets/bluesnakebody.png");
    }
    else if (selectedSkin == 3)
    {
        snakeHeadTexture.loadFromFile("assets/pinksnakehead.png");
        snakeBodyTexture.loadFromFile("assets/pinksnakebody.png");
    }
    if (selectedMap == 0)
    {
    backgroundTexture.loadFromFile("assets/grass.jpeg");
    }
    else if (selectedMap == 1)
    {
    backgroundTexture.loadFromFile("assets/desert.jpeg");
    }
    else if (selectedMap == 2)
    {
    backgroundTexture.loadFromFile("assets/retro.jpeg");
    }
}
void loadHighScore()
{
    ifstream scoreFile;

    scoreFile.open("highscore.txt");

    if (!scoreFile)
    {
        highScore = 0;
    }
    else
    {
        scoreFile >> highScore;

        scoreFile.close();
    }
}

void saveHighScore()
{
    ofstream scoreFile;

    scoreFile.open("highscore.txt");

    if (!scoreFile)
    {
        cout << "File cannot be opened" << endl;
    }
    else
    {
        scoreFile << highScore;

        scoreFile.close();
    }
}

void checkHighScore()
{
    if (score > highScore)
    {
        highScore = score;

        saveHighScore();
    }
}

bool isOnSnake(int x, int y) {
    for (int i = 0; i < snakeLength; i++) {
        if (snake[i].x == x && snake[i].y == y)
            return true;
    }
    return false;
}

void placeFood() {
    // Choose a random square until it is not occupied by the snake.
    do {
        food.x = rand() % columns;
        food.y = rand() % rows;
    } while (isOnSnake(food.x, food.y));
}
void placePoison()
{
    do
    {
        poison.x = rand() % columns;
        poison.y = rand() % rows;
    }
    while (isOnSnake(poison.x, poison.y) ||
           (poison.x == food.x && poison.y == food.y) ||
           (shieldPresent && poison.x == shield.x && poison.y == shield.y));

    poisonPresent = true;
    poisonLifeClock.restart();
}

void placeShield()
{
    do
    {
        shield.x = rand() % columns;
        shield.y = rand() % rows;
    }
    while (isOnSnake(shield.x, shield.y) ||
           (shield.x == food.x && shield.y == food.y) ||
           (poisonPresent && shield.x == poison.x && shield.y == poison.y));

    shieldPresent = true;
     shieldLifeClock.restart();
}
void setRandomSpawnTimes()
{
    nextPoisonSpawn = 15 + rand() % 11;
    nextShieldSpawn = 20 + rand() % 11;
}

void resetGame() {
    snakeLength = 3;
    snake[0].x = 20;
    snake[0].y = 14;
    snake[1].x = 19;
    snake[1].y = 14;
    snake[2].x = 18;
    snake[2].y = 14;

    directionX = 1;
    directionY = 0;
    score = 0;
    loadHighScore();
    gameOver = false;
    poisonPresent = false;
    shieldPresent = false;
    shieldActive = false;
    gameOverZoom = false;
    placeFood();
    setRandomSpawnTimes();

    poisonSpawnClock.restart();
    shieldSpawnClock.restart();
    movementClock.restart();
    shieldClock.restart();

poisonLifeClock.restart();
shieldLifeClock.restart();
}

void handleGameInput(Event event) {
    if (event.type != Event::KeyPressed)
        return;

    if (gameOver) {
        if (event.key.code == Keyboard::R)
            resetGame();
        return;
    }

    // These checks stop the snake from turning straight backwards.
    if (event.key.code == Keyboard::Up && directionY != 1) {
        directionX = 0;
        directionY = -1;
    } else if (event.key.code == Keyboard::Down && directionY != -1) {
        directionX = 0;
        directionY = 1;
    } else if (event.key.code == Keyboard::Left && directionX != 1) {
        directionX = -1;
        directionY = 0;
    } else if (event.key.code == Keyboard::Right && directionX != -1) {
        directionX = 1;
        directionY = 0;
    }
}

void moveSnake() {
    Point newHead;
    newHead.x = snake[0].x + directionX;
    newHead.y = snake[0].y + directionY;

 //Wall collision
   if (newHead.x < 0 || newHead.x >= columns ||
    newHead.y < 0 || newHead.y >= rows)
{
    if (shieldActive)
    {
        // Wrap the snake to the opposite side
        if (newHead.x < 0)
            newHead.x = columns - 1;

        else if (newHead.x >= columns)
            newHead.x = 0;

        if (newHead.y < 0)
            newHead.y = rows - 1;

        else if (newHead.y >= rows)
            newHead.y = 0;
    }
    else
    {
        Death();
        return;
    }
}
    bool ateFood = false;
    if (newHead.x == food.x && newHead.y == food.y)
        ateFood = true;

    // If food is not eaten, the tail moves away on this turn.
    int lastPartToCheck = snakeLength - 1;
    if (ateFood)
        lastPartToCheck = snakeLength;

    // Check whether the new head would touch the snake's body.
   // Check self-collision
for (int i = 0; i < lastPartToCheck; i++)
{
    if (newHead.x == snake[i].x &&
        newHead.y == snake[i].y)
    {
        if (!shieldActive)
        {
            Death();
            return;
        }
    }
}

    if (ateFood && snakeLength < maximumLength)
{
    snakeLength = snakeLength + 1;
    score = score + 10;
    appleSound.play();
   
}
    // Move the body from the last square towards the head.
    for (int i = snakeLength - 1; i > 0; i--)
        snake[i] = snake[i - 1];

    snake[0] = newHead;

    if (poisonPresent &&
    newHead.x == poison.x &&
    newHead.y == poison.y)
{

     poisonSound.play();

    Death();
    return;
}

// Check if the snake eats the shield
if (shieldPresent &&
    newHead.x == shield.x &&
    newHead.y == shield.y)
{
    shieldSound.play();

    shieldActive = true;
    shieldClock.restart();
    shieldPresent = false;
}

    if (ateFood) {
        if (snakeLength == maximumLength)
           Death();
        else
            placeFood();
    }
}
float getMovementInterval() {
    float interval = 0.12f - (snakeLength - 3) * 0.004f;
    if (interval < 0.045f){interval = 0.045f;}
    return interval;}
void updateGame()
{
    if (gameOver)
        return;

    // Turn off shield after 6 seconds
    if (shieldActive &&
        shieldClock.getElapsedTime().asSeconds() >= 6)
    {
        shieldActive = false;
    }

    // Spawn poison after its random timer
    if (!poisonPresent &&
        poisonSpawnClock.getElapsedTime().asSeconds() >= nextPoisonSpawn)
    {
        placePoison();
        poisonSpawnClock.restart();
        nextPoisonSpawn = 15 + rand() % 11;
    }

    // Spawn shield after its random timer
    if (!shieldPresent &&
        shieldSpawnClock.getElapsedTime().asSeconds() >= nextShieldSpawn)
    {
        placeShield();
        shieldSpawnClock.restart();
        nextShieldSpawn = 20 + rand() % 11;
    }

    // Remove poison after 8 seconds
    if (poisonPresent &&
        poisonLifeClock.getElapsedTime().asSeconds() >= itemLifetime)
    {
        poisonPresent = false;
    }

    // Remove shield after 8 seconds
    if (shieldPresent &&
        shieldLifeClock.getElapsedTime().asSeconds() >= itemLifetime)
    {
        shieldPresent = false;
    }

    // Move snake
    if (movementClock.getElapsedTime().asSeconds() >= getMovementInterval())
    {
        moveSnake();
        movementClock.restart();
    }
}
void drawGame(RenderWindow& window, Font& font) {
    window.clear();
    Sprite background;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 40);
    background.setScale(800.0f/backgroundTexture.getSize().x, 560.0f/backgroundTexture.getSize().y);
    window.draw(background); 
    //Drawing boundary
    RectangleShape boundary;
    boundary.setSize(Vector2f(columns * cellSize, rows * cellSize));
    boundary.setPosition(0, 40);
    boundary.setFillColor(Color::Transparent);
    boundary.setOutlineColor(Color::Red);
    boundary.setOutlineThickness(2);
    window.draw(boundary); 

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(
    "Score: " + to_string(score) + "    High Score: " + to_string(highScore));
    scoreText.setCharacterSize(22);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 8);
    window.draw(scoreText);
    if (shieldActive)
{
    Text shieldText;

    shieldText.setFont(font);

    int remainingShieldTime =
        6 - (int)shieldClock.getElapsedTime().asSeconds();

    if (remainingShieldTime < 0)
        remainingShieldTime = 0;

    shieldText.setString("Shield: " + to_string(remainingShieldTime) + "s");

    shieldText.setCharacterSize(22);
    shieldText.setFillColor(Color::Cyan);
    shieldText.setPosition(620, 8);

    window.draw(shieldText);
}

    //Adding sprites
    Sprite snakeSprite;
   for (int i = 0; i < snakeLength; i++)
{
    if (i == 0)
    {
        snakeSprite.setTexture(snakeHeadTexture);

        // Blink the head during death
        if (gameOver &&
            (int)(deathClock.getElapsedTime().asSeconds() * 6) % 2 == 0)
        {
            continue;
        }
    }
    else
    {
        snakeSprite.setTexture(snakeBodyTexture);
    }

    snakeSprite.setPosition(
        snake[i].x * cellSize,
        snake[i].y * cellSize + 40
    );

    window.draw(snakeSprite);
}
   if (poisonPresent)
{
    poisonSprite.setPosition(
        poison.x * cellSize,
        poison.y * cellSize + 40
    );

    float remainingTime =
        itemLifetime - poisonLifeClock.getElapsedTime().asSeconds();

    if (remainingTime > 3 || (int)(remainingTime * 5) % 2 == 0)
    {
        window.draw(poisonSprite);
    }
}
    if (shieldPresent)
{
    shieldSprite.setPosition(
        shield.x * cellSize,
        shield.y * cellSize + 40
    );

    float remainingTime =
        itemLifetime - shieldLifeClock.getElapsedTime().asSeconds();

    if (remainingTime > 3 || (int)(remainingTime * 5) % 2 == 0)
    {
        window.draw(shieldSprite);
    }
}


    
    appleSprite.setPosition(food.x * cellSize, food.y * cellSize+40);
    window.draw(appleSprite);

    window.display();
}
