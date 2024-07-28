#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // for sleep function

#define MAX_PARKING_SPOTS 10

enum UserType {
    ATTENDANT,
    ADMIN
};

struct User {
    char username[20];
    char password[20];
    enum UserType type;
};

enum VehicleType {
    CAR,
    MOTORCYCLE,
    TRUCK
};

struct Vehicle {
    int id;
    time_t arrival_time;
    enum VehicleType type;
};

struct ParkingSpot {
    enum VehicleType type;
    int is_occupied;
    struct Vehicle parked_vehicle;
};

struct QueueNode {
    struct Vehicle vehicle;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
};

struct Reservation {
    int reservation_id;
    char username[20];
    struct Vehicle reserved_vehicle;
    time_t reservation_time;
};

// Function prototypes
void initQueue(struct Queue* q);
int isQueueEmpty(struct Queue* q);
void enqueue(struct Queue* q, struct Vehicle vehicle);
struct Vehicle dequeue(struct Queue* q);
void displayQueue(struct Queue* q);
void allocateParkingSpot(struct ParkingSpot spots[], struct Vehicle vehicle);
double calculateParkingFee(time_t arrival_time, enum VehicleType type);
void displayParkingLot(struct ParkingSpot spots[]);
void displayStatistics(struct Queue* q);
int authenticateUser(struct User users[], char username[], char password[]);
void processPayment(double amount);
int makeReservation(struct Reservation reservations[], struct Vehicle vehicle, char username[]);
void cancelReservation(struct Reservation reservations[], int reservation_id);
void displayReservedSpots(struct Reservation reservations[]);

void vehicleArrive(struct Queue* q, int* vehicleCount, enum UserType authenticatedUser);
void vehicleEntry(struct Queue* q, struct ParkingSpot spots[], enum UserType authenticatedUser);
void vehicleExit(struct Queue* q, struct ParkingSpot spots[], int spot_number, enum UserType authenticatedUser);

int main() {
    int spot_number;
    struct Queue parkingQueue;
    initQueue(&parkingQueue);
    char username[20];
    struct ParkingSpot parkingSpots[MAX_PARKING_SPOTS];
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        parkingSpots[i].type = (i < 4) ? CAR : (i < 7) ? MOTORCYCLE : TRUCK;
        parkingSpots[i].is_occupied = 0;
    }

    struct User users[2] = {{"attendant", "123", ATTENDANT}, {"admin", "adminpass", ADMIN}};

    struct Reservation reservations[MAX_PARKING_SPOTS];
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        reservations[i].reservation_id = 0; // Initialize reservation slots
    }

    int vehicleCount = 1;
    int option;
    int authenticatedUser = -1; // Indicates no user is authenticated

    do {
        printf("\nAutomated Parking System Menu:\n");
        printf("1. Vehicle arrives\n");
        printf("2. Vehicle enters\n");
        printf("3. Vehicle exits\n");
        printf("4. Display vehicles in queue\n");
        printf("5. Display parking lot status\n");
        printf("6. Display parking statistics\n");
        printf("7. Authenticate user\n");
        printf("8. Make a reservation\n");
        printf("9. Cancel a reservation\n");
        printf("10. Display reserved spots\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                vehicleArrive(&parkingQueue, &vehicleCount, authenticatedUser);
                break;
            }
            case 2: {
                vehicleEntry(&parkingQueue, parkingSpots, authenticatedUser);
                break;
            }
            case 3: {
                printf("Enter parking spot number: ");
                scanf("%d", &spot_number);  // Read spot_number here
                vehicleExit(&parkingQueue, parkingSpots, spot_number, authenticatedUser);   
                //struct Vehicle exitingVehicle = spot->parked_vehicle;
                //double parking_fee = calculateParkingFee(exitingVehicle.arrival_time, exitingVehicle.type);

                // Process payment
                //processPayment(parking_fee);
                //printf("Vehicle %d has exited from spot #%d. Parking fee: $%.2lf\n", exitingVehicle.id, spot_number, parking_fee);
                break;
            }
            case 4: {
                if (authenticatedUser == ADMIN) {
                    // Display vehicles in the queue (if any)
                    printf("Vehicles in queue:\n");
                    displayQueue(&parkingQueue);
                } else {
                    printf("Authentication required. Please authenticate as an admin.\n");
                }
                break;
            }
            case 5: {
                // Display parking lot status
                displayParkingLot(parkingSpots);
                break;
            }
            case 6: {
                // Display parking statistics
                displayStatistics(&parkingQueue);
                break;
            }
            case 7: {
                char username[20];
                char password[20];
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                authenticatedUser = authenticateUser(users, username, password);

                if (authenticatedUser >= 0) {
                    printf("Authentication successful!\n");
                } else {
                    printf("Authentication failed.\n");
                }
                break;
            }
            case 8: {
                if (authenticatedUser == ATTENDANT) {
                    vehicleEntry(&parkingQueue, parkingSpots, authenticatedUser);
                } else {
                    printf("Authentication required. Please authenticate as an attendant.\n");
                }
                break;
            }
            case 9: {
                if (authenticatedUser == ATTENDANT) {
                    // Cancel a reservation
                    int reservation_id;
                    printf("Enter reservation ID to cancel: ");
                    scanf("%d", &reservation_id);
                    cancelReservation(reservations, reservation_id);
                    printf("Reservation with ID %d has been canceled.\n", reservation_id);
                } else {
                    printf("Authentication required. Please authenticate as an attendant.\n");
                }
                break;
            }
            case 10: {
                // Display reserved spots
                displayReservedSpots(reservations);
                break;
            }
            case 11: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice! Please enter a valid option.\n");
                break;
            }
        }
    } while (option != 11);

    return 0;
}

