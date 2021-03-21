#ifndef EDGE_H
#define EDGE_H

#include "Draw.h"

class Node;
class Edge : public Draw
{
public:
	Edge();
	Edge(Node* node1, Node* node2, int weight);

	float get_x1();
	float get_y1();
	float get_x2();
	float get_y2();
	int get_weight();

	void set_x1(float *x_);
	void set_x2(float *x_);
	void set_y1(float *y_);
	void set_y2(float *y_);
	void set_weight(int weight_);

	void show(sf::RenderWindow& window);

private:
	float *x1, *y1, *x2, *y2;
	int weight;
};

#endif