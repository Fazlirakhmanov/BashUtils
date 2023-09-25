#ifndef CAT_H
#define CAT_H

#include <stdbool.h>

typedef struct {
  bool b_number_nonblank;
  bool E_show_ends;
  bool e_show_ends_nonprinting;
  bool n_number;
  bool s_squeeze_blank;
  bool T_show_tabs;
  bool t_show_tabs_nonprinting;
  bool v_show_nonprinting;
  int countLines;
  int countBreaks;
  int countFiles;
  bool isCurrentLineIsBreak;
  bool isPreviousLineIsBreak;
} Flags;

void s21_cat(int argc, char **argv);
void parcer(int argc, char *argv[], Flags *short_options);
void runCat(int argc, char *argv[], Flags *short_options);
void printCat(char ch, Flags *short_options);
void print_error();

#endif