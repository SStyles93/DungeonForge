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

	//Map map(50,50);
	Generator m_randomGenerator(50,50);
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
						m_randomGenerator.generate();
						break;
				}
			}
		}

		//====================================IMGUI RENDER=========================================================

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Map Generator");

		static int map_size[2] = { m_randomGenerator.getMap().getWidth(), m_randomGenerator.getMap().getHeight()};
		ImGui::Text("Map Size");
		ImGui::InputInt2("", map_size);
		if (map_size[0] < 0) map_size[0] = 0;
		if (map_size[1] < 0) map_size[1] = 0;
		if (m_randomGenerator.getMap().getWidth() != map_size[0] || m_randomGenerator.getMap().getHeight() != map_size[1])
		{
			Map map(map_size[0], map_size[1]);
			m_randomGenerator.getMap();
		}
		ImGui::Text("Seed");
		int *seed = 0;
		ImGui::InputInt("", seed);
		if (*seed < -1) *seed = -1;
		if (*seed > INT32_MAX) *seed = INT32_MAX;



		static int selected_generator = 0;
		const char* names[] = { "Binary Space Partitioning", "Cellular Automata", "Drunkard's Walk", "Perlin" /*,"Wave Function Collapse" */};

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
					m_randomGenerator.setAlgorithm((AlgorithmType)i);
					selected_generator = i;
				}
			ImGui::EndPopup();
		}
		static int show_error_message = 0;
		if (ImGui::Button("Generate"))
		{
			m_randomGenerator.generate();
		}
		if (show_error_message && selected_generator == -1)
			ImGui::TextColored(ImVec4(sf::Color::Red), "No generator was selected");

		ImGui::End();

		//ImGui::ShowDemoWindow();
		//========================================RENDER=====================================================

		window.clear(sf::Color::Black);
		//map = generator.GetMap();
		renderer.render(window, m_randomGenerator.getMap());

		ImGui::SFML::Render(window);
		window.display();

	}
	//========================================SHUTDOWN=====================================================

	ImGui::SFML::Shutdown();
	return 0;
}
