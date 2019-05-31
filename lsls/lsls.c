#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

char *concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

int main(int argc, char **argv)
{
  struct dirent *entry;
  char *path;
  struct stat buffer;
  DIR *directory = opendir(argv[1]);

  if (argc != 2)
  {
    printf("Nope");
    exit(1);
  }

  if (directory == NULL)
  {
    printf("Something has gone horribly, horribly wrong");
    exit(1);
  }

  entry = readdir(directory);
  while (entry != NULL)
  {
    path = concat(argv[1], entry->d_name);
    stat(path, &buffer);

    if (S_ISREG(buffer.st_mode))
    {
      printf("%10llu  %s\n", buffer.st_size, entry->d_name);
    }
    else
    {
      printf("<DIR>  %s\n", entry->d_name);
    }
    entry = readdir(directory);
  }
  closedir(directory);
  free(path);

  return 0;
}