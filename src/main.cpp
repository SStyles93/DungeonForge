#include "Generator.hpp"
#include "Map.hpp"
#include "Renderer.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <cassert>

int main()
{
	//========================================WINDOW INIT=====================================================
	// create the window

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Dungeon Forge");
	if (!ImGui::SFML::Init(window)) return 1;

	//=========================================PROGRAM INIT====================================================
	// run the program as long as the window is open

	Map map(50,50);
	Generator generator(map);
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
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				switch (keyPressed->scancode)
				{
					case sf::Keyboard::Scancode::Backspace:
					case sf::Keyboard::Scancode::Enter:
						generator.Generate();
						break;
				}
			}
		}

		//====================================IMGUI RENDER=========================================================

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Map Generator");

		static int map_size[2] = { generator.GetMap().GetWidth(), generator.GetMap().GetHeight()};
		ImGui::Text("Map Size");
		ImGui::InputInt2("", map_size);
		if (map_size[0] < 0) map_size[0] = 0;
		if (map_size[1] < 0) map_size[1] = 0;
		if (generator.GetMap().GetWidth() != map_size[0] || generator.GetMap().GetHeight() != map_size[1])
		{
			Map map(map_size[0], map_size[1]);
			generator.SetMap(map);
		}



		static int selected_generator = 0;
		const char* names[] = { "Perlin", "Drunkard's Walk", "Binary Space Partitioning", "Cellular Automata", "Wave Function Collapse" };

		if (ImGui::Button("Select the Generator"))
			ImGui::OpenPopup("Generator_Popup");
		//ImGui::SameLine();
		//ImGui::TextUnformatted();
		ImGui::TextColored(ImVec4(sf::Color::Green), selected_generator == -1 ? "<None>" : names[selected_generator]);
		if (ImGui::BeginPopup("Generator_Popup"))
		{
			ImGui::SeparatorText("Generators");
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
				{
					generator.SetAlgorithm((AlgorithmType)i);
					selected_generator = i;
				}
			ImGui::EndPopup();
		}
		static int show_error_message = 0;
		if (ImGui::Button("Generate"))
		{
			generator.Generate();
		}
		if (show_error_message && selected_generator == -1)
			ImGui::TextColored(ImVec4(sf::Color::Red), "No generator was selected");

		ImGui::End();

		//ImGui::ShowDemoWindow();
		//========================================RENDER=====================================================

		window.clear(sf::Color::Black);
		map = generator.GetMap();
		renderer.render(window, map);

		ImGui::SFML::Render(window);
		window.display();

	}
	//========================================SHUTDOWN=====================================================

	ImGui::SFML::Shutdown();
	return 0;
}
