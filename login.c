#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int authenticate_user(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("<p>Error: Could not open the file.</p>");
        return 0;
    }

    char line[100], stored_username[50], stored_password[50];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%s", stored_username, stored_password);
        if (strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
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

    if (authenticate_user(username, password)) {
        printf("<h1>Login Successful</h1>");
        printf("<p>Welcome, %s!</p>", username);
        printf("<a href=\"/cgi-bin/logout.cgi\"><button>Logout</button></a>");
    } else {
        printf("<script>alert('Invalid username or password. Please try again.');</script>");
        printf("<script>window.location.href = '/login.html';</script>");
    }

    return 0;
}
