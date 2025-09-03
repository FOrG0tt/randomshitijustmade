#include <stdio.h>   
#include <conio.h>   
#include <stdlib.h>  
#include <dos.h>     
#include <string.h> 

// Screen size and effect settings
// Width is the width of the terminal (obviously) and the height is literally the height of the terminal
// Trail is how long the matrix trails are in the beginning.
#define WIDTH 80     
#define HEIGHT 24    
#define TRAIL 4     

/* ---------------- MATRIX RAIN ---------------- */
// in order to recreate the matrix effect, we need to work on two things.
// The trail, and the controller itself.

// The idea here is that we create the rain seperately. this way we can handle it easily.
// This function creates the rain itself so basically 1 drop of the rain
void draw_column(int col, int head) {
    int row, pos, tail; // no values in the local variables (used later)
 // the "col" here is where the head starts so basically where the head is on the x axis
 // the "head" here is where the head part of the rain is 

    
    // this is for the trail effect
    for (row = 0; row < TRAIL; row++) { // this is the core mechanic. we need to loop this if our row is less than the trail
        pos = head - row; // this makes it so it knows where it is

        // Only draw if inside screen boundaries
        if (pos >= 0 && pos < HEIGHT) { // checks if its not above the screen or below the screen
            gotoxy(col + 1, pos + 1);             // move cursor to where we putting the chars
            textcolor(row == 0 ? 15 : 10);        // if row 0 then white, if row is not 0 then green ez pz bro
            cprintf("%c", 33 + random(90));       // Random ASCII picker
        }
    }

    // Erase the tail so the column doesn’t stretch forever
    tail = head - TRAIL;
    if (tail >= 0 && tail < HEIGHT) { // same logic except as above but this tiem it checks the tail, cuz we need to erase teh tail
        gotoxy(col + 1, tail + 1);  // once again still the same
        cprintf(" ");
    }
}

// Controls the entire Matrix rain animation
// controls the entire rain animation
void matrixRain() {
    int head[WIDTH];  // array that stores the y-position (head) of each column
    int col;          // loop counter for columns
    int spawning = 1; // flag to keep respawning drops (turns 0 later to stop)
    int row;          // loop counter for rows (mainly for fade-out)

    clrscr();      // clear screen before starting
    randomize();   // seed random number generator so rain looks different each run

    // initialize each column with a random start position
    for (col = 0; col < WIDTH; col++) // funny ahh loop
        head[col] = random(HEIGHT) - random(HEIGHT); // random negative start offsets

    // main loop runs until any key is pressed
    while (!kbhit()) {
        for (col = 0; col < WIDTH; col++) { // another funny ahh loop
            if (random(2) == 0) {     // 50/50 chance this column updates this frame
                draw_column(col, head[col]); // draw it
                head[col]++;          // move head down

                // respawn drop if it fell off the bottom
                if (spawning && head[col] >= HEIGHT + TRAIL)
                    head[col] = -random(HEIGHT);
            }
        }
        delay(20); // small delay so it doesn’t run crazy fast
    }

    getch();       // eat the pressed key
    spawning = 0;  // stop spawning new drops

    // fade out effect by clearing line by line
    for (row = 1; row <= HEIGHT; row++) {
        gotoxy(1, row);
        for (col = 0; col < WIDTH; col++)
            cprintf(" ");
        delay(15);
    }
}

/* ---------------- TYPED MESSAGES ---------------- */
// simulates typing text letter by letter (like hacker terminal)
void typeMessage(char *msg) {
    int i;                  // loop counter
    int len = strlen(msg);  // length of the message
    int x = (WIDTH - len) / 2; // starting X (so it’s centered)
    int y = HEIGHT / 2;        // Y position (center of screen)

    textcolor(10); // green text
    for (i = 0; i < len; i++) {
        gotoxy(x + i + 1, y);  // move cursor for each letter
        cprintf("%c", msg[i]); // print the letter
        delay(180);            // delay = fake typing speed
    }
}

// erases the typed message backwards
void eraseMessage(char *msg) {
    int i;                  // loop counter (backwards)
    int len = strlen(msg);  // message length
    int x = (WIDTH - len) / 2; // same center X as before
    int y = HEIGHT / 2;        // same Y

    for (i = len - 1; i >= 0; i--) {
        gotoxy(x + i + 1, y);
        cprintf(" ");   // replace with space
        delay(100);
    }
}

