# Simple Sudoku Solver using Backtracking

def print_grid(grid):
    for row in grid:
        print(row)

def is_safe(grid, row, col, num):
    # Check if num is not in the current row
    if num in grid[row]:
        return False
    # Check if num is not in the current column
    if num in [grid[i][col] for i in range(9)]:
        return False
    # Check 3x3 box
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if grid[start_row + i][start_col + j] == num:
                return False
    return True

def solve_sudoku(grid):
    for row in range(9):
        for col in range(9):
            if grid[row][col] == 0:  # empty cell
                for num in range(1, 10):
                    if is_safe(grid, row, col, num):
                        grid[row][col] = num
                        if solve_sudoku(grid):
                            return True
                        grid[row][col] = 0  # backtrack
                return False
    return True

if solve_sudoku(sudoku_grid):
    print("Sudoku solved successfully:")
    print_grid(sudoku_grid)
else:
    print("No solution exists")
