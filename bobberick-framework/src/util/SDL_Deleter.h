#ifndef BOBBERICK_TOOLS_SDL_DELETER_H
#define BOBBERICK_TOOLS_SDL_DELETER_H

#include <SDL.h>
#include <memory>

struct SDL_Deleter
{
    void operator()(SDL_Surface* ptr) {
        if (ptr) {
            SDL_FreeSurface(ptr);
        }
    }

    void operator()(SDL_Texture* ptr) {
        if (ptr) {
            SDL_DestroyTexture(ptr);
        }
    }

    void operator()(SDL_Renderer* ptr) {
        if (ptr) {
            SDL_DestroyRenderer(ptr);
        }
    }

    void operator()(SDL_Window* ptr) {
        if (ptr) {
            SDL_DestroyWindow(ptr);
        }
    }

    void operator()(SDL_RWops* ptr) {
        if (ptr) {
            SDL_RWclose(ptr);
        }
    }
};

template<class T, class D = std::default_delete<T>>
struct sdl_shared_pointer : public std::shared_ptr<T>
{
    explicit sdl_shared_pointer(T* t = nullptr) : std::shared_ptr<T>(t, D()) {}

    void reset(T* t = nullptr)
    {
        std::shared_ptr<T>::reset(t, D());
    }
};

typedef sdl_shared_pointer<SDL_Surface, SDL_Deleter> SDL_SurfacePointer;
typedef sdl_shared_pointer<SDL_Window, SDL_Deleter> SDL_WindowPointer;
typedef sdl_shared_pointer<SDL_Texture, SDL_Deleter> SDL_TexturePointer;
typedef sdl_shared_pointer<SDL_Renderer, SDL_Deleter> SDL_RendererPointer;
typedef sdl_shared_pointer<SDL_RWops, SDL_Deleter> SDL_RWopsPointer;


#endif //BOBBERICK_TOOLS_SDL_DELETER_H
