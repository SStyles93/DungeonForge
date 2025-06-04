#include "Generator.hpp"
#include "Map.hpp"
#include "Renderer.hpp"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	//========================================================================================================================

	SDL_Init(SDL_INIT_VIDEO);

	// SDL GL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	//========================================================================================================================

	SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window* window = SDL_CreateWindow(
		"DungeonForge",
		1280,
		720,
		window_flags);
	if (window == nullptr)
	{
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return -1;
	}

	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if (gl_context == nullptr)
	{
		printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
		return -1;
	}
	SDL_GL_SetSwapInterval(1); // Enable vsync

	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_ShowWindow(window);

	//========================================================================================================================

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Window Cocking

	// Setup Dear ImGui style
	//ImGui::StyleColorsLight();
	ImGui::StyleColorsDark();

	//Init Windows with ImGui
	ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 130");

	//========================================================================================================================

	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, "DungeonForge");
	Renderer renderer(sdlRenderer);
	Map map(0, 0);
	Generator generator;

	bool running = true;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
				running = false;

			ImGui_ImplSDL3_ProcessEvent(&event);
		}

		
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//========================================================================================================================


		glDrawArrays(GL_TRIANGLES, 0, 6);
		//renderer.RenderMap(map);

		//========================================================================================================================

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		//========================================================================================================================

		// ImGui window
		ImGui::Begin("Dungeon Controls");
		if (ImGui::Button("Generate Dungeon"))
		{
			map = Map(50, 50);
			generator.Generate(map);
		}
		ImGui::Text("Map Size");
		int mapSize[2]{ map.GetWidth(), map.GetHeight() };
		ImGui::InputInt2("", mapSize, 0);
		//ImGui::SliderFloat2("", mapSize, 0.0f, 0.0f, "%.3f", 0);
		ImGui::End();

		//========================================================================================================================

		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	//========================================================================================================================

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	//Destroy
	SDL_DestroyRenderer(sdlRenderer);
	SDL_GL_DestroyContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
