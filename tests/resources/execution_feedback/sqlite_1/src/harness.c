/*
   FANDANGO with FCC puts the generated input into a temporary file, passing the
   filepath as an argument to the program.
   `sqlite3.h` & `sqlite3.c` containt an Amalgamation of Sqlite (without support
   for external libraries and the CLI program). We pass the file path to this
   program, which reads the produced SQL command.
 */

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <temporary input file>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Error: Could not open file");
    return 1;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return 1;
  }

  long size = ftell(file);
  if (size < 0) {
    fclose(file);
    return 1;
  }
  rewind(file);

  char *sql = malloc((size_t)size + 1);
  if (!sql) {
    perror("Malloc error");
    fclose(file);
    return 1;
  }

  size_t bytes_read = fread(sql, 1, (size_t)size, file);
  int read_failed = ferror(file);
  fclose(file);

  if (read_failed) {
    free(sql);
    return 1;
  }

  sql[bytes_read] = '\0';
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  const char *db_filename = "database.db";
  rc = sqlite3_open(db_filename, &db);

  if (rc) {
    printf("Can't open database: %s\n", sqlite3_errmsg(db));
    remove(db_filename);
    return 1;
  }
  // Use the Input Created by the fuzzzer
  rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

  sqlite3_close(db);
  free(sql);
  remove(db_filename);

  printf("Error message: %s\n", zErrMsg);

  return 0;
}
