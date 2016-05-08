#ifndef PART_HPP
#define PART_HPP


#include <SFML/Graphics.hpp>


class Part {
public:
    Part(const sf::Texture& texture,
         const sf::Vector2f& pos,
         float scale = 1.0f, float rot = 0.0f);

    void set(const sf::Vector2f& pos,
             float scale = 1.0f, float rot = 0.0f);

    void draw(sf::RenderTexture& tex);

private:
    sf::Sprite spr_;
    sf::Vector2f pos_;
    float scale_;
    float rot_;
};


#endif // PART_HPP
