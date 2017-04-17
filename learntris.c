#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define board (22, 10)

char board[22][10];
char activePiece[4 * sizeof(char)][4 * sizeof(char)];
int score = 0;
int lineCleared = 0;

void initializeBoard()
{
  for (int i = 0; i < 22; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      board[i][j] = '.';
    }
    // printf("\n");
  }
}

void printBoard()
{
  for (int i = 0; i < 22; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

void clearLines()
{


  for (int i = 0; i < 22; i++)
  {
    int clearable = 1;
    for (int j = 0; j < 10; j++)
    {

      // printf("%c", board[i][j]);
      // if the line isn't clearable
      if (board[i][j] == '.') { clearable = 0; }

      // if clearable
      if (clearable && j == 9)
      {
        // printf("clearing line %i\n", j);
        for (j = 0; j < 10; j++)
        {
          board[i][j] = '.';
          // printf("%c", board[i][j]);
        }
        score += 100;
        lineCleared += 1;
      }

    }
    // printf("\n");
  }
}

void createEmptyTetramino(int dimensions)
{
  char (*newPiece)[dimensions] = malloc( sizeof(char [dimensions][dimensions]) );
  // create empty tetramino
  for (int i = 0; i < dimensions; i++)
  {
    for (int j = 0; j < dimensions; j++)
    {
      // printf("currently at %i %i\n", i, j);
      newPiece[i][j] = '.';
      // printf("%c\n", newPiece[i][j]);
    }
  }

  // points active piece to newly created piece
  for (int i = 0; i < dimensions; i++)
  {
    for (int j = 0; j < dimensions; j++)
    {
      // printf("currently at %i %i\n", i, j);
      activePiece[i][j] = newPiece[i][j];
      // printf("%c\n", activePiece[i][j]);
    }
  }

  if (newPiece != NULL) (free(newPiece));

}

void printActiveTetramino()
{
  // loop through the tetramino array
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (activePiece[i][j] != 0)
      {
        printf("%c ", activePiece[i][j]);
      }

    }
    printf("\n");
  }
}

void createActiveTetramino(char piece)
{

  // creates the appropriate tetramino according to passed parameter
  switch (piece)
  {
    case 'I':
    createEmptyTetramino(4);

    for (int j = 0; j < 4; j++)
    {
      activePiece[1][j] = 'c';
    }
    break;

    case 'J':
    createEmptyTetramino(3);

    activePiece[0][0] = 'b';
    for (int j = 0; j < 3; j++)
    {
      activePiece[1][j] = 'b';
    }
    break;

    case 'L':
    createEmptyTetramino(3);

    activePiece[0][2] = 'o';
    for (int j = 0; j < 3; j++)
    {
      activePiece[1][j] = 'o';
    }
    break;

    case 'T':
    createEmptyTetramino(3);

    activePiece[0][1] = 'm';
    for (int j = 0; j < 3; j++)
    {
      activePiece[1][j] = 'm';
    }
    break;

    case 'O':
    createEmptyTetramino(2);
    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
      {
        activePiece[i][j] = 'y';
      }
    }
    break;

    case 'Z':
    createEmptyTetramino(3);

    activePiece[0][0] = 'r';
    activePiece[0][1] = 'r';
    activePiece[1][1] = 'r';
    activePiece[1][2] = 'r';
    break;

    case 'S':
    createEmptyTetramino(3);

    activePiece[0][1] = 'g';
    activePiece[0][2] = 'g';
    activePiece[1][0] = 'g';
    activePiece[1][1] = 'g';
    break;

    default:
    break;
  }
}

int main()
{
  char input = ' ';
  // char board[22][10];
  char character = ' ';

  initializeBoard();

  do
  {
    input = getc(stdin);

    // if the input is one of these characters...
    if (strpbrk(&input, "LSTOZJI") != 0) { createActiveTetramino(input); }

    switch (input)
    {
      case 'p':
      printBoard();
      break;

      case 'g':
      for (int i = 0; i < 22; i++)
      {
        for (int j = 0; j < 10; j++)
        {
          scanf(" %c", &character);
          board[i][j] = character;
        }
      }
      // printBoard();
      break;

      case 'c':
      initializeBoard();
      break;

      case 's':
      clearLines();
      break;

      case 't':
      printActiveTetramino();
      break;

      case '?':
      input = getc(stdin);
      switch (input)
      {
        case 's':
        printf("%i\n", score);
        break;
        case 'n':
        printf("%i\n", lineCleared);
        break;
        default: break;
      }
      break;

      // case 'q':
      // return 0;
      //
      // case EOF: break;
      // case '\n': break;
    }
  } while (input != 'q');
  return 0;
}
