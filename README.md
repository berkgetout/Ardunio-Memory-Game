**Project: Memory Game on Arduino with LCD Display**

**Project Description:**
This project aims to develop a memory game using Arduino and an LCD display. Players will attempt to progress through levels by recalling and entering random numbers and symbols shown on the screen in the correct sequence. If they enter the sequence incorrectly, their lives decrease, and the game continues until lives (3) run out, at which point the game ends.

**Components:**
- Main Menu: Includes options to "Play" and access "Settings".
- Settings Menu: Allows selection of difficulty levels.
- Game Screen: Displays random numbers and arrow symbols during gameplay.
- Gameplay: Players must correctly input the displayed numbers and symbols in sequence. Incorrect inputs reduce the remaining lives, and the game continues until lives are exhausted. When lives reach zero, the game ends, and the restart menu is displayed.

**Libraries and Variable Definitions:**
- Uses the LiquidCrystal library for controlling the LCD display.
- Defines different symbols (heart, right arrow, left arrow).
- Defines variables such as lives, score, difficulty level, etc.

**Functions:**
- `readKey()`: Determines which button is pressed based on the analog input read.
- `printHearts()`: Displays the remaining lives using a heart symbol on the screen.
- `setup()`: Initializes settings and displays the main menu.
- `displayMenu()`, `handleMenu()`: Manages the main menu and its controls.
- `displaySettings()`, `selectDifficulty()`: Manages the settings menu and difficulty selection.
- `startGame()`: Initiates the game and calls necessary functions.
- `generateSequence()`, `displaySequence()`: Generates and displays a random sequence of numbers and symbols.
- `getUserInput()`, `checkUserInput()`: Collects user input and verifies its correctness.
- `gameOver()`, `restartMenu()`, `resetGame()`: Handles game ending, restart menu display, and game reset operations.

**Material List:**
- 1 x Arduino Uno
- 1 x 16x2 LCD screen
- 1 x LCD keypad shield
