# 24 CIPHER 
## Team 52 Members
This game is brought to you by the great minds of Team 52:
- Amos Chan               (3036xxxx36)
- Au Lok Yi               (3035xxxx54)
- Herman Leung            (3036xxxx84)
- Sean Wicaksana Faustine (3036xxxx24)
- Wong Chi Ho             (3036xxxx47)

With the help of
- Ascii Art Archive
- https://www.asciiart.eu/text-to-ascii-art

## Game Description 
24 Cipher is a terminal-based puzzle game in which players must combine 4 randomly dealt cards exactly once using basic arithmetic operations (+, −, ×, ÷) to reach 24. Each card valued as follows:
- A : 1 or 11
- Faced Cards (J, Q, K) : 10
- #Number Cards : its own #number

A **full in-game tutorial** is available when you launch the game, including practice rounds and detailed instructions! Try out the tutorial option on the homepage!

**Key Features**:
1. Multiple Difficulty Modes: Easy (only + and -), Classic (all operations), and Time Attack (speed challenge)
2. Random question generation with dynamic card system
3. Intelligent hint system with mode-specific strategies
4. Interactive tutorial with practice rounds
5. Persistent leaderboard with score history
6. Robust invalid (8+ error cases handled) and incorrect handling
7. Terminal-based UI with ncurses

## External Dependencies
Throughout the whole project, we only use 1 non-standard C++ libary:
1. **ncursesw/ncurses.h**  (pre-installed in the CS Department Servers)
   *Features Supported*:  
     - Terminal UI rendering (menus, cards, colored text)  
     - Real-time keyboard input handling  
     - Screen management for game states
       
## Coding Requirement Features
### 1. Generation of Random Events
- **Implementation**: `generate.cpp` uses `rand()` and `srand(time(0))` to:
  - Randomly select card values (1-13) and suits (♦, ♣, ♥, ♠)
  - Randomly determine Ace values (1 or 11)
  - Generate solvable card combinations
- **Supports**: Core gameplay by ensuring fresh, randomized challenges each round

### 2. Data Structures for Storing Data
- **Implementation**:
  - `vector<pair<int, int>>` stores card values and suits
  - `vector<Player_info>` manages leaderboard data
  - `stack` used in expression evaluation
  - `unordered_map` for operator precedence
- **Supports**: 
  - Card management and game state
  - Leaderboard functionality
  - Input expression parsing

### 3. Dynamic Memory Management
- **Implementation**:
  - `Player_info` struct uses dynamic arrays for score storage
  - `addScoreToPlayer()` handles array resizing when needed
  - Proper memory cleanup with `delete[]`
- **Supports**: 
  - Efficient score storage in leaderboard
  - Scalable player history tracking

### 4. File Input/Output
- **Implementation**:
  - `saveLeaderboardToFile()` writes player data to "leaderboard.txt"
  - Includes timestamp and formatted output
  - Uses `ofstream` for file operations
- **Supports**: Persistent leaderboard between game sessions

### 5. Program Codes in Multiple Files
- **Implementation**:
  - Modular design with 10+ header/source files
  - Clear separation of concerns (UI, logic, data)
- **Supports**: 
  - Maintainability and team collaboration
  - Clean code organization
- **File Structures**:
  
    |** File Name    **          |** Function   **                       |
    |------------------------|-----------------------------------|
    | 24cardgame.[h/cpp]     | Core game logic and leaderboard   |
    | displaymessage.[h/cpp] | Error and feedback messages       |
    | generate.[h/cpp]       | Card generation and solving logic |
    | takeinput.[h/cpp]      | Input processing and validation   |
    | tutorial.[h/cpp]       | Game instructions and practice    |
    | timeattackmode.[h/cpp] | Time Attack mode implementation   |
    | main.cpp               | Program entry point and menus     |

## Compilation and Execution Instructions
Follow these simple steps to set up, compile, and enjoy the game on the CS Academy Servers:
1. **Download the Project ZIP:**
   - Open the github repository “TEAM52-24CARDSGAME”
   - Click the green “<> Code ▼” button
   - Select "Local"  → "Download ZIP"
   - Make sure you extract the ZIP in your local memory first
     
2. **Transfer Extracted Files:**
   - Open FileZilla (or any SFTP client).
     * Connect using:
         Host: `sftp://academy.cs.hku.hk`
         Username: `your_cs_account`
         Password: `your_cs_account_password`
   - Upload the extracted project folder to your server's home directory
     
3. **Login to the server:**
   - Open Terminal (macOS/Linux) or PowerShell (Windows).
   - SSH into the server:
     * ssh your_cs_account@gatekeeper.cs.hku.hk
     * ssh your_cs_account@academy11.cs.hku.hk
     
4. **Compile and run**:
   - Navigate to the Project Directory, and then:
      ```bash
      $ make && make run
      ```
5. Last but not least, **don’t forget to enjoy!**

## Ncurses Download (if necessary) 
If you're planning on running the game on your local Linux/Mac, you might need to download the ncurses library first. Please kindly refer to the steps below:
  ```bash
  $ sudo apt install libncurses5-dev  # Ubuntu/Debian
  $ brew install ncurses              # MacOS
  ```
