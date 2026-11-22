#include "SnakeGame.h"
#include <cstdlib>
#include <string>
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
int score = 0;
int highScore = 0;
bool gameOver = false;
Clock movementClock;
Texture backgroundTexture;

if (!backgroundTexture.loadFromFile("assets/cleargrass.jpeg"))
        cout << "Background image could not be loaded." << endl;
Texture gameOverTexture;
Sprite gameOverSprite;
void loadGameOverImage()
{if (!gameOverTexture.loadFromFile("assets/gameover.png"))
    { cout << "Failed to load Game Over image" << endl;}
    else
    {gameOverSprite.setTexture(gameOverTexture);
      gameOverSprite.setScale(
            800.0f / gameOverTexture.getSize().x,
            600.0f / gameOverTexture.getSize().y);
    }
}
void drawGameOver(RenderWindow& window, Font& font)
{
    window.clear();
    // Draw the Game Over image
    window.draw(gameOverSprite);
    // Display the score
Text scoreText;
scoreText.setFont(font);
scoreText.setString(to_string(score));
scoreText.setCharacterSize(30);
scoreText.setFillColor(Color::White);
scoreText.setPosition(495, 215);
        
    window.draw(scoreText);
// Display the high score
Text highScoreText;
highScoreText.setFont(font);
highScoreText.setString(to_string(highScore));
highScoreText.setCharacterSize(30);
highScoreText.setFillColor(Color::White);
highScoreText.setPosition(510, 275);

    window.draw(highScoreText);
    window.display();
}

bool isGameOver()
{
    return gameOver;
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
            return true;}
    return false;}
void placeFood() {
    // Choose a random square until it is not occupied by the snake.
    do {
        food.x = rand() % columns;
        food.y = rand() % rows;
    } while (isOnSnake(food.x, food.y));
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
    gameOver = false;
    placeFood();
    movementClock.restart();
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

    // Check whether the new head would go outside the board.
    if (newHead.x < 0 || newHead.x >= columns ||
        newHead.y < 0 || newHead.y >= rows) {
        gameOver = true;
        return;
    }

    bool ateFood = false;
    if (newHead.x == food.x && newHead.y == food.y)
        ateFood = true;

    // If food is not eaten, the tail moves away on this turn.
    int lastPartToCheck = snakeLength - 1;
    if (ateFood)
        lastPartToCheck = snakeLength;

    // Check whether the new head would touch the snake's body.
    for (int i = 0; i < lastPartToCheck; i++) {
        if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
            gameOver = true;
            return;
        }
    }

    if (ateFood && snakeLength < maximumLength) {
        snakeLength = snakeLength + 1;
        score = score + 10;
    }

    // Move the body from the last square towards the head.
    for (int i = snakeLength - 1; i > 0; i--)
        snake[i] = snake[i - 1];

    snake[0] = newHead;

    if (ateFood) {
        if (snakeLength == maximumLength)
            gameOver = true;
        else
            placeFood();
    }
}

float getMovementInterval() {
    float interval = 0.12f - (snakeLength - 3) * 0.004f;
    if (interval < 0.045f){interval = 0.045f;}
    return interval;}

void updateGame() {
    if (gameOver == true){return;}      
    if (movementClock.getElapsedTime().asSeconds() >= getMovementInterval())
    {
        moveSnake();
        movementClock.restart();
    }
}

void drawGame(RenderWindow& window, Font& font) {
    window.clear(Color(20, 20, 25));

    Sprite background;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 40);
    background.setScale(800.0f/backgroundTexture.getSize().x, 560.0f/backgroundTexture.getSize().y);
    window.draw(background);

//Drawing  the  boundary
    RectangleShape boundary;
    boundary.setSize(Vector2f(columns*cellSize, rows*cellSize));
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

    // Vector2f is an SFML shape-size type, not the C++ vector container.
    RectangleShape snakeBlock(Vector2f(cellSize - 1, cellSize - 1));

    for (int i = 0; i < snakeLength; i++) {
        snakeBlock.setPosition(snake[i].x * cellSize, snake[i].y * cellSize + 40);
        if (i == 0)
            snakeBlock.setFillColor(Color::Green);
        else
            snakeBlock.setFillColor(Color(80, 200, 100));
        window.draw(snakeBlock);
    }

    RectangleShape foodBlock(Vector2f(cellSize - 1, cellSize - 1));
    foodBlock.setPosition(food.x * cellSize, food.y * cellSize + 40);
    foodBlock.setFillColor(Color::Red);
    window.draw(foodBlock);

    window.display();
}
