#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#define NUM_PRODUCTS 20
#define NUM_CUSTOMERS 5
#define ORDERS_PER_CUSTOMER 10

typedef struct {
    char name[20];
    double price;
    int item_count;
    int requests;
    int sold;
} Product;


void initialize_catalog(Product catalog[]) {
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        sprintf(catalog[i].name, "Product %d", i + 1); // Set product name
        catalog[i].price = (rand() % 1000) / 10.0; // Random price between 0.0 and 99.9
        catalog[i].item_count = 2;
        catalog[i].requests = 0;
        catalog[i].sold = 0;
    }
}

void process_order(Product catalog[], int product_id, int *successful, double *revenue) {
    catalog[product_id].requests++;
    if (catalog[product_id].item_count > 0) {
        catalog[product_id].item_count--;
        catalog[product_id].sold++;
        *successful = 1;
        *revenue = catalog[product_id].price;
    } else {
        *successful = 0;
        *revenue = 0.0;
    }
}

void generate_report(Product catalog[]) {
    int total_requests = 0, total_successful = 0, total_failed = 0;
    double total_revenue = 0.0;

    printf("\nSummary Report:\n");
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        printf("%s\n", catalog[i].name); // Use product name from the struct
        printf(" - Requests: %d\n", catalog[i].requests);
        printf(" - Sold: %d\n", catalog[i].sold);
        printf(" - Remaining: %d\n", catalog[i].item_count);

        total_requests += catalog[i].requests;
        total_successful += catalog[i].sold;
        total_failed += catalog[i].requests - catalog[i].sold;
        total_revenue += catalog[i].sold * catalog[i].price;
    }

    printf("\nFinal Summary:\n");
    printf("Total Requests: %d\n", total_requests);
    printf("Total Successful: %d\n", total_successful);
    printf("Total Failed: %d\n", total_failed);
    printf("Total Revenue: %.2f\n", total_revenue);
}

int num_gen() {
    srand(time(NULL)); // Set seed based on current time
        int value = rand() % 20; // Generate different numbers between 0-19
	return value+1;
}
