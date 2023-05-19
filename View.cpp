#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include <vector>
#include "Controller.hpp"
#include <string>


sf::CircleShape getCircle(bool color) // true = red, false = black
{
    sf::CircleShape circle(40.f);
    circle.setOutlineThickness(3.f);
    circle.setOutlineColor(sf::Color::Yellow);

    if (color)
    {
        circle.setFillColor(sf::Color::Red);
    }
    else
    {
        circle.setFillColor(sf::Color::Black);
    }

    return circle;
}

// sf::Vertex getLine(sf::CircleShape up, sf::CircleShape down)
// {
//     return sf::Vertex(sf::Vector2f(up.getPosition().x + up.getRadius(), down.getPosition().y - down.getRadius()), sf::Color::Black);
// }


int main()
{
    Controller newController;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width - 200, sf::VideoMode::getDesktopMode().height - 200), "Data Structure Visualization", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(120);

    sf::Font font;
    font.loadFromFile("font.ttf");
    
    // circle.setPosition(350.f, 250.f); // позиция круга на экране

    // запускаем цикл обработки событий
    while (window.isOpen())
    {
        // std::cout << "window is open\n";
        if (newController.end)
        {
            window.close();
            break;
        }
        // std::cout << "end is false\n";

        bool f = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // std::cout << "event close was called \n";
                f = true;
                window.close();
                break;
            }
            // std::cout << "event close was not called \n";
        }
        // std::cout << "f check \n";
        if (f)
        {
            break;
        }
        // std::cout << "f false \n";

        window.clear(sf::Color(248, 248, 217));
        std::vector< sf::CircleShape > nodes;
        std::vector< sf::Text > nums;

        if (newController.updated)
        {
            for (auto node: newController.getter)
            {
                if (node == std::make_tuple(0, 'n', 1, 1))
                {
                    window.clear(sf::Color(248, 248, 217));
                    break;
                }

                int tier = std::get<2>(node), num = std::get<3>(node); 

                nums.push_back(sf::Text());
                nums.back().setFont(font);
                nums.back().setCharacterSize(24);
                nums.back().setFillColor(sf::Color::White);

                if (std::get<1>(node) == 'r')
                {
                    nums.back().setString(std::to_string(std::get<0>(node)));
                    nodes.push_back(getCircle(true));
                }
                else if (std::get<1>(node) == 'b')
                {
                    nums.back().setString(std::to_string(std::get<0>(node)));
                    nodes.push_back(getCircle(false));
                }

                nodes.back().setOrigin(nodes.back().getRadius(), nodes.back().getRadius());
                nodes.back().setPosition(window.getSize().x / (float)(1 << tier) * (num * 2.f - 1.f), ((tier - 1.f) * 120.f) + 80.f);
                sf::FloatRect textBounds = nums.back().getLocalBounds();
                nums.back().setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
                nums.back().setPosition(nodes.back().getPosition());

                window.draw(nodes.back());
                window.draw(nums.back());

                // для каждого узла надо нарисовать двух пустых
                sf::CircleShape up = nodes.back();

                nums.push_back(sf::Text());
                nums.back().setFont(font);
                nums.back().setCharacterSize(24);
                nums.back().setFillColor(sf::Color::White);
                nums.back().setString("NULL");
                nodes.push_back(getCircle(false));
                nodes.back().setOrigin(nodes.back().getRadius(), nodes.back().getRadius());
                nodes.back().setPosition(window.getSize().x / (float)(1 << (tier + 1)) * ((num * 2 - 1) * 2.f - 1.f), (((tier + 1) - 1.f) * 120.f) + 80.f);
                sf::FloatRect textBounds1 = nums.back().getLocalBounds();
                nums.back().setOrigin(textBounds1.left + textBounds1.width / 2.f, textBounds1.top + textBounds1.height / 2.f);
                nums.back().setPosition(nodes.back().getPosition());
                window.draw(nodes.back());
                window.draw(nums.back());

                sf::Vertex line1[] =
                {
                    sf::Vertex(sf::Vector2f(up.getPosition().x, up.getPosition().y + up.getRadius())),
                    sf::Vertex(sf::Vector2f(nodes.back().getPosition().x, nodes.back().getPosition().y - nodes.back().getRadius()))
                };
                line1[0].color = sf::Color::Black;
                line1[1].color = sf::Color::Black;
                window.draw(line1, 2, sf::Lines);

                nums.push_back(sf::Text());
                nums.back().setFont(font);
                nums.back().setCharacterSize(24);
                nums.back().setFillColor(sf::Color::White);
                nums.back().setString("NULL");
                nodes.push_back(getCircle(false));
                nodes.back().setOrigin(nodes.back().getRadius(), nodes.back().getRadius());
                nodes.back().setPosition(window.getSize().x / (float)(1 << (tier + 1)) * ((num * 2) * 2.f - 1.f), (((tier + 1) - 1.f) * 120.f) + 80.f);
                sf::FloatRect textBounds2 = nums.back().getLocalBounds();
                nums.back().setOrigin(textBounds2.left + textBounds2.width / 2.f, textBounds2.top + textBounds2.height / 2.f);
                nums.back().setPosition(nodes.back().getPosition());
                window.draw(nodes.back());
                window.draw(nums.back());

                sf::Vertex line2[] =
                {
                    sf::Vertex(sf::Vector2f(up.getPosition().x, up.getPosition().y + up.getRadius())),
                    sf::Vertex(sf::Vector2f(nodes.back().getPosition().x, nodes.back().getPosition().y - nodes.back().getRadius()))
                };
                line2[0].color = sf::Color::Black;
                line2[1].color = sf::Color::Black;
                window.draw(line2, 2, sf::Lines);

                // std::cout << std::endl << node.first << " " << node.second;
            }
        }

        window.display();

        newController.read();
    }

    return 0;
}

// -lsfml-graphics -lsfml-window -lsfml-system