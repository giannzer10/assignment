
#include "diloseis.h"

int main() {
    Product catalog[NUM_PRODUCTS];
    int parent_to_child[NUM_CUSTOMERS][2]; // Pipe for parent to child
    int child_to_parent[NUM_CUSTOMERS][2]; // Pipe for child to parent
    pid_t pid;

    initialize_catalog(catalog);

    for (int customer = 1; customer <= NUM_CUSTOMERS; customer++) {
        // Create pipes
        pipe(parent_to_child[customer - 1]);
        pipe(child_to_parent[customer - 1]);

        if ((pid = fork()) == 0) {
            // Child process
            close(parent_to_child[customer - 1][1]); // Close unused write end
            close(child_to_parent[customer - 1][0]); // Close unused read end

            double total_spent = 0.0;

            for (int order = 0; order < ORDERS_PER_CUSTOMER; order++) {
                int product_id;
                product_id = num_gen(); // Use num_gen to generate product ID (1-based)

                // Send order to parent
                write(child_to_parent[customer - 1][1], &product_id, sizeof(product_id));

                // Wait for response
                int success;
                double price;
                read(parent_to_child[customer - 1][0], &success, sizeof(success));
                read(parent_to_child[customer - 1][0], &price, sizeof(price));

                if (success) {
    		total_spent += price;
		}
		else
		{
    			total_spent += 0.0;
		}

		const char* result;
		if (success) {
    		result = "Success";
		}
		else {
    		result = "Failure";
			}

		double temp_timi;
		if (success) {
    		temp_timi = price;
		} else
		{
    		temp_timi = 0.0;
		}


                printf("Customer %d: Product %d -> %s, Price: %.2f\n", 
                       customer, product_id, result, temp_timi);

                sleep(1); // Wait before sending next order
            }

            printf("Customer %d: Total Spent: %.2f\n", customer, total_spent);

            close(parent_to_child[customer - 1][0]);
            close(child_to_parent[customer - 1][1]);
            exit(0);
        }
    }

    // Parent process
    for (int customer = 1; customer <= NUM_CUSTOMERS; customer++) {
        close(parent_to_child[customer - 1][0]); // Close unused read end
        close(child_to_parent[customer - 1][1]); // Close unused write end
    }

    for (int customer = 1; customer <= NUM_CUSTOMERS; customer++) {
        for (int order = 0; order < ORDERS_PER_CUSTOMER; order++) {
            int product_id;
            read(child_to_parent[customer - 1][0], &product_id, sizeof(product_id)); // Read from child

            int success = 0;
            double revenue = 0.0;
            process_order(catalog, product_id - 1, &success, &revenue);

            write(parent_to_child[customer - 1][1], &success, sizeof(success)); // Send response to child
            write(parent_to_child[customer - 1][1], &revenue, sizeof(revenue));
        }
    }

    for (int customer = 1; customer <= NUM_CUSTOMERS; customer++) {
        wait(NULL); // Wait for each child process to finish
    }

    generate_report(catalog);

    return 0;
}



