// hexomino.js
// This file implements the 3-Color Covering.
// It contains tiling and packing algorithm. And, three Coloring algorithm.
// Initially, we can see what order the boards of 15x15 are filled.
// Then, we can see what color each figure is painted in.
// Specific decription is given in the pdf file.

// Colors to distinguish each figure when the solution is found
colors = [
    "#EEAAAA", "#DDBB99", "#CCCC88", "#BBDD99", "#AAEEAA", "#99DDBB", "#B22222",
    "#88CCCC", "#99BBDD", "#AAAAEE", "#BB99DD", "#CC88CC", "#DD99BB", "#663399",
    "#C0C0C0" ,"#4682B4", "#D2B48C", "#2E8B57", "#FF0000", "#B0E0E6", "#DB7093",
    "#FFDAB9",   "green", "#EEE8AA",    "gray", "#191970", "#00FA9A", "#48D1CC",
    "#C71585", "#800000", "#FFA07A",  "orange",  "yellow", "#2F4F4F", "#FF8C00",
    "#556B2F", "white"

];

// Setup
function setup() { 
  createCanvas(2500, 2500);
  puzzle = new Puzzle();
  puzzle.run(15 ,15);
  paint(puzzle);
} 


let count = 0;

// Move Hexomino figure and check it
function Square(x, y) {
  this.x = x;
  this.y = y;
  this.move = function(row, column) {
    return new Square(this.x + column, this.y + row);
  };
  this.check = function(width, height) {
    if (this.x < 0 || this.y < 0) {
      return false;
    } else {
      if (this.x >= width || this.y >= height) {
        return false;
      } else {
        return true;
      }
    }
  };
}

// Make new hexomino object and move it.
function Hexomino(key, squares) {
  this.key = key;
  this.squares = squares.map(function(square) {
    return new Square(square[0], square[1]);
  });
  this.move = function(row, column) {
    var hexomino = new Hexomino(this.key, []);
    hexomino.squares = this.squares.map(function(square) {
      return square.move(row, column);
    });
    return hexomino;
  };
}

