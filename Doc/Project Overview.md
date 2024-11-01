### Project Overview

Develop a command-line program to implement a Tetris game. The project uses a state machine to manage transitions between various game states. The state machine leverages C++ polymorphism, with each state handled by a dedicated class. The core game logic of Tetris is implemented in `PlayState`, which interacts with the `Cube` and `Map` classes.

### Implementation Details

#### 2.1 StateMachine and BaseState

The `StateMachine` is a class with a continuous loop in the `main()` function that repeatedly calls the `StateMachine`’s `update()` and `render()` functions. It also repeatedly checks whether the `end` attribute of the `StateMachine` is `true`; if it is, the loop breaks, and the game ends.

**StateMachine Member Functions:**
- `void change()`: Switches the game state
- `void update()`: Updates game data
- `void render()`: Renders and displays the game content on the screen
- `void stop()`: Stops the state machine by setting the `end` boolean attribute to `true`
- `bool exit()`: Checks if the game should exit and returns the value of `end`

**State Transition Principle:**
1. `StateMachine` is used in conjunction with the `BaseState` class.
2. `BaseState` is the base class for all state classes, and it defines five virtual functions: `enter()` (state entry function), `bgrender()` (background render function), `update()` (game data update function), `render()` (real-time render function), and `exit()` (state exit function). Each function is empty by default. New states can be added by inheriting from `BaseState` and overriding some of these functions as needed for `StateMachine` to call.
3. `StateMachine` includes a `BaseState **list` and an `int current` attribute to maintain an array of `BaseState*`. Each pointer in the array points to a state class derived from `BaseState`. `StateMachine` member functions call the appropriate functions of `list[current]`, and different derived state classes can be accessed by changing the value of `current`.

#### 2.2 Five Game States

##### 2.2.1 StartState
**Main Functionality:** Displays the start screen, showing the game title *Tetris*. Players press the space bar to toggle options and press Enter to either start the game or view the high score board.

**Main Member Functions:**
- `void update()`: Checks for user input; pressing space toggles options, and pressing Enter calls the `StateMachine`’s `change()` function to switch to either `PlayState`, `HighScoreState`, or `EndState`, based on the selected option.
- `void bgrender()`: Renders the background, displaying the game title and the options "Start" and "HighScore".
- `void render()`: Updates and displays an arrow ("=>") next to the selected option based on the option toggled in `update()`.

##### 2.2.2 PlayState
**Main Functionality:** Implements the core logic of Tetris. Random blocks appear that can be rotated, moved left and right, and made to fall faster. Once a row is complete, it clears. The score is updated in real-time, and the next block is previewed. The game also supports pausing.

**Core Game Logic:**
1. `PlayState` works in conjunction with the `Cube` and `Map` classes (`Cube` handles the current falling block, while `Map` manages blocks that have landed).
2. `PlayState` maintains two `Cube*` pointers: `Cube *current` for the falling block and `Cube *next` for the next block. Once the block pointed to by `current` lands, it points to `next`, and `next` is updated with a new randomly generated block.
3. After a block lands, `PlayState` calls the `Map`’s `addCube` method to record the landed block’s position.
4. The speed of falling blocks is controlled by adjusting the `speed` parameter in the `Sleep(speed)` function.

**Main Member Functions:**
- `void enter()`: Called by `StateMachine` when entering `PlayState`, it initializes game data, such as resetting the player’s score (stored in the `score` variable) to zero.
- `void update()`: Uses `Cube` and `Map` member functions to implement pause functionality and update game data in real-time. Player input is passed to `Cube` functions, and pausing is achieved by leveraging `getch()`’s blocking feature to pause on pressing the space bar.
- `void render()`: Displays the game interface, including blocks, player score, and the upcoming block.

##### 2.2.3 GameoverState
**Main Functionality:** Displays the player’s final score and rank after the game ends. It prompts the player to enter their name and then transitions to `HighScoreState`.

**Core Principle:** 
The main challenge is passing data between states. `PlayState` needs to pass the player’s score to `GameoverState`, and `GameoverState` needs to pass the player’s name and score to `HighScoreState`. This is achieved by overloading the `enter()` function to accept a `string enterParams` parameter, which records transition data. Different pieces of information are separated by ‘&’, such as “name&score” for name-score pairs.

##### 2.2.4 HighScoreState
**Main Functionality:** Displays the top ten high scores, including player names and scores.

**Core Principle:**
1. To retain the high score list, `HighScoreState` writes the scores to a local file, `highscore.lst`, within the game’s directory. Each time the game is launched, it reads data from `highscore.lst`.
2. High score rules:
   - Only the highest score for each player name is saved.
   - Only the top ten scores are displayed.
   - Players with identical scores are ordered alphabetically.
3. A `map` and `vector` are used to prevent duplicate names and to display scores in sorted order. The `vector` is sorted using `sort()` to rank the high scores.

##### 2.2.5 EndState

**Main Functionality:** A transition screen for game exit. The window closes after a three-second countdown.

**Core Principle:** The countdown is implemented using the `Sleep` function for timing. The countdown effect is achieved by repeatedly printing numbers and using `\b` to backspace and overwrite the previous number.

![](C:\Users\Harry\Desktop\Github\Img\StateTransfer.png)

**Note:** "->" indicates that the state at the start of the arrow can transition to the state the arrow points to. `StartState` is the starting point of the game. The states `StartState`, `PlayState`, and `HighScoreState` can all transition directly to `EndState` when the player presses 'q' to end the game.



### 2.3 `Cube` Class and `Map` Class

#### 2.3.1 `Cube` Class
**Main Functionality:** Manages the falling blocks, including rendering, updating information, rotating, falling, and collision detection.

**Core Principles:**
1. **Block Shape and Color:** A global variable `shapesheet` is used to store shape data for the blocks. When displaying a block, `Cube` retrieves the shape information from `shapesheet`. Each block has an `(x, y)` coordinate, and `shapesheet` stores the relative coordinates of the four squares that make up the block, allowing the shape to be defined. Each new block has a randomly generated shape and color.
2. **Collision Detection:** Each block is composed of four smaller squares, and collision detection checks each square individually to see if it collides with another object.
3. **Movement, Falling, and Rotation:** `Cube` maintains two sets of `(x, y, rotation)` data (coordinates and rotation angle). When the player rotates or moves the block, the new `(x, y, rotation)` is updated while the previous values are kept in memory. If a collision occurs, the values revert to the old `(x, y, rotation)`; if not, the new values remain. When displaying the block, the block at the old coordinates is erased by printing spaces, and the new block is printed at the updated coordinates. This achieves a seamless visual update on the screen.  
   - **Note:** There’s an asynchronous update issue here, as the block automatically falls one step after a set time interval. During this interval, the block can be moved and rotated multiple times. To handle this, the program repeatedly checks user input in a loop before each fall step.

#### 2.3.2 `Map` Class
**Main Functionality:** Manages blocks that have already landed.

**Core Principles:**
1. After each block lands, the `Map` class’s `addCube` method records the `Cube` data in a 2D array. It then checks if any rows are fully occupied. Once all full rows are detected, the program clears these rows and shifts the rows above downwards. The number of cleared rows is relayed to `PlayState`, where it is used to update the player's score.
2. The `Map` class has a `maxh` attribute that records the maximum height of the block stack. When this parameter exceeds a certain value, `PlayState` transitions to `GameoverState`, ending the game.