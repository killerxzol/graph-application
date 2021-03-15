#include "Node.h"

Node::Node() {
    set_x(0);
    set_y(0);
    set_name("");
}

Node::Node(float x, float y, std::string name) {
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
std::string Node::get_name() { return name; }
std::string Node::get_weight() { return weight; }
std::vector<std::pair<Node*, std::string>> Node::get_neighbors() { return neighbours; }

void Node::set_x(float X) { x = X; }
void Node::set_y(float Y) { y = Y; }
void Node::set_name(std::string NAME) { name = NAME; }
void Node::set_weight(std::string WEIGHT) { weight = WEIGHT; }

void Node::add_neighbour(Node* node, std::string weight)
{
    for (auto neighbour : neighbours)
    {
        if (neighbour.first == node)
            return;
    }
    neighbours.push_back({ node, weight });
    node->add_neighbour(this, weight);
}

void Node::delete_neighbour(Node* node)
{
    int i = 0;
    for (auto neighbour : neighbours)
    {
        if (neighbour.first == node)
            break;
        i++;
    }
    if (i < neighbours.size())
    {
        neighbours.erase(neighbours.begin() + i);
        node->delete_neighbour(this);
    }    
}