// Cordinates of Hexomino figures (rotation, flip)
function Hexominos() {
  this.shapes = [
    [ // #14 = 8 4 rotation, flip
      new Hexomino( 0, [[0,1],[1,1],[1,2],[2,1],[3,1],[3,0]]),
      new Hexomino( 0, [[0,0],[1,0],[1,1],[1,2],[2,2],[1,3]]),
      new Hexomino( 0, [[0,1],[0,2],[1,1],[2,1],[2,0],[3,1]]),
      new Hexomino( 0, [[0,1],[1,0],[1,1],[1,2],[1,3],[2,3]]),

      new Hexomino( 0, [[0,0],[0,1],[1,1],[2,1],[3,1],[2,2]]),
      new Hexomino( 0, [[0,3],[1,3],[1,2],[1,1],[2,1],[1,0]]),
      new Hexomino( 0, [[0,1],[1,0],[1,1],[2,1],[3,1],[3,2]]),
      new Hexomino( 0, [[0,2],[1,2],[1,3],[1,1],[1,0],[2,0]]),
    ],

    [ // #10 = 8 4 rotation, flip
      new Hexomino( 1, [[0,2],[1,2],[2,2],[3,2],[3,1],[3,0]]),
      new Hexomino( 1, [[0,0],[1,0],[2,0],[2,1],[2,2],[2,3]]),
      new Hexomino( 1, [[0,0],[0,1],[0,2],[1,0],[2,0],[3,0]]),
      new Hexomino( 1, [[0,0],[0,1],[0,2],[0,3],[1,3],[2,3]]),

      new Hexomino( 1, [[0,0],[0,1],[0,2],[1,2],[2,2],[3,2]]),  
      new Hexomino( 1, [[0,3],[1,3],[2,3],[2,2],[2,1],[2,0]]),
      new Hexomino( 1, [[0,0],[1,0],[2,0],[3,0],[3,1],[3,2]]),
      new Hexomino( 1, [[0,0],[0,1],[0,2],[0,3],[1,0],[2,0]]),
    ],
    [ // #23 = 8 4 rotation, flip
      new Hexomino( 2, [[0,1],[1,1],[2,1],[2,2],[2,0],[3,0]]),
      new Hexomino( 2, [[0,0],[0,1],[1,1],[2,1],[1,2],[1,3]]),
      new Hexomino( 2, [[0,2],[1,2],[1,1],[1,0],[2,1],[3,1]]),
      new Hexomino( 2, [[0,2],[1,0],[1,1],[1,2],[2,2],[2,3]]),

      new Hexomino( 2, [[0,0],[1,0],[1,1],[1,2],[2,1],[3,1]]),
      new Hexomino( 2, [[0,2],[0,3],[1,2],[2,2],[1,1],[1,0]]),
      new Hexomino( 2, [[0,1],[1,1],[2,1],[2,0],[2,2],[3,2]]),
      new Hexomino( 2, [[0,1],[1,1],[2,1],[2,0],[1,2],[1,3]]),
    ],
    [ // #11 = 8 4 rotation, flip
      new Hexomino( 3, [[0,2],[1,2],[2,2],[3,2],[2,1],[2,0]]),
      new Hexomino( 3, [[0,1],[1,1],[2,0],[2,1],[2,2],[2,3]]),
      new Hexomino( 3, [[0,0],[1,0],[1,1],[1,2],[2,0],[3,0]]),
      new Hexomino( 3, [[0,0],[0,1],[0,2],[0,3],[1,2],[2,2]]),

      new Hexomino( 3, [[0,2],[1,2],[1,1],[1,0],[2,2],[3,2]]),
      new Hexomino( 3, [[0,2],[1,2],[2,0],[2,1],[2,2],[2,3]]),
      new Hexomino( 3, [[0,0],[1,0],[2,0],[3,0],[2,1],[2,2]]),
      new Hexomino( 3, [[0,0],[0,1],[0,2],[0,3],[1,1],[2,1]]),
    ],
    [ // #25 = 8 4 rotation, flip
      new Hexomino( 4, [[0,1],[1,1],[1,2],[2,1],[2,0],[3,0]]),
      new Hexomino( 4, [[0,0],[0,1],[1,1],[1,2],[2,2],[1,3]]),
      new Hexomino( 4, [[0,2],[1,2],[1,1],[2,1],[2,0],[3,1]]),
      new Hexomino( 4, [[0,1],[1,0],[1,1],[1,2],[2,2],[2,3]]),

      new Hexomino( 4, [[0,0],[1,0],[1,1],[2,1],[3,1],[2,2]]),
      new Hexomino( 4, [[0,3],[0,2],[1,2],[1,1],[2,1],[1,0]]),
      new Hexomino( 4, [[0,1],[1,1],[1,0],[2,1],[2,2],[3,2]]),
      new Hexomino( 4, [[0,2],[1,2],[1,3],[1,1],[2,1],[2,0]]),
    ],
    [ // #5 = 8 4 rotation, flip
      new Hexomino( 5, [[0,1], [1,1],[2,1],[3,1],[3,0],[4,0]]),
      new Hexomino( 5, [[0,1], [1,1],[1,0],[2,0],[3,0],[4,0]]),
      new Hexomino( 5, [[0,0], [0,1],[0,2],[0,3],[1,3],[1,4]]),
      new Hexomino( 5, [[0,0], [0,1],[1,1],[1,2],[1,3],[1,4]]),

      new Hexomino( 5, [[0,0], [1,0],[1,1],[2,1],[3,1],[4,1]]),
      new Hexomino( 5, [[0,0], [1,0],[2,0],[3,0],[3,1],[4,1]]),
      new Hexomino( 5, [[0,4], [0,3],[1,3],[1,2],[1,1],[1,0]]),
      new Hexomino( 5, [[0,4], [0,3],[0,2],[0,1],[1,1],[1,0]]),
    ],

    [ // #2 = 8 4 rotation, flip
      new Hexomino( 6, [[0,1], [1,1], [2,1], [3, 1], [4,1], [4,0]]),
      new Hexomino( 6, [[0,0], [1,0], [1,1], [1, 2], [1,3], [1,4]]),
      new Hexomino( 6, [[0,1], [0,0], [1,0], [2, 0], [3,0], [4,0]]),
      new Hexomino( 6, [[0,0], [0,1], [0,2], [0, 3], [0,4], [1,4]]),

      new Hexomino( 6, [[0,0], [0,1], [1,1], [2,1], [3,1], [4,1]]),
      new Hexomino( 6, [[0,4], [1,4], [1,3], [1,2], [1,1], [1,0]]),
      new Hexomino( 6, [[0,0], [1,0], [2,0], [3,0], [4,0], [4,1]]),
      new Hexomino( 6, [[0,0], [0,1], [0,2], [0,3], [0,4], [1,0]]),
    ],

    [ // #15 = 4 2 rotation, flip
      new Hexomino( 7, [[0,1],[0,2],[1,1],[2,1],[3,1],[3,0]]),
      new Hexomino( 7, [[0,0],[1,0],[1,1],[1,2],[1,3],[2,3]]),

      new Hexomino( 7, [[0,0],[0,1],[1,1],[2,1],[3,1],[3,2]]),
      new Hexomino( 7, [[0,3],[1,3],[1,2],[1,1],[1,0],[2,0]]),
    ],
    // ----------------------------------------------------------------------------------------
    [ // #24 = 8 4 rotation, flip
      new Hexomino( 8, [[0,1],[1,1],[2,1],[2,2],[1,0],[2,0]]),
      new Hexomino( 8, [[0,0],[0,1],[1,0],[2,0],[1,1],[1,2]]),
      new Hexomino( 8, [[0,0],[0,1],[0,2],[1,2],[1,1],[2,1]]),
      new Hexomino( 8, [[0,2],[1,0],[1,1],[1,2],[2,1],[2,2]]),

      new Hexomino( 8, [[0,0],[1,0],[0,1],[1,1],[2,1],[0,2]]),
      new Hexomino( 8, [[0,1],[0,2],[1,2],[1,1],[1,0],[2,2]]),
      new Hexomino( 8, [[0,1],[1,1],[1,2],[2,2],[2,1],[2,0]]),
      new Hexomino( 8, [[0,0],[1,0],[2,0],[1,1],[1,2],[2,1]]),
    ],

    [ // #9 = 4 4 rotation, no flip
      new Hexomino( 9, [[1,0],[2,0],[0,1],[1,1],[2,1],[3,1]]),
      new Hexomino( 9, [[0,1],[0,2],[1,0],[1,1],[1,2],[1,3]]),
      new Hexomino( 9, [[0,0],[1,0],[2,0],[3,0],[1,1],[2,1]]),
      new Hexomino( 9, [[0,0],[0,1],[0,2],[0,3],[1,1],[1,2]]),
    ],
    [ // #26 = 8 4 rotation, flip
      new Hexomino( 10, [[0,2],[1,2],[2,2],[2,1],[2,0],[3,0]]),
      new Hexomino( 10, [[0,0],[0,1],[1,1],[2,1],[2,2],[2,3]]),
      new Hexomino( 10, [[0,2],[1,2],[1,1],[1,0],[2,0],[3,0]]),
      new Hexomino( 10, [[0,0],[0,1],[0,2],[1,2],[2,2],[2,3]]),

      new Hexomino( 10, [[0,0],[1,0],[1,1],[1,2],[2,2],[3,2]]),
      new Hexomino( 10, [[0,3],[0,2],[1,2],[2,2],[2,1],[2,0]]),
      new Hexomino( 10, [[0,0],[1,0],[2,0],[2,1],[2,2],[3,2]]),
      new Hexomino( 10, [[0,3],[0,2],[0,1],[1,1],[2,1],[2,0]]),
    ],
    
    [ // #3 = 8 4 rotation, flip
      new Hexomino( 11, [[0,1], [1,1], [2,1], [3,1],[3,0],[4,1]]),
      new Hexomino( 11, [[0,0], [0,1], [0,2], [0,3],[1,3],[0,4]]),
      new Hexomino( 11, [[0,1], [1,1], [1,0], [1,2],[1,3],[1,4]]),
      new Hexomino( 11, [[0,0], [1,0], [1,1], [2,0],[3,0],[4,0]]),

      new Hexomino( 11, [[0,1], [1,1], [1,0], [2,1],[3,1],[4,1]]),
      new Hexomino( 11, [[0,3], [1,3], [1,4], [1,2],[1,1],[1,0]]),
      new Hexomino( 11, [[0,0], [1,0], [2,0], [3,0],[3,1],[4,0]]),
      new Hexomino( 11, [[0,0], [0,1], [1,1], [0,2],[0,3],[0,4]]),

    ],

    [ // #12 = 4 4 rotation, no flip
      new Hexomino( 12, [[0,1],[1,1],[2,1],[3,1],[3,2],[3,0]]),
      new Hexomino( 12, [[0,0],[1,0],[1,1],[1,2],[1,3],[2,0]]),
      new Hexomino( 12, [[0,0],[0,1],[0,2],[1,1],[2,1],[3,1]]),
      new Hexomino( 12, [[1,0],[1,1],[1,2],[1,3],[0,3],[2,3]]),
    ],

    [ // #19 = 8 4 rotation, flip
      new Hexomino( 13, [[0,0],[2,0],[3,0],[0,1],[1,1],[2,1]]),
      new Hexomino( 13, [[0,0],[0,1],[1,1],[1,2],[1,3],[0,3]]),
      new Hexomino( 13, [[0,1],[1,1],[1,0],[2,0],[3,0],[3,1]]),
      new Hexomino( 13, [[0,0],[1,0],[0,1],[0,2],[1,2],[1,3]]),

      new Hexomino (13, [[0,0],[1,0],[1,1],[2,1],[3,1],[3,0]]),
      new Hexomino (13, [[0,0],[1,0],[1,1],[1,2],[0,2],[0,3]]),
      new Hexomino (13, [[0,0],[0,1],[1,0],[2,0],[2,1],[3,1]]),
      new Hexomino (13, [[0,1],[0,2],[0,3],[1,3],[1,1],[1,0]]),
    ],
    [ // #21 = 4 2 rotation, flip
      new Hexomino( 14, [[0,1],[1,1],[2,1],[1,0],[2,0],[3,0]]),
      new Hexomino( 14, [[0,0],[0,1],[0,2],[1,1],[1,2],[1,3]]),

      new Hexomino( 14, [[0,0],[1,0],[2,0],[1,1],[2,1],[3,1]]),
      new Hexomino( 14, [[0,1],[0,2],[0,3],[1,0],[1,1],[1,2]]),
    ],
    // --------------------------------------------------------------------------------------------
        [ // #7 = 8 4 rotation, flip
      new Hexomino( 15, [[0,1],[1,1],[1,0],[2,1],[3,1],[3,0]]),
      new Hexomino( 15, [[0,0],[0,2],[1,0],[1,1],[1,2],[1,3]]),
      new Hexomino( 15, [[0,0],[0,1],[1,0],[2,0],[2,1],[3,0]]),
      new Hexomino( 15, [[0,0],[0,1],[0,2],[0,3],[1,1],[1,3]]),

      new Hexomino( 15, [[0,0],[2,0],[0,1],[1,1],[2,1],[3,1]]),
      new Hexomino( 15, [[0,1],[0,3],[1,0],[1,1],[1,2],[1,3]]),
      new Hexomino( 15, [[0,0],[1,0],[2,0],[3,0],[1,1],[3,1]]),
      new Hexomino( 15, [[0,0],[0,1],[0,2],[0,3],[1,0],[1,2]]),
    ],
    [ // #27 = 8 4 rotation, flip
      new Hexomino( 16, [[0,2],[1,2],[2,2],[2,1],[3,1],[3,0]]),
      new Hexomino( 16, [[0,0],[1,0],[1,1],[2,1],[2,2],[2,3]]),
      new Hexomino( 16, [[0,2],[0,1],[1,1],[1,0],[2,0],[3,0]]),
      new Hexomino( 16, [[0,0],[0,1],[0,2],[1,2],[1,3],[2,3]]),

      new Hexomino( 16, [[0,0],[0,1],[1,1],[1,2],[2,2],[3,2]]),
      new Hexomino( 16, [[0,3],[1,3],[1,2],[2,2],[2,1],[2,0]]),
      new Hexomino( 16, [[0,0],[1,0],[2,0],[2,1],[3,1],[3,2]]),
      new Hexomino( 16, [[0,3],[0,2],[0,1],[1,1],[1,0],[2,0]]),
    ],
    [ // #31 = 8 4 rotation, flip
      new Hexomino( 17, [[0,2],[1,2],[1,1],[2,1],[3,1],[3,0]]),
      new Hexomino( 17, [[0,0],[1,0],[1,1],[1,2],[2,2],[2,3]]),
      new Hexomino( 17, [[0,2],[0,1],[1,1],[2,1],[2,0],[3,0]]),
      new Hexomino( 17, [[0,0],[0,1],[1,1],[1,2],[1,3],[2,3]]),

      new Hexomino( 17, [[0,0],[0,1],[1,1],[2,1],[2,2],[3,2]]),
      new Hexomino( 17, [[0,3],[1,3],[1,2],[1,1],[2,1],[2,0]]),
      new Hexomino( 17, [[0,0],[1,0],[1,1],[2,1],[3,1],[3,2]]),
      new Hexomino( 17, [[0,3],[0,2],[1,2],[1,1],[1,0],[2,0]]),

    ],
    [ // #4 = 4 4 rotation, no flip
      new Hexomino( 18, [[0,1], [1, 1], [2, 1], [2,0], [3,1], [4,1]]),
      new Hexomino( 18, [[0,0], [1, 0], [2, 0], [2,1], [3,0], [4,0]]),
      new Hexomino( 18, [[0,2], [1, 2], [1, 3], [1,4], [1,1], [1,0]]),
      new Hexomino( 18, [[0,0], [0, 1], [0, 2], [1,2], [0,3], [0,4]]),
    ],

    [ // #13 = 8 4 rotation, flip
      new Hexomino( 19, [[0,1],[1,1],[2,1],[2,2],[3,1],[3,0]]),
      new Hexomino( 19, [[0,0],[1,0],[1,1],[1,2],[1,3],[2,1]]),
      new Hexomino( 19, [[0,1],[0,2],[1,1],[1,0],[2,1],[3,1]]),
      new Hexomino( 19, [[1,0],[1,1],[1,2],[0,2],[1,3],[2,3]]),

      new Hexomino( 19, [[0,0],[0,1],[1,1],[1,2],[2,1],[3,1]]),
      new Hexomino( 19, [[0,3],[1,3],[1,2],[2,2],[1,1],[1,0]]),
      new Hexomino( 19, [[0,1],[1,1],[2,1],[2,0],[3,1],[3,2]]),
      new Hexomino( 19, [[0,1],[1,1],[1,0],[2,0],[1,2],[1,3]]),
    ],


    [ // #20 = 4 2 rotation, flip
      new Hexomino( 20, [[0,1],[1,1],[2,1],[2,0],[3,0],[4,0]]),
      new Hexomino( 20, [[0,0],[0,1],[0,2],[1,2],[1,3],[1,4]]),

      new Hexomino( 20, [[0,0],[1,0],[2,0],[2,1],[3,1],[4,1]]),
      new Hexomino( 20, [[1,0],[1,1],[1,2],[0,2],[0,3],[0,4]]),
    ],

    [ // #1 = 2 2 rotation, no flip
      new Hexomino( 21, [[0,0], [0, 1], [0, 2], [0, 3], [0,4], [0,5]]),
      new Hexomino( 21, [[0,0], [1, 0], [2, 0], [3, 0], [4,0], [5,0]]),
    ],
    // --------------------------------------------------------------------------------------------------
    [// #21 duplicate figure = 4 2 rotation, flip
      new Hexomino( 22, [[0,1],[1,1],[2,1],[1,0],[2,0],[3,0]]),
      new Hexomino( 22, [[0,0],[0,1],[0,2],[1,1],[1,2],[1,3]]),

      new Hexomino( 22, [[0,0],[1,0],[2,0],[1,1],[2,1],[3,1]]),
      new Hexomino( 22, [[0,1],[0,2],[0,3],[1,0],[1,1],[1,2]]),
    ],
    [ // #32 = 4 4 rotation, no flip
      new Hexomino( 23, [[0,0],[0,1],[1,1],[0,2],[1,2],[2,2]]),
      new Hexomino( 23, [[0,2],[1,2],[2,2],[1,1],[2,1],[2,0]]),
      new Hexomino( 23, [[0,0],[1,0],[2,0],[0,1],[1,1],[0,2]]),
      new Hexomino( 23, [[0,0],[1,0],[2,0],[1,1],[2,1],[2,2]]),
    ],
    [ // #22 = 2 2 rotation, no flip
      new Hexomino( 24, [[0,0],[1,0],[2,0],[0,1],[1,1],[2,1]]),
      new Hexomino( 24, [[0,0],[0,1],[0,2],[1,0],[1,1],[1,2]]),
    ],
    [ // #18 = 8 4 rotation, flip
      new Hexomino( 25, [[0,2],[1,2],[2,2],[2,1],[2,0],[3,1]]),
      new Hexomino( 25, [[0,1],[1,1],[1,0],[2,1],[2,2],[2,3]]),
      new Hexomino( 25, [[0,1],[1,1],[1,2],[1,0],[2,0],[3,0]]),
      new Hexomino( 25, [[0,0],[0,1],[0,2],[1,2],[1,3],[2,2]]),

      new Hexomino( 25, [[0,1],[1,0],[1,1],[1,2],[2,2],[3,2]]),
      new Hexomino( 25, [[0,2],[1,2],[1,3],[2,2],[2,1],[2,0]]),
      new Hexomino( 25, [[0,0],[1,0],[2,0],[2,1],[3,1],[2,2]]),
      new Hexomino( 25, [[1,0],[0,1],[0,2],[0,3],[1,1],[2,1]]),
    ],
        [ // #16 = 4 2 rotation, flip
      new Hexomino( 26, [[0,1],[1,1],[1,2],[2,1],[2,0],[3,1]]),
      new Hexomino( 26, [[0,1],[1,1],[1,0],[1,2],[1,3],[2,2]]),

      new Hexomino( 26, [[0,1],[1,1],[1,0],[2,1],[2,2],[3,1]]),
      new Hexomino( 26, [[0,2],[1,2],[1,3],[1,1],[2,1],[1,0]]),
    ],

    [ // #33 = 4 4 rotation, no flip
      new Hexomino( 27, [[0,2],[0,1],[1,2],[1,1],[1,0],[2,1]]),
      new Hexomino( 27, [[0,1],[1,1],[1,2],[1,0],[2,1],[2,2]]),
      new Hexomino( 27, [[0,1],[1,1],[2,1],[1,0],[2,0],[1,2]]),
      new Hexomino( 27, [[0,0],[0,1],[1,0],[1,1],[2,1],[1,2]]),
    ],
            [ // #30 = 4 4 rotation, no flip
      new Hexomino( 28, [[0,1],[1,1],[1,0],[2,0],[1,2],[2,2]]),
      new Hexomino( 28, [[0,0],[0,1],[1,1],[1,2],[2,1],[2,0]]),
      new Hexomino( 28, [[0,0],[1,0],[1,1],[2,1],[1,2],[0,2]]),
      new Hexomino( 28, [[0,2],[0,1],[1,1],[1,0],[2,1],[2,2]]),
    ],

    [ // #34 = 8 4 rotation, flip
      new Hexomino( 29, [[0,1],[0,2],[1,2],[1,1],[1,0],[2,0]]),
      new Hexomino( 29, [[0,0],[0,1],[1,1],[2,1],[1,2],[2,2]]),
      new Hexomino( 29, [[0,2],[1,2],[1,1],[1,0],[2,1],[2,0]]),
      new Hexomino( 29, [[0,0],[0,1],[1,0],[1,1],[2,1],[2,2]]),

      new Hexomino( 29, [[0,0],[1,0],[1,1],[1,2],[2,1],[2,2]]),
      new Hexomino( 29, [[0,2],[0,1],[1,1],[1,0],[2,0],[2,1]]),
      new Hexomino( 29, [[0,0],[0,1],[1,0],[1,1],[1,2],[2,2]]),
      new Hexomino( 29, [[0,2],[0,1],[1,1],[1,2],[2,1],[2,0]]),
    ],
    [ // #35 = 4 2 rotation, flip
      new Hexomino( 30, [[0,2],[1,2],[1,1],[2,1],[2,0],[3,0]]),
      new Hexomino( 30, [[0,0],[0,1],[1,1],[1,2],[2,2],[2,3]]),

      new Hexomino( 30, [[0,0],[1,0],[1,1],[2,1],[2,2],[3,2]]),
      new Hexomino( 30, [[0,3],[0,2],[1,2],[1,1],[2,1],[2,0]])
    ],
    [ // #6 = 8 4 rotation, flip
      new Hexomino( 31, [[0,1],[1,1],[2,1],[3,1],[2,0],[3,0]]),
      new Hexomino( 31, [[0,0],[0,1],[1,0],[1,1],[1,2],[1,3]]),
      new Hexomino( 31, [[0,0],[0,1],[1,0],[1,1],[2,0],[3,0]]),
      new Hexomino( 31, [[0,0],[0,1],[0,2],[0,3],[1,2],[1,3]]),

      new Hexomino( 31, [[0,0],[0,1],[1,0],[1,1],[2,1],[3,1]]),
      new Hexomino( 31, [[0,2],[0,3],[1,3],[1,2],[1,1],[1,0]]),
      new Hexomino( 31, [[0,0],[1,0],[2,0],[3,0],[2,1],[3,1]]),
      new Hexomino( 31, [[0,0],[0,1],[0,2],[0,3],[1,0],[1,1]]),
    ],

    [ // #28 = 8 4 rotation, flip
      new Hexomino( 32, [[0,2],[1,2],[2,2],[2,1],[2,0],[1,0]]),
      new Hexomino( 32, [[0,1],[0,0],[1,0],[2,0],[2,1],[2,2]]),
      new Hexomino( 32, [[0,0],[0,1],[0,2],[1,2],[1,0],[2,0]]),
      new Hexomino( 32, [[0,0],[0,1],[0,2],[1,2],[2,2],[2,1]]),

      new Hexomino( 32, [[0,0],[0,1],[0,2],[1,2],[2,2],[1,0]]),
      new Hexomino( 32, [[0,1],[0,2],[1,2],[2,2],[2,1],[2,0]]),
      new Hexomino( 32, [[0,0],[1,0],[2,0],[2,1],[2,2],[1,2]]),
      new Hexomino( 32, [[0,2],[0,1],[0,0],[1,0],[2,0],[2,1]]),
    ],
    
    [ // #29 = 8 4 rotation, flip
      new Hexomino( 33, [[0,2],[1,2],[2,2],[1,1],[1,0],[2,0]]),
      new Hexomino( 33, [[0,0],[0,1],[1,1],[2,1],[2,2],[2,0]]),
      new Hexomino( 33, [[0,0],[1,0],[2,0],[1,1],[1,2],[0,2]]),
      new Hexomino( 33, [[0,0],[0,1],[0,2],[1,1],[2,1],[2,2]]),

      new Hexomino( 33, [[0,0],[1,0],[1,1],[1,2],[0,2],[2,2]]),
      new Hexomino( 33, [[0,2],[0,1],[1,1],[2,1],[2,2],[2,0]]),
      new Hexomino( 33, [[0,0],[1,0],[2,0],[1,1],[1,2],[2,2]]),
      new Hexomino( 33, [[0,0],[0,1],[0,2],[1,1],[2,1],[2,0]]),
    ],
    [ // #17 = 4 4 rotation, no flip
      new Hexomino( 34, [[0,1],[1,1],[2,1],[2,0],[2,2],[3,1]]),
      new Hexomino( 34, [[0,1],[1,1],[1,0],[1,2],[1,3],[2,1]]),
      new Hexomino( 34, [[0,1],[1,1],[1,0],[1,3],[2,1],[3,1]]),
      new Hexomino( 34, [[0,2],[1,0],[1,1],[1,2],[2,2],[1,3]]),
    ],
    [ // #8 = 4 4 rotation, no flip
      new Hexomino( 35, [[0,0],[3,0],[0,1],[1,1],[2,1],[3,1]]),
      new Hexomino( 35, [[0,0],[0,3],[1,0],[1,1],[1,2],[1,3]]),
      new Hexomino( 35, [[0,0],[0,1],[1,0],[2,0],[3,0],[3,1]]),
      new Hexomino( 35, [[0,0],[0,1],[0,2],[0,3],[1,0],[1,3]]),
    ],
  ];

  // Enumerator for Hexomino figure
  this.rectangle = [];
  this.enumerator = function(row, column, width, height) {
    return this.shapes.map(function(a) {
      return a.map(function(b) {
        return b.move(row, column);
      }).filter(function(c) {
        return c.squares.every(function(d) {
          return d.check(width, height);
        });
      });
    });
  };

  // Initialize Hexomino figure
  this.initialize = function(width, height) {
    var row, column;
    for (row = 0; row < height; row++) {
      this.rectangle[row] = [];
      for (column = 0; column < width; column++) {
        this.rectangle[row][column] = 
          this.enumerator(row, column, width, height);
      }
    }
  };
}

