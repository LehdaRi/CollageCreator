#ifndef COLLAGE_HPP
#define COLLAGE_HPP


#include "Part.hpp"

#include <vector>


class Collage {
public:
    Collage(const std::vector<sf::Texture>& texs,
            std::default_random_engine& r,
            unsigned nParts, unsigned imgw, unsigned imgh);

    void draw(sf::RenderTexture& tex);
    void drawStencil(sf::RenderTexture& tex);

    void addPart(std::default_random_engine& r);

    void randomize(std::default_random_engine& r);
    void randomize(std::default_random_engine& r, unsigned n);
    void randomizeTop(std::default_random_engine& r);

    void addHit(unsigned stencil);
    void clearHits(void);

private:
    std::vector<Part> parts_;
};


#endif // COLLAGE_HPP
