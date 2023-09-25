#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  s21_grep(argc, argv);
  return 0;
}

void s21_grep(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr,
            "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
            "more information.\n");
    exit(1);
  }
  char *keywords[MAX_ARGS] = {NULL};
  char *commandLineArgumenstList[MAX_ARGS] = {NULL};
  char *files[MAX_ARGS] = {NULL};
  FILE *file;
  Flags flags = {false, false, false, false, false,
                 false, false, false, false, false};
  Options addOptions = {0, 0, 0, 0, 0};
  createKeywordsList(argv, keywords, &addOptions);
  makeCommandlineArgumentsList(argc, argv, commandLineArgumenstList);
  while (readFlagsGrep(argc, argv, &flags, keywords, &addOptions) != -1)
    ;
  makeFilesList(argc, commandLineArgumenstList, &flags, files, &addOptions);
  runGrep(&flags, keywords, files, &file, &addOptions);
  for (int j = 0; j < addOptions.countKeywords; j++) free(keywords[j]);
}

int readFlagsGrep(int argc, char *argv[], Flags *flags, char *keywords[],
                  Options *addOptions) {
  int option = getopt(argc, argv, "e:ivclnhsof:");
  switch (option) {
    case 'e':
      if (flags->e_pattern != true && flags->f_file != true) {
        for (int j = 0; j < addOptions->countKeywords; j++) {
          free(keywords[j]);
        }
        addOptions->countKeywords = 0;
      }
      flags->e_pattern = true;
      appendKeywordsList(keywords, optarg, addOptions);
      break;
    case 'i':
      flags->i_ignoreCase = true;
      break;
    case 'v':
      flags->v_invertMatch = true;
      break;
    case 'c':
      flags->c_count = true;
      break;
    case 'l':
      flags->l_filesWithMatches = true;
      break;
    case 'n':
      flags->n_lineNumber = true;
      break;
    case 'h':
      flags->h_noFilename = true;
      break;
    case 's':
      flags->s_noMessages = true;
      break;
    case 'o':
      flags->o_onlyMatching = true;
      break;
    case 'f':
      if (flags->f_file != true && flags->e_pattern != true) {
        for (int j = 0; j < addOptions->countKeywords; j++) {
          free(keywords[j]);
        }
        addOptions->countKeywords = 0;
      }
      flags->f_file = true;
      createKeywordsListF(keywords, optarg, addOptions);
      break;
  }
  return option;
}

void makeCommandlineArgumentsList(int argc, char *argv[],
                                  char *commandLineArgumenstList[]) {
  for (int i = KEYWORD_INDEX; i < argc; i++) {
    commandLineArgumenstList[i - 1] = argv[i];
  }
}

void makeFilesList(int argc, char *commandLineArgumentsList[], Flags *flags,
                   char *files[], Options *addOptions) {
  int isFlagAtTheBeginning = false;
  for (int i = 0, j = 0; i < argc - 1; i++) {
    if (i == 0 && (flags->e_pattern || flags->f_file) == false) {
      if (commandLineArgumentsList[i][0] == '-') isFlagAtTheBeginning = true;
      continue;
    }
    if (i > 0 && commandLineArgumentsList[i - 1][0] == '-') {
      if (strlen(commandLineArgumentsList[i - 1]) > 2) {
        if (strchr(commandLineArgumentsList[i - 1] + 2, 'e') != NULL ||
            strchr(commandLineArgumentsList[i - 1] + 2, 'f') != NULL)
          continue;
      } else if (strcmp(commandLineArgumentsList[i - 1], "-e") == 0 ||
                 strcmp(commandLineArgumentsList[i - 1], "-f") == 0)
        continue;
    }
    if (commandLineArgumentsList[i][0] == '-') continue;
    if (i > 0 && isFlagAtTheBeginning &&
        commandLineArgumentsList[i - 1][0] == '-' &&
        commandLineArgumentsList[i][0] != '-') {
      continue;
    }
    files[j] = commandLineArgumentsList[i];
    j++;
    addOptions->countFiles++;
  }
}

void createKeywordsList(char *argv[], char *keywords[], Options *addOptions) {
  int i = KEYWORD_INDEX;
  while (argv[i][0] == '-') i++;
  keywords[addOptions->countKeywords] = malloc(strlen(argv[i]) + 1);
  strcpy(keywords[addOptions->countKeywords], argv[i]);
  addOptions->countKeywords++;
}

void appendKeywordsList(char *keywords[], char *optarg, Options *addOptions) {
  keywords[addOptions->countKeywords] = malloc(strlen(optarg) + 1);
  strcpy(keywords[addOptions->countKeywords], optarg);
  addOptions->countKeywords++;
}

void createKeywordsListF(char *keywords[], char *optarg, Options *addOptions) {
  char lineFromFile[BUFSIZ];
  FILE *file = fopen(optarg, "r");
  if (file == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
    exit(1);
  }
  while (fgets(lineFromFile, sizeof lineFromFile, file) !=
         NULL) {  // lineFromFile
    if (lineFromFile[strlen(lineFromFile) - 1] == '\n')
      lineFromFile[strlen(lineFromFile) - 1] = '\0';
    keywords[addOptions->countKeywords] = malloc(strlen(lineFromFile) + 1);
    strcpy(keywords[addOptions->countKeywords], lineFromFile);
    addOptions->countKeywords++;
  }
  fclose(file);
}