// State of Hexomino figure, check if a shape is used or not, and select not used one
function State(rectangle, mask, count) {
  this.rectangle = rectangle;
  this.mask = mask;
  this.count = count;
  this.shapes = [];
  this.index = -1;

  // Function to make new Square object.
  this.select = function() {
    var row, column;
    for (row = 0; row < this.rectangle.length; row++) {
      for (column = 0; column < this.rectangle[row].length; column++) {
        if (this.rectangle[row][column] == false) {
          return new Square(column, row);
        }
      }
    }
    return null;
  };

  // Select a figure and add it.
  this.add = function(rectangle) {
    var square, shapes;
    square = this.select();
    if (square != null) {
      shapes = rectangle[square.y][square.x];
      this.mask.forEach(function(value, index) {
        if (value == false) {
          shapes[index].forEach(function(shape) {
            this.shapes.push(shape);
          }, this);
        }
      }, this);
    }
  };
  // Move on to the next index
  this.next = function() {
    this.index = this.index + 1;
    return this.index < this.shapes.length;
  };

  // Check if the shape fits
  this.fit = function() {
    var shape;
    shape = this.shapes[this.index];
    return shape.squares.every(function(square) {
      return this.rectangle[square.y][square.x] == false;
    }, this);
  };

  // If the shape fits, mark it, add count the number of cells (6)
  this.copy = function() {
    var rectangle, shape, mask, count;
    rectangle = this.rectangle.map(function(row) {
      return row.slice();
    });
    shape = this.shapes[this.index];
    shape.squares.forEach(function(square) {
      rectangle[square.y][square.x] = true;
    });
    mask = this.mask.slice();
    mask[shape.key] = true;

    count = this.count + 6;

    
    return new State(rectangle, mask, count);
  };
}

