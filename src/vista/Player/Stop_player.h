#ifndef __STOPPLAYER_H__
#define __STOPPLAYER_H__
#include <string>
#include <SDL2/SDL_image.h>
#include "../Sprite.h"
#include "../Rect.h"
#include "Player.h"

/*Estado de la clase Player, hereda de State */
class StopPlayer : public Sprite
{
public:
    StopPlayer(const Window &window, const int &direction);
    ~StopPlayer();
    virtual int render(const Rect &dest);
    virtual void setSrc(Rect &src) override;
    virtual bool isDone() override;

private:
    Rect src;
    bool done;
    int direction;
};

#endif
