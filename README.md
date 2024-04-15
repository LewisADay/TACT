# TACT
Text Adventure Creation Tool, A tool, for creating, Text Adventure Games (TAGs).

## Introductions
This repository is an exercise set to me by a prospective employer.

The task is to create an engine or other tool for the creation of text adventure style games, hence I present TACT, the Text Adventure Creation Tool.

I use [Walnut](https://github.com/StudioCherno/Walnut) as the base for this operation, itself a wrapper around [Dear ImGui](https://github.com/ocornut/imgui), making use of the GLFW + Vulkan backend. I use ImGui due to its simplicity and the velocity it lends to development. Walnut is a well supported and documented wrapper for ImGui, which reduces code duplication and boilerplate requirements for ImGUI. Further I make use of [imnodes](https://github.com/Nelarius/imnodes) to power the node-based editor.

## Installation

### Requirements
- Windows 11. Since Walnut is a Windows only (for now) wrapper for ImGui.
- [Visual Studio 2022](https://visualstudio.com)
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows)

### Getting Started
We utilise premake to generate solution files, whose use is conveniently abstracted to `Setup.bat`. Once you've cloned, run `Setup.bat` to generate Visual Studio 2022 solution/project files. Once you've opened the solution, you can run the TACT project to launch the creation tool.

## Usage Instructions

For full usage instructions please see the [Usage Guide](USAGE.md)

## Roadmap

- [ ] Saving/Loading
  - [ ] Serialisation/Deserialisation library chosen/written
  - [ ] Drag and drop save files onto application to load
- [ ] TAG (Game) Generation
  - [ ] Output format chosen
  - [ ] Format generation
- [ ] Be able to flip nodes to have inputs on the right and outputs on the left
  - [ ] A colour based demarkation of what side is input and output
- [ ] Zoom in and out in the editor
- [ ] Variable support
  - [ ] Support nodes outputing values and being input to other nodes, e.g. player health
- [ ] More node types
  - [ ] Logic node, apply logical statements to flow control, e.g. do this path when the player has more gold than x, and this path when they have less
- [ ] General styling UI/UX improvements - it's functional as is, but could look a lot nicer

## 3rd party libaries
- [imnodes](https://github.com/Nelarius/imnodes)
- [Walnut](https://github.com/StudioCherno/Walnut)

Which itself contains

- [Dear ImGui](https://github.com/ocornut/imgui)
- [GLFW](https://github.com/glfw/glfw)
- [stb_image](https://github.com/nothings/stb)
- [GLM](https://github.com/g-truc/glm)
