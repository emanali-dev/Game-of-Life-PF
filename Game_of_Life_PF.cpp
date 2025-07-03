
#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <ctime>   

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

using namespace std;


const int rows = 15;
const int cols = 15;

void makegrid(int grid[][cols]) //to make the grid of the generation 0
 {
    srand(time(nullptr));   //random number generator
    for (int i = 0; i < rows; i++)
     {
        for (int j = 0; j < cols; j++)
         {
            grid[i][j] = rand() % 2;    
        }
    }
}

void printGrid(const int grid[][cols])  //to print the grid of generation 0
 {
    cout << "\t\t\tGeneration 0: " << endl;
    for (int i = 0; i < rows; i++) 
    {
        // Print horizontal line before each row
        for (int j = 0; j < cols; j++)

        cout << BLUE << "+---";
        cout << "+" << endl;

        // Print row line
        for (int j = 0; j < cols; j++) 
        {
            cout << BLUE << "| ";

            if (grid[i][j] == 1)
            {
                cout << RED << setw(1) << grid[i][j] << RESET << " ";
            }
            else
            {
                cout << GREEN << setw(1) << grid[i][j] << RESET << " ";
            }
            
        }
        cout << BLUE << "|" << endl;
    }

    // Print horizontal line after the last row
    for (int j = 0; j < cols; j++)
    {
        cout << BLUE << "+---";
    }
  
  cout << "+" << endl;
    cout << RESET;
}



void checkcell(const int grid[][cols], int cellrow, int cellcol, int& livecount) //to check whether cell is alive or dead
 {
    if (cellrow >= 0 && cellrow < rows && cellcol >= 0 && cellcol < cols) 
    {
        if (grid[cellrow][cellcol] == 1)
         {
            cout << "The cell at (" << cellrow << ", " << cellcol << ") is alive." << endl;
            livecount++;
        }
        else {
            cout << "The cell at (" << cellrow << ", " << cellcol << ") is dead." << endl;
        }
    }
    else {
        cout << "Invalid coordinates." << endl;
    }
}



void add(int sec_array[][2], int index, int cellrow, int cellcol) // to store the x and y coordinates in the secondary array
{
    sec_array[index][0] = cellrow;  //cellrow = x coordinate of the cell
    sec_array[index][1] = cellcol;  //cellcol = y coordninate of the cell
}



int countLiveNeighbors(const int grid[][cols], int cellrow, int cellcol) // to count the live neighbors of the user entered cell
{
    int liveNeighbors = 0;
    //initialized i = -1 and j = -1, it starts from one cell above and one cell to the left of the current cell.
    for (int i = -1; i <= 1; i++) 
    {
        for (int j = -1; j <= 1; j++) 
        {
            int newRow = cellrow + i;   //This calculates the row index of the neighboring cell by adding the loop variable i to the current cell's row index cellrow
            int newCol = cellcol + j;   //this calculates the column index of the neighboring cell by adding the loop variable j to the current cell's column index cellcol
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && (i != 0 || j != 0)) //ensures that we don't count the current cell itself as its own neighbor.
            {
                if (grid[newRow][newCol] == 1) 
                {
                    liveNeighbors++;
                }
            }
        }
    }
    return liveNeighbors;
}

int countDeadNeighbors(const int grid[][cols], int cellrow, int cellcol, int nei_array[][2], int& nei_count) // to count the live neighbors of the user entered cell
{
    int deadNeighbors = 0;
    for (int i = -1; i <= 1; i++)
     {
        for (int j = -1; j <= 1; j++) 
        {
            int newRow = cellrow + i;
            int newCol = cellcol + j;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && (i != 0 || j != 0))
            {
                if (grid[newRow][newCol] == 0) {
                    // Store coordinates of dead neighbor
                    nei_array[nei_count][0] = newRow;
                    nei_array[nei_count][1] = newCol;
                    nei_count++;
                    deadNeighbors++;
                }
            }
        }
    }
    return deadNeighbors;
}

void applyrules(int grid[][cols], int nextgrid[][cols]) // tp apply the rules of Game of life (according to the running example provided)
 {
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j)
         {
            int aliveNeighbors = countLiveNeighbors(grid, i, j);

            // Rule 1: Birth 
            if (grid[i][j] == 0 && aliveNeighbors == 3)
             {
                nextgrid[i][j] = 1;
            }
            // Rule 2: Survival
            else if (grid[i][j] == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3))
             {
                nextgrid[i][j] = 1;
            }
            // Rule 3: Death by loneliness
            else if (grid[i][j] == 1 && aliveNeighbors <= 1) 
            {
                nextgrid[i][j] = 0;
            }
            // Rule 4: Death by overcrowding
            else if (grid[i][j] == 1 && aliveNeighbors > 3)
             {
                nextgrid[i][j] = 0;
            }
            // Otherwise, cell remains in its current state
            else {
                nextgrid[i][j] = grid[i][j];
            }
        }
    }
}

