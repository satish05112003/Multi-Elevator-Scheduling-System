#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEVATORS 5
#define MAX_FLOORS    50

typedef struct {
    int id;
    int currentFloor;
    int targetFloor;   // -1 means no target (idle)
    int direction;     // -1 down, 0 idle, +1 up
} Elevator;

int my_abs(int x) {
    return x < 0 ? -x : x;
}

void initElevators(Elevator lifts[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        lifts[i].id = i;
        lifts[i].currentFloor = 0;
        lifts[i].targetFloor = -1;
        lifts[i].direction = 0;
    }
}

void printStatus(Elevator lifts[], int n, int numFloors) {
    int i;
    printf("\n===== SYSTEM STATUS =====\n");
    printf("Floors: 0 to %d\n", numFloors - 1);
    for (i = 0; i < n; i++) {
        const char *dirStr;
        if (lifts[i].direction > 0) dirStr = "UP";
        else if (lifts[i].direction < 0) dirStr = "DOWN";
        else dirStr = "IDLE";

        printf("Lift %d | Floor: %2d | Target: %2d | Dir: %s\n",
               lifts[i].id,
               lifts[i].currentFloor,
               lifts[i].targetFloor,
               dirStr);
    }
    printf("=========================\n\n");
}

// choose best elevator for a hall call (nearest idle or lightest busy)
int chooseBestElevator(Elevator lifts[], int n, int reqFloor) {
    int bestIdx = -1;
    int bestCost = 1000000;
    int i;

    for (i = 0; i < n; i++) {
        int cost = my_abs(lifts[i].currentFloor - reqFloor);

        // if elevator already has a target, make it less preferred
        if (lifts[i].targetFloor != -1) {
            cost += 5;
        }

        if (cost < bestCost) {
            bestCost = cost;
            bestIdx = i;
        }
    }
    return bestIdx;
}

void assignHallCall(Elevator lifts[], int n, int numFloors, int floor) {
    int idx;

    if (floor < 0 || floor >= numFloors) {
        printf("Invalid floor.\n");
        return;
    }

    idx = chooseBestElevator(lifts, n, floor);
    if (idx == -1) {
        printf("No elevator available (should not happen).\n");
        return;
    }

    lifts[idx].targetFloor = floor;
    if (lifts[idx].currentFloor < floor) lifts[idx].direction = 1;
    else if (lifts[idx].currentFloor > floor) lifts[idx].direction = -1;
    else lifts[idx].direction = 0; // already there

    printf("Hall call at floor %d assigned to Lift %d.\n", floor, lifts[idx].id);
}

void stepElevators(Elevator lifts[], int n) {
    int i;
    printf("\n--- Advancing one time step ---\n");
    for (i = 0; i < n; i++) {
        if (lifts[i].targetFloor == -1) {
            // idle, nothing to do
            continue;
        }

        if (lifts[i].currentFloor < lifts[i].targetFloor) {
            lifts[i].currentFloor++;
            lifts[i].direction = 1;
        } else if (lifts[i].currentFloor > lifts[i].targetFloor) {
            lifts[i].currentFloor--;
            lifts[i].direction = -1;
        } else {
            // reached target
            printf("Lift %d reached floor %d. Door opens (conceptually).\n",
                   lifts[i].id, lifts[i].currentFloor);
            lifts[i].targetFloor = -1;
            lifts[i].direction = 0;
        }
    }
    printf("--- Time step complete ---\n\n");
}

void printMenu() {
    printf("1. Add hall call (someone calls lift from a floor)\n");
    printf("2. Advance one time step\n");
    printf("3. Show status\n");
    printf("4. Exit\n");
    printf("Select option: ");
}

int main() {
    Elevator lifts[MAX_ELEVATORS];
    int numElevators, numFloors;
    int choice;
    int running = 1;

    printf("=== Simple Multi-Elevator Scheduling System ===\n");

    printf("Enter number of floors (max %d): ", MAX_FLOORS);
    if (scanf("%d", &numFloors) != 1 || numFloors < 2 || numFloors > MAX_FLOORS) {
        printf("Invalid number of floors.\n");
        return 0;
    }

    printf("Enter number of elevators (max %d): ", MAX_ELEVATORS);
    if (scanf("%d", &numElevators) != 1 || numElevators < 1 || numElevators > MAX_ELEVATORS) {
        printf("Invalid number of elevators.\n");
        return 0;
    }

    initElevators(lifts, numElevators);
    printf("\nSystem initialized with %d floors (0 to %d) and %d elevators.\n\n",
           numFloors, numFloors - 1, numElevators);

    while (running) {
        printStatus(lifts, numElevators, numFloors);
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        if (choice == 1) {
            int floor;
            printf("Enter floor for hall call (0 - %d): ", numFloors - 1);
            if (scanf("%d", &floor) != 1) {
                printf("Invalid input.\n");
                break;
            }
            assignHallCall(lifts, numElevators, numFloors, floor);

        } else if (choice == 2) {
            stepElevators(lifts, numElevators);

        } else if (choice == 3) {
            printStatus(lifts, numElevators, numFloors);

        } else if (choice == 4) {
            printf("Exiting.\n");
            running = 0;

        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
