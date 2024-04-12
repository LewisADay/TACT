# TACT
Text Adventure Creation Tool, A tool, for creating, text adventure games

## Introductions
This repository is designed to meet the criteria of an exercise set to me by a prospective employer, which was required to be available as a public GitHub repository, so here it is.

The task is to create an engine or other tool for the creation of text adventure style games, hence I present TACT, the Text Adventure Creation Tool.

I have used [Walnut](https://github.com/StudioCherno/Walnut) as the base for this operation, which is itself a wrapper around [Dear ImGui](https://github.com/ocornut/imgui), making use of the GLFW + Vulkan backend. I have elected to use ImGui due to its simplicity and the velocity it lends to development, I don't wish to waste a long time creating my own UI system from scratch, that would be sufficient work on its own. Walnut was a natural choice therefore, as it is basically ImGui with less steps, which allowed me to get into the meat of the problem quite quickly.

Since Walnut is a Windows only wrapper for ImGui, you will require a Windows 11 environment.

## Requirements
- [Visual Studio 2022](https://visualstudio.com) (not strictly required, however included setup scripts only support this)
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows) (preferably a recent version)

## Getting Started
Due to the heavy reliance on [Walnut](https://github.com/StudioCherno/Walnut) we borrow it's setup procedure.
Once you've cloned, run `Setup.bat` to generate Visual Studio 2022 solution/project files. Once you've opened the solution, you can run the TACT project to launch the creation tool.

### 3rd party libaries
- [Walnut](https://github.com/StudioCherno/Walnut)

Which itself contains

- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)
- [GLM](https://github.com/g-truc/glm)
