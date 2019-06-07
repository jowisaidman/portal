#ifndef __DANCINGPLAYER_H__
#define __DANCINGPLAYER_H__
#include <string>
#include <SDL2/SDL_image.h>
#include "../Sprite.h"
#include "../Rect.h"

#include "Player.h"

/*Estado de la clase Player, hereda de Sprite */
class DancingPlayer : public Sprite
{
public:
    DancingPlayer(const Window &window, const int &direction);
    ~DancingPlayer();
    virtual int render(const Rect &dest);
    virtual void setSrc(Rect &src) override;

private:
    Rect src;
    int direction;
};

#endif
