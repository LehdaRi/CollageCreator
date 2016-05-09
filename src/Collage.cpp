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

void Collage::drawStencil(sf::RenderTexture& tex) {
    auto i=0u;
    for (auto& p : parts_)
        p.drawStencil(tex, ++i);
}

void Collage::randomize(std::default_random_engine& r) {
    for (auto& p : parts_)
        p.set(sf::Vector2f(RF*IMGW, RF*IMGH), 0.01f+RF*0.35f, RF*360.0f);
}

void Collage::randomize(std::default_random_engine& r, unsigned n) {
    for (auto i=0u; i<n; ++i) {
        auto& p = parts_[r()%parts_.size()];
        p.set(sf::Vector2f(RF*IMGW, RF*IMGH), 0.01f+RF*0.35f, RF*360.0f);
    }
}

void Collage::randomizeTop(std::default_random_engine& r) {
    unsigned tophits = 0u;
    auto id = 0u;
    for (auto i=0u; i<parts_.size(); ++i) {
        if (parts_[i].hits_ > tophits) {
            id = i;
            tophits = parts_[id].hits_;
        }
    }
    printf("tophits: %u, id: %u\n", tophits, id);
    parts_[id].set(sf::Vector2f(RF*IMGW, RF*IMGH), 0.01f+RF*0.35f, RF*360.0f);
}

void Collage::addHit(unsigned stencil) {
    parts_.at(stencil-1).hits_++;
}

void Collage::clearHits(void) {
    for (auto& p : parts_)
        p.hits_ = 0;
}