void runGrep(Flags *flags, char *keywords[], char *files[], FILE **file,
             Options *addOptions) {
  char lineFromFile[BUFSIZ];
  for (int i = 0; i < addOptions->countFiles; i++) {
    *file = fopen(files[i], "r");
    if (*file == NULL) {
      fprintf(stderr, "grep: %s: No such file or directory\n", files[i]);
      continue;
    }
    int j = 0;
    while (fgets(lineFromFile, sizeof lineFromFile, *file) !=
           NULL) {  // lineFromFile
      addOptions->countCurrentLine++;
      if (!flags->o_onlyMatching) {
        for (j = 0; j < addOptions->countKeywords; j++) {
          if (printGrep(lineFromFile, keywords[j], files[i], flags,
                        addOptions)) {
            break;
          }
        }
      }
      if (flags->o_onlyMatching)
        printGrepO(lineFromFile, keywords, files[i], flags, addOptions);
    }
    printGrepOthers(files[i], flags, addOptions);
    fclose(*file);
    addOptions->countMatches = 0;
    addOptions->countCurrentLine = 0;
  }
}

int printGrep(char *lineFromFile, char *keywordname, char *filename,
              Flags *flags, Options *addOptions) {
  int isMatched = false;
  if (regexResult(lineFromFile, keywordname, flags) == flags->v_invertMatch) {
    isMatched = true;
    addOptions->countMatches++;
    if (((flags->c_count || flags->l_filesWithMatches) == 0) &&
        !(flags->o_onlyMatching && flags->v_invertMatch)) {
      if (addOptions->countFiles > 1 && !(flags->h_noFilename))
        printf("%s:", filename);
      if (flags->n_lineNumber) printf("%d:", addOptions->countCurrentLine);
      if (!flags->o_onlyMatching) {
        if (lineFromFile[strlen(lineFromFile) - 1] == '\n')
          lineFromFile[strlen(lineFromFile) - 1] = '\0';
        printf("%s\n", lineFromFile);
      }
    }
  }
  return isMatched;
}

char *strndup_(const char *s, size_t n) {
  char *p;
  size_t n1;
  for (n1 = 0; n1 < n && s[n1] != '\0'; n1++) continue;
  p = malloc(n + 1);
  if (p != NULL) {
    memcpy(p, s, n1);
    p[n1] = '\0';
  }
  return p;
}

void printGrepO(char *lineFromFile, char *keywords[], char *filename,
                Flags *flags, Options *addOptions) {
  regex_t regex;
  regmatch_t match;
  int regexFlags = 0;
  if (flags->i_ignoreCase)
    regexFlags |= REG_ICASE;
  else
    regexFlags |= REG_EXTENDED;
  int offset = 0;
  int isMatchFoundForFile = false;
  while (lineFromFile[offset] != '\0') {
    int isMatchFound = false;
    int min = strlen(lineFromFile);
    int max = 0;
    int result = -1;
    for (int j = 0; j < addOptions->countKeywords; j++) {
      result = regcomp(&regex, keywords[j], regexFlags);
      if (result != 0) {
        fprintf(stderr, "Error compiling regular expression\n");
        regfree(&regex);
      }
      if (regexec(&regex, &lineFromFile[offset], 1, &match, 0) ==
          flags->v_invertMatch) {
        if (result != 0 && result != REG_NOMATCH) {
          fprintf(stderr, "Error executing regexec\n");
        }
        isMatchFound = true;
        isMatchFoundForFile = true;
        if (min > offset + match.rm_so) {
          min = offset + match.rm_so;
          max = offset + match.rm_eo;
        }
      }
      regfree(&regex);
    }
    if (!isMatchFound || flags->v_invertMatch) {
      break;
    }
    char *matchedString = strndup_(&lineFromFile[min], max - min);
    if ((flags->c_count || flags->l_filesWithMatches) == 0 &&
        !flags->v_invertMatch) {
      if (addOptions->countFiles > 1 && !(flags->h_noFilename))
        printf("%s:", filename);
      if (flags->n_lineNumber) printf("%d:", addOptions->countCurrentLine);
      printf("%s\n", matchedString);
    }
    free(matchedString);
    offset = min + 1;
  }
  if (isMatchFoundForFile) addOptions->countMatches++;
}

void printGrepOthers(char *filename, Flags *flags, Options *addOptions) {
  if (flags->c_count) {
    if (!flags->l_filesWithMatches) {
      if (addOptions->countFiles > 1 && !flags->h_noFilename)
        printf("%s:", filename);
      printf("%d\n", addOptions->countMatches);
    } else if (addOptions->countMatches > 0) {
      printf("%s\n", filename);
    }
  } else if (flags->l_filesWithMatches && addOptions->countMatches > 0)
    printf("%s\n", filename);
}

int regexResult(char *lineFromFile, char *regexPattern, Flags *flags) {
  regex_t regex;
  int regexFlags = 0;
  int result = -1;
  if (flags->i_ignoreCase)
    regexFlags |= REG_ICASE;
  else
    regexFlags |= REG_EXTENDED;
  result = regcomp(&regex, regexPattern, regexFlags);
  if (result != 0) {
    fprintf(stderr, "Error compiling regular expression\n");
    regfree(&regex);
  }
  result = regexec(&regex, lineFromFile, 0, NULL, 0);
  if (result != 0 && result != REG_NOMATCH) {
    fprintf(stderr, "Error executing regexec\n");
  }
  regfree(&regex);
  return result;
}