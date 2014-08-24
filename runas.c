#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sysexits.h>
#include <unistd.h>

#define MAX_GROUPS 10

static char* progname;

void
drop_privs(const char *user)
{
    struct passwd *usr;
    struct group *grp;
    char uid[10];
    gid_t groups[MAX_GROUPS];
    int ngroups = MAX_GROUPS;

    usr = getpwnam(user);
    if (usr == NULL) {
        perror(progname);
        if (errno == ENOENT) {
            exit(EX_NOUSER);
        } else {
            exit(3);
        }
    }

    ngroups = getgrouplist(user, usr->pw_gid, groups, &ngroups);
    if (ngroups < 0) {
        // FIXME Handle more than 10 groups
        perror("getgrouplist");
        exit(3);
    }

    if (setgid(usr->pw_gid)) {
        perror("setgid");
        exit(3);
    }
    if (setgroups(ngroups, groups)) {
        perror("setgroups");
        exit(3);
    }
    if (setuid(usr->pw_uid)) {
        perror("setuid");
        exit(3);
    }
    if (setenv("USER", user, 1)) {
        perror(progname);
        exit(3);
    }
    if (setenv("HOME", usr->pw_dir, 1)) {
        perror(progname);
        exit(3);
    }
    if (setenv("SHELL", usr->pw_shell, 1)) {
        perror(progname);
        exit(3);
    }
    if (snprintf(uid, 10, "%d", usr->pw_uid) >= 10) {
        fprintf(stderr, "%s: UID %d too long\n", progname, usr->pw_uid);
        exit(3);
    }
    if (setenv("UID", uid, 1)) {
        perror(progname);
        exit(3);
    }
}

int
main(int argc, char **argv)
{
    const char *user;
    int ec, i;
    char **prog_args;
    progname = argv[0];
    if (argc < 3) {
        fprintf(stderr, "usage: %s user program [args]\n", progname);
        return 2;
    }

    user = argv[1];
    drop_privs(user);

    prog_args = alloca(sizeof(char*) * argc - 1);
    for (i = 2; i < argc; i++) {
        prog_args[i-2] = argv[i];
    }
    prog_args[argc - 2] = NULL;
    execvp(prog_args[0], prog_args);
    perror(progname);
    return 3;
}
