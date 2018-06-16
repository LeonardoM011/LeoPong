#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

#include "renderer/Renderer.h"
#include "window/Window.h"
#include "buffer/VertexBufferLayout.h"
#include "texture/Texture.h"
#include "object/Object.h"
#include "object/Player.h"
#include "object/Slab.h"

int main(int argc, char **argv) {
	// Creating Window
	Window window("LeoPong V0.0.1.0", 640, 480);
	{
		// Printing our latest OpenGL Version
		std::cout << glGetString(GL_VERSION) << std::endl;

		// Creating our Renderer Object
		Renderer renderer;
		renderer.ChangeBackgroundColor(0.0f, 0.0f, 0.0f);

		Camera camera(0.0f, 0.0f);

		// Creating our Shader
		Shader shader("res/shaders/Basic.shader");

		std::vector<Slab*> slabBuffer;
		for (int i = 0; i < 41; i++) {
			slabBuffer.push_back(new Slab(0.0f, -1.0f + (0.05f * i), 0.01f, 0.05f, shader, renderer, camera));
		}

		Player player(-0.8f, 0.0f, 0.04f, 0.20f, shader, renderer, camera);
		Player enemy(0.8f, 0.0f, 0.04f, 0.20f, shader, renderer, camera);
		enemy.BindKey(Bind::MOVEUP, GLFW_KEY_UP);
		enemy.BindKey(Bind::MOVEDOWN, GLFW_KEY_DOWN);

		while (!window.ShouldClose()) {
			window.Update();
			double Delta = window.GetDelta();

			// Flush Depth and Color Buffer
			renderer.Clear();


			player.Draw(Delta);
			enemy.Draw(Delta);
			for (auto const &x : slabBuffer) {
				x->Draw();
			}

			window.Swap();
		}
		shader.Delete();
	}
	// Terminating Window
	window.Terminate();
    return 0;
}
