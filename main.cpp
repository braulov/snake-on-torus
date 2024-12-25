#include <bits/stdc++.h>
using namespace std;

// Random number generator
mt19937_64 rnd;

// Class representing the game engine for the "snake on a torus" problem
class engine {
private:
    long long n, m; // Dimensions of the torus (n rows, m columns)
    long long steps = 0; // Counter for the number of steps taken
    pair<int, int> currentPos; // Current position of the snake
    pair<int, int> applePos; // Position of the apple
    bool isOver = false; // Flag indicating if the game is over (snake has reached the apple)

public:
    // Default constructor (creates a minimal torus of size 1x1)
    engine() { this->n = 1, this->m = 1; }

    // Constructor initializing the torus dimensions, snake position, and apple position
    engine(long long n, long long m, pair<int, int> currentPos, pair<int, int> applePos) {
        this->currentPos = currentPos;
        this->applePos = applePos;
        this->n = n;
        this->m = m;
    }

    // Move the snake up (wrapping around if necessary)
    void up() {
        steps++;
        this->currentPos.first -= 1;
        if (this->currentPos.first == -1) this->currentPos.first += n;
    }

    // Move the snake down (wrapping around if necessary)
    void down() {
        steps++;
        this->currentPos.first += 1;
        if (this->currentPos.first == n) this->currentPos.first -= n;
    }

    // Move the snake left (wrapping around if necessary)
    void left() {
        steps++;
        this->currentPos.second -= 1;
        if (this->currentPos.second == -1) this->currentPos.second += m;
    }

    // Move the snake right (wrapping around if necessary)
    void right() {
        steps++;
        this->currentPos.second += 1;
        if (this->currentPos.second == m) this->currentPos.second -= m;
    }

    /**
     * Executes a movement command and checks if the game is over.
     * @param s Command string ("UP", "DOWN", "LEFT", "RIGHT")
     * @return true if the snake has reached the apple, false otherwise
     */
    bool sendSignal(const string& s) {
        if (isOver) return currentPos == applePos;
        if (s == "LEFT") left();
        else if (s == "RIGHT") right();
        else if (s == "DOWN") down();
        else if (s == "UP") up();
        else cout << "Unknown command, try again\n";
        isOver |= (currentPos == applePos); // Update game state
        return currentPos == applePos;
    }

    /**
     * Prints the current state of the game field to the console.
     * '*' represents the snake, '0' represents the apple, 'x' if they overlap, '-' for empty cells.
     */
    void printField() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pair<int, int> cur = {i, j};
                if (this->currentPos == cur && this->applePos == cur) cout << 'x' << ' ';
                else if (this->currentPos == cur) cout << '*' << ' ';
                else if (this->applePos == cur) cout << '0' << ' ';
                else cout << '-' << ' ';
            }
            cout << '\n';
        }
    }

    /**
     * @return Total number of steps taken by the snake.
     */
    [[nodiscard]] int getSteps() const { return this->steps; }

    /**
     * @return true if the game is over (snake has reached the apple), false otherwise.
     */
    [[nodiscard]] bool gameIsOver() const { return isOver; }
};

// Function to solve the game using a spiral search pattern
int spiralSolve(engine eng) {
    int k = 1;
    while (!eng.gameIsOver()) {
        for (int i = 0; i < k; i++) eng.sendSignal("UP");
        for (int i = 0; i < k; i++) eng.sendSignal("LEFT");
        for (int i = 0; i < k + 1; i++) eng.sendSignal("DOWN");
        for (int i = 0; i < k + 1; i++) eng.sendSignal("RIGHT");
        k += 2;
    }
    return eng.getSteps();
}

// Function to solve the game using a random walk in all four directions
int randomWalk4(engine eng) {
    while (!eng.gameIsOver()) {
        int direction = rnd() % 4;
        if (direction == 0) eng.sendSignal("LEFT");
        else if (direction == 1) eng.sendSignal("RIGHT");
        else if (direction == 2) eng.sendSignal("UP");
        else eng.sendSignal("DOWN");
    }
    return eng.getSteps();
}

// Function to solve the game using a random walk in two directions (UP and RIGHT)
int randomWalk2(engine eng) {
    while (!eng.gameIsOver()) {
        int direction = rnd() % 2;
        if (direction == 0) eng.sendSignal("RIGHT");
        else eng.sendSignal("UP");
    }
    return eng.getSteps();
}

// Function to solve the game by moving in a diagonal pattern (works for coprime dimensions)
int coprimeCase(engine eng) {
    while (!eng.gameIsOver()) {
        eng.sendSignal("RIGHT");
        eng.sendSignal("UP");
    }
    return eng.getSteps();
}

// Function to solve the game using a mixed strategy
int mixSolve(engine eng) {
    int curX = 0, curY = 0;
    while (!eng.gameIsOver()) {
        int mvX = rnd() % 2, mvY = rnd() % 2;
        if (mvX) {
            eng.sendSignal("RIGHT");
            for (int i = 0; i <= curY; i++) eng.sendSignal("DOWN");
            for (int i = 0; i <= curY; i++) eng.sendSignal("UP");
        }
        if (mvY) {
            eng.sendSignal("UP");
            for (int i = 0; i <= curX; i++) eng.sendSignal("LEFT");
            for (int i = 0; i <= curX; i++) eng.sendSignal("RIGHT");
        }
    }
    return eng.getSteps();
}

// Main function to run multiple tests with random initial conditions
int main() {
    rnd.seed(time(0)); // Initialize random seed
    int t = 100; // Number of test cases
    long double numberOfTests = t;
    long double averageRatio = 0;
    int badTests = 0;

    while (t--) {
        long long n = 1001, m = 1001;
        pair<int, int> currentPos = {rnd() % n, rnd() % m};
        pair<int, int> applePos = {rnd() % n, rnd() % m};

        engine eng(n, m, currentPos, applePos);
        int steps = mixSolve(eng);

        // Check if the solution is too slow
        if (steps > (35 * n * m)) {
            badTests++;
        }
        averageRatio += ((long double)steps / (long double)(n * m));
    }

    cout << "Average ratio steps/S = " << averageRatio / numberOfTests << '\n';
    cout << "Number of tests with steps > 35S = " << badTests << '\n';
}
