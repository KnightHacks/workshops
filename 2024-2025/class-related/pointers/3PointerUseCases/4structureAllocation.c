#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct User {
  int id;
  int *friend_id_list;
} User;

int main() {
  User user;
  user.friend_id_list = malloc(sizeof(int) * 2);
  user.id = 5;
  user.friend_id_list[0] = 0;
  user.friend_id_list[1] = 1;
  free(user.friend_id_list);

  User *users;
  users = malloc(sizeof(User) * SIZE);
  for (int i=0; i < SIZE; i++){
    users[i].id = i;
    users[i].friend_id_list = malloc(sizeof(int) * 2);
  }

  printf("%d\n", users[1].id);        // prints "1"
  printf("%d\n", (*(users+1)).id);    // prints "1"
  printf("%d\n", (users+1)->id);      // prints "1"

  for (int i=0; i < SIZE; i++){
    free(users[i].friend_id_list);
  }
  free(users);

  return 0;
}