/* ---------------- ASCII ART ---------------- */
// shows a big ascii banner with a reveal effect
void displayAsciiArt() {
    int i; // loop counter
    char *asciiArt[6] = { // array of strings (the logo lines)
        "  _______    _ _____     _____ ____  _____  ________   __",
        " |___  / |  | |  __ \\   / ____/ __ \\|  __ \\|  ____\\ \\ / /",
        "    / /| |__| | |__) | | |   | |  | | |  | | |__   \\ V / ",
        "   / / |  __  |  _  /  | |   | |  | | |  | |  __|   > <  ",
        "  / /__| |  | | | \\ \\  | |___| |__| | |__| | |____ / . \\ ",
        " /_____|_|  |_|_|  \\_\\  \\_____\\____/|_____/|______/_/ \\_\\"
    };

    clrscr();  // clear before drawing
    textcolor(10);

    // print each line one by one
    for (i = 0; i < 6; i++) {
        gotoxy((WIDTH - strlen(asciiArt[i])) / 2 + 1, i + 2);
        cprintf("%s", asciiArt[i]);
        delay(50);
    }

    // add subtitle under it
    gotoxy((WIDTH - 26) / 2 + 1, 9);
    cprintf("WE OWN THE WORLD SINCE 2008");
    delay(1000);
}

/* ---------------- HACKER TERMINAL ---------------- */
// shows fake hacking logs line by line
void hackerTerminal() {
    int row = 10; // starting row to print logs
    int i;        // loop counter

    // array of fake log messages
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

    // custom delays for each log (to look less robotic)
    int delays[] = {1200, 1000, 1000, 1500, 1200, 800, 700, 700, 700, 1000, 600, 600, 600, 600, 600, 700};

    for (i = 0; i < 16; i++) {
        gotoxy(1, row + i);     // move down each time
        cprintf("%s", sequence[i]);
        delay(delays[i]);       // unique pause per log
    }
}

/* ---------------- CLEAR TERMINAL BELOW ASCII ---------------- */
// wipes everything under the ascii art (so new stuff looks clean)
void clearTerminalBelowAscii(int asciiHeight) {
    int row; // loop counter for rows
    int col; // loop counter for columns

    for (row = asciiHeight + 1; row <= HEIGHT; row++)
        for (col = 1; col <= WIDTH; col++) {
            gotoxy(col, row);
            cprintf(" ");
        }
}

/* ---------------- CYPHER'S EYE ---------------- */
// another fake “system scan” sequence
void cyphersEyeSequence() {
    int row = 9;        // starting row to print
    int i;              // loop counter
    int currentRow;     // keeps track of where we’re printing next

    // arrays of fake subsystems
    char *cameras[] = {"CAM_01", "CAM_02", "CAM_03"};
    char *phones[]  = {"PH_01", "PH_02"};
    char *banks[]   = {"ATM_01", "BANK_01"};
    char *police[]  = {"POL_01"};
    char *locks[]   = {"DOOR_01", "VAULT_01"};

    clearTerminalBelowAscii(7);

    gotoxy(1, row); cprintf("INIT CYPHER'S EYE v1.0..."); delay(1000);
    gotoxy(1, row + 1); cprintf("SCANNING NETWORKS..."); delay(800);

    currentRow = row + 2; // start after the headers

    // show each group w/ staggered timing
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
// asks the user yes/no
void joinPrompt() {
    char ch;  // stores pressed key
    int x = (WIDTH - 40) / 2; // horizontal position for prompt
    int y = HEIGHT - 2;       // bottom of the screen

    gotoxy(x + 1, y); 
    cprintf("WILL YOU JOIN US IN THIS ADVENTURE, NEO?");

    // loop until user presses Y or N
    while (1) {
        ch = getch(); // wait for key
        if (ch == 'Y' || ch == 'y') {
            clrscr();
            typeMessage("Welcome to ZHR.");
            delay(5000);
            exit(0); // exit program (joined)
        }
        if (ch == 'N' || ch == 'n') {
            exit(0); // exit immediately (refused)
        }
    }
}

/* ---------------- MAIN ---------------- */
// main driver: runs everything in sequence
int main() {
    matrixRain(); // start with the matrix effect

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

    return 0; // exit cleanly
}
}
