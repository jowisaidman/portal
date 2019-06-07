#include "../Window.h"
#include "Dancing_player.h"
#include "Player.h"
#include "../Constants.h"
#include <string>
#include <iostream>
#define MAX_WIDTH (9 * WIDTH_PLAYER_DANCING + 9)

DancingPlayer::DancingPlayer(const Window &window, const int &direction) : direction(direction), Sprite(PLAYER_FILENAME, window),
                                                                           src(X_START_POSITION, Y_POSITION_PLAYER_DANCING, WIDTH_PLAYER_DANCING, HEIGHT_PLAYER_DANCING)
{
}

int DancingPlayer::render(const Rect &dest)
{
  int response;
  if (direction == 1)
  {
    response = Sprite::render(src, dest);
  }
  else
  {
    response = Sprite::render(src, dest, SDL_FLIP_VERTICAL, 180);
  }
  int x_src = src.getX();
  int y_src = src.getY();
  x_src = (x_src + WIDTH_PLAYER_DANCING + 1) % (MAX_WIDTH);
  if (x_src == 1)
  {
    y_src = (y_src + HEIGHT_PLAYER_DANCING + 2) % (9 * HEIGHT_PLAYER_DANCING + 18 + Y_POSITION_PLAYER_DANCING);
  }
  if (y_src == 0)
  {
    y_src = Y_POSITION_PLAYER_DANCING;
  }
  src.set(x_src, y_src, WIDTH_PLAYER_DANCING, HEIGHT_PLAYER_DANCING);
  return response;
}

void DancingPlayer::setSrc(Rect &src)
{
  this->src.set(src.getX(), src.getY(), src.getWidth(), src.getHeight());
}

DancingPlayer::~DancingPlayer()
{
}