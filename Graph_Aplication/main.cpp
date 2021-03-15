#include "Node.h"
#include "Graph.h"
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <limits.h> 
//#include <SFML/Graphics.hpp>

sf::VertexArray edge(float x1, float y1, float x2, float y2)
{
    sf::VertexArray line(sf::Lines, 2);

    line[0].position = sf::Vector2f(x1, y1);
    line[0].color = sf::Color(66, 103, 178);

    line[1].position = sf::Vector2f(x2, y2);
    line[1].color = sf::Color(66, 103, 178);

    return line;
}

void path(std::vector<int> c, std::vector<Node*> nodes_list, int i) {
    if (c[i] == -1)
    {
        return;
    }
    path(c, nodes_list, c[i]);
    std::cout << nodes_list[i]->get_name() << " ";
}

void dijkstra_algorithm(std::vector<Node*> nodes_list, std::string _begin_node, int n) {

    int min, index, len, name;
    std::vector<int> a, b, c;

    int begin_node;
    for (begin_node = 0; nodes_list[begin_node]->get_name() != _begin_node; ++begin_node);

    for (int i = 0; i < n; ++i)
    {
        a.push_back(INT_MAX);
        b.push_back(0);
        c.push_back(-1);
    }

    a[begin_node] = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            min = INT_MAX;
            if (!b[j] && a[j] < min)
            {
                min = a[j];
                index = j;
            }
        }

        b[index] = 1;

        for (auto neighbor : nodes_list[index]->get_neighbors())
        {
            len = std::stoi(neighbor.second);
            for (name = 0; neighbor.first != nodes_list[name]; ++name);
            if (a[index] + len < a[name])
            {
                c[name] = index;
                a[name] = a[index] + len;
            }
        }
    }

    std::cout << "From | To \t Distance \t Path" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << _begin_node << "  ->  " << nodes_list[i]->get_name() << "\t\t";
        if (a[i] == INT_MAX)
        {
            std::cout << "No path" << "\t " << "No path";
            std::cout << std::endl;
            continue;
        }
        else
        {
            std::cout << a[i] << "\t ";
            std::cout << _begin_node << " ";
            path(c, nodes_list, i);
            std::cout << std::endl;
        }
    }
}