// Run the puzzle solver
function Puzzle() {
  let rectcount = 0;
  this.stack = [];
  this.first = function(width, height) {
    var rectangle, row, column, mask;
    rectangle = [];
    for (row = 0; row < height; row++) {
      rectangle[row] = [];
      for (column = 0; column < width; column++) {
        rectangle[row][column] = false;
      }
    }

    // Exclude by 3x3 in the middle of the board
    if (rectcount === 0){
      rectangle[6][6] =  true;
      rectangle[6][7] =  true;
      rectangle[6][8] =  true;
      rectangle[7][6] =  true;
      rectangle[7][7] =  true;
      rectangle[7][8] =  true;
      rectangle[8][6] =  true;
      rectangle[8][7] =  true;
      rectangle[8][8] =  true;
      rectcount = 1;
    }
    // Vars to check wheter or not each shape is used
    mask = [
      false, false, false, false, false, false, false,
      false, false, false, false, false, false, false,
      false, false, false, false, false, false, false,
      false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false
    ];
    return new State(rectangle, mask, 0);
  };

  // Run the puzzle solver, set object, stop program when the solution is found
  this.run = function(width, height) {
    var hexominos, state, count;
    hexominos = new Hexominos();
    hexominos.initialize(width, height);
    state = this.first(width, height);
    state.add(hexominos.rectangle);
    this.stack.push(state);
    
    // 33 figures cells = 198
    count = 198;
    
    // If the shape fits, then push the state to the stack
    while (this.stack.length > 0) {
      state = this.stack.pop();
      if (state.count == count) {
        break;
      }
      while (state.next()) {
        if (state.fit()) {
          this.stack.push(state);
          state = state.copy();
          state.add(hexominos.rectangle);
          this.stack.push(state);
          break;
        }
      }
    }
  };
}

