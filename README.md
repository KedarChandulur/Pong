# Pong using C++ and SFML

A classic Pong game built using C++ and the SFML library. 

**Tools used**: Visual Studio Community 2019 / 2022, CMake, SFML Library (v2.6.2).

---

## How to Build and Run the Game Locally

This project uses **CMake** and a **Git Submodule** to manage the SFML dependency. This makes it incredibly easy to compile the game on any machine without needing to manually download or link external libraries.

### Clone the Repository
Because SFML is included as a Git submodule, you must clone the repository recursively to pull down the SFML files at the same time:

```bash
git clone --recurse-submodules https://github.com/KedarChandulur/Pong
```

If you already cloned the repo normally, run the below command inside the project folder to fetch SFML

```bash
git submodule update --init --recursive
```

### After the Depenencies setup:
After SFML setup is successful, Build the project based on the IDE you are using.

## Game Files can be found here:
https://drive.google.com/drive/folders/1ZCkskUGtOwU5iOyZXaubolIBeso4dU0h?usp=sharing

**Game Instructions(Keybindings)**:
- **Escape**: Use this keybinding to go from in game -> main menu and/or Quit the application from main menu.
- **Enter**: Use this keybinding to select elements in main menu or restart(game) menu.
- **C**: Use this keybinding to switch from player vs cpu to player vs player mode or vice versa.
- **Number 1, 2, 3, 4**: Use these keybindings to change Cpu(AI) difficulty.
- **Arrow Up and/or down[Menu Specific]**: Use these keybindings to naviagate between text elements in main menu or restart(game) menu.
- **Arrow Up and/or down[In Game Specific]**: Use these keybindings to move Right(Player - 2's) Paddle, while in player vs player mode.
- **W and/or S**: Use these keybindings to move Left(Player - 1's) Paddle, mode won't have any affect on Left(Player - 1's) Paddle.

**Game Screenshots**:
![MainMenu_Screen](https://user-images.githubusercontent.com/47148900/149375575-63be9292-eb28-47ca-b640-6fe811a4cbe1.png)
![InGame_Screen](https://user-images.githubusercontent.com/47148900/149375604-ac69fbd6-e724-40b8-a7e6-b8ed989d3d84.png)
![RestartMenu_Screen](https://user-images.githubusercontent.com/47148900/149375622-2b536b4d-88ea-4e94-8a96-157f86bed898.png)
