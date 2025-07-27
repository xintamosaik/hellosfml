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
constexpr float ZERO = 0.f;
float acceleration = 25.f;

bool left_up = false;
bool left_down = false;

bool right_up = false;
bool right_down = false;

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "CMake SFML Project - PONG Clone");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape pad_left({PADDLE_WIDTH, PADDLE_HEIGHT});
    pad_left.setFillColor(sf::Color::White);
    pad_left.move({SCREEN_MARGIN_LEFT, SCREEN_MARGIN_TOP});

    sf::RectangleShape pad_right({PADDLE_WIDTH, PADDLE_HEIGHT});
    pad_right.setFillColor(sf::Color::White);
    pad_right.move({PADDLE_RIGHT_POSITION_X, SCREEN_MARGIN_TOP});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return EXIT_SUCCESS;
            }
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                    return EXIT_SUCCESS;
                }
            }

            left_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W);
            left_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S);

            right_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up);
            right_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down);
        }

        if (left_up && pad_left.getPosition().y >= 0) {
            pad_left.move({ZERO, acceleration * -1});
        }
        if (left_down && pad_left.getPosition().y <= SCREEN_HEIGHT - PADDLE_HEIGHT) {
            pad_left.move({ZERO, acceleration});
        }

        if (right_up && pad_right.getPosition().y >= 0) {
            pad_right.move({ZERO, acceleration * -1});
        }
        if (right_down && pad_right.getPosition().y <= SCREEN_HEIGHT - PADDLE_HEIGHT) {
            pad_right.move({ZERO, acceleration});
        }

        window.clear(sf::Color::Black);
        window.draw(pad_left);
        window.draw(pad_right);
        window.display();
    }
}
