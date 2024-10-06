# MinerGuild-Pathfinder-Management-System
# Project Overview
This project, titled Miner's Guild Pathfinder Management System, was developed as part of my first semester coursework for the "Algorithm and Programming" class. The project uses the C programming language to create an application that allows the Miner's Guild to manage the mining maps, find the shortest paths, and determine the number of possible routes to mine safely. The program involves handling multiple map files, processing map data, and solving pathfinding problems through recursive methods.

# Case Description
The Miner's Guild is an organization where miners gather to sell mining products and explore new mines. When a new mine is discovered, a guild mapper is tasked with mapping the layout of the mine. Once the map is complete, the guild must determine the shortest path from the entry point to the abundant mining location (represented by 'X'). This requires calculating the minimum steps from the entry ('0') to the mining location and the number of possible paths available.

My task was to create an application to help manage these maps, which are stored in .dig files, and facilitate the guild in analyzing the mining layout efficiently.

# Objectives
- Implement a management system for the mining maps - This involves developing a program that can list, add, and save the progress of discovered maps.
- Find the shortest path to the mining site - Using recursive methods, the program calculates the minimum number of steps required to reach the mining point and determines how many different possible paths exist.
- Create a user-friendly interface for the admin to manage, sort, and discover new mining maps.

# Project Features
The application consists of several features:
1. Main Menu: The user is provided with a menu to select from the following options:
- Show Discovered Map List
- Discover New Map
- Exit & Save Progress

2. Map List Management:
- The application allows users to view all discovered maps and display details such as the map's filename, minimum steps, and possible path count. The list can be sorted by these criteria in ascending or descending order.

3. Pathfinding for Maps:
- When discovering a new map, the user inputs the name of a .dig file that represents the mine layout.
- The map file contains entries representing walls (#), starting points (0), and safe mining points (X). The program calculates the shortest path using a recursive algorithm that only allows up, down, left, and right movements (no diagonal moves).
- If the map file meets the requirements, the program outputs the calculated minimum steps and possible paths, then saves the processed map.

4. Saving and Loading Progress:
- The application keeps track of the discovered maps and saves them to a file (map-List.txt) to ensure progress is not lost and can be resumed when needed.

# Implementation Details
- Recursive Pathfinding: The core algorithm uses recursion to explore all possible paths and find the shortest route from the starting point to the mining location ('X'). It also counts the number of distinct paths with the minimum distance.
- File Handling: The application makes extensive use of file handling to manage the .dig files, read map layouts, and store progress.
- Data Structures: Structures (struct) are used to hold map information such as dimensions, file locations, start and end positions, and pathfinding results.

# Tools and Technologies Used
- Language: C Programming
- Libraries: Standard C libraries such as stdio.h, stdlib.h, string.h

# Challenges
- Recursive Complexity: Implementing a recursive solution to find all possible paths while avoiding infinite loops required careful handling of visited nodes and distance calculations.
- Map Layout Validation: Ensuring that the user inputs a valid .dig file and that the map meets all required conditions was a key challenge that involved error handling and verification processes.

# Conclusion
The Miner's Guild Pathfinder Management System successfully implements a solution for the Miner's Guild to manage mining maps and determine the optimal paths to reach valuable mining locations. This project enhanced my understanding of recursive algorithms, file handling, and structuring user-friendly programs in C. It also demonstrated the importance of efficient data handling and algorithmic approaches in solving real-world problems. The project showcases a practical application of pathfinding techniques and file management, providing a valuable experience in algorithm development.
