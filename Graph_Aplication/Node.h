#ifndef NODE_H
#define NODE_H

#include "Draw.h"

class Edge;
class Node: public Draw
{
public:

	Node();
	Node(float x, float y, int name);
	Node(Node* node);

	float get_x();
	float get_y();
	float* get_x_();
	float* get_y_();
	int get_name();
	std::vector<std::pair<Node*, Edge*>> get_neighbors();

	void set_x(float X);
	void set_y(float Y);
	void set_name(int NAME);
	void add_neighbour(Node* node, Edge* edge);
	void delete_neighbour(std::pair<Node*, Edge*> node);
	std::vector<Edge*> delete_node();
	void show(sf::RenderWindow& window);
	

private:
	float x, y;
	int name;
	std::vector<std::pair<Node*, Edge*>> neighbours;

};

#endif