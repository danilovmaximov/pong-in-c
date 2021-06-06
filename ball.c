/*******************************************************************
  Game of pong in C for MZ_APO.

  start.c  - main script
  state_controller  - handling states' update and render, handling transitions between the states
  text_utils.c  - supporting methods for the work with text.
  periphery_utils.c  - supporting methods for the work with periphery.
  menu.c  - rendering and handling the menu.
  countdown.c  - countdown before the logic and render.
  game.c  - game proccess.
  pads.c  - the game's pads logic and render.
  ball.c  - the game's ball logic and render.
  game_end.c  - rendering game's end screen, it's logic.

  (C) Copyright 2021 by Danil Maksimov
  e-mail: maksidan@fel.cvut.cz
  license: any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "ball.h"

int ball_x_pos = BALL_INIT_X;
int ball_y_pos = BALL_INIT_Y;
int ball_speed = BALL_MOVE_SPEED;
int ball_x_velocity = 1, ball_y_velocity = 1;
bool out_of_bounds = false;

/*
 *  Method for rendering the ball in the game.
 */
void render_ball()
{
    fill_rect
    (
        ball_x_pos, ball_y_pos, 
        BALL_SIZE, BALL_SIZE, WHITE
    );
}

/*
 *  Method for resetting the ball after a goal.
 */
void reset_ball()
{
    ball_x_pos = BALL_INIT_X;
    ball_y_pos = BALL_INIT_Y;
    ball_speed = BALL_MOVE_SPEED;
    ball_x_velocity = 1, ball_y_velocity = 1;
    out_of_bounds = false;
}

/*
 *  Method for checking if a collistion occured and handling it.
 */
int handle_collision()
{
    // Initial values
    int result = NO_COLLISTION;
    int x_check = 0, y_check = 0;

    for (int i = 0; i < ball_speed; i++)
    {
        // Set upfront distance to check for collisions
        if (ball_x_velocity == 1) x_check = ball_x_pos + BALL_SIZE + i;
        else x_check = ball_x_pos - i;

        if (ball_y_velocity == 1) y_check = ball_y_pos + BALL_SIZE + i;
        else y_check = ball_y_pos - i;

        // Handle all simple collision cases
        if (y_check >= pad1_pos && 
            y_check < pad1_pos + PADS_HEIGHT &&
            x_check < PADS_X_OFFSET + PADS_WIDTH)
        {
            result = VERTICAL_COLLISION;
            ball_x_pos = PADS_X_OFFSET + PADS_WIDTH + ball_speed - i;
        }
        else if (y_check >= pad2_pos &&
                 y_check < pad2_pos + PADS_HEIGHT &&
                 x_check >= DISPLAY_WIDTH - PADS_X_OFFSET - PADS_WIDTH)
        {
            result = VERTICAL_COLLISION;
            ball_x_pos = DISPLAY_WIDTH - PADS_X_OFFSET - PADS_WIDTH - BALL_SIZE - ball_speed + i;
        }
        else if (x_check < 0)
        {
            result = LEFT_OUT_OF_BOUNDS;
            break;
        }
        else if (x_check >= DISPLAY_WIDTH)
        {
            result = RIGHT_OUT_OF_BOUNDS;
            break;
        }

        // Handle corner collistions
        if (y_check < 0)
        {
            if (result == HORIZONTAL_COLLISION) result = CORNER_COLLISION;
            else result = HORIZONTAL_COLLISION;
            ball_y_pos = ball_speed - i;
        }
        else if (y_check >= DISPLAY_HEIGHT)
        {
            if (result == HORIZONTAL_COLLISION) result = CORNER_COLLISION;
            else result = HORIZONTAL_COLLISION;
            ball_y_pos = DISPLAY_HEIGHT - ball_speed - BALL_SIZE + i;
        }

        if (result != NO_COLLISTION) break;
    }

    return result;
}

/*
 *  Method for updating the ball's state and position.
 */
void update_ball()
{
    if (out_of_bounds) out_of_bounds = false;
    
    switch (handle_collision())
    {
    case VERTICAL_COLLISION:
        ball_x_velocity *= -1;
        ball_y_pos += ball_y_velocity * ball_speed;
        ball_speed++;
        break;

    case HORIZONTAL_COLLISION:
        ball_y_velocity *= -1;
        ball_x_pos += ball_x_velocity * ball_speed;
        break;

    case CORNER_COLLISION:
        ball_x_velocity *= -1;
        ball_y_velocity *= -1;
        ball_speed += 1;
        break;
    
    case LEFT_OUT_OF_BOUNDS:
        pulse_led(0b001, 2);
        update_score(PLAYER_2);

        out_of_bounds = true;
        break;

    case RIGHT_OUT_OF_BOUNDS:
        pulse_led(0b100, 1);
        update_score(PLAYER_1);

        out_of_bounds = true;
        break;

    default:
        ball_x_pos += ball_x_velocity * ball_speed;
        ball_y_pos += ball_y_velocity * ball_speed;
        break;
    }

    if (out_of_bounds)
    {
        reset_ball();
    }
}