// Sleep function
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

let keyarray = [];
async function paint() { 

  // Set 15x15 board
  var board = [ 
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36],
                [36,36,36,36,36,36,36,36,36,36,36,36,36,36,36]
              ]
  // Store information about the order in which shapes were used
      puzzle.stack.forEach(function(state) {
    var shape;
    shape = state.shapes[state.index];
      keyarray.push(shape.key)
      shape.squares.forEach(async function(square) {
        board[square.y][square.x] = shape.key
        });
    });
  
// Show tiling animation of the solution
  wcounter = 0;
  while(wcounter < 36){
            await sleep(1000)
  for(let i=0; i<15; i++){
    for(let j=0; j<15; j++){
      if(board[i][j] == keyarray[wcounter]){
        fill(colors[keyarray[wcounter]])
        rect(j*25, i*25, 25, 25)
      }
    }
  }
    wcounter++;
  }

    checkboard(board)
}

let array = []
let w = 30 // width

let SIZE = 15
let regions = {}

// Check which shapes are used and make an array containing their information
function checkboard(board){
    let countcheck = 0;
    let containarray = [];
    
    // Store the shapes used
    for(let i =0; i< 15; i++){
        console.log(board[i])
        value = 0;
      for (let j=0; j<36; j++){
        isInArray = board[i].includes(value);
        isInArray2 = containarray.includes(value);

          if(isInArray == true && isInArray2 == false){
            containarray[j] = value
          }

        value++
      }
    }
    
    // Store unused shapes.
    let skipval = [];
    console.log("containarray", containarray)
    
    for (let i =0; i<36; i++){
      if(containarray[i] == undefined)
        skipval.push(i);
    }
    console.log(skipval);
    
    // Ready to convert to adjacency matrix
    printboard(board, skipval, containarray)
}

