#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

#include "Part.hpp"
#include "Collage.hpp"
#include "Defines.hpp"


double imgDiff(Collage& col, const sf::Image& img1, const sf::Image& img2, const sf::Image& img2stencil) {
    auto s = img1.getSize();

    auto* p1 = img1.getPixelsPtr();
    auto* p2 = img2.getPixelsPtr();
    auto* p2s = img2stencil.getPixelsPtr();

    double diff = 0.0;
    double d = 0.0;
    for (auto j=0u; j<s.y; ++j)
        for (auto i=0u; i<s.x; ++i) {
            d = abs(p1[j*s.x*4 + i*4] - p2[j*s.x*4 + i*4])
              + abs(p1[j*s.x*4 + i*4 + 1] - p2[j*s.x*4 + i*4 + 1])
              + abs(p1[j*s.x*4 + i*4 + 2] - p2[j*s.x*4 + i*4 + 2])
              + abs(p1[j*s.x*4 + i*4 + 3] - p2[j*s.x*4 + i*4 + 3]);
            diff += d;
            if (d > 300) {
                unsigned stencil = p2s[j*s.x*4 + i*4]*256 + p2s[j*s.x*4 + i*4 + 1];
                if (stencil > 0)
                    col.addHit(stencil);
            }
        }

    return diff;
}


int main(void) {
    std::default_random_engine r(time(NULL));

    sf::RenderTexture rtex, rtex2, rtex2s;
    rtex.create(IMGW, IMGH);
    rtex2.create(IMGW, IMGH);
    rtex2s.create(IMGW, IMGH);
    rtex.clear(sf::Color(0, 0, 0, 255));
    rtex2.clear(sf::Color(0, 0, 0, 255));
    rtex2s.clear(sf::Color(0, 0, 0, 255));
    sf::Sprite spr(rtex2.getTexture());

    std::vector<sf::Texture> texs;
    texs.resize(3);
    texs[0].loadFromFile("res/comp/img1.png");
    texs[1].loadFromFile("res/comp/img2.png");
    texs[2].loadFromFile("res/comp/img3.png");

    Collage col(texs, r, 5, IMGW, IMGH);
    Collage col2(texs, r, 5, IMGW, IMGH);
    col2.draw(rtex);
    col2.draw(rtex2);
    col2.drawStencil(rtex2s);
    rtex.display();

    sf::Image img;
    img.loadFromFile("res/as.png");
    sf::Image img2;

    col2.clearHits();
    double diff = imgDiff(col2, img, rtex2.getTexture().copyToImage(), rtex2s.getTexture().copyToImage());
    printf("%0.4f\n", diff);

    // Declare and create a new window
    sf::RenderWindow window(sf::VideoMode(IMGW, IMGH), "CollageCreator");
    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);

    // The main loop - ends as soon as the window is closed
    while (window.isOpen()) {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event)) {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        rtex2.clear(sf::Color(0, 0, 0, 255));
        rtex2s.clear(sf::Color(0, 0, 0, 255));

        col2 = col;
        col2.randomizeTop(r);
        col2.draw(rtex2);
        col2.drawStencil(rtex2s);

        rtex2.display();
        rtex2s.display();

        window.clear();
        window.draw(spr);
        window.display();

        col2.clearHits();
        double newdiff = imgDiff(col2, img, rtex2.getTexture().copyToImage(), rtex2s.getTexture().copyToImage());
        printf("%0.4f   %0.4f\n", newdiff, diff);
        if (newdiff < diff) {
            col = col2;

            rtex.clear(sf::Color(0, 0, 0, 255));
            col.draw(rtex);
            rtex.display();

            diff = newdiff;
        }
    }

    return 0;
}
