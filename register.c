#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int username_exists(const char *username) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("<p>Error: Could not open the file.</p>");
        return 0;
    }

    char line[100], stored_username[50];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%*s", stored_username);
        if (strcmp(stored_username, username) == 0) {
            fclose(file);
            return 1;  // Username exists
        }
    }

    fclose(file);
    return 0;  // Username does not exist
}

void save_user(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("<p>Error: Could not open the file.</p>");
        return;
    }

    fprintf(file, "%s,%s\n", username, password);
    fclose(file);
}

int main() {
    printf("Content-Type: text/html\n\n");

    char *data = getenv("CONTENT_LENGTH");
    if (data == NULL) {
        printf("<p>Error: No data received!</p>");
        return 1;
    }

    int length = atoi(data);
    char input[length + 1];
    fgets(input, length + 1, stdin);

    char username[50], password[50];
    sscanf(input, "username=%[^&]&password=%s", username, password);

    if (username_exists(username)) {
        printf("<script>alert('Username already exists. Please choose a different username.');</script>");
        printf("<script>window.location.href = '/register.html';</script>");
    } else {
        save_user(username, password);
        
          printf("<script>alert('Registration Successful!');</script>");
        printf("<script>window.location.href = '/login.html';</script>");
    }

    return 0;
}