// Convert the board to adjacency matrix and start graph coloring
function printboard(board, skipval, containarray){
  
  // Stores information about which shapes are adjacent to each.
  for (let i = 0; i < SIZE; i++) {
    for (let j = 0; j < SIZE; j++) {
        region = board[i][j]
        if (!(region in regions)) {regions[region] = {}}
        if (i > 0) {
            if (board[i-1][j] != region) {
                regions[region][board[i-1][j]] = true

            }
        }
        if (i < SIZE - 1) {
            if (board[i+1][j] != region) {
                regions[region][board[i+1][j]] = true

            }
        }
        if (j > 0) {
            if (board[i][j-1] != region) {
                regions[region][board[i][j-1]] = true

            }
        }
        if (j < SIZE - 1) {
            if (board[i][j+1] != region) {
                regions[region][board[i][j+1]] = true

            }
        }

      array.push(regions)
    }
  }

  // Declares an empty array to store the information of "region."
    var x = new Array(36);

    for (var i = 0; i < 36; i++) {
      x[i] = new Array(36);
    }
  
  // Store the information of "region" in the array 'x'.
  let index = 0
  for (let value=0; value<36; value++){
    for (var k = 0; k<36; k++){
      if(array[0][value] == undefined){
        for (let j =0; j<36; j++)
          x[index][j] = 0
      }
      else if (array[0][value] != undefined){
        x[index][k] = array[0][value][k]
        if(x[index][k] === true){
          x[index][k] = 1
        }
        else{
          x[index][k] = 0
        }
        
      }
    }
        index++
  }

  // Remove the row and column corresponding to the unsued shape.
  let j = 0;
  let limit = 36;
  let counter = 0;
  while(j < skipval.length ){
    for(let i = 0; i < limit; i++){
      x[i].splice(skipval[j] - counter,1);
    }
    x.splice((skipval[j] - counter ,skipval[j] - counter), 1);
    
    j++;
    limit--;
    counter++;
  }
  
  // Ready to color using the adjacency matrix
  graph = x;
  console.log(x.length)
  V = x.length
  graphColoring(graph, 3, containarray, board);
}

