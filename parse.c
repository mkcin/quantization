#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#define BUFFER 32

#define INPUT_ASSERT(expression) if(!(expression)) goto wrong_input;
#define IGNORE_ASSERT(expression) if(!(expression)) goto ignore_input;
#define ALLOC_ASSERT(expression) if(!(expression)) goto alloc_error;

static const char* DECLARE = "DECLARE";
static const char* REMOVE = "REMOVE";
static const char* VALID = "VALID";
static const char* ENERGY = "ENERGY";
static const char* EQUAL = "EQUAL";

static uint64_t convert_to_ull(const char* s)
{
  int sl=strlen(s);
  uint64_t val = 0;
  for(int i=0; i<sl; i++)
    val = val*10+s[i]-'0';
  return val;
}

inline static int correct_history (const char* s)
{
  int sl=strlen(s);
  for(int i=0; i<sl; i++)
    if(!(s[i]-'0' >= 0 && s[i]-'0' <= 3))
      return 0;
  return 1;
}

inline static int correct_word (const char* s)
{
  int sl=strlen(s);
  for(int i=0; i<sl; i++)
    if(!islower(s[i]))
      return 0;
  return 1;
}

inline static int correct_energy (const char* s)
{
  int sl=strlen(s);
  for(int i=0; i<sl; i++)
    if(!isdigit(s[i]))
      return 0;
  uint64_t val = 0;
  for(int i=0; i<sl; i++)
    if(val*10+s[i]-'0' < val)
      return 0;
    else
      val=val*10+s[i]-'0';
  return 1;
}

inline static int valid_line(const char* s)
{
  if(s[0] == '#') return 1;
  int space = 1;
  for(int i=0; s[i]!='\0'; i++) {
    if(s[i] == ' ') {
      if(space)
        return 0;
      else
        space = 1;
    }
    else if(isupper(s[i]) || isdigit(s[i]) || s[i]=='\n')
      space = 0;
    else
      return 0;
  }
  int sl=strlen(s);
  if(sl != 0 && s[sl-1] == ' ') return 0;
  return 1;
}

char *read_string(void (*destroy)())
{
  char *str = malloc(sizeof(char) * BUFFER), *err = NULL;
  ALLOC_ASSERT(str);
  uint32_t pos, curr_char;
  for(pos = 0; str != NULL && (curr_char = fgetc(stdin)) != '\n'; pos++)
  {
    str[pos] = (char)curr_char;
    if(feof(stdin)) {
      if(pos != 0) INPUT_ASSERT(0);
      break;
    }
    if(pos % BUFFER == BUFFER - 1) {
      if((err = realloc(str, sizeof(char) * (BUFFER + pos + 1))) == NULL)
        ALLOC_ASSERT(0)
      str = err;
      err=NULL;
    }
  }
  free(err);
  if(str != NULL) {
    str = realloc(str, pos+1);
    ALLOC_ASSERT(str);
    str[pos] = '\0';
    if(str[0] != '#' && strlen(str) != pos) INPUT_ASSERT(0)
  }
    // str[pos] = '\0';
  return str;

alloc_error:
  free(str);
  free(err);
  destroy();
  exit(1);
wrong_input:
  free(str);
  free(err);
  return NULL;
}

char *nth_word(const char *s, int n, void (*destroy)()) {
  const int CHUNK = 200;
  int length = strlen(s);
  char *word = NULL;
  int space=0, pointer=0, size=CHUNK;
  for(int i=0; i<length; i++) {
    if(s[i] == ' ') {
      space++;
      if(space == n) {
        break;
      }
    }
    else if(space == n-1) {
      if(word == NULL) {
        word = malloc(CHUNK*sizeof(char));
        ALLOC_ASSERT(word!=NULL)
      }
      word[pointer++] = s[i];
      if(s[i] == '\n') {
        if(pointer == 1) {
          free(word);
          return NULL;
        }
        word = realloc(word, pointer);
        ALLOC_ASSERT(word!=NULL)
        word[pointer-1] = '\0';
        return word;
      }
      if(pointer%CHUNK == 0) {
        size += CHUNK;
        word = realloc(word, size);
        ALLOC_ASSERT(word!=NULL)
      }
    }
  }
  if(word==NULL) return NULL;
  word = realloc(word, pointer+1);
  word[pointer] = '\0';
  ALLOC_ASSERT(word!=NULL)
  return word;

alloc_error:
  destroy();
  exit(1);
}

void parse(
  void (*insert)(const char*),
  void (*delete)(const char*),
  void (*valid)(const char*),
  void (*equal)(const char*, const char*),
  void (*get_value)(const char*),
  void (*set_value)(const char*, uint64_t),
  void (*destroy)()
)
{
  char *splited[5] = {NULL, NULL, NULL, NULL, NULL};
  char* line = NULL;

  line = read_string(destroy);

  INPUT_ASSERT(line)
  INPUT_ASSERT(valid_line(line));

  int words_number = 0;
  for(int i=1; i<=4; i++) {
    splited[i] = nth_word(line, i, destroy);
    words_number += (splited[i]!=NULL);
  }
  IGNORE_ASSERT(!(words_number == 0 || splited[1][0]=='#'))
  INPUT_ASSERT(words_number <= 3)
  if (strcmp(splited[1], DECLARE) == 0) {
    INPUT_ASSERT(words_number == 2)
    INPUT_ASSERT(correct_history(splited[2]))
    insert(splited[2]);
  }
  else if(strcmp(splited[1], REMOVE) == 0) {
    INPUT_ASSERT(words_number == 2)
    INPUT_ASSERT(correct_history(splited[2]))
    delete(splited[2]);
  }
  else if(strcmp(splited[1], VALID) == 0) {
    INPUT_ASSERT(words_number == 2)
    INPUT_ASSERT(correct_history(splited[2]))
    valid(splited[2]);
  }
  else if(strcmp(splited[1], ENERGY) == 0) {
    INPUT_ASSERT(words_number == 2 || words_number == 3)
    INPUT_ASSERT(correct_history(splited[2]))
    if(words_number == 2)
      get_value(splited[2]);
    else {
      INPUT_ASSERT(correct_energy(splited[3]))
      set_value(splited[2], convert_to_ull(splited[3]));
    }
  }
  else if(strcmp(splited[1], EQUAL) == 0) {
    INPUT_ASSERT(words_number == 3)
    INPUT_ASSERT(correct_history(splited[2]))
    INPUT_ASSERT(correct_history(splited[3]))
    equal(splited[2], splited[3]);
  }
  else
    INPUT_ASSERT(0)

  free(line);
  for(int i=1; i<=4; i++) {
    if(splited[i]) free(splited[i]);
  }
  return;

ignore_input:
  free(line);
  for(int i=1; i<=4; i++) {
    free(splited[i]);
  }
  return;
wrong_input:
  fprintf(stderr, "ERROR\n");
  free(line);
  for(int i=1; i<=4; i++) {
    free(splited[i]);
  }
}

#undef BUFFER
#undef INPUT_ASSERT
#undef ALLOC_ASSERT
#undef IGNORE_ASSERT
