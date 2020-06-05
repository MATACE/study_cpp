// C system head
#include <stdio.h>

// C++ system head

// Other lib head

// Locate project lib head

// Custom #define

#define crBegin(state) switch (state) { case 0:

#define crReturn(state, ret) (state) = __LINE__; return (ret); case __LINE__:

#define crEnd() }

// Use namespace

typedef struct {
    int i;
    int num;
    int state;
} task;

int cb(task *t)
{
    crBegin(t->state);
    for (;;) {
        t->num = 1;
        for (t->i = 0; t->i < 20; t->i++) {
            crReturn(t->state, t->num);
            t->num += 1;
        }
    }
    crEnd();
}

int main(int argc, char const *argv[])
{
    task t;
    int i;

    t.state = 0;

    for (i = 0; i < 100; i++) {
        if (i % 5 == 0) {
            printf("\n");
        }
        printf("%d ", cb(&t));
    }
    return 0;
}