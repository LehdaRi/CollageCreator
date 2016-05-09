#include "Part.hpp"


#define PI 3.14159265f


Part::Part(const sf::Texture& texture,
           const sf::Vector2f& pos,
           float scale, float rot) :
    spr_(texture), pos_(pos),
    scale_(scale), rot_(rot),
    hits_(0u)
{
    spr_.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    spr_.setPosition(pos_);
    spr_.setScale(scale_, scale_);
    spr_.setRotation(rot_);
}

void Part::set(const sf::Vector2f& pos,
               float scale, float rot) {
    pos_ = pos;
    scale_ = scale;
    rot_ = rot;

    spr_.setPosition(pos_);
    spr_.setScale(scale_, scale_);
    spr_.setRotation(rot_);

}

void Part::draw(sf::RenderTexture& tex) {
    //spr_.setColor(sf::Color::Black);
    //for (auto i=0u; i<8; ++i) {
    //    spr_.setPosition(pos_+(3.0f+5.0f*scale_)*sf::Vector2f(cosf(0.25*PI*i), sinf(0.25*PI*i)));
    //    tex.draw(spr_);
    //}

    spr_.setColor(sf::Color::White);
    tex.draw(spr_);
}

void Part::drawStencil(sf::RenderTexture& tex, unsigned s) {
    //spr_.setColor(sf::Color::Black);
    //for (auto i=0u; i<8; ++i) {
    //    spr_.setPosition(pos_+(3.0f+5.0f*scale_)*sf::Vector2f(cosf(0.25*PI*i), sinf(0.25*PI*i)));
    //    tex.draw(spr_);
    //}

    spr_.setColor(sf::Color(s/256, s%256, 0, 255));
    tex.draw(spr_);
}
