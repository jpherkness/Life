#include "SFML/Graphics.hpp"
#include <iostream>
#include "Grid.hpp"

int main() {
    
    sf::Vector2u size(60, 60); // The size of the window in pixels
    int scale = 20;
    
    Grid grid(size.x, size.y);
    sf::Clock clock;
    sf::Time time = sf::seconds(0.05f);
    
    // window
    sf::RenderWindow window(sf::VideoMode(size.x * scale, size.y * scale), "Life");
    window.setFramerateLimit(60);

    // pixel screen
    sf::Texture texture;
    texture.create(size.x, size.y);
    sf::Sprite screen(texture);
    screen.setScale(scale, scale);
    
    // events
    sf::Event event;
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                    grid.paused = !grid.paused;
                if (event.key.code == sf::Keyboard::R)
                    grid.randomize();
            }
            
            if (event.type == sf::Event::MouseButtonPressed){
                int x = sf::Mouse::getPosition(window).x / scale;
                int y = sf::Mouse::getPosition(window).y / scale;
                grid.cells[x + y * grid.width] = !grid.cells[x + y * grid.width];
            }
        }
        
        window.clear();
        
        // Update the game
        if (clock.getElapsedTime() > time)
        {
            clock.restart();
            grid.update();
        }
        // Draw current grid state
        sf::Uint8 *pixels = new sf::Uint8[size.x * size.y * 4];
        for(int i = 0; i < size.x; i++){
            for(int j = 0; j < size.y; j++){
                bool alive = grid.cells[i + j * size.x];
                int a = (i + j * size.x) * 4;
                if(alive)
                {
                    pixels[a] = 124;
                    pixels[a+1] = 176;
                    pixels[a+2] = 214;
                    pixels[a+3] = 255;
                }
                else
                {
                    pixels[a] = 15;
                    pixels[a+1] = 34;
                    pixels[a+2] = 48;
                    pixels[a+3] = 255;
                }
            }
        }
        texture.update(pixels);
        delete[] pixels;
        window.draw(screen);
        window.display();
    }
    return 0;
}