// Rest of the code remains the same as provided in the previous response.
void initQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* q) {
    return (q->size == 0);
}

// Function to enqueue a vehicle into the queue
void enqueue(struct Queue* q, struct Vehicle vehicle) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->vehicle = vehicle;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    q->size++;
}

// Function to dequeue a vehicle from the queue
struct Vehicle dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        struct Vehicle emptyVehicle = {-1}; // Indicates an empty vehicle
        return emptyVehicle;
    }

    struct QueueNode* temp = q->front;
    struct Vehicle vehicle = temp->vehicle;

    q->front = q->front->next;
    free(temp);
    q->size--;

    return vehicle;
}

// Function to allocate a parking spot for a vehicle
void allocateParkingSpot(struct ParkingSpot spots[], struct Vehicle vehicle) {
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        if (!spots[i].is_occupied && spots[i].type == vehicle.type) {
            spots[i].is_occupied = 1;
            spots[i].parked_vehicle = vehicle;
            printf("Vehicle %d has been allocated parking spot %d.\n", vehicle.id, i + 1);
            break;
        }
    }
}

// Function to calculate parking fee
double calculateParkingFee(time_t arrival_time, enum VehicleType type) {
    time_t current_time;
    time(&current_time);
    double duration = difftime(current_time, arrival_time);

    double fee_per_hour;
    switch (type) {
        case CAR:
            fee_per_hour = 2.0;
            break;
        case MOTORCYCLE:
            fee_per_hour = 1.0;
            break;
        case TRUCK:
            fee_per_hour = 3.0;
            break;
        default:
            fee_per_hour = 0.0; // Unknown vehicle type
            break;
    }

    double fee = (duration / 3600) * fee_per_hour;
    return fee;
}

// Function to display the parking lot status
void displayParkingLot(struct ParkingSpot spots[]) {
    printf("Parking Lot Status:\n");
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        printf("Spot %d: ", i + 1);
        if (spots[i].is_occupied) {
            printf("Occupied by Vehicle %d (%s)\n", spots[i].parked_vehicle.id,
                (spots[i].parked_vehicle.type == CAR) ? "Car" :
                (spots[i].parked_vehicle.type == MOTORCYCLE) ? "Motorcycle" : "Truck");
        } else {
            printf("Empty\n");
        }
    }
}

// Function to display parking statistics
void displayStatistics(struct Queue* q) {
    printf("Parking Lot Statistics:\n");
    printf("Total parked vehicles: %d\n", q->size);
    printf("Parking lot capacity: %d\n", MAX_PARKING_SPOTS);
    printf("Available parking spots: %d\n", MAX_PARKING_SPOTS - q->size);
}

// Function to authenticate a user
int authenticateUser(struct User users[], char username[], char password[]) {
    for (int i = 0; i < sizeof(users) % sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return users[i].type;
        }
    }
    return -1; // Authentication failed
}

