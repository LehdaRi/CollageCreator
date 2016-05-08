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
    void randomize(std::default_random_engine& r);

private:
    std::vector<Part> parts_;
};


#endif // COLLAGE_HPP
