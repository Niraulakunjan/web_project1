#include <stdio.h>
#include <stdlib.h>

int main() {
    // Send HTTP headers to clear the session cookie
    printf("Content-Type: text/html\n");
    printf("Set-Cookie: session=; expires=Thu, 01 Jan 1970 00:00:00 GMT; path=/\n\n");

    // Send the HTML content
    printf("<!DOCTYPE html>\n");
    printf("<html lang=\"en\">\n");
    printf("<head>\n");
    printf("    <meta charset=\"UTF-8\">\n");
    printf("    <title>Logout</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("    <h1>You have been logged out</h1>\n");
    printf("    <p>Redirecting to <a href=\"/index.html\">home page</a>...</p>\n");
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}