// Check if the 3-Coloring is possible.
function graphColoring(graph, m, containarray, board){

  let color = []
  for (let i = 0; i < V; i++){
    color[i] = 0;
  }

  // Call function graphColoringCheck for vertex 0
  if (graphColoringCheck(graph, m, color, 0, containarray, board) == false){
    console.log("No Solution");
    return false;
  }

  // Print the solution
  printSolution(color, containarray, board);
  return true;
}

function isSafe (v, graph, color, c, containarray, board){

  for (let i = 0; i < V; i++){

  if (graph[v][i] && c == color[i])
      return false;
  }
  return true;
}

function graphColoringCheck(graph, m, color, v, containarray, board){
  // If all vertices are assigned a color, then return true
  if (v == V)
    return true;

  // Consider this vertex v and try different colors
  for (let c = 1; c <= m; c++){
    // Check if assignment of color c to v is fine
    if (isSafe(v, graph, color, c, containarray, board)){
      color[v] = c;

      // assign a color for the rest of the vertices recursively
      if (graphColoringCheck (graph, m, color, v+1, containarray, board) == true)
        return true;

      // If assigning color c doesn't lead to a solution then remove it
      color[v] = 0;
    }
  }

  // If no color can be assigned to this vertex then return false
  return false;
}

// Check the colors assigned to each shape and ready to print.
function printSolution(color, containarray, board)
{
  console.log("Solution Exists: \n");
  console.log("Color Lists", color);
  
  threecolorpaint(color, containarray, board)
}

// Paint the solution
async function threecolorpaint(color, containarray, board){
  let keyarray = [];
  console.log("contain array", containarray)
    puzzle.stack.forEach(function(state) {
    var shape;
    shape = state.shapes[state.index];
      keyarray.push(shape.key)
    });
  
  wcounter = 0;
  let counter = 0
  let value = 0;
  while(wcounter < 36){
    

  // Paint the solution
  await sleep(500)
  for(let i=0; i<15; i++){
    for(let j=0; j<15; j++){

      if(containarray[value] != undefined){
        if(color[counter] == 1){
          if(board[i][j] == containarray[value]){
            fill('red')
            rect(j*25, i*25, 25, 25)
          }
        }

        else if (color[counter] == 2){
          if(board[i][j] == containarray[value]){
            fill('blue')
            rect(j*25, i*25, 25, 25)        
          }
        }

        else if (color[counter] == 3){
          if(board[i][j] == containarray[value]){
            fill('yellow')
            rect(j*25, i*25, 25, 25)      
          }
        }
      }
      else{
        value++;
      }
    }
  }  
        wcounter++;
        value++;
        counter++;
  }
}
