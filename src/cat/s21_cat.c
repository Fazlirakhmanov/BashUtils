#define _GNU_SOURCE

#include "s21_cat.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  s21_cat(argc, argv);
  return 0;
}

void s21_cat(int argc, char **argv) {
  if (argc < 2) {
    print_error();
    exit(1);
  }
  Flags short_options = {false, false, false, false, false, false, false,
                         false, 1,     0,     0,     false, false};
  parcer(argc, argv, &short_options);
  runCat(argc, argv, &short_options);
}

void parcer(int argc, char *argv[], Flags *short_options) {
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  int option = 0;
  while ((option = getopt_long(argc, argv, "bEensTtv", long_options, NULL)) !=
         -1) {
    switch (option) {
      case 'n':
        short_options->n_number = true;
        break;
      case 'b':
        short_options->b_number_nonblank = true;
        break;
      case 's':
        short_options->s_squeeze_blank = true;
        break;
      case 'T':
        short_options->T_show_tabs = true;
        break;
      case 't':
        short_options->t_show_tabs_nonprinting = true;
        break;
      case 'e':
        short_options->e_show_ends_nonprinting = true;
        break;
      case 'E':
        short_options->E_show_ends = true;
        break;
      case 'v':
        short_options->v_show_nonprinting = true;
        break;
      default:
        fprintf(stderr, "Error: Invalid arguments\n");
        exit(1);
    }
  }
}

void runCat(int argc, char *argv[], Flags *short_options) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      FILE *file = fopen(argv[i], "rb");
      if (file == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
        continue;
      }
      short_options->countFiles++;
      int ch = 0;
      bool isLineBreak = false, isFirstCh = true;
      if (short_options->countFiles > 1 && fgetc(file) != EOF) {
        printf("\n");
        short_options->countLines++;
      }
      while ((ch = fgetc(file)) != EOF) {
        if (short_options->b_number_nonblank && isFirstCh && ch == '\n') {
          if (short_options->countFiles == 1)
            short_options->countLines = 0;
          else
            short_options->countLines--;
        }
        if (ch == '\n' && (isLineBreak || isFirstCh))
          short_options->countBreaks++;
        else
          short_options->countBreaks = 0;
        if (short_options->s_squeeze_blank && short_options->countBreaks > 1)
          continue;
        if (isLineBreak) {
          if (short_options->b_number_nonblank) {
            if (ch != '\n') short_options->countLines++;
          } else
            short_options->countLines++;
        }
        if (isLineBreak || isFirstCh) {
          if (short_options->n_number && !short_options->b_number_nonblank)
            printf("%6i\t", short_options->countLines);
          else if (short_options->b_number_nonblank && ch != '\n')
            printf("%6i\t", short_options->countLines);
        }
        if (ch == '\n')
          isLineBreak = true;
        else
          isLineBreak = false;
        isFirstCh = false;
        printCat(ch, short_options);
      }
    }
  }
}

void printCat(char ch, Flags *short_options) {
  if (short_options->v_show_nonprinting ||
      short_options->e_show_ends_nonprinting ||
      short_options->t_show_tabs_nonprinting) {
    if (ch >= 0 && ch <= 31 && ch != '\n' && ch != '\t') {
      printf("^%c", ch + 64);
    } else if (ch == 127) {
      printf("^?");
    } else if (ch == '\n' && (short_options->e_show_ends_nonprinting ||
                              short_options->E_show_ends)) {
      printf("%s", "$\n");
    } else if (ch == '\t' && (short_options->t_show_tabs_nonprinting ||
                              short_options->T_show_tabs)) {
      printf("%s", "^I");
    } else {
      printf("%c", ch);
    }
  } else if (short_options->T_show_tabs) {
    if (ch == '\t')
      printf("%s", "^I");
    else
      printf("%c", ch);
  } else if (short_options->E_show_ends) {
    if (ch == '\n')
      printf("%s", "$\n");
    else
      printf("%c", ch);
  } else
    printf("%c", ch);
}

void print_error() { printf("Please input correct flag and file name\n"); }
