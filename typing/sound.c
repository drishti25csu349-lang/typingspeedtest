#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_SAMPLE_LEN 10000
#define MAX_TYPED_LEN  10000

// Count words
int countWords(const char *text) {
    int count = 0, inWord = 0;
    while (*text) {
        if (isspace((unsigned char)*text))
            inWord = 0;
        else if (!inWord) {
            inWord = 1;
            count++;
        }
        text++;
    }
    return count;
}

// Calculate accuracy
float calculateAccuracy(const char *original, const char *typed) {
    int correct = 0;
    int total = strlen(original);
    int typed_len = strlen(typed);
    for (int i = 0; i < total && i < typed_len; i++) {
        if (original[i] == typed[i]) correct++;
    }
    if (total == 0) return 0.0f;
    return ((float)correct / total) * 100.0f;
}

int main() {
    srand((unsigned int)time(NULL));

    // 🟢 Easy
    const char *easy25 =
        "The golden sun dipped below the horizon, painting the sky in shades of crimson and violet as a cool breeze whispered through the quiet village.";
    const char *easy50 =
        "As the first raindrops began to fall, children ran into the open field, laughing and twirling with joy, while their parents watched from porches, sipping warm tea, reminiscing about their own carefree childhood days when rain wasn’t just weather—it was a celebration of life, hope, and simple happiness.";
    const char *easy100 =
        "In the heart of the bustling city, where honking cars and flashing lights filled every corner, a small park remained untouched—a quiet haven for those seeking peace. Beneath a sprawling banyan tree, an old man sat daily, sketching the world around him with gentle strokes, capturing fleeting moments of beauty often ignored by hurried strangers. Children played nearby, their laughter echoing like a melody of innocence. The scent of blooming jasmine drifted through the air, blending with the distant aroma of street food, and for a brief, perfect moment, everything felt timeless, calm, and beautifully connected.";

    // 🟡 Medium
    const char *medium25 =
        "The library stood silent after dusk, its tall shelves guarding countless stories, while a single lamp burned softly beside a forgotten book of poetry.";
    const char *medium50 =
        "Beneath the fading evening light, the traveler rested by the riverside, tracing ripples with a stick as he pondered the many choices that had shaped his journey. Each reflection on the water reminded him of moments lost and found, teaching him that peace often comes quietly, after endless wandering.";
    const char *medium100 =
        "On the morning of her departure, the train station was unusually quiet, filled only with the hum of engines and the distant echo of announcements. She stood by the window, suitcase in hand, watching the world blur past like a painting in motion. Every sound—the whistle, the wheels, the murmur of strangers—seemed to pull her between the past she was leaving and the uncertain future ahead. As the train began to move, she felt both fear and freedom intertwine, realizing that sometimes, moving forward isn’t about escaping, but about trusting the journey to shape what lies beyond.";

    // 🔴 Hard
    const char *hard25 =
        "Amid the labyrinth of human ambition, silence emerges not as absence but as a profound articulation of thought, unspoken yet resonating with inexplicable clarity.";
    const char *hard50 =
        "When the tempest of uncertainty consumes rational thought, the mind retreats into abstract corridors of memory, weaving fragments of experience into elaborate justifications. Within this intricate architecture of reasoning, truth becomes elastic—stretching, reshaping, and often dissolving entirely beneath the weight of interpretation and the relentless pursuit of meaning.";
    const char *hard100 =
        "In an age obsessed with immediacy, where every fleeting impulse demands acknowledgment, the art of contemplation has become a quiet rebellion. The individual who dares to pause, to dwell within ambiguity rather than flee from it, discovers that understanding is not a sudden illumination but a gradual unfolding. Meaning, like light refracted through glass, changes shape depending on where one stands. Thus, wisdom is not acquired through accumulation of facts but through endurance of complexity—the patience to listen when silence speaks, and the courage to question even the certainties that promise comfort yet conceal the deeper contours of truth.";

    // --- Menu ---
    printf("===== Typing Speed Test =====\n");
    printf("Select Difficulty Level:\n1. Easy\n2. Medium\n3. Hard\n");
    int level; printf("Enter choice: "); scanf("%d", &level); getchar();
    if (level < 1 || level > 3) level = 1;

    printf("\nSelect Test Type:\n1. Word Count (25/50/100)\n2. Custom Text\n");
    int choice; printf("Enter choice: "); scanf("%d", &choice); getchar();

    const char *sample = NULL;
    if (choice == 1) {
        printf("\nSelect Word Limit:\n1. 25 words\n2. 50 words\n3. 100 words\n");
        int wc; printf("Enter choice: "); scanf("%d", &wc); getchar();
        switch (level) {
            case 1: sample = (wc == 1) ? easy25 : (wc == 2) ? easy50 : easy100; break;
            case 2: sample = (wc == 1) ? medium25 : (wc == 2) ? medium50 : medium100; break;
            case 3: sample = (wc == 1) ? hard25 : (wc == 2) ? hard50 : hard100; break;
        }
    } else {
        static char custom[MAX_SAMPLE_LEN];
        printf("\nEnter your custom text:\n");
        fgets(custom, sizeof(custom), stdin);
        custom[strcspn(custom, "\n")] = '\0';
        sample = custom;
    }

    // Timer selection
    printf("\nSelect Timer Duration:\n1. 30 seconds\n2. 60 seconds\n3. 120 seconds\n");
    int tChoice; printf("Enter choice: "); scanf("%d", &tChoice); getchar();
    int timerSeconds = (tChoice == 1) ? 30 : (tChoice == 2) ? 60 : 120;

    // Wrong-key beep toggle
    printf("\nEnable Beep Sound for Wrong Keys? (1=Yes, 0=No): ");
    int beepToggle; scanf("%d", &beepToggle); getchar();

    // Pre-start countdown
    system("cls");
    for (int i = 3; i >= 1; i--) {
        printf("Starting in %d...\n", i);
        Beep(800, 200); // beep on each count
        Sleep(800);
        system("cls");
    }
    Beep(1200, 300); // final beep

    system("cls");
    printf("===== Typing Speed Test =====\n");
    printf("You have %d seconds. Start typing:\n\n%s\n\n", timerSeconds, sample);
    printf("------------------------------------------\n");

    static char typed[MAX_TYPED_LEN];
    int pos = 0;
    time_t start = time(NULL);

    // Typing loop
    while (difftime(time(NULL), start) < timerSeconds) {

        int timeLeft = timerSeconds - (int)difftime(time(NULL), start);

        // live countdown
        printf("\033[s");  
        printf("\033[H");  
        printf("Time left: %2d seconds \n", timeLeft);
        printf("\033[u");  
        fflush(stdout);

        if (kbhit()) {
            char ch = getch();

            // stop on ENTER
            if (ch == 13) break;

            // backspace handling
            if (ch == 8 && pos > 0) {
                pos--;
                printf("\b \b");
            }
            else if (isprint(ch)) {
                typed[pos] = ch;

                // WRONG-KEY beep logic
                if (beepToggle && ch != sample[pos]) {
                    Beep(500, 100);
                }

                pos++;
                printf("%c", ch);
            }
        }
        Sleep(80);
    }

    typed[pos] = '\0';

    // TIME UP ALERT
    Beep(1500, 400);  
    Beep(1500, 400);
    system("cls");
    printf("\n\n  TIME UP!  \n\n");
    Sleep(1200);

    // Results
    int wordsTyped = countWords(typed);
    float wpm = ((float)wordsTyped / timerSeconds) * 60.0f;
    float accuracy = calculateAccuracy(sample, typed);

    printf("\n===== RESULTS =====\n");
    printf("Difficulty Level : %s\n", 
           (level == 1 ? "EASY" : level == 2 ? "MEDIUM" : "HARD"));
    printf("Time Limit       : %d seconds\n", timerSeconds);
    printf("Words in Sample  : %d\n", countWords(sample));
    printf("Words Typed      : %d\n", wordsTyped);
    printf("Typing Speed     : %.2f WPM\n", wpm);
    printf("Accuracy         : %.2f%%\n", accuracy);
    printf("===========================\n");
    printf("Great job! Keep practicing. \n");

    return 0;
}
