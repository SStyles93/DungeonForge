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
    //if (!ImGui::SFML::Init(window)) return 1;

    //=============================================================================================
    // run the program as long as the window is open
    
    Generator generator;
    Map map(50, 50);
    generator.Perlin(map);  //  Generate dungeon on start
    Renderer renderer;

    //=============================================================================================
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        //=============================================================================================
        // check all the window's events that were triggered since the last iteration of the loop

        while (const std::optional event = window.pollEvent())
        {
            //ImGui::SFML::ProcessEvent(window, *event);

            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->scancode)
                {
                    case sf::Keyboard::Scancode::P:
                        generator.Perlin(map);
                        break;
                    case sf::Keyboard::Scancode::D:
                        generator.DrunkardsWalk(map);
                        break;
                    case sf::Keyboard::Scancode::B:
                        generator.BSP(map);
                        break;
                }
            }
        }
      
        //=============================================================================================
        
       /* ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();*/

        //=============================================================================================

        window.clear(sf::Color::Black);

        renderer.render(window, map);

        //ImGui::SFML::Render(window);
        window.display();

        //=============================================================================================
    }

    //ImGui::SFML::Shutdown();
	return 0;
}
