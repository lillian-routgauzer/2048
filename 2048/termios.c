#include "game.h"

// getchar with termios.
char getch() {
  char buf = 0;

  // structure to store original terminal settings
  struct termios old = {0};
  fflush(stdout);

  // take current terminal attributes and store them in 'old'
  if (tcgetattr(0, &old) < 0) {
    perror("tcsetattr()");
  }

  // turns off canonical mode
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;

  // set minimum number of characters to read to 1 and timeout to 0 seconds
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;

  // apply modified terminal settings
  if (tcsetattr(0, TCSANOW, &old) < 0) {
    perror("tcsetattr ICANON");
  }
  // read a single character from the terminal
  if (read(0, &buf, 1) < 0) {
    perror("read()");
  }

  // restore og terminal settings
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;

  // apply restored terminal settings
  if (tcsetattr(0, TCSADRAIN, &old) < 0) {
    perror("tcsetattr ~ICANON");
  }

  // return the character read from the terminal
  return buf;
}