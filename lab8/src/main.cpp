#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::Text text;
    sf::Font font;
    font.loadFromFile("./fonts/MiniBananaDemoRegular.ttf");
    text.setFont(font);
    text.setString("Hello");
    text.setPosition(sf::Vector2<float>(0, 200));
    text.setCharacterSize(48);
    text.setFillColor(sf::Color(100, 0, 150));

    sf::SoundBuffer sb;
    sb.loadFromFile("./sounds/sound.wav");

    sf::Sound sound;
    sound.setBuffer(sb);
    sound.setVolume(25);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sound.play();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        window.draw(circle);
        window.draw(text);

        // end the current frame
        window.display();
    }

    return 0;
}
