board = [[0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0]]


def print_board(board):
    '''
    Prints the current state of the board
    '''
    for row in board:
        print(row)
    print("\n")


def attacking_pairs(row):
    count = 0
    for i in range(3):
        for j in range(i + 1, 4):
            slope = (row[i] - row[j]) / (i - j)
            if slope == 0 or slope == 1 or slope == -1:
                count += 1
    return count


def solve_4_queens(board, n, fixed, row):
    if n == 4:
        return attacking_pairs(row), []

    col = 0
    while col in fixed:
        col += 1

    min_cost = 6
    optimal_row = -1
    further_optimal_rows = []
    for i in range(4):
        board[i][col] = 1
        fixed.add(col)
        row[col] = i

        cost, pos = solve_4_queens(board, n + 1, fixed, row)
        if cost < min_cost:
            min_cost = cost
            optimal_row = i
            further_optimal_rows = pos

        board[i][col] = 0
        fixed.discard(col)
        del (row[col])

    further_optimal_rows.append((optimal_row, col))
    print("  "*n, further_optimal_rows)
    return min_cost, further_optimal_rows


if __name__ == "__main__":
    n = int(input('How many queens are fixed? (0-3):  '))
    fixed = set()
    row = {}
    if n > 0:
        print("Enter fixed queens:")
    for i in range(n):
        r, c = [int(x) for x in input().split(" ")]
        board[r][c] = 1
        row[c] = r
        fixed.add(c)

    print("\nINITIAL CONFIGURATION:")
    print_board(board)

    print("STATE SPACE CONFIGURATIONS:")
    h, pos = solve_4_queens(board, n, fixed, row)
    for r, c in pos:
        board[r][c] = 1

    print("\nOPTIMAL CONFIGURATION:")
    print_board(board)
