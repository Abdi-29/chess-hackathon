import chess
import chess.pgn
from collections import defaultdict, Counter
import zstandard

pgn_file = 'lichess_db.pgn.zst'

max_ply = 20

move_counts = defaultdict(Counter)

def open_file(file_path):
    return zstandard.open(file_path, 'rt')


with open_file(pgn_file) as file:
    while True:
        game = chess.pgn.read_game(file)
        if game is None:
            break
        board = game.board()
        moves = game.mainline_moves()
        ply_count = 0
        for move in moves:
            if ply_count >= max_ply:
                break
            fen = board.fen()
            move_str = move.uci()
            move_counts[fen][move_str] += 1
            board.push(move)
            ply_count += 1

opening_book = {}
for fen, move_counter in move_counts.items():
    sorted_moves = sorted(move_counter.keys(), key=lambda x: move_counter[x], reverse=True)
    opening_book[fen] = sorted_moves

with open('opening_book.txt', 'w') as f:
    for fen, moves in opening_book.items():
        f.write(fen + '\n')
        f.write(' '.join(moves) + '\n')