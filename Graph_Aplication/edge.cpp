#include "Edge.h"
#include "Node.h"

Edge::Edge() {
    set_x1(0);
    set_x2(0);
    set_y1(0);
    set_y2(0);
    set_weight(0);
}

Edge::Edge(Node* node1, Node* node2, int weight) {
    set_x1(node1->get_x_());
    set_y1(node1->get_y_());
    set_x2(node2->get_x_());
    set_y2(node2->get_y_());
    set_weight(weight);
}

float Edge::get_x1() { return *x1; }
float Edge::get_x2() { return *x2; }
float Edge::get_y1() { return *y1; }
float Edge::get_y2() { return *y2; }
int Edge::get_weight() { return weight; }

void Edge::set_x1(float *x_) { x1 = x_; }
void Edge::set_x2(float *x_) { x2 = x_; }
void Edge::set_y1(float *y_) { y1 = y_; }
void Edge::set_y2(float *y_) { y2 = y_; }
void Edge::set_weight(int weight_) { weight = weight_; }

void Edge::show(sf::RenderWindow& window)
{
    sf::VertexArray line(sf::Lines, 2);

    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");

    line[0].position = sf::Vector2f(this->get_x1(), this->get_y1());
    line[0].color = sf::Color(66, 103, 178);

    line[1].position = sf::Vector2f(this->get_x2(), this->get_y2());
    line[1].color = sf::Color(66, 103, 178);

    std::string text = std::to_string(this->get_weight());
    sf::Text edge_weight = { text, font, 11 };
    edge_weight.setPosition(sf::Vector2f((this->get_x1() + this->get_x2()) / 2, (this->get_y1() + this->get_y2()) / 2));
    edge_weight.setFillColor(sf::Color(137, 143, 156));

    window.draw(line);
    window.draw(edge_weight);
}