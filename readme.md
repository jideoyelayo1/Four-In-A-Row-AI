# FourInARow_minimax

## Description
FourInARow_minimax is a C++ implementation of the classic game Connect Four. The project features a two-player mode where you can play against an AI opponent that utilizes the Minimax algorithm with Alpha-Beta pruning for intelligent moves.

## Project Files
- **FourInARow_minimax.cpp**: This file contains the C++ source code for the Connect Four game, including the game logic and AI implementation.
- **FourInARow_minimax.sln**: This is the Visual Studio solution file for the project. Double-click on it to open your project in Visual Studio.
- **README.md**: This documentation file.
- ... (Other project files and resources, if applicable)

## Getting Started
Follow these steps to run the game:

1. Compile the C++ code using a C++ compiler (e.g., g++):
   ```bash
   g++ -o connect_four FourInARow_minimax.cpp
   ```

2. Run the compiled executable:
   ```bash
   ./connect_four
   ```

3. Choose to play against the AI or another human player. Make your move by entering the column number where you want to place your piece.

4. The AI will take its turn automatically. The game continues until one player wins or the board is filled.

5. To exit the game at any time, enter '9'.

## Customization
- Adjust the AI's maximum depth of search by modifying the `MAX_AI_DEPTH` variable in the `Game` class for a more challenging or quicker AI.
- Modify the evaluation function in the `evaluate` and `evaluateLine` methods to enhance the AI's performance and strategy.

## Project Structure
- `Player`: Represents a player with a name and a number (1 for the user and 2 for the AI).
- `Game`: Contains the game logic, board state, and functions for playing the game, including AI moves using the Minimax algorithm with Alpha-Beta pruning.

## Enjoy Your Game!
Have fun playing Connect Four against your AI opponent! If you encounter any issues or have questions, feel free to seek assistance.
