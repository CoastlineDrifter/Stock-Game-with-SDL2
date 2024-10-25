#pragma once


class UI {
public:
    void Render(SDL_Surface* Surface) {
        MyButton.Render(Surface);
    }

    void HandleEvent(const SDL_Event& E) {
        MyButton.HandleEvent(E);
    }

    // x = 50, y = 50, w = 50, h = 50
    Button MyButton{ 50, 50, 50, 50 };
};

class Rectangle {
public:
    Rectangle(int x, int y, int w, int h)
        : Rect{ x, y, w, h } {}

    void Render(SDL_Surface* Surface) {
        SDL_FillRect(
            Surface, &Rect, SDL_MapRGB(
                Surface->format, 255, 0, 0
            )
        );
    }

private:
    SDL_Rect Rect{ 0, 0, 0, 0 };
};

class Button : public Rectangle {
    public:
        Button(int x, int y, int w, int h)
            : Rectangle{x, y, w, h}{}

        void HandleEvent(const SDL_Event& E) {

        }
};