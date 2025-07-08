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

	Generator generator(49, 49);
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
						generator.generate();
						break;
				}
			}
		}

		//====================================IMGUI RENDER=========================================================

		ImGui::SFML::Update(window, deltaClock.restart());

		// Main Window
		ImGui::Begin("Map Generator");

		// Map Size
		static int map_size[2] = { generator.getMap().getWidth(), generator.getMap().getHeight() };
		ImGui::Text("Map Size");
		ImGui::InputInt2("", map_size);
		if (map_size[0] < 0) map_size[0] = 0;
		if (map_size[1] < 0) map_size[1] = 0;
		if (generator.getMap().getWidth() != map_size[0] || generator.getMap().getHeight() != map_size[1])
		{
			Map map(map_size[0], map_size[1]);
			generator.setMap(map);
		}

		//Seed selection
		static int seed = -1;
		ImGui::InputInt("Seed", &seed);
		if (seed < -1) seed = -1;
		if (seed > INT32_MAX) seed = INT32_MAX;
		generator.setSeed(seed);


		static int selected_generator = 0;
		const char* names[] = { "Binary Space Partitioning", "Cellular Automata", "Drunkard's Walk", "Perlin" /*,"Wave Function Collapse" */ };

		//Dropdown List with Popup window
		if (ImGui::Button("Select the Generator"))
			ImGui::OpenPopup("Generator_Popup");
		if (ImGui::BeginPopup("Generator_Popup"))
		{
			ImGui::SeparatorText("Generators");
			for (int i = 0; i < IM_ARRAYSIZE(names); i++)
				if (ImGui::Selectable(names[i]))
				{
					generator.setAlgorithm((AlgorithmType)i);
					selected_generator = i;
				}
			ImGui::EndPopup();
		}

		// Name Label
		ImGui::TextColored(ImVec4(sf::Color::Green), selected_generator == -1 ? "<None>" : names[selected_generator]);

		static int roomEdge = 10;
		static int fillProbability = 45;
		static int iterations = 5;

		switch (selected_generator)
		{
			case 0:
				ImGui::InputInt("Room Edge", &roomEdge);
				generator.setMaxRoomEdgeSize(roomEdge);
				break;
			case 1:
				ImGui::InputInt("Fill Probability", &fillProbability);
				generator.setFillProbability(fillProbability);

				ImGui::InputInt("Iterations", &iterations);
				generator.setIterations(iterations);
				break;
			default:
				break;
		}


		// Generator Button
		static int show_error_message = 0;
		if (ImGui::Button("Generate"))
		{
			generator.generate();
		}
		if (show_error_message && selected_generator == -1)
			ImGui::TextColored(ImVec4(sf::Color::Red), "No generator was selected");

		ImGui::End();
		//ImGui::ShowDemoWindow();
		//========================================RENDER=====================================================

		window.clear(sf::Color::Black);
		//map = generator.GetMap();
		renderer.render(window, generator.getMap());

		ImGui::SFML::Render(window);
		window.display();

	}
	//========================================SHUTDOWN=====================================================

	ImGui::SFML::Shutdown();
	return 0;
}
