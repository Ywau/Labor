#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;

class Ball {
  public:
	Ball(float size) : radius(size) {
		this->shape = sf::CircleShape(size);
		this->pos = sf::Vector2<float>();
		this->speed = sf::Vector2<float>(0, 1);
		float air_velocity = 0.1 / 50 * radius;
		this->velocity = sf::Vector2<float>(0, air_velocity);
		shape.setFillColor(sf::Color(0, 0, 255, 255));
	}
	Ball(float size, sf::Vector2<float> pos) : Ball(size) { this->pos = pos; }
	Ball(float size, sf::Vector2<float> pos, sf::Color color)
		: Ball(size, pos) {
		this->shape.setFillColor(color);
	}

	void Update() {
		this->checkCollision();
		speed += velocity;
		pos += speed;
		shape.setPosition(pos);
	}
	void Draw(sf::RenderWindow &window) { window.draw(shape); }

  private:
	void checkCollision() {
		if (pos.y < 0) {
			pos.y = 0;
			speed.y *= -1;
		} else if (pos.y + 2 * radius > HEIGHT) {
			pos.y = HEIGHT - 2 * radius;
			speed.y *= -1;
			speed.y *= 0.9;
		}
	}
	float radius;
	sf::Vector2<float> pos;
	sf::Vector2<float> speed;
	sf::Vector2<float> velocity;
	sf::CircleShape shape;
};

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
	sf::Clock clock;
	Ball *ball1 =
		new Ball(25, sf::Vector2<float>(10, 0), sf::Color(0, 0, 255, 255));
	Ball *ball2 =
		new Ball(50, sf::Vector2<float>(100, 0), sf::Color(255, 0, 0, 255));
	Ball *ball3 =
		new Ball(75, sf::Vector2<float>(300, 0), sf::Color(0, 255, 255, 255));
	clock.restart();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		ball1->Update();
		ball1->Draw(window);
		ball2->Update();
		ball2->Draw(window);
		ball3->Update();
		ball3->Draw(window);
		window.display();
		float pTime = clock.getElapsedTime().asMilliseconds();
		while (pTime < 1000. / 60) {
			pTime = clock.getElapsedTime().asMilliseconds();
		}
		clock.restart();
	}

	return 0;
}
