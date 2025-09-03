#include <stdio.h>   
#include <conio.h>   
#include <stdlib.h>  
#include <dos.h>     
#include <string.h> 

// Screen size and effect settings
#define WIDTH 80     /* Console width in characters */
#define HEIGHT 25    // Console height in characters
#define TRAIL 4      // Length of the trailing effect in the rain

/* ---------------- MATRIX RAIN ---------------- */
// Draws one falling column of Matrix rain characters
// `col` = which column to draw in
// `head` = current "head" position of the falling rain
void draw_column(int col, int head) {
    int row, pos, tail;

    // Loop through trail characters
    for (row = 0; row < TRAIL; row++) {
        pos = head - row; // Position of this character in the column

        // Only draw if inside screen boundaries
        if (pos >= 0 && pos < HEIGHT) {
            gotoxy(col + 1, pos + 1);             // Move cursor
            textcolor(row == 0 ? 15 : 10);        // Head is white, trail is green
            cprintf("%c", 33 + random(90));       // Random ASCII character
        }
    }

    // Erase the tail so the column doesn’t stretch forever
    tail = head - TRAIL;
    if (tail >= 0 && tail < HEIGHT) {
        gotoxy(col + 1, tail + 1);
        cprintf(" ");
    }
}

// Controls the entire Matrix rain animation
void matrixRain() {
    int head[WIDTH], col, spawning = 1, row;

    clrscr();      // Clear screen before starting
    randomize();   // Randomize random() generator for fresh values

    // Initialize each column with a random head position
    for (col = 0; col < WIDTH; col++)
        head[col] = random(HEIGHT) - random(HEIGHT);

    // Loop until a key is pressed
    while (!kbhit()) {
        for (col = 0; col < WIDTH; col++) {
            if (random(2) == 0) {     // Randomly decide whether this column falls this frame
                draw_column(col, head[col]);
                head[col]++;          // Move the column downward

                // Respawn a new column at the top if it reached the bottom
                if (spawning && head[col] >= HEIGHT + TRAIL)
                    head[col] = -random(HEIGHT);
            }
        }
        delay(20); // Delay so animation doesn’t run too fast
    }

    getch();       // Consume the pressed key so it doesn’t leak
    spawning = 0;  // Stop spawning new columns

    // Fade out effect: wipe each row slowly
    for (row = 1; row <= HEIGHT; row++) {
        gotoxy(1, row);
        for (col = 0; col < WIDTH; col++)
            cprintf(" ");
        delay(15);
    }
}

/* ---------------- TYPED MESSAGES ---------------- */
// Simulates typing a message slowly (like a hacker terminal)
void typeMessage(char *msg) {
    int i, len = strlen(msg);
    int x = (WIDTH - len) / 2; // Center horizontally
    int y = HEIGHT / 2;        // Center vertically
    textcolor(10);             // Green text like Matrix
    for (i = 0; i < len; i++) {
        gotoxy(x + i + 1, y);  // Position cursor
        cprintf("%c", msg[i]); // Print character one by one
        delay(180);            // Typing effect
    }
}

// Erases the typed message backwards
void eraseMessage(char *msg) {
    int i, len = strlen(msg);
    int x = (WIDTH - len) / 2;
    int y = HEIGHT / 2;
    for (i = len - 1; i >= 0; i--) {
        gotoxy(x + i + 1, y);
        cprintf(" ");          // Replace character with space
        delay(100);
    }
}

/* ---------------- ASCII ART ---------------- */
// Displays an ASCII banner with delay for dramatic reveal
void displayAsciiArt() {
    int i;
    char *asciiArt[6] = {
        "  _______    _ _____     _____ ____  _____  ________   __",
        " |___  / |  | |  __ \\   / ____/ __ \\|  __ \\|  ____\\ \\ / /",
        "    / /| |__| | |__) | | |   | |  | | |  | | |__   \\ V / ",
        "   / / |  __  |  _  /  | |   | |  | | |  | |  __|   > <  ",
        "  / /__| |  | | | \\ \\  | |___| |__| | |__| | |____ / . \\ ",
        " /_____|_|  |_|_|  \\_\\  \\_____\\____/|_____/|______/_/ \\_\\"
    };

    clrscr();  // Clear screen for clean banner
    textcolor(10);

    // Print each line with a small delay for dramatic effect
    for (i = 0; i < 6; i++) {
        gotoxy((WIDTH - strlen(asciiArt[i])) / 2 + 1, i + 2);
        cprintf("%s", asciiArt[i]);
        delay(50);
    }

    // Print subtitle below the art
    gotoxy((WIDTH - 26) / 2 + 1, 9);
    cprintf("WE OWN THE WORLD SINCE 2008");
    delay(1000);
}

