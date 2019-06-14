#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <SDL2/SDL_image.h>
#include "Window.h"
#include "Rect.h"

class Sprite
{
public:
    /**
     * Crea un SDL_Texture, lanza una excepción si el filename es inválido
     **/
    Sprite(SDL_Texture *texture, const Window &window);
    /**
     * Libera la memoria reservada por la textura
     **/
    virtual ~Sprite();
    
    /**
     * Renderiza la textura cargada
     **/
    // int render(const Rect &src, const Rect &dest) const;
    int render(const Rect &src, const Rect &dest, SDL_RendererFlip flip = SDL_FLIP_NONE, float angle = 0, const int &color = 0) const;
    virtual int render(const Rect &dest) = 0;
    virtual bool isDone(){return true;};
    virtual void setSrc(Rect &src){this->src.set(src.getX(), src.getY(), src.getWidth(), src.getHeight());};
    virtual Rect getSrc() { return src; };
    virtual void restart(){};
    virtual void setDirection(const int& direction){this->direction = direction;};
    void addColor(const int &id, const int &r, const int &g, const int &b);

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Rect src;
    int direction;
    std::map<Uint8, std::vector<int>> colors;
};

#endif
