#include "Generator.hpp"
#include "Map.hpp"
#include "Renderer.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>


int main()
{	
    //=============================================================================================
    // create the window

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Forge");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    if (!ImGui::SFML::Init(window))
        return -1;

    //=============================================================================================
    // run the program as long as the window is open
    
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        //=============================================================================================
        // check all the window's events that were triggered since the last iteration of the loop

        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        //=============================================================================================

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        //=============================================================================================
        // clear the window with black color
        
        window.clear(sf::Color::Black);

        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        window.draw(shape);
        ImGui::SFML::Render(window);
        // end the current frame
        window.display();

        //=============================================================================================
    }

    ImGui::SFML::Shutdown();
	return 0;
}