/* ---------------- HACKER TERMINAL ---------------- */
// Simulates hacking text logs scrolling down
void hackerTerminal() {
    int row = 10, i;
    char *sequence[] = {
        "INITIALIZING ROOTKIT v3.7...",
        "LOADING EXPLOIT MODULES...",
        "LOADING SQL INJECTION SCRIPTS...",
        "CONNECTING TO GLOBAL NETWORK [IP: 192.168.99.42]...",
        "AUTHENTICATING ADMIN ACCESS...",
        "ACCESS GRANTED. SYSTEMS BREACHED.",
        "POWER GRID CONTROL: ACTIVE",
        "TRAINS: REMOTE OVERRIDE ENGAGED",
        "SATELLITES: ONLINE AND TRACKING",
        "DUMPING DATABASES...",
        "USER: ANDREI | PASS: ********",
        "USER: MIGUEL  | PASS: ********",
        "USER: P  | PASS: ********",
        "USER: MANLOLOYO  | PASS: ********",
        "FIREWALLS BYPASSED",
        "ENCRYPTION KEYS CAPTURED"
    };
    int delays[] = {1200, 1000, 1000, 1500, 1200, 800, 700, 700, 700, 1000, 600, 600, 600, 600, 600, 700};

    // Print each "log entry" with its own delay (to simulate real processing time)
    for (i = 0; i < 16; i++) {
        gotoxy(1, row + i);
        cprintf("%s", sequence[i]);
        delay(delays[i]);
    }
}

/* ---------------- CLEAR TERMINAL BELOW ASCII ---------------- */
// Wipes everything below the ASCII art so it looks like new content is loading
void clearTerminalBelowAscii(int asciiHeight) {
    int row, col;
    for (row = asciiHeight + 1; row <= HEIGHT; row++)
        for (col = 1; col <= WIDTH; col++) {
            gotoxy(col, row);
            cprintf(" ");
        }
}

/* ---------------- CYPHER'S EYE ---------------- */
// Simulates a system scan listing cameras, phones, banks, etc.
void cyphersEyeSequence() {
    int row = 9, i, currentRow;
    char *cameras[] = {"CAM_01", "CAM_02", "CAM_03"};
    char *phones[]  = {"PH_01", "PH_02"};
    char *banks[]   = {"ATM_01", "BANK_01"};
    char *police[]  = {"POL_01"};
    char *locks[]   = {"DOOR_01", "VAULT_01"};

    clearTerminalBelowAscii(7);

    gotoxy(1, row); cprintf("INIT CYPHER'S EYE v1.0..."); delay(1000);
    gotoxy(1, row + 1); cprintf("SCANNING NETWORKS..."); delay(800);

    currentRow = row + 2;

    // Print subsystems with staggered timing for realism
    for (i = 0; i < 3; i++) { gotoxy(1, currentRow + i); cprintf("[CYBER] %s ONLINE", cameras[i]); delay(400); }
    currentRow += 3;
    for (i = 0; i < 2; i++) { gotoxy(1, currentRow + i); cprintf("[CYBER] %s ACTIVE", phones[i]); delay(400); }
    currentRow += 2;
    for (i = 0; i < 2; i++) { gotoxy(1, currentRow + i); cprintf("[CYBER] %s ONLINE", banks[i]); delay(500); }
    currentRow += 2;
    for (i = 0; i < 1; i++) { gotoxy(1, currentRow + i); cprintf("[CYBER] %s ONLINE", police[i]); delay(500); }
    currentRow += 1;

    gotoxy(1, currentRow); cprintf("ANALYZING LOCKED SYSTEMS..."); delay(800);
    currentRow++;
    for (i = 0; i < 2; i++) { gotoxy(1, currentRow + i); cprintf("[CYBER] %s UNLOCKED", locks[i]); delay(600); }
    currentRow += 2;
    gotoxy(1, currentRow); cprintf("[INFO] CYPHER'S EYE ACTIVE"); delay(3000);
}

/* ---------------- JOIN PROMPT ---------------- */
// Interactive yes/no prompt to decide whether the user joins
void joinPrompt() {
    char ch;
    int x = (WIDTH - 40) / 2, y = HEIGHT - 2;
    gotoxy(x + 1, y); 
    cprintf("WILL YOU JOIN US IN THIS ADVENTURE, NEO?");

    // Infinite loop until user presses Y or N
    while (1) {
        ch = getch();
        if (ch == 'Y' || ch == 'y') {
            clrscr();
            typeMessage("Welcome to ZHR.");
            delay(5000);
            exit(0); // End program
        }
        if (ch == 'N' || ch == 'n') {
            exit(0); // End program immediately
        }
    }
}

/* ---------------- MAIN ---------------- */
// Main driver of the program: controls the whole sequence
int main() {   // should be int, not void
    matrixRain();
    typeMessage("You are the chosen one, Neo.");
    delay(1000);
    eraseMessage("You are the chosen one, Neo.");

    typeMessage("We are Zero Hour. We are everywhere.");
    delay(1000);
    eraseMessage("We are Zero Hour. We are everywhere.");

    typeMessage("Initializing ZHR Codex...");
    delay(500);

    displayAsciiArt();
    hackerTerminal();
    cyphersEyeSequence();
    joinPrompt();
    getch();

    return 0; // Proper exit code
}
