#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

int main(void) {
    struct passwd *pw;

    pw = getpwnam("sp2021");
    printf("UID : %d\n", (int)pw->pw_uid);
    printf("Login Name : %s\n", pw->pw_name);
    printf("Password : %s\n", pw->pw_passwd);

    return 0;
}