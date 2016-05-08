#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

#include "Part.hpp"
#include "Collage.hpp"
#include "Defines.hpp"


double imgDiff(const sf::Image& img1, const sf::Image& img2) {
    auto s = img1.getSize();

    auto* p1 = img1.getPixelsPtr();
    auto* p2 = img2.getPixelsPtr();

    double diff = 0.0;
    for (auto j=0u; j<s.y; ++j)
        for (auto i=0u; i<s.x; ++i)
            diff += abs(p1[j*s.x*4 + i*4] - p2[j*s.x*4 + i*4])
                  + abs(p1[j*s.x*4 + i*4 + 1] - p2[j*s.x*4 + i*4 + 1])
                  + abs(p1[j*s.x*4 + i*4 + 2] - p2[j*s.x*4 + i*4 + 2])
                  + abs(p1[j*s.x*4 + i*4 + 3] - p2[j*s.x*4 + i*4 + 3]);

    return diff;
}


int main(void) {
    std::default_random_engine r(time(NULL));

    sf::RenderTexture rtex, rtex2;
    rtex.create(IMGW, IMGH);
    rtex2.create(IMGW, IMGH);
    rtex.clear(sf::Color(0, 0, 0, 255));
    rtex2.clear(sf::Color(0, 0, 0, 255));
    sf::Sprite spr(rtex.getTexture());

    sf::Texture tex1;
    tex1.loadFromFile("res/comp/img1.png");

    Collage col({tex1}, r, 10, IMGW, IMGH);
    Collage col2({tex1}, r, 10, IMGW, IMGH);
    col2.draw(rtex);

    sf::Image img;
    img.loadFromFile("res/as.png");
    sf::Image img2;


    double diff = printf("%0.4f\n", imgDiff(img, rtex.getTexture().copyToImage()));

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

        // Activate the window for OpenGL rendering


        rtex2.clear(sf::Color(0, 0, 0, 255));

        col2.randomize(r);
        col2.draw(rtex2);

        rtex2.display();

        window.clear();
        window.draw(spr);
        window.display();

        double newdiff = printf("%0.4f\n", imgDiff(img, rtex2.getTexture().copyToImage()));
        if (newdiff < diff) {
            col = col2;

            rtex.clear(sf::Color(0, 0, 0, 255));
            col.draw(rtex);
            rtex.display();
        }
    }

    return 0;
}
