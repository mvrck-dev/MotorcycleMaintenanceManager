#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAINTENANCE_FILE "maintenance.txt"
#define CHASSIS_MAX_LENGTH 17
#define TAX_RATE 0.18

typedef struct {
    char manufacturer[50];
    char model[50];
    char chassis[CHASSIS_MAX_LENGTH + 1];
} Bike;

typedef struct {
    char description[100];
    double charge;
} Service;

typedef struct {
    Bike bike;
    Service services[10];
    int service_count;
    double total_cost;
    double service_charge; // Total cost + tax
} MaintenanceRecord;

void add_new_maintenance() {
    MaintenanceRecord record;
    record.service_count = 0;
    record.total_cost = 0.0;
    record.service_charge = 0.0;

    printf("New Maintenance\n");
    printf("Bike's Manufacturer: ");
    fgets(record.bike.manufacturer, sizeof(record.bike.manufacturer), stdin);
    strtok(record.bike.manufacturer, "\n"); // Remove newline

    printf("Bike's Model: ");
    fgets(record.bike.model, sizeof(record.bike.model), stdin);
    strtok(record.bike.model, "\n"); // Remove newline

    printf("Chassis Number (max 17 characters): ");
    fgets(record.bike.chassis, sizeof(record.bike.chassis), stdin);
    strtok(record.bike.chassis, "\n"); // Remove newline

    char proceed;
    printf("Proceed (Y/N): ");
    scanf(" %c", &proceed);
    getchar(); // Consume newline

    if (proceed != 'Y' && proceed != 'y') {
        printf("Cancelled.\n");
        return;
    }

    while (1) {
        printf("Enter a Service: ");
        fgets(record.services[record.service_count].description, sizeof(record.services[record.service_count].description), stdin);
        strtok(record.services[record.service_count].description, "\n"); // Remove newline

        printf("Enter Service Charge: ");
        scanf("%lf", &record.services[record.service_count].charge);
        getchar(); // Consume newline

        record.total_cost += record.services[record.service_count].charge;
        record.service_count++;

        char add_more;
        printf("Do you want to enter more services (Y/N): ");
        scanf(" %c", &add_more);
        getchar(); // Consume newline

        if (add_more != 'Y' && add_more != 'y') {
            break;
        }
    }

    // Calculate service charge including tax
    record.service_charge = record.total_cost + (record.total_ ncost * TAX_RATE);

    printf("1. Save the service record\n");
    printf("2. Print Bill\n");

    int choice;
    scanf("%d", &choice);
    getchar(); // Consume newline

    FILE *file = fopen(MAINTENANCE_FILE, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    // Store data in file
    fprintf(file, "%s,%s,%s,", record.bike.manufacturer, record.bike.model, record.bike.chassis);

    // List of services and charges
    for (int i = 0; i < record.service_count; i++) {
        fprintf(file, "\"%s, %.2f\",", record.services[i].description, record.services[i].charge);
    }

    // Write total cost and service charge
    fprintf(file, "%.2f, %.2f\n", record.total_cost, record.service_charge);

    if (choice == 2) {
        printf("\nBill:\n");
        printf("Bike Manufacturer: %s\n", record.bike.manufacturer);
        printf("Bike Model: %s\n", record.bike.model);
        printf("Chassis Number: %s\n", record.bike.chassis);
        printf("Total Cost: %.2f\n", record.total_cost);
        printf("Service Charge (with tax): %.2f\n", record.service_charge);
        printf("Services:\n");
        for (int i = 0; i < record.service_count; i++) {
            printf("  - %s: %.2f\n", record.services[i].description, record.services[i].charge);
        }
    }

    fclose(file);
    printf("Record saved successfully.\n");
}

void view_maintenance_history() {
    FILE *file = fopen(MAINTENANCE_FILE, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("1. View all history\n");
    printf("2. Search by chassis number\n");

    int choice;
    scanf("%d", &choice);
    getchar(); // Consume newline

    if (choice == 1) {
        char line[256];
        printf("\nMaintenance History:\n");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
    } else if (choice == 2) {
        char chassis[CHASSIS_MAX_LENGTH + 1];
        printf("Enter Chassis Number: ");
        fgets(chassis, sizeof(chassis), stdin);
        strtok(chassis, "\n"); // Remove newline

        printf("\nMaintenance Records for Chassis Number: %s\n", chassis);

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, chassis)) {
                printf("%s", line);
            }
        }
    } else {
        printf("Invalid choice.\n");
    }

    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\nHome:\n");
        printf("1. New Maintenance\n");
        printf("2. Maintenance History\n");
        printf("3. Exit\n");

        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                add_new_maintenance();
                break;
            case 2:
                view_maintenance_history();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
