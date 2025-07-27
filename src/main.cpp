#include <SFML/Graphics.hpp>
#include <iostream>
constexpr unsigned WINDOW_WIDTH = 1290;
constexpr unsigned WINDOW_HEIGHT = 1080;

constexpr float SCREEN_WIDTH = static_cast<float>(WINDOW_WIDTH);
constexpr float SCREEN_HEIGHT = static_cast<float>(WINDOW_HEIGHT);

constexpr float PADDLE_HEIGHT = 300.f;
constexpr float PADDLE_WIDTH = 60.f;

constexpr float SCREEN_MARGIN_TOP = 25.f;
constexpr float SCREEN_MARGIN_BOTTOM = SCREEN_HEIGHT - 25.f;
constexpr float SCREEN_MARGIN_LEFT = 50.f;
constexpr float SCREEN_MARGIN_RIGHT = SCREEN_WIDTH - SCREEN_MARGIN_TOP;

constexpr float PADDLE_RIGHT_POSITION_X = SCREEN_MARGIN_RIGHT - PADDLE_WIDTH;

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape pad_left({PADDLE_WIDTH, PADDLE_HEIGHT});
    pad_left.setFillColor(sf::Color::White);

    sf::RectangleShape pad_right({PADDLE_WIDTH, PADDLE_HEIGHT});
    pad_right.setFillColor(sf::Color::White);

    // get the size of the window
    sf::Vector2u size = window.getSize();
    const auto [WINDOW_WIDTH, WINDOW_HEIGHT] = size;

    pad_left.move({SCREEN_MARGIN_LEFT, SCREEN_MARGIN_TOP});
    pad_right.move({PADDLE_RIGHT_POSITION_X, SCREEN_MARGIN_TOP});
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
                // Left Paddle Up
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
                    if (const auto [x, y] = pad_left.getPosition(); y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
                        const sf::Vector2f position = pad_left.getPosition();
                        pad_left.move({0.f, 25.f});
                    } else {
                        pad_left.setPosition({SCREEN_MARGIN_LEFT, SCREEN_HEIGHT - 300.f});
                    }
                }
                // Left Paddle Down
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
                    const sf::Vector2f position = pad_left.getPosition();
                    if (const auto [x, y] = position; y > 0) {
                        pad_left.move({0.f, -25.f});
                    } else {
                        pad_left.setPosition({SCREEN_MARGIN_LEFT, 0.f});
                    }
                }
                // Right Paddle Up
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
                    const sf::Vector2f position = pad_right.getPosition();
                    if (const auto [x, y] = position; y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
                        pad_right.move({0.f, 25.f});
                    } else {
                        pad_right.setPosition({SCREEN_MARGIN_LEFT, SCREEN_HEIGHT - 300.f});
                    }
                }
                // Right Paddle Down
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
                    const sf::Vector2f position = pad_right.getPosition(); // = (15, 55)
                    if (const auto [x, y] = position; y > 0) {
                        pad_right.move({0.f, -25.f});
                    } else {
                        pad_right.setPosition({SCREEN_MARGIN_LEFT, 0.f});
                    }
                }

            }
        }

        window.clear(sf::Color::Black);

        window.draw(pad_left);
        window.draw(pad_right);
        window.display();
    }
}
