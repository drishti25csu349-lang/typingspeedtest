#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    char text[] = "Welcome to the Typing Speed Test!";
    char input[200];
    clock_t start, end;

    printf("%s\n", text);
    printf("Start typing and press Enter when done:\n");

    start = clock();
    fgets(input, sizeof(input), stdin);
    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    int correct = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == input[i])
            correct++;
    }

    double accuracy = ((double)correct / strlen(text)) * 100;
    double wpm = ((strlen(input) / 5.0) / (time_taken / 60.0));

    printf("\nTime: %.2f sec\nAccuracy: %.2f%%\nWPM: %.2f\n",
           time_taken, accuracy, wpm);

    return 0;
}
