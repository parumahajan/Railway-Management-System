#include <stdio.h>
#include <string.h>

#define MAX_SEATS 30
#define MAX_NAME_LENGTH 50
#define FIXED_FARE 2500.0 // Assuming a fixed fare for all seats

struct Passenger {
    char name[MAX_NAME_LENGTH];
    int age;
    char mobile_number[15];
    int is_reserved;
    float fare;
};

struct Route {
    char from[20];
    char to[20];
};

struct Passenger passengers[MAX_SEATS];
struct Route routes[] = {
    {"Chennai", "Hyderabad"},
    {"Bangalore", "Hyderabad"},
    {"Chennai", "Bangalore"}
};

void initializeBus() {
    for (int i = 0; i < MAX_SEATS; i++) {
        passengers[i].is_reserved = 0; // 0 indicates seat is available
    }
}

void showAvailableSeats() {
    printf("Available Seats for Routes:\n");

    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        printf("From %s to %s:\n", routes[i].from, routes[i].to);
        for (int j = 0; j < MAX_SEATS; j += 2) {
            printf("Seat %2d [ ]    Seat %2d [ ]\n", j + 1, j + 2);
            printf("------------------------------\n");
        }
    }
}

void reserveSeat() {
    int seat, route_choice;
    printf("Select a route:\n");
    for (int i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        printf("%d. From %s to %s\n", i + 1, routes[i].from, routes[i].to);
    }
    scanf("%d", &route_choice);
    if (route_choice < 1 || route_choice > sizeof(routes) / sizeof(routes[0])) {
        printf("Invalid route choice!\n");
        return;
    }

    printf("Enter seat number to reserve: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > MAX_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    if (passengers[seat - 1].is_reserved == 0) {
        printf("Enter passenger name for seat %d: ", seat);
        scanf("%s", passengers[seat - 1].name);
        
        printf("Enter passenger age: ");
        scanf("%d", &passengers[seat - 1].age);

        printf("Enter passenger mobile number: ");
        scanf("%s", passengers[seat - 1].mobile_number);

        passengers[seat - 1].is_reserved = 1;
        passengers[seat - 1].fare = FIXED_FARE;

        printf("Seat %d reserved for %s (Age: %d, Mobile: %s) with fare %.2f\n",
               seat, passengers[seat - 1].name, passengers[seat - 1].age, passengers[seat - 1].mobile_number, passengers[seat - 1].fare);
    } else {
        printf("Seat %d is already reserved\n", seat);
    }
}

void showReservedSeats() {
    printf("Reserved Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (passengers[i].is_reserved == 1) {
            printf("Seat %d - %s (Age: %d, Mobile: %s) - Fare: %.2f\n", i + 1,
                   passengers[i].name, passengers[i].age, passengers[i].mobile_number, passengers[i].fare);
        }
    }
}

int main() {
    int choice;

    initializeBus();

    do {
        printf("\nBus Reservation System\n");
        printf("1. Show available seats\n");
        printf("2. Reserve a seat\n");
        printf("3. Show reserved seats\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAvailableSeats();
                break;
            case 2:
                reserveSeat();
                break;
            case 3:
                showReservedSeats();
                break;
            case 4:
                printf("Exiting... Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}