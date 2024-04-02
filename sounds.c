#include <stdio.h>
#include <stdlib.h> // for system function
#include <unistd.h> // for usleep function

void playSound(const char* soundFile) {
    char command[256];
    snprintf(command, sizeof(command), "afplay %s &", soundFile); // Audio File Play... I guess only for Mac?
    // printf("Command: %s\n", command);
    system(command);
}

int main() {
    playSound("/Users/inezyoon/Desktop/git/term2git/Cveloppers/meow.wav");
    printf("During game you'll hear: \n");
    usleep(1000000); // 1 second = 1000000 microseconds)
    playSound("/Users/inezyoon/Desktop/git/term2git/Cveloppers/lose.wav");
    printf("If you lose: \n");
    usleep(3000000); // 3 seconds, thanks jason i can math properly
    playSound("/Users/inezyoon/Desktop/git/term2git/Cveloppers/win.wav");
    printf("If you win: \n");
    usleep(1000000);
    printf("DONE!\n");
    return 0;
}
