import numpy as np
import sys,time

def read_board() -> np.ndarray:
   row, col = map(int, input().split(' ')) # don't need it
   board = np.loadtxt(sys.stdin,dtype=np.bool_)
   return board

def available(board:np.ndarray) -> list: # return all possible moves
   move_list = []
   for i in range(board.shape[0]):
      next_board = board.copy()
      if sum(next_board[i,0:]) > 0: 
         move_list.append(f"r{i}")

   for i in range(board.shape[1]):
      next_board = board.copy()
      if sum(next_board[0:,i]) > 0: 
         next_board[0:,i] = 0
         move_list.append(f"c{i}")

   return move_list

decision_move = None

def alpha_beta_max(board, depth, alpha, beta, value) -> int: # max player
   
   global decision_move

   if depth == 0 or board.sum() == 0: return value
   for move in available(board): # list all possible next board
      next_board = board.copy()
      if move[0] == 'r':
         v = sum(next_board[int(move[1]),0:])
         next_board[int(move[1]),0:] = 0
      else: 
         v = sum(next_board[0:,int(move[1])])
         next_board[0:,int(move[1])] = 0

      score = alpha_beta_min(next_board, depth-1, alpha, beta, value+v)
      # print(next_board,depth,score,alpha,beta,'\n')
      if score >= beta: 
         decision_move = move
         return beta  # fail hard beta-cutoff
      if score > alpha: # alpha acts like max in MiniMax
         alpha = score
         decision_move = move

   return alpha

def alpha_beta_min(board, depth, alpha, beta, value) -> int: # min player
   if depth == 0 or board.sum() == 0: return value
   for move in available(board): # list all possible next board
      next_board = board.copy()
      if move[0] == 'r': 
         v = sum(next_board[int(move[1]),0:])
         next_board[int(move[1]),0:] = 0
         
      else: 
         v = sum(next_board[0:,int(move[1])])
         next_board[0:,int(move[1])] = 0
         
      score = alpha_beta_max(next_board, depth-1, alpha, beta,value-v)
      # print(next_board,depth,score,alpha,beta,'\n')
      if score <= alpha: return alpha # fail hard alpha-cutoff
      if score < beta: beta = score # beta acts like min in MiniMax
   return beta

def main():
   start_time = time.time()
   board = read_board()  # read board info from x.txt
   score = alpha_beta_max(board, 8, -1e9, 1e9, 0)

   if decision_move[0] == 'r': print(f"Row # : {int(decision_move[1])+1}")
   else: print(f"Column # : {int(decision_move[1])+1}")

   print(f"{score} points")
   print(f"Totle run time = {round(time.time()-start_time,5)} seconds.")

if __name__ == "__main__":
    main()
