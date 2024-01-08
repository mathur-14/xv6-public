#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

typedef unsigned char u_char;
int strcasecmp(const char *s1, const char *s2);
char tolower(unsigned char ch);

char buf[5120];
char prev_buf[5120], curr_buf[5120], new_buf[1000][5120], new_dup_buf[1000][5120], prev_dup[5120];
int buf_dups[1000];

void uniq(int fd, char *name, int flag_c, int flag_d, int flag_i) {
  int n, i, j, d, line, d_line, dup_count;
  i = j = line = d_line = d = 0;
  dup_count = 1;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    for(i=0; i<n; i++){
      if(buf[i] == '\n' || i == n-1) {
        j=0;
        if((flag_i == 0 && strcmp(prev_buf, curr_buf) != 0) || (flag_i == 1 && strcasecmp(prev_buf, curr_buf) != 0)) {
          strcpy(prev_buf, curr_buf);
          strcpy(new_buf[line], curr_buf);
          line++;
          buf_dups[d_line-1] = dup_count;
          dup_count=1;
          d_line++;
          if(strcmp(prev_dup, "") != 0) {
            strcpy(new_dup_buf[d], prev_dup);
            d++;
            strcpy(prev_dup, "");
          }
        }
        else {
          dup_count = dup_count + 1;
          strcpy(prev_dup, curr_buf);
        }
      }
      else {
        curr_buf[j] = buf[i];
        j++;
      }
    }
    buf_dups[d_line-1] = dup_count;
  }
  if(strcmp(prev_dup, "") != 0) {
    strcpy(new_dup_buf[d], prev_dup);
    d++;
  }
  if(n < 0){
    printf(1, "uniq: read error\n");
    exit();
  }
  if(flag_c == 1)
    for(i = 0; i < line; i++) {
      printf(1, "%d %s\n",buf_dups[i], new_buf[i]);
    }
  else if(flag_d == 1)
    for(i = 0; i < d; i++) {
      printf(1, "%s\n", new_dup_buf[i]);
    }
  else
    for(i = 0; i < line; i++) {
      printf(1, "%s\n", new_buf[i]);
    }
}

char tolower(unsigned char ch) {
  if (ch >= 'A' && ch <= 'Z')
    ch = 'a' + (ch - 'A');
  return ch;
}

int strcasecmp(const char *s1, const char *s2) {
  const unsigned char *us1 = (const u_char *)s1, *us2 = (const u_char *)s2;

  while (tolower(*us1) == tolower(*us2++))
    if (*us1++ == '\0')
      return (0);
  return (tolower(*us1) - tolower(*--us2));
}

int main(int argc, char *argv[]) {
  int fd, i;
  int flag_c, flag_i, flag_d;
  flag_c = flag_d = flag_i = 0;

  if(argc <= 1){
    uniq(0, "", flag_c, flag_i, flag_d);
    exit();
  }

  for(i = 1; i < argc; i++){
    if(argv[i][0] == '-') {
      switch(argv[i][1]) {
        case 'c':
          flag_c = 1;
          break;
        case 'd':
          flag_d = 1;
          break;
        case 'i':
          flag_i = 1;
          break;
        default:
          break;
      }
      continue;
    }
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[i]);
      exit();
    }
    uniq(fd, argv[i], flag_c, flag_d, flag_i);
    close(fd);
  }
  exit();
}
