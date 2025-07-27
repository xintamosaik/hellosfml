#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << static_cast<int>(keyPressed->scancode) << std::endl;
                    std::cout << "code: " << static_cast<int>(keyPressed->code) << std::endl;
                    std::cout << "control: " << keyPressed->control << std::endl;
                    std::cout << "alt: " << keyPressed->alt << std::endl;
                    std::cout << "shift: " << keyPressed->shift << std::endl;
                    std::cout << "system: " << keyPressed->system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString() <<
                            std::endl;
                    std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed->scancode)) <<
                            std::endl;
                    std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed->code)) <<
                            std::endl;
                }
                // by key code
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    shape.move({-5.f, 0.f});
                    std::cout << "left pressed" << std::endl;
                }
                // by scan code
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                    shape.move({5.f, 0.f});
                    std::cout << "right pressed" << std::endl;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    std::cout << "the left mouse button was pressed" << std::endl;
                }
            }
        }

        window.clear(sf::Color::Black);

        // move the entity relatively to its current position

        window.draw(shape);
        window.display();
    }
}
