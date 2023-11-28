from copy import deepcopy
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
        # print(" ".join(["Q" if cell == 1 else "." for cell in row]))


def check_conf(i, j, row):
    '''
    Check whether queens in two given columns are conflicting
    '''
    slope = (row[i] - row[j]) / (i - j)
    return (slope == 1 or slope == 0 or slope == -1)


def move_queen(col, board, row):
    '''
    Given a column, find the cell with min conflicts and move the queen there
    '''
    min_conf = 4
    min_conf_row = -1
    for i in range(4):
        if (col == 0 or col == 3) and (i == 0 or i == 3):
            continue
        count = 0
        for j in range(4):
            if col != j:
                slope = (row[j] - i) / (j - col)
                if slope == 0 or slope == 1 or slope == -1:
                    count += 1
        if count < min_conf:
            min_conf = count
            min_conf_row = i

    # if the cell with min conflict is current cell, don't move queen
    if row[col] == min_conf_row:
        return 0
    board[row[col]][col] = 0
    board[min_conf_row][col] = 1
    row[col] = min_conf_row
    return 1


def solve_4_queens(board, fixed, row):
    '''
    Solve the 4-queens given initial board config
    '''
    for k in range(10):
        prev_board = deepcopy(board)
        # dictionary to keep count of conflicts
        conf_count = {x: 0 for x in range(4) if x not in fixed}
        tot_conf = 0
        for i in range(3):
            for j in range(i + 1, 4):
                if check_conf(i, j, row):
                    tot_conf += 1
                    if i not in fixed:
                        conf_count[i] = 1 + conf_count.get(i, 0)
                    if j not in fixed:
                        conf_count[j] = 1 + conf_count.get(j, 0)
        # print(conf_count)
        print("h = {}\n".format(tot_conf))

        max_conf = max(conf_count.values())
        if max_conf == 0:
            print("4-Queens Solved!!!\n")
            break
        print('Move {}:'.format(k+1))

        max_conf_cols = [
            k for k in conf_count.keys() if conf_count[k] == max_conf]
        for col in max_conf_cols:
            if move_queen(col, board, row):
                # print(col)
                break
        if prev_board == board:
            print("No Solution!!!\n")
            break
        print_board(board)


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

    # Choose initial positions for other queens
    print("Enter other queens:")
    for i in range(4 - n):
        r, c = [int(x) for x in input().split(" ")]
        board[r][c] = 1
        row[c] = r

    print("\nInitial Configuration:")
    print_board(board)

    solve_4_queens(board, fixed, row)
