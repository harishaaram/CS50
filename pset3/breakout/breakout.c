//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// 

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    double velocity_y = 2.0;
    double velocity_x = drand48() * 10;
    while (lives > 0 && bricks > 0 && points < 50)
    {
        GEvent event = getNextEvent (MOUSE_EVENT);

        // paddle movement
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = (getX(event));
                double y = (4 * HEIGHT/5);
                setLocation(paddle, x, y);
            }
        }
        
        // move ball
        move(ball, velocity_x, velocity_y);

        // bounce off right and left edge of window
        if ((getX(ball) + getWidth(ball) >= WIDTH) || (getX(ball) <= 0) )
        {
            velocity_x = -velocity_x;
        }

        // ball touches bottom edge of window
        else if (getY(ball) + getWidth(ball) >= HEIGHT)
        {
            removeGWindow(window, ball);
            lives--;
            pause(500);
            if(lives != 0)
                ball = initBall(window);
            

        }
        // ball touches top edge of window
        else if (getY(ball) <= 0 )
        {
            velocity_y = -velocity_y;
        }


        // linger before moving again
        pause(10);
        GObject object = detectCollision(window, ball);
        if(object != NULL)
        {
            if (object == paddle) 
            velocity_y = -velocity_y;

            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                velocity_y = -velocity_y;
                points = points + 1;
                updateScoreboard(window, label, points);

            }
        }
        
        }

    // wait for click before exiting
    waitForClick();
    setLabel(label, "Game Over");
    pause(1000);
    
    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int y,b;
    b = (WIDTH - (COLS +1) * 10)/COLS;
    for(int i=1; i <= ROWS; i++)
    {
        y = -10 + i * HEIGHT/(5 * ROWS);
        for(int j = 1;j <= COLS; j++)
        {
            GRect brick = newGRect(10 * j + (j-1) * b, y, b, 10);
            setFilled(brick, true);
            setColor(brick, "red");
            add(window, brick);
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2, HEIGHT/2, 20, 20);
    setFilled(ball, true);
    setColor(ball, "black");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // * paddle 
    GRect Paddle =  newGRect(-50 + WIDTH/2, 4 * HEIGHT/5, 100, 10);
    setFilled(Paddle, true);
    setColor(Paddle, "blue");
    add(window, Paddle);
    return Paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("label");
    setFont(label, "SansSerif-36");
    add(window, label);

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