int main() {

    bool _move_node = false, _remove_node = false, _create_node = false, _create_edge_first = true, _create_edge_second = false;
    float radius = 20;
    int nodes_number, names, width = 640, height = 480, dot, first = -1, second = -1, _pass;
    int** matrix;

    std::vector<Node*> nodes_list;

    sf::Font font;
    sf::Text edge_weight;
    std::vector<sf::CircleShape> nodes_circles;
    std::vector<sf::Text> nodes_names;

    std::ifstream file("matrix.txt");
    file >> nodes_number;

    matrix = new int* [nodes_number];
    for (int i = 0; i < nodes_number; ++i) matrix[i] = new int[nodes_number];

    for (int i = 0; i < nodes_number; ++i)
        for (int j = 0; j < nodes_number; ++j)
            file >> matrix[i][j];

    graph_constructor(nodes_list, nodes_number, width - radius, height - radius, matrix);

    for (int i = 0; i < nodes_number; i++)
        delete[] matrix[i];
    delete[] matrix;

    if (!font.loadFromFile("Roboto-Black.ttf"))
    {
        std::cout << "Font not found." << std::endl;
        exit(-1);
    }

    names = nodes_number;

    for (int i = 0; i < nodes_number; ++i)
    {
        sf::CircleShape circle;
        circle.setRadius(radius);
        circle.setPosition(sf::Vector2f(nodes_list[i]->get_x() - radius, nodes_list[i]->get_y() - radius));
        circle.setFillColor(sf::Color(66, 103, 178));
        nodes_circles.push_back(circle);

        sf::Text name = { nodes_list[i]->get_name(), font, 11 };
        name.setPosition(sf::Vector2f(nodes_list[i]->get_x(), nodes_list[i]->get_y()));
        name.setFillColor(sf::Color::White);
        nodes_names.push_back(name);
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Graph class", sf::Style::Default, settings);

    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (sqrt(pow(nodes_list[i]->get_x() - pos.x, 2) + pow(nodes_list[i]->get_y() - pos.y, 2)) < radius)
                    {
                        _pass = i;
                        _move_node = true;
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (sqrt(pow(nodes_list[i]->get_x() - pos.x, 2) + pow(nodes_list[i]->get_y() - pos.y, 2)) < radius)
                    {
                        _pass = i;
                        _remove_node = true;
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (sqrt(pow(nodes_list[i]->get_x() - pos.x, 2) + pow(nodes_list[i]->get_y() - pos.y, 2)) > radius)
                    {
                        _create_node = true;
                        break;
                    }
                }
                if (!nodes_number)
                {
                    _create_node = true;
                }

            }

            if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Middle)
            {
                for (int i = 0; i < nodes_number; ++i)
                {
                    if (_create_edge_first && sqrt(pow(nodes_list[i]->get_x() - pos.x, 2) + pow(nodes_list[i]->get_y() - pos.y, 2)) < radius)
                    {
                        first = i;
                        _create_edge_first = false;
                        _create_edge_second = true;
                        break;
                    }
                    if (_create_edge_second && sqrt(pow(nodes_list[i]->get_x() - pos.x, 2) + pow(nodes_list[i]->get_y() - pos.y, 2)) < radius)
                    {
                        second = i;
                        _create_edge_second = false;
                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                {
                    std::string enter_node;
                    std::cout << "Initial node: ";
                    std::cin >> enter_node;
                    dijkstra_algorithm(nodes_list, enter_node, nodes_number);
                }
            }


            if (event.type == sf::Event::MouseButtonReleased)
                if (event.key.code == sf::Mouse::Left)
                    _move_node = false;

            if (_move_node)
            {
                _create_node = false;
                nodes_list[_pass]->set_x(pos.x);
                nodes_list[_pass]->set_y(pos.y);
                nodes_circles[_pass].setPosition(sf::Vector2f(nodes_list[_pass]->get_x() - radius, nodes_list[_pass]->get_y() - radius));
                nodes_names[_pass].setPosition(sf::Vector2f(nodes_list[_pass]->get_x(), nodes_list[_pass]->get_y()));
            }

            if (_remove_node)
            {
                Node* node = nodes_list[_pass];
                for (auto neighbour : node->get_neighbors())
                    neighbour.first->delete_neighbour(node);

                nodes_list.erase(nodes_list.begin() + _pass);
                nodes_circles.erase(nodes_circles.begin() + _pass);
                nodes_names.erase(nodes_names.begin() + _pass);
                nodes_number--;
                _remove_node = false;
            }

            if (_create_node)
            {
                std::string new_name = std::to_string(names + 1);
                nodes_list.push_back(new Node{ (float)pos.x, (float)pos.y, new_name });

                sf::CircleShape circle;
                circle.setRadius(radius);
                circle.setPosition(sf::Vector2f(nodes_list.back()->get_x() - radius, nodes_list.back()->get_y() - radius));
                circle.setFillColor(sf::Color(66, 103, 178));
                nodes_circles.push_back(circle);

                sf::Text name = { nodes_list.back()->get_name(), font, 10 };
                name.setPosition(sf::Vector2f(nodes_list.back()->get_x(), nodes_list.back()->get_y()));
                name.setFillColor(sf::Color::White);
                nodes_names.push_back(name);

                names++;
                nodes_number++;
                _create_node = false;
            }

            if (!_create_edge_first && !_create_edge_second)
            {
                std::cout << "Edge weight:\t";
                std::string new_edge;
                std::cin >> new_edge;

                nodes_list[first]->add_neighbour(nodes_list[second], new_edge);

                _create_edge_first = true;
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < nodes_number; ++i)
        {

            window.draw(nodes_circles[i]);
            window.draw(nodes_names[i]);

            for (auto neighbor : nodes_list[i]->get_neighbors())
            {
                sf::VertexArray line = edge(nodes_list[i]->get_x(), nodes_list[i]->get_y(), neighbor.first->get_x(), neighbor.first->get_y());

                edge_weight = { neighbor.second, font, 11 };
                edge_weight.setPosition(sf::Vector2f((nodes_list[i]->get_x() + neighbor.first->get_x()) / 2, (nodes_list[i]->get_y() + neighbor.first->get_y()) / 2));
                edge_weight.setFillColor(sf::Color(137, 143, 156));

                window.draw(line);
                window.draw(edge_weight);
            }
        }

        window.display();

    }

    return 0;
}