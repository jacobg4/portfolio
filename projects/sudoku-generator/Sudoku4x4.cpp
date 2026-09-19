#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <chrono>

using namespace std;

// Function prototypes
void generateSudoku(int arr[][4]);
void shuffle2x2Grids(int arr[][4]);
void shuffleArray(int arr[], int size);
bool isNumberIn2x2Grid(int arr[][4], int startRow, int startCol, int num);
bool isNumberInRow(int arr[][4], int row, int num);
bool isNumberInColumn(int arr[][4], int col, int num);
void printArray(int arr[][4], int size);

// Function to generate the Sudoku puzzle
void generateSudoku(int arr[][4]) {
    srand(time(0)); // Seed the random number generator with current time

    // Fill each 2x2 grid with numbers 1-4 without repetition
    for (int i = 0; i < 4; i += 2) {
        for (int j = 0; j < 4; j += 2) {
            int nums[4] = {1, 2, 3, 4};
            shuffleArray(nums, 4);
            int index = 0;
            for (int row = i; row < i + 2; ++row) {
                for (int col = j; col < j + 2; ++col) {
                    arr[row][col] = nums[index++];
                }
            }
        }
    }

    // Shuffle the positions of the 2x2 grids
    shuffle2x2Grids(arr);
}

// Function to shuffle the positions of the 2x2 grids within the larger 4x4 grid
void shuffle2x2Grids(int arr[][4]) {
    int grids[4] = {0, 1, 2, 3};
    shuffleArray(grids, 4);

    int tempArr[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tempArr[i][j] = arr[i][j];
        }
    }

    for (int i = 0; i < 4; ++i) {
        int rowOffset = (grids[i] / 2) * 2;
        int colOffset = (grids[i] % 2) * 2;

        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 2; ++col) {
                arr[row + rowOffset][col + colOffset] = tempArr[row][col];
            }
        }
    }
}

// Function to shuffle an array
void shuffleArray(int arr[], int size) {
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Function to check if the number is already present in the 2x2 grid
bool isNumberIn2x2Grid(int arr[][4], int startRow, int startCol, int num) {
    for (int row = startRow; row < startRow + 2; ++row) {
        for (int col = startCol; col < startCol + 2; ++col) {
            if (arr[row][col] == num) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if the number is already present in the row
bool isNumberInRow(int arr[][4], int row, int num) {
    for (int col = 0; col < 4; ++col) {
        if (arr[row][col] == num) {
            return true;
        }
    }
    return false;
}

// Function to check if the number is already present in the column
bool isNumberInColumn(int arr[][4], int col, int num) {
    for (int row = 0; row < 4; ++row) {
        if (arr[row][col] == num) {
            return true;
        }
    }
    return false;
}

// Function to print the array
void printArray(int arr[][4], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to start the timer
auto startTimer() {
    return chrono::high_resolution_clock::now();
}

// Function to stop the timer and print elapsed time
void stopTimer(chrono::time_point<chrono::high_resolution_clock> startTime) {
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;
    cout << "Elapsed time: " << minutes << " minutes and " << seconds << " seconds" << endl;
}

int main() {
    int sudoku[4][4] = {{0}};

    auto startTime = startTimer(); // Start the timer

    generateSudoku(sudoku);
    printArray(sudoku, 4);

    // Stop the timer and print elapsed time
    stopTimer(startTime);

    return 0;
}