// Function to process a payment
void processPayment(double amount) {
    // Implement payment processing logic here
    printf("Payment processed. Amount: $%.2f\n", amount);

    // In a real system, you might perform actions like:
    // 1. Charging the customer's credit card or deducting from a digital wallet.
    // 2. Updating the transaction history.
    // 3. Sending a payment confirmation email or receipt.
    // 4. Logging the payment for auditing purposes.

    // For the sake of this example, we'll just simulate a delay to mimic payment processing.
    printf("Simulating payment processing...\n");
    sleep(2); // Sleep for 2 seconds to simulate payment processing time

    // Payment processed successfully
    printf("Payment processed successfully.\n");
}

// Function to make a reservation
int makeReservation(struct Reservation reservations[], struct Vehicle vehicle, char username[]) {
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        if (reservations[i].reservation_id == 0) {
            reservations[i].reservation_id = i + 1;
            strcpy(reservations[i].username, username);
            reservations[i].reserved_vehicle = vehicle;
            reservations[i].reservation_time = time(NULL);
            return reservations[i].reservation_id;
        }
    }
    return -1; // Reservation failed
}

// Function to cancel a reservation
void cancelReservation(struct Reservation reservations[], int reservation_id) {
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        if (reservations[i].reservation_id == reservation_id) {
            reservations[i].reservation_id = 0;
            return;
        }
    }
}

// Function to display reserved spots
void displayReservedSpots(struct Reservation reservations[]) {
    printf("Reserved Parking Spots:\n");
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        if (reservations[i].reservation_id != 0) {
            printf("Reservation ID: %d, Username: %s, Vehicle Type: %s\n",
                reservations[i].reservation_id, reservations[i].username,
                (reservations[i].reserved_vehicle.type == CAR) ? "Car" :
                (reservations[i].reserved_vehicle.type == MOTORCYCLE) ? "Motorcycle" : "Truck");
        }
    }
}

//function to display the vehicles in queue
void displayQueue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("No vehicles in the parking queue.\n");
        return;
    }

    struct QueueNode* current = q->front;
    int vehicleCount = 1;
    while (current != NULL) {
        struct Vehicle vehicle = current->vehicle;
        printf("Vehicle %d (%s)\n", vehicleCount,
               (vehicle.type == CAR) ? "Car" :
               (vehicle.type == MOTORCYCLE) ? "Motorcycle" : "Truck");
        current = current->next;
        vehicleCount++;
    }
}

void vehicleArrive(struct Queue* q, int* vehicleCount, enum UserType authenticatedUser) {
    if (authenticatedUser == ATTENDANT) {
        if (q->size < MAX_PARKING_SPOTS) {
            struct Vehicle newVehicle = {(*vehicleCount), time(NULL)};
            printf("Enter vehicle type (0: Car, 1: Motorcycle, 2: Truck): ");
            int type;
            scanf("%d", &type);
            newVehicle.type = (enum VehicleType)type;
            enqueue(q, newVehicle);
            printf("Vehicle %d has arrived and is waiting.\n", (*vehicleCount));
            (*vehicleCount)++;
        } else {
            printf("Parking lot is full!\n");
        }
    } else {
        printf("Authentication required. Please authenticate as an attendant.\n");
    }
}

void vehicleEntry(struct Queue* q, struct ParkingSpot spots[], enum UserType authenticatedUser) {
    if (authenticatedUser == ATTENDANT) {
        if (isQueueEmpty(q)) {
            printf("No vehicles in the parking queue.\n");
            return;
        }

        struct Vehicle enteringVehicle = dequeue(q);
        allocateParkingSpot(spots, enteringVehicle);
        printf("Vehicle %d has entered the parking lot.\n", enteringVehicle.id);
    } else {
        printf("Authentication required. Please authenticate as an attendant.\n");
    }
}

void vehicleExit(struct Queue* q, struct ParkingSpot spots[], int spot_number, enum UserType authenticatedUser) {
    if (authenticatedUser == ATTENDANT) {
        if (spot_number >= 0 && spot_number < MAX_PARKING_SPOTS) {
            struct ParkingSpot* spot = &spots[spot_number];
            if (spot->is_occupied) {
                printf("Spot #%d is empty.\n", spot_number);
            } else {
                struct Vehicle exitingVehicle = spot->parked_vehicle;
                double parking_fee = calculateParkingFee(exitingVehicle.arrival_time, exitingVehicle.type);

                // Process payment
                processPayment(parking_fee);

                spot->is_occupied = 0;
                printf("Vehicle %d has exited from spot #%d. Parking fee: $%.2lf\n", exitingVehicle.id, spot_number, parking_fee);
            }
        } else {
            printf("Invalid spot number.\n");
        }
    } else {
        printf("Authentication required. Please authenticate as an attendant.\n");
    }
}
