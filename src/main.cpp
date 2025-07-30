#include <SFML/Graphics.hpp>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 1290;
constexpr unsigned WINDOW_HEIGHT = 900;

constexpr float SCREEN_WIDTH = static_cast<float>(WINDOW_WIDTH);
constexpr float SCREEN_HEIGHT = static_cast<float>(WINDOW_HEIGHT);
constexpr float SCREEN_MARGIN_TOP = 25.f;
constexpr float SCREEN_MARGIN_BOTTOM = SCREEN_HEIGHT - 25.f;
constexpr float SCREEN_MARGIN_LEFT = 50.f;
constexpr float SCREEN_MARGIN_RIGHT = SCREEN_WIDTH - SCREEN_MARGIN_TOP;

constexpr float PADDLE_HEIGHT = 300.f;
constexpr float PADDLE_WIDTH = 60.f;
constexpr float PADDLE_RIGHT_POSITION_X = SCREEN_MARGIN_RIGHT - PADDLE_WIDTH;

constexpr float ZERO = 0.f;

constexpr float BALL_RADIUS = 20.f;
constexpr float BALL_DIAMETER = BALL_RADIUS * 2;

float speed_paddle = 25.f;
float speed_ball = 2.f;
float speed_ball_vertical = 5.f;

bool left_up = false;
bool left_down = false;

bool right_up = false;
bool right_down = false;

bool ball_moving = false;

enum Direction {
    NONE,
    TOP_RIGHT,
    TOP_LEFT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT,
};

char ball_direction = TOP_RIGHT;

int main() {
    sf::RenderWindow window;
    try {
        window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "CMake SFML Project - PONG Clone");
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape pad_left({PADDLE_WIDTH, PADDLE_HEIGHT});
    pad_left.setFillColor(sf::Color::White);
    pad_left.move({SCREEN_MARGIN_LEFT, SCREEN_MARGIN_TOP});

    sf::RectangleShape pad_right({PADDLE_WIDTH, PADDLE_HEIGHT});
    pad_right.setFillColor(sf::Color::White);
    pad_right.move({PADDLE_RIGHT_POSITION_X, SCREEN_MARGIN_TOP});

    sf::CircleShape ball(BALL_RADIUS);
    ball.setFillColor(sf::Color::White);
    ball.setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

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
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                    ball_moving = true;
                }
            }

            left_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W);
            left_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S);

            right_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up);
            right_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                const auto [x,y] = localPosition;
                std::cout << x << ' ' << y << '\n';
            }
        } // END POLL EVENT

        if (left_up && pad_left.getPosition().y >= 0) {
            pad_left.move({ZERO, speed_paddle * -1});
        }
        if (left_down && pad_left.getPosition().y <= SCREEN_HEIGHT - PADDLE_HEIGHT) {
            pad_left.move({ZERO, speed_paddle});
        }

        if (right_up && pad_right.getPosition().y >= 0) {
            pad_right.move({ZERO, speed_paddle * -1});
        }
        if (right_down && pad_right.getPosition().y <= SCREEN_HEIGHT - PADDLE_HEIGHT) {
            pad_right.move({ZERO, speed_paddle});
        }

        // ball collision walls
        const auto [x,y] = ball.getPosition();

        if (y <= 0) {
            if (ball_direction == TOP_LEFT) {
                ball_direction = BOTTOM_LEFT;
            }
            if (ball_direction == TOP_RIGHT) {
                ball_direction = BOTTOM_RIGHT;
            }
        }

        if (y >= SCREEN_HEIGHT - BALL_DIAMETER) {
            if (ball_direction == BOTTOM_LEFT) {
                ball_direction = TOP_LEFT;
            }
            if (ball_direction == BOTTOM_RIGHT) {
                ball_direction = TOP_RIGHT;
            }
        }

        if (x <= 0) {
            if (ball_direction == TOP_LEFT) {
                ball_direction = TOP_RIGHT;
            }

            if (ball_direction == BOTTOM_LEFT) {
                ball_direction = BOTTOM_RIGHT;
            }
        }

        if (x >= SCREEN_WIDTH - BALL_DIAMETER) {
            if (ball_direction == TOP_RIGHT) {
                ball_direction = TOP_LEFT;
            }

            if (ball_direction == BOTTOM_RIGHT) {
                ball_direction = BOTTOM_LEFT;
            }
        }


        switch (ball_direction) {
            case NONE:
                break;
            case TOP_LEFT:
                ball.move({-speed_ball, -speed_ball_vertical});
                break;
            case TOP_RIGHT:
                ball.move({speed_ball, -speed_ball_vertical});
                break;
            case BOTTOM_LEFT:
                ball.move({-speed_ball, speed_ball_vertical});
                break;
            case BOTTOM_RIGHT:
                ball.move({speed_ball, speed_ball_vertical});
                break;
            default:
                break;
        }

        window.clear(sf::Color::Black);
        window.draw(pad_left);
        window.draw(pad_right);
        window.draw(ball);
        window.display();
    }
}
