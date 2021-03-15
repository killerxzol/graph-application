#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

class Node {
public:

	Node();
	Node(float x, float y, std::string name);
	Node(Node* node);

	float get_x();
	float get_y();
	std::string get_name();
	std::string get_weight();
	std::vector<std::pair<Node*, std::string>> get_neighbors();

	void set_x(float X);
	void set_y(float Y);
	void set_name(std::string NAME);
	void set_weight(std::string WEIGHT);
	void add_neighbour(Node* node, std::string weight);
	void delete_neighbour(Node* node);

private:

	float x, y;
	std::string name, weight;
	std::vector<std::pair<Node*, std::string>> neighbours;

};

#endif