void printgrid(const int nextgrid[][cols]) //to print the updated grid(nextgrid) of every generation
{
    for (int i = 0; i < rows; i++) 
    {
        // Print horizontal line before each row
        for (int j = 0; j < cols; j++) 
        {
            cout << BLUE << "+---";
        }
        cout << "+" << endl;
        // Print row line
        for (int j = 0; j < cols; j++)
        {
            cout << BLUE << "| ";
            if (nextgrid[i][j] == 1)
            {
                cout << RED << setw(1) << nextgrid[i][j] << RESET << " ";
            }
            else
            {
                cout << GREEN << setw(1) << nextgrid[i][j] << RESET << " ";
            }
        }
        cout << BLUE << "|" << endl;
        cout << RESET;
    }

    // Print horizontal line after the last row
    for (int j = 0; j < cols; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
}

void start() //to start the game
{
   
    int grid[rows][cols];
    int livecount = 0;
   
   //calling the functions to make and print grid
    makegrid(grid);
    printGrid(grid);

    // Read user-input cell coordinates
    int size;   //here size is the number of cells user want to enter
    cout << "Enter the number of cells: " << endl;
    cin >> size;

    int sec_array[size][2]; //to store the user entered cells 

    cout << "Enter the coordinates of the cells: " << endl << endl;
    for (int i = 0; i < size; i++)
     {
        int cellrow, cellcol;   // cellrow =x coordinate,   cellcol = y coordinate

        cout << "Row Coordinate of cell " << i + 1 << ": ";
        cin >> cellrow;

        cout << "Column Coordinate of cell " << i + 1 << ": ";
        cin >> cellcol;

        checkcell(grid,cellrow, cellcol, livecount);    //calling the function to check live and dead cell
        cout << endl;
       
        add(sec_array, i, cellrow, cellcol);    //calling the function to store the cells in the sec array
    }

    cout << endl << endl;

    cout << "Number of live cells are : " << livecount << endl; //display the number of livecells

    int nei_array[rows * cols][2];  //neighbouring array to store neighbour cells
    int nei_count = 0;

    for (int i = 0; i < size; i++) 
    {
        countDeadNeighbors(grid, sec_array[i][0], sec_array[i][1], nei_array, nei_count);
    }

    cout << endl << endl;
    // Display the contents of nei_array
    cout << " Neighbouring_array:" << endl;

   for (int i = 0; i < nei_count; i++)
    {
       cout << "Dead Neighbor " << i + 1 << " ( " << nei_array[i][0] << ",  " << nei_array[i][1] << " )" << endl;
 }

    cout << endl << endl;
    // Display the contents of sec_array
    cout << "Secondary_array:" << endl;
    for (int i = 0; i < size; i++) 
    {
        cout << "Cell " << i + 1 << " ( " << sec_array[i][0] << ",  " << sec_array[i][1] << " )" << endl;

        int liveNeighbors = countLiveNeighbors(grid, sec_array[i][0], sec_array[i][1]);

        cout << "Number of live neighboring cells for cell " << i + 1 << ": " << liveNeighbors << endl;
    }

    cout << endl << endl;
    // Count the number of live cells of neighbouring cells stored in nei_array
    cout << "Counting live neighboring cells for dead neighbors" << endl;
    for (int i = 0; i < nei_count; i++)
     {
        int liveNeighbors = countLiveNeighbors(grid, nei_array[i][0], nei_array[i][1]);

        cout << "Number of live neighboring cells for Dead Neighbor " << i + 1 << ": " << liveNeighbors << endl;
    }

    // Prompt user to enter the number of generations
    int generations;
    cout << "Enter the number of generations: ";
    cin >> generations;

    // Apply rules for the specified number of generations
    for (int gen = 1; gen <= generations; gen++)
     {
        cout << "Generation: " << gen << endl;
        int nextgrid[rows][cols];
        applyrules(grid, nextgrid);
        printgrid(nextgrid);
        cout << endl;

        // Update grid for the next generation
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = nextgrid[i][j];
            }
        }

        // Update nei_array and sec_array for the next generation
        int updated_nei_array[rows * cols][2];
        int updated_nei_count = 0;
        for (int i = 0; i < size; i++) {
            countDeadNeighbors(grid, sec_array[i][0], sec_array[i][1], updated_nei_array, updated_nei_count);
        }

        // Update sec_array
        for (int i = 0; i < size; i++) {
            sec_array[i][0] = nextgrid[i][0];
            sec_array[i][1] = nextgrid[i][1];
        }

        // Display the contents of updated nei_array
        cout << "updated nei_array:" << endl;
        for (int i = 0; i < updated_nei_count; i++) 
        {
            cout << "Dead Neighbor " << i + 1 << " ( " << updated_nei_array[i][0] << ",  " << updated_nei_array[i][1] << " )" << endl;
        }

        cout << endl;

        // Display the contents of updated sec_array
        cout << "Updated sec_array:" << endl;
        for (int i = 0; i < size; i++)
         {
            cout << "Cell " << i + 1 << " ( " << sec_array[i][0] << ",  " << sec_array[i][1] << " )" << endl;
            int liveNeighbors = countLiveNeighbors(grid, sec_array[i][0], sec_array[i][1]);
            cout << "Number of live neighboring cells for cell " << i + 1 << ": " << liveNeighbors << endl;
        }

        cout << endl;

        // Count the number of live cells of neighboring cells stored in updated nei_array
        cout << "Counting live neighboring cells for updated dead neighbors" << endl << endl;
        for (int i = 0; i < updated_nei_count; i++)
         {
            int liveNeighbors = countLiveNeighbors(grid, updated_nei_array[i][0], updated_nei_array[i][1]);
            cout << "Number of live neighboring cells for Dead Neighbor " << i + 1 << ": " << liveNeighbors << endl;
        }

        cout << endl;
    }
}

int main() {
    start();
    return 0;
}