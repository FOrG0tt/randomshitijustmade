#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25
#define TRAIL 4

/* ---------------- MATRIX RAIN ---------------- */
void draw_column(int col, int head) {
    int row, pos, tail;
    for (row = 0; row < TRAIL; row++) {
        pos = head - row;
        if (pos >= 0 && pos < HEIGHT) {
            gotoxy(col + 1, pos + 1);
            textcolor(row == 0 ? 15 : 10);
            cprintf("%c", 33 + random(90));
        }
    }
    tail = head - TRAIL;
    if (tail >= 0 && tail < HEIGHT) {
        gotoxy(col + 1, tail + 1);
        cprintf(" ");
    }
}

void matrixRain() {
    int head[WIDTH], col, spawning = 1, row;
    clrscr();
    randomize();
    for (col = 0; col < WIDTH; col++)
        head[col] = random(HEIGHT) - random(HEIGHT);

    while (!kbhit()) {
        for (col = 0; col < WIDTH; col++) {
            if (random(2) == 0) {
                draw_column(col, head[col]);
                head[col]++;
                if (spawning && head[col] >= HEIGHT + TRAIL)
                    head[col] = -random(HEIGHT);
            }
        }
        delay(20);
    }
    getch(); // consume key
    spawning = 0;

    for (row = 1; row <= HEIGHT; row++) {
        gotoxy(1, row);
        for (col = 0; col < WIDTH; col++)
            cprintf(" ");
        delay(15);
    }
}

/* ---------------- TYPED MESSAGES ---------------- */
void typeMessage(char *msg) {
    int i, len = strlen(msg);
    int x = (WIDTH - len) / 2;
    int y = HEIGHT / 2;
    textcolor(10);
    for (i = 0; i < len; i++) {
        gotoxy(x + i + 1, y);
        cprintf("%c", msg[i]);
        delay(180);
    }
}

void eraseMessage(char *msg) {
    int i, len = strlen(msg);
    int x = (WIDTH - len) / 2;
    int y = HEIGHT / 2;
    for (i = len - 1; i >= 0; i--) {
        gotoxy(x + i + 1, y);
        cprintf(" ");
        delay(100);
    }
}

/* ---------------- ASCII ART ---------------- */
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
    clrscr();
    textcolor(10);
    for (i = 0; i < 6; i++) {
        gotoxy((WIDTH - strlen(asciiArt[i])) / 2 + 1, i + 2);
        cprintf("%s", asciiArt[i]);
        delay(50);
    }
    gotoxy((WIDTH - 26) / 2 + 1, 9);
    cprintf("WE OWN THE WORLD SINCE 2008");
    delay(1000);
}

/* ---------------- HACKER TERMINAL ---------------- */
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
    for (i = 0; i < 16; i++) {
        gotoxy(1, row + i);
        cprintf("%s", sequence[i]);
        delay(delays[i]);
    }
}

/* ---------------- CLEAR TERMINAL BELOW ASCII ---------------- */
void clearTerminalBelowAscii(int asciiHeight) {
    int row, col;
    for (row = asciiHeight + 1; row <= HEIGHT; row++)
        for (col = 1; col <= WIDTH; col++) {
            gotoxy(col, row);
            cprintf(" ");
        }
}

/* ---------------- CYPHER'S EYE ---------------- */
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
void joinPrompt() {
    char ch;
    int x = (WIDTH - 40) / 2, y = HEIGHT - 2;
    gotoxy(x + 1, y); 
    cprintf("WILL YOU JOIN US IN THIS ADVENTURE, NEO?");

    while (1) {
        ch = getch();
        if (ch == 'Y' || ch == 'y') {
            clrscr();
            typeMessage("Welcome to ZHR.");
            delay(5000);
            exit(0);
        }
        if (ch == 'N' || ch == 'n') {
            exit(0);
        }
    }
}

/* ---------------- MAIN ---------------- */
void main() {
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
}
