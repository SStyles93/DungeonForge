#include "Generator.hpp"
#include "Map.hpp"
#include "Renderer.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>


int main()
{	
    //========================================WINDOW INIT=====================================================
    // create the window

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Forge");
    if (!ImGui::SFML::Init(window)) return 1;

    //=========================================PROGRAM INIT====================================================
    // run the program as long as the window is open
    
    Generator generator;
    Map map(50, 50);
    generator.Perlin(map);  //  Generate dungeon on start
    Renderer renderer;

    sf::Clock deltaClock;
    //======================================LOGIC LOOP=======================================================
    while (window.isOpen())
    {
        //======================================EVENT LOOP=======================================================

        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            /*else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
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
                    case sf::Keyboard::Scancode::C:
                        generator.CellularAutomata(map, 45, 5);
                        break;
                    case sf::Keyboard::Scancode::W:
                        generator.WaveFunctionCollapse(map);
                        break;
                }
            }*/
        }
      
        //====================================IMGUI RENDER=========================================================
        
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Map Generator");

        static int selected_generator = -1;
        const char* names[] = { "Perlin", "Drunkard's Walk", "Binary Space Partitioning", "Cellular Automata", "Wave Function Collapse" };

        if (ImGui::Button("Select the Generator"))
            ImGui::OpenPopup("Generator_Popup");
        ImGui::SameLine();
        ImGui::TextUnformatted(selected_generator == -1 ? "<None>" : names[selected_generator]);
        if (ImGui::BeginPopup("Generator_Popup"))
        {
            ImGui::SeparatorText("Generators");
            for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                if (ImGui::Selectable(names[i]))
                    selected_generator = i;
            ImGui::EndPopup();
        }
        static int show_error_message = 0;
        if (ImGui::Button("Generate"))
        {
            switch (selected_generator)
            {
                case 0:
                    generator.Perlin(map);
                    break;
                case 1:
                    generator.DrunkardsWalk(map);
                    break;
                case 2:
                    generator.BSP(map);
                    break;
                case 3:
                    generator.CellularAutomata(map, 45, 5);
                    break;
                case 4:
                    generator.WaveFunctionCollapse(map);
                    break;
                default:
                    show_error_message = 1;
                    printf("Trying to generate map without any generator selected");
                    break;
            }
        }
        if(show_error_message && selected_generator == -1)
        ImGui::TextColored(ImVec4(sf::Color::Red), "No generator was selected");

        ImGui::End();

        //ImGui::ShowDemoWindow();
        //========================================RENDER=====================================================

        window.clear(sf::Color::Black);

        renderer.render(window, map);

        ImGui::SFML::Render(window);
        window.display();

    }
    //========================================SHUTDOWN=====================================================

    ImGui::SFML::Shutdown();
	return 0;
}
