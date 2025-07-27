#include <SFML/Graphics.hpp>
#include <iostream>
constexpr float PADDLE_HEIGHT = 300.f;
constexpr float PADDLE_WIDTH = 60.f;

constexpr float SCREEN_MARGIN = 25.f;
constexpr float SCREEN_MARGIN_SIDES = 50.f;

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape shape({ PADDLE_WIDTH, PADDLE_HEIGHT });
    shape.setFillColor(sf::Color::White);

    // get the size of the window
    sf::Vector2u size = window.getSize();
    const auto [WINDOW_WIDTH, WINDOW_HEIGHT] = size;

    shape.move({SCREEN_MARGIN_SIDES,  SCREEN_MARGIN});
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
                    if (const auto [x, y] = shape.getPosition(); y < WINDOW_HEIGHT - PADDLE_HEIGHT) {
                        const sf::Vector2f position = shape.getPosition(); // = (15, 55)
                        shape.move({0.f, 25.f});
                    } else {
                        shape.setPosition({SCREEN_MARGIN_SIDES, WINDOW_HEIGHT - 300.f});
                    }



                }
                // by scan code
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {

                    const sf::Vector2f position = shape.getPosition(); // = (15, 55)
                    if (const auto [x, y] = position; y > 0) {
                        shape.move({0.f, -25.f});
                    } else {
                        shape.setPosition({SCREEN_MARGIN_SIDES, 0.f});
                    }


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
