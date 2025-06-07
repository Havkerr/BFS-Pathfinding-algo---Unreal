# BFS-Pathfinding-algo---Unreal
This Repo demonstrate demonstrates BFS in Unreal Engine. It uses both C++ and Blueprints for optimal performance and easier debugging.


---

## Setup Instructions

1. **Create the Tile Blueprint**
   - In `Content/Maze/`, create a new Blueprint class based on `MazeTile`, name it: `BP_MazeTile`.
   - Assign a simple cube mesh: `Tile/Cube` as the visual representation.

2. **Configure MazeRunner**
   - Add `MazeRunner.cpp` to your level.
   - In the **Details** panel of `MazeRunner`, assign:
     - `BP_MazeTile` as the Maze Tile Blueprint.

3. **Add MazeBot**
   - Place the `MazeBot` actor in the level.
   - In `MazeRunner`'s **Details** panel, assign:
     - `MazeBot` as the bot that will run the maze.

---

## How It Works

- When you **Run** the project:
  - The bot starts traversing the maze.
  - **Tile Color Codes**:
    - 🟩 **Green**: Final path to the destination
    - 🟦 **Blue**: Tiles that were visited during search
    - 🟪 **Pink**: Tiles that were not visited

---

## Customization

### Change Maze Size
- In the **Details** panel of `MazeManager`, update the maze dimensions.
- The generator will adjust accordingly.

### Change Target/Destination
- Open `MazeManager.cpp`
- Modify the 2D array `TargetLocation[][]`
  - Set the coordinates to any valid index within the maze bounds.
  - Example:
    ```cpp
    AMazeTile* EndTile = MazeGrid[][];

    ```

---

## Technologies Used
- **Unreal Engine**
- **C++**
- **Blueprints**

---

## Notes
- Make sure all required assets (like `MazeBot`, `BP_MazeTile`, etc.) are properly placed and referenced in the level.
- Ideal for learning grid-based pathfinding with real-time feedback via color-coded tiles.

---

## Author
*Shubham Anand*  


