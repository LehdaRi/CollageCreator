#include "Collage.hpp"
#include "Defines.hpp"


Collage::Collage(const std::vector<sf::Texture>& texs,
                 std::default_random_engine& r,
                 unsigned nParts, unsigned imgw, unsigned imgh) {
    for (auto i=0u; i<nParts; ++i) {
        unsigned texid = r() % texs.size();
        parts_.emplace_back(texs[texid], sf::Vector2f(RF*IMGW, RF*IMGH), 0.05f+RF*0.25f, RF*360.0f);
    }
}

void Collage::draw(sf::RenderTexture& tex) {
    for (auto& p : parts_)
        p.draw(tex);
}

void Collage::randomize(std::default_random_engine& r) {
    for (auto& p : parts_)
        p.set(sf::Vector2f(RF*IMGW, RF*IMGH), 0.05f+RF*0.25f, RF*360.0f);
}
