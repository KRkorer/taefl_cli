# taefl_cli

Hnefatafl on board 9x9 using console line interface.

## How to compile ?

Run `make`, without any parameters.

## How to use ?

Run `taefl_cli`, follow the on-screen instructions.
You can find information about previous move in 'moves.txt'.

## Rules

Players take turns making moves.

The defending side wins by leading its king into one of the corner squares. Attacking — if they managed to capture the king.

The attacking side moves first.

All pieces move like the rook in Chess – in a straight line for as many empty squares as the player chooses.

Pieces cannot hop over other pieces and cannot move diagonally.

With the exception of the king, no pieces can stand on the "throne" (e5) and corner squares.

Pieces can pass through the throne.

If a piece clips an opponent's piece between itself and another piece or between itself and a corner square/throne, the opponent's piece is considered eaten and removed from the board.

A king is considered captured when he is surrounded from four sides. In this case, the sides can be considered corner cells, the throne, and the sides of the board.

A piece can pass between two enemy ones. In this case, it is not considered eaten.
