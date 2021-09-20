#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Take user's name and say hello
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}