#include <stdbool.h>
#include <stdio.h>

#ifndef S21_GREP_H
#define S21_GREP_H

#define KEYWORD_INDEX 1
#define MAX_ARGS 100

typedef struct {
  bool e_pattern;
  bool i_ignoreCase;
  bool v_invertMatch;
  bool c_count;
  bool l_filesWithMatches;
  bool n_lineNumber;
  bool h_noFilename;
  bool s_noMessages;
  bool f_file;
  bool o_onlyMatching;
} Flags;

typedef struct {
  int countFiles;
  int countKeywords;
  int countTotalLines;
  int countCurrentLine;
  int countMatches;
} Options;

void s21_grep(int argc, char *argv[]);
int readFlagsGrep(int argc, char *argv[], Flags *flags, char *keywords[],
                  Options *addOptions);
int printGrep(char *lineFromFile, char *keywordname, char *filename,
              Flags *flags, Options *addOptions);
void appendFilesList(char *argv[], int optind, char *files[]);
void appendFilesListForFlagE(char *argv[], char *files[]);
void createKeywordsList(char *argv[], char *keywords[], Options *addOptions);
void createKeywordsListF(char *keywords[], char *optarg, Options *addOptions);
void appendKeywordsList(char *keywords[], char *optarg, Options *addOptions);
void makeCommandlineArgumentsList(int argc, char *argv[],
                                  char *commandLineArgumenstList[]);
void makeFilesList(int argc, char *commandLineArgumenstList[], Flags *flags,
                   char *files[], Options *addOptions);
int regexResult(char *lineFromFile, char *regexPattern, Flags *flags);
void runGrep(Flags *flags, char *keywords[], char *files[], FILE **file,
             Options *addOptions);
char *strndup_(const char *s, size_t n);
void printGrepO(char *lineFromFile, char *keywords[], char *filename,
                Flags *flags, Options *addOptions);
void printGrepOthers(char *filename, Flags *flags, Options *addOptions);

#endif