///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:a
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 

// CS 136
//  
// Name: Richard Yuan
// login ID: kqyuan
///////////////////////////////////////////////////////////////////////////// 

#include "suggest.h"
#include <string.h>
#include <assert.h>
#include "cs136-trace.h"

///////////////////////////////////////////////////////////////////////////// 
// do not modify this constants:
const int SUGGEST_MAX_STRLEN = 63;
/////////////////////////////////////////////////////////////////////////////

// delete(dict, word) deletes a letter from the word.
// time: O(n^2)
static void delete(const struct triple_s *dict, const char *word, 
                   struct triple_s *dict2) {
  int len = strlen(word);
  char str[64];
  for (int i = 0; i < len; ++i) {
    strcpy(str, word);
    for (int j = i; j < len; ++j) {
      str[j] = str[j + 1];
    }
    if (sss_search(dict, str) != -1) {
      sss_add(dict2, str);
    }
  }
}

// insert(dict, word, dict2) enters a letter to the word
// time: O(n^2)
static void insert(const struct triple_s *dict, const char *word, 
                   struct triple_s *dict2) {
  int len = strlen(word) + 1;
  char str[64];
  char store1;
  char store2;
  for (int i = 0; i < len; ++i) {
    strcpy(str, word);
    store1 = str[i];
    for (int j = i; j < len - 1; ++j) {
      store2 = str[j + 1];
      str[j + 1] = store1;
      store1 = store2;
    }
    for (int c = 97; c < 123; ++c) {
      str[i] = c;
      if (sss_search(dict, str) != -1) {
        sss_add(dict2, str);
      }
    }
  }
}

// sub(dict, word, dict2) substitutes a letter with a char in a word
// time: O(n^2)
static void sub(const struct triple_s *dict, const char *word, 
                struct triple_s *dict2) {
  int len = strlen(word);
  char str[64];
  char store1;
  for (int i = 0; i < len; ++i) {
    strcpy(str, word);
    store1 = str[i];
    for (int c = 97; c < 123; ++c) {
      str[i] = c;
      if (sss_search(dict, str) != -1) {
        sss_add(dict2, str);
      }
    }
  }
}

// adjacent(dict, word, dict2) swaps adjacent letters of a word by one
// time: O(n)
static void adjacent(const struct triple_s *dict, const char *word, 
                     struct triple_s *dict2) {
  int len = strlen(word);
  char str[64];
  char store1;
  for (int i = 0; i < len - 1; ++i) {
    strcpy(str, word);
    store1 = str[i];
    str[i] = str[i + 1];
    str[i + 1] = store1;
    if (sss_search(dict, str) != -1) {
      sss_add(dict2, str);
    }
  }
}

struct triple_s *suggest(const struct triple_s *dict, const char *word) {
  assert(dict);
  assert(word);
  int len = strlen(word);
  assert(len < SUGGEST_MAX_STRLEN);
  struct triple_s *dict2 = sss_create();
  delete(dict, word, dict2);
  insert(dict, word, dict2);
  sub(dict, word, dict2);
  adjacent(dict, word, dict2);
  return dict2;      
}
