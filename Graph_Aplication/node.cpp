#include "Node.h"
#include "Edge.h"

Node::Node() {
    set_x(0);
    set_y(0);
    set_name(0);
}

Node::Node(float x, float y, int name) {
    set_x(x);
    set_y(y);
    set_name(name);
}

Node::Node(Node* node) {
    set_x(node->get_x());
    set_y(node->get_y());
    set_name(node->get_name());
}

float Node::get_x() { return x; }
float Node::get_y() { return y; }
float* Node::get_x_() { return &x; }
float* Node::get_y_() { return &y; }
int Node::get_name() { return name; }
std::vector<std::pair<Node*, Edge*>> Node::get_neighbors() { return neighbours; }

void Node::set_x(float X) { x = X; }
void Node::set_y(float Y) { y = Y; }
void Node::set_name(int NAME) { name = NAME; }

void Node::add_neighbour(Node* node, Edge* edge)
{
    for (auto neighbour : neighbours)
    {
        if (neighbour.first == node)
            return;
    }
    neighbours.push_back({ node, edge });
    node->add_neighbour(this, edge);
}

void Node::delete_neighbour(std::pair<Node*, Edge*> pair)
{
    neighbours.erase(std::find(neighbours.begin(), neighbours.end(), pair));
}

std::vector<Edge*> Node::delete_node()
{
    std::vector<Edge*> edges;
    for (auto &pair : neighbours)
    {
        pair.first->delete_neighbour({ this, pair.second });
        edges.push_back(pair.second);
    }
    return edges;
}

void Node::show(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");

    float radius = 20;
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(sf::Vector2f(this->get_x() - radius, this->get_y() - radius));
    circle.setFillColor(sf::Color(66, 103, 178));
    window.draw(circle);

    sf::Text name = { std::to_string(this->get_name()), font, 11 };
    name.setPosition(sf::Vector2f(this->get_x(), this->get_y()));
    name.setFillColor(sf::Color::White);
    
    window.draw(name);
}