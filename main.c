#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct singin {
    char name[30];
    char password[30];
};

void viewPolicyDetails(const char* customerID);
void addCommentOrRequest(const char* customerID);
void updatePersonalInformation(const char* customerID);

int main() {
    // General variables
    char Class[10];
    int choice;
    int userChoice;
    char storeComments[1000];
    FILE *fptrComments;


    // Admin sector
    struct singin admin[5]; // 5 = max admins that can sign-in
    int adminNum = 0;
    FILE *fptrAdmin;
    FILE *fptrAdminID;
    char storeAdminName[30];
    char storeAdminPassword[30];

    // Agent sector
    struct singin agent[50]; // 50 = max agents that can sign-in
    FILE *fptrAgent;
    FILE *fptrAgentID;
    char storeAgentName[30];
    char storeAgentPassword[30];

    // Customer sector
    struct singin customer[500]; // 500 = max customers that can sign-in
    FILE *fptrCustomer;
    FILE *fptrCustomerID;
    FILE *fptrCustomerPolicies;
    char storeCustomerName[30];
    char storeCustomerPassword[30];

    // First line

    printf("\n");
    printf("\t*/-Welcome To Insurance Company Management System-\\* \n");
    printf("\n");
    printf("\t----------------------------------------------------\n");
    printf("\n");
    printf(" 1 : if you were Admin \t 2 : if you were Agent \t 3 : if you were Customer\n");
    scanf("%d", &choice);

    // User choice
    switch (choice) {
    case 1:

        printf("You entered as Admin\n");
        printf("Sign in : 1\nLog in : 2\n");
        scanf("%d", &userChoice);

        switch (userChoice) {
        case 1:
            fptrAdmin = fopen("admin-signin.csv", "a");
            fptrAdminID = fopen("admin-id.csv", "a");
            strcpy(Class, "Admin");
            getchar();
            // Admin inputs
            printf("Enter your name: ");
            fgets(admin[adminNum].name, sizeof(admin[adminNum].name), stdin);
            printf("Enter your ID: ");
            fgets(admin[adminNum].password, sizeof(admin[adminNum].password), stdin);
            // Remove newline characters
            admin[adminNum].name[strcspn(admin[adminNum].name, "\n")] = 0;
            admin[adminNum].password[strcspn(admin[adminNum].password, "\n")] = 0;
            fprintf(fptrAdmin, "%s,%s\n", admin[adminNum].name, admin[adminNum].password);
            fprintf(fptrAdminID, "%s\n", admin[adminNum].password);

            fclose(fptrAdmin);
            fclose(fptrAdminID);
            break;
        case 2:
            adminNum = 0;
            fptrAdminID = fopen("admin-id.csv", "r");
            if (fptrAdminID == NULL) {
                printf("Failed to open admin-id.csv\n");
                return 1;
            }

            // Read admin IDs from file
            while (fscanf(fptrAdminID, "%29s", admin[adminNum].password) != EOF) {
                adminNum++;
            }
            fclose(fptrAdminID);

            getchar();
            printf("Enter The ID: ");
            fgets(storeAdminPassword, sizeof(storeAdminPassword), stdin);
            storeAdminPassword[strcspn(storeAdminPassword, "\n")] = 0; // Remove newline character

            int loggedIn = 0;

            for (int i = 0; i < adminNum; i++) {
                if (strcmp(admin[i].password, storeAdminPassword) == 0) {
                    loggedIn = 1;
                    break;
                }
            }

            if (loggedIn) {
                printf("Successful login\n");
            } else {
                printf("Failed login\n");
                return 0;
            }

            break;
        default:
            printf("Invalid choice\n");
            return 0;
        }

        // Admin code
        do{
        printf("\n--------------------\n");
        printf("1: User Management\n");
        printf("2: Policy Management\n");
        printf("3: View Customer Claims\n");
        printf("Enter your choice: \n");
        scanf("%d", &userChoice);
        switch (userChoice) {

        case 1:
            printf("1: Create User \n");
            printf("2: Search User\n");
            printf("3: Update User\n");
            printf("4: View Users\n");
            printf("5: Create Agent \n");
            printf("6: Search Agent\n");
            printf("7: Update Agent\n");
            printf("8: View Agents\n");
            printf("---Deletion Sector----\n");
            printf("9: Delete Users\n");
            printf("10: Delete Agents\n");
            printf("NUM>10: Show Menu Again\n");
            printf("Enter your choice: \n");
            scanf("%d", &userChoice);

            switch (userChoice) {
            case 1: // Create User
                // Code to create a new user profile
                if (adminNum < 500) {
                    printf("Enter customer name: ");
                    getchar();
                    fgets(customer[adminNum].name, sizeof(customer[adminNum].name), stdin);

                    printf("Enter customer ID: ");
                    fgets(customer[adminNum].password, sizeof(customer[adminNum].password), stdin);

                    // Remove newline characters
                    customer[adminNum].name[strcspn(customer[adminNum].name, "\n")] = 0;
                    customer[adminNum].password[strcspn(customer[adminNum].password, "\n")] = 0;

                    // Assuming you want to store customer data in a file
                    fptrCustomer = fopen("customer-signin.csv", "a");
                    fptrCustomerID = fopen("customer-id.csv", "a");
                    if (fptrCustomer != NULL) {
                        fprintf(fptrCustomer, "%s,%s\n", customer[adminNum].name, customer[adminNum].password);
                        fprintf(fptrCustomerID, "%s\n", customer[adminNum].password);
                        fclose(fptrCustomer);
                        fclose(fptrCustomerID);
                    } else {
                        printf("Failed to open customer data file\n");
                    }

                    printf("Customer created successfully\n");
                    adminNum++; // Increment the number of customers
                } else {
                    printf("Maximum number of customers reached\n");
                }
                break;

            case 2: // Search User
                // Code to search for a specific user profile
                adminNum = 0;
                fptrCustomerID = fopen("customer-id.csv", "r");
                fptrCustomer = fopen("customer-signin.csv", "r");

                if (fptrCustomerID == NULL || fptrCustomer == NULL) {
                    printf("Failed to open customer data files\n");
                    if (fptrCustomerID != NULL) fclose(fptrCustomerID);
                    if (fptrCustomer != NULL) fclose(fptrCustomer);
                    break;
                }

                // Load customer IDs from file
                while (fscanf(fptrCustomerID, "%29s", customer[adminNum].password) != EOF) {
                    adminNum++;
                }
                fclose(fptrCustomerID);

                getchar(); // Clear input buffer
                printf("Enter customer ID to search: ");
                fgets(storeCustomerPassword, sizeof(storeCustomerPassword), stdin);
                storeCustomerPassword[strcspn(storeCustomerPassword, "\n")] = 0; // Remove newline character

                int found = 0; // Flag to track if the customer is found
                for (int i = 0; i < adminNum; i++) {
                    if (strcmp(customer[i].password, storeCustomerPassword) == 0) {
                        // Find corresponding name from the customer-signin.csv file [ CHAT-GPT-EDITED ]

                        while (fgets(storeCustomerName, sizeof(storeCustomerName), fptrCustomer) != NULL) {
                            if (strstr(storeCustomerName, storeCustomerPassword) != NULL) {
                                printf("Customer found:\n");
                                printf("Name: %s", storeCustomerName);
                                printf("ID: %s\n", customer[i].password);
                                found = 1;
                                break;
                            }
                        }
                        break; // Stop searching once customer is found
                    }
                }

                if (!found) {
                    printf("Customer not found\n");
                }

                fclose(fptrCustomer);
                break;

            case 3: // Update User
                // Code to update an existing user profile
            fptrCustomer = fopen("customer-signin.csv", "r+");
            fptrCustomerID = fopen("customer-id.csv", "r+");

            if (fptrCustomer == NULL || fptrCustomerID == NULL) {
                printf("Failed to open customer data files for updating\n");
                return 1;
            }

            adminNum = 0;
            // Load customer IDs from file
            while (fscanf(fptrCustomerID, "%29s", customer[adminNum].password) != EOF) {
                adminNum++;
            }
            rewind(fptrCustomerID); // Reset file pointer to the beginning

            char searchInput[30];
            printf("Enter customer ID to update profile: ");
            getchar(); // Clear input buffer
            fgets(searchInput, sizeof(searchInput), stdin);

            // Remove newline character from the input
            searchInput[strcspn(searchInput, "\n")] = '\0';

            found = 0; // Flag to track if the customer is found
            for (int i = 0; i < adminNum; i++) {
                if (strcmp(customer[i].password, searchInput) == 0) {
                    found = 1;

                    while (fgets(storeCustomerName, sizeof(storeCustomerName), fptrCustomer) != NULL) {
                            if (strstr(storeCustomerName, storeCustomerPassword) != NULL) {
                                printf("Customer found:\n");
                                printf("Name: %s", storeCustomerName);
                                printf("ID: %s\n", customer[i].password);
                                found = 1;
                                break;
                            }
                        }

            printf("Enter updated name: ");
            fgets(customer[i].name, sizeof(customer[i].name), stdin);
            printf("Enter updated ID: ");
            fgets(customer[i].password, sizeof(customer[i].password), stdin);

                // Update customer profile in the file
                fseek(fptrCustomer, 0, SEEK_SET); // Reset file pointer to the beginning
            for (int j = 0; j < adminNum; j++) {
                fprintf(fptrCustomer, "%s,%s\n", customer[j].name, customer[j].password);
                fprintf(fptrCustomerID, "%s\n", customer[j].password);
                }
                printf("Customer profile updated successfully\n");
                break; // Stop searching once customer is found
                }
            }

            if (!found) {
                printf("Customer not found\n");
            }

            fclose(fptrCustomer);
            fclose(fptrCustomerID);
            break;


            case 4: // view all users
                // Code to View all users
                fptrCustomer = fopen("customer-signin.csv", "r");
                if (fptrCustomer == NULL) {
                    printf("Failed to open file\n");
                    break;
                }
                while (fgets(storeCustomerName, sizeof(storeCustomerName), fptrCustomer) != NULL) {
                    printf("\n%s\n", storeCustomerName);
                }
                fclose(fptrCustomer);
                break;

            case 5:
                // Create Agent code
    if (adminNum < 50) { // Assuming 50 is the maximum number of agents
        printf("Enter agent name: ");
        getchar(); // Clear input buffer
        fgets(agent[adminNum].name, sizeof(agent[adminNum].name), stdin);

        printf("Enter agent ID: ");
        fgets(agent[adminNum].password, sizeof(agent[adminNum].password), stdin);

        // Remove newline characters
        agent[adminNum].name[strcspn(agent[adminNum].name, "\n")] = '\0';
        agent[adminNum].password[strcspn(agent[adminNum].password, "\n")] = '\0';

        // Assuming you want to store agent data in a file
        fptrAgent = fopen("agent-signin.csv", "a");
        fptrAgentID = fopen("agent-id.csv", "a");
        if (fptrAgent != NULL && fptrAgentID != NULL) {
            fprintf(fptrAgent, "%s,%s\n", agent[adminNum].name, agent[adminNum].password);
            fprintf(fptrAgentID, "%s\n", agent[adminNum].password);
            fclose(fptrAgent);
            fclose(fptrAgentID);
            printf("Agent created successfully\n");
            adminNum++; // Increment the number of agents
        } else {
            printf("Failed to open agent data file\n");
        }
    } else {
        printf("Maximum number of agents reached\n");
    }
    break;

            case 6:
                // Search Agent code
    adminNum = 0;
    fptrAgentID = fopen("agent-id.csv", "r");
    if (fptrAgentID == NULL) {
        printf("Failed to open agent-id.csv\n");
        return 1;
    }

    // Read agent IDs from file
    while (fscanf(fptrAgentID, "%29s", agent[adminNum].password) != EOF) {
        adminNum++;
    }
    fclose(fptrAgentID);

    getchar(); // Clear input buffer
    printf("Enter agent ID to search: ");
    fgets(storeAgentPassword, sizeof(storeAgentPassword), stdin);
    storeAgentPassword[strcspn(storeAgentPassword, "\n")] = '\0'; // Remove newline character

     found = 0; // Flag to track if the agent is found
    for (int i = 0; i < adminNum; i++) {
        if (strcmp(agent[i].password, storeAgentPassword) == 0) {
            // Find corresponding name from the agent-signin.csv file

            while (fgets(storeAgentName, sizeof(storeAgentName), fptrAgent) != NULL) {
                if (strstr(storeAgentName, storeAgentPassword) != NULL) {
                    printf("Agent found:\n");
                    printf("Name: %s", storeAgentName);
                    printf("ID: %s\n", agent[i].password);
                    found = 1;
                    break;
                }
            }
            break; // Stop searching once agent is found
        }
    }

    if (!found) {
        printf("Agent not found\n");
    }

    fclose(fptrAgent);
    break;

            case 7:
                // Update Agent code
    fptrAgent = fopen("agent-signin.csv", "r+");
    fptrAgentID = fopen("agent-id.csv", "r+");

    if (fptrAgent == NULL || fptrAgentID == NULL) {
        printf("Failed to open agent data files for updating\n");
        return 1;
    }

    adminNum = 0;
    // Load agent IDs from file
    while (fscanf(fptrAgentID, "%29s", agent[adminNum].password) != EOF) {
        adminNum++;
    }
    rewind(fptrAgentID); // Reset file pointer to the beginning

     searchInput[30];
    printf("Enter agent ID to update profile: ");
    getchar(); // Clear input buffer
    fgets(searchInput, sizeof(searchInput), stdin);

    // Remove newline character from the input
    searchInput[strcspn(searchInput, "\n")] = '\0';

     found = 0; // Flag to track if the agent is found
    for (int i = 0; i < adminNum; i++) {
        if (strcmp(agent[i].password, searchInput) == 0) {
            found = 1;

            while (fgets(storeAgentName, sizeof(storeAgentName), fptrAgent) != NULL) {
                if (strstr(storeAgentName, storeAgentPassword) != NULL) {
                    printf("Agent found:\n");
                    printf("Name: %s", storeAgentName);
                    printf("ID: %s\n", agent[i].password);
                    found = 1;
                    break;
                }
            }

            printf("Enter updated name: ");
            fgets(agent[i].name, sizeof(agent[i].name), stdin);
            printf("Enter updated ID: ");
            fgets(agent[i].password, sizeof(agent[i].password), stdin);

            // Update agent profile in the file
            fseek(fptrAgent, 0, SEEK_SET); // Reset file pointer to the beginning
            for (int j = 0; j < adminNum; j++) {
                fprintf(fptrAgent, "%s,%s\n", agent[j].name, agent[j].password);
                fprintf(fptrAgentID, "%s\n", agent[j].password);
            }
            printf("Agent profile updated successfully\n");
            break; // Stop searching once agent is found
        }
    }

    if (!found) {
        printf("Agent not found\n");
    }

    fclose(fptrAgent);
    fclose(fptrAgentID);
    break;

            case 8:

                // View All Agents code
    fptrAgent = fopen("agent-signin.csv", "r");

    if (fptrAgent == NULL) {
        printf("Failed to open agent data file for viewing\n");
        return 1;
    }

    printf("List of All Agents:\n");

    // Read and display each line (agent) in the file
    while (fgets(storeAgentName, sizeof(storeAgentName), fptrAgent) != NULL) {
        printf("%s", storeAgentName);
    }

    fclose(fptrAgent);
    break;

// Deletion code for Users
case 9: {
    char userIdToDelete[30];
    printf("Enter the user ID to delete: ");
    getchar(); // Clear input buffer
    fgets(userIdToDelete, sizeof(userIdToDelete), stdin);
    userIdToDelete[strcspn(userIdToDelete, "\n")] = 0; // Remove newline character

    // Load customer data from files
    FILE *fptrCustomer = fopen("customer-signin.csv", "r");
    FILE *fptrCustomerID = fopen("customer-id.csv", "r");

    if (fptrCustomer == NULL || fptrCustomerID == NULL) {
        printf("Failed to open customer data files\n");
        if (fptrCustomer) fclose(fptrCustomer);
        if (fptrCustomerID) fclose(fptrCustomerID);
        break;
    }

    int customerCount = 0;
    while (fscanf(fptrCustomerID, "%29s", customer[customerCount].password) != EOF) {
        customerCount++;
    }
    fclose(fptrCustomerID);

    for (int i = 0; i < customerCount; i++) {
        fgets(customer[i].name, sizeof(customer[i].name), fptrCustomer);
        customer[i].name[strcspn(customer[i].name, "\n")] = 0;
    }
    fclose(fptrCustomer);

    int userIndexToDelete = -1;
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customer[i].password, userIdToDelete) == 0) {
            userIndexToDelete = i;
            break;
        }
    }

    if (userIndexToDelete != -1) {
        // Remove user from customer array
        for (int i = userIndexToDelete; i < customerCount - 1; i++) {
            customer[i] = customer[i + 1];
        }
        customerCount--;

        // Update customer-id.csv file
        fptrCustomerID = fopen("customer-id.csv", "w");
        if (fptrCustomerID != NULL) {
            for (int i = 0; i < customerCount; i++) {
                fprintf(fptrCustomerID, "%s\n", customer[i].password);
            }
            fclose(fptrCustomerID);
        } else {
            printf("Failed to open customer-id.csv for updating\n");
        }

        // Update customer-signin.csv file
        fptrCustomer = fopen("customer-signin.csv", "w");
        if (fptrCustomer != NULL) {
            for (int i = 0; i < customerCount; i++) {
                fprintf(fptrCustomer, "%s,%s\n", customer[i].name, customer[i].password);
            }
            fclose(fptrCustomer);
        } else {
            printf("Failed to open customer-signin.csv for updating\n");
        }

        printf("User deleted successfully\n");
    } else {
        printf("User not found\n");
    }

    break;
}

// Deletion code for Agents
case 10: {
    char agentIdToDelete[30];
    printf("Enter the agent ID to delete: ");
    getchar(); // Clear input buffer
    fgets(agentIdToDelete, sizeof(agentIdToDelete), stdin);
    agentIdToDelete[strcspn(agentIdToDelete, "\n")] = 0; // Remove newline character

    // Load agent data from files
    FILE *fptrAgent = fopen("agent-signin.csv", "r");
    FILE *fptrAgentID = fopen("agent-id.csv", "r");

    if (fptrAgent == NULL || fptrAgentID == NULL) {
        printf("Failed to open agent data files\n");
        if (fptrAgent) fclose(fptrAgent);
        if (fptrAgentID) fclose(fptrAgentID);
        break;
    }

    int agentCount = 0;
    while (fscanf(fptrAgentID, "%29s", agent[agentCount].password) != EOF) {
        agentCount++;
    }
    fclose(fptrAgentID);

    for (int i = 0; i < agentCount; i++) {
        fgets(agent[i].name, sizeof(agent[i].name), fptrAgent);
        agent[i].name[strcspn(agent[i].name, "\n")] = 0;
    }
    fclose(fptrAgent);

    int agentIndexToDelete = -1;
    for (int i = 0; i < agentCount; i++) {
        if (strcmp(agent[i].password, agentIdToDelete) == 0) {
            agentIndexToDelete = i;
            break;
        }
    }

    if (agentIndexToDelete != -1) {
        // Remove agent from agent array
        for (int i = agentIndexToDelete; i < agentCount - 1; i++) {
            agent[i] = agent[i + 1];
        }
        agentCount--;

        // Update agent-id.csv file
        fptrAgentID = fopen("agent-id.csv", "w");
        if (fptrAgentID != NULL) {
            for (int i = 0; i < agentCount; i++) {
                fprintf(fptrAgentID, "%s\n", agent[i].password);
            }
            fclose(fptrAgentID);
        } else {
            printf("Failed to open agent-id.csv for updating\n");
        }

        // Update agent-signin.csv file
        fptrAgent = fopen("agent-signin.csv", "w");
        if (fptrAgent != NULL) {
            for (int i = 0; i < agentCount; i++) {
                fprintf(fptrAgent, "%s,%s\n", agent[i].name, agent[i].password);
            }
            fclose(fptrAgent);
        } else {
            printf("Failed to open agent-signin.csv for updating\n");
        }

        printf("Agent deleted successfully\n");
    } else {
        printf("Agent not found\n");
    }

    break;
}while ( userChoice != 0);

            }


            break;
        case 2:
            printf("1. Add Policy\n");
            printf("2. View Policies\n");
            printf("NUM>2: Show Menu Again\n");
            printf("Enter your choice: ");
            userChoice = 0;
            scanf("%d", &userChoice);
            switch (userChoice) {
                case 1: {
                // Add Policy: Select a customer and assign a policy
                char *policies[] = {
                    "Auto Insurance",
                    "Health Insurance",
                    "Property Insurance",
                    "Life Insurance",
                    "Commercial Insurance",
                    "Travel Insurance",
                    "Pet Insurance",
                    "Crop Insurance",
                    "Marine Insurance",
                    "Liability Insurance"
                    };
                int numPolicies = sizeof(policies) / sizeof(policies[0]);
                int policyChoice;
                int customerIndex;

                // Display list of customers with IDs
                fptrCustomer = fopen("customer-signin.csv", "r");
                if (fptrCustomer == NULL) {
                    printf("Failed to open customer file\n");
                    break;
                }
                // Chat-GPT
                struct singin customers[500]; // Temporary storage for customers
                int customerCount = 0;

                while (fgets(storeCustomerName, sizeof(storeCustomerName), fptrCustomer) != NULL) {
                    char *token = strtok(storeCustomerName, ",");
                if (token) {
                    strcpy(customers[customerCount].name, token);
                    token = strtok(NULL, ",");
                if (token) {
                    strcpy(customers[customerCount].password, token);
                    customerCount++;
                    }
                }
            }

                fclose(fptrCustomer);

            for (int i = 0; i < customerCount; i++) {
                printf("%d: %s\n", i, customers[i].name);
            }

            // Get customer choice
            printf("Enter customer number: ");
            scanf("%d", &customerIndex);
            if (customerIndex < 0 || customerIndex >= customerCount) {
            printf("Invalid customer number\n");
            break;
            }

            // Choose policy
            printf("Select a policy to assign:\n");
            for (int i = 0; i < numPolicies; i++) {
                printf("%d: %s\n", i + 1, policies[i]);
            }
            printf("Enter policy number: ");
            scanf("%d", &policyChoice);
            if (policyChoice < 1 || policyChoice > numPolicies) {
                printf("Invalid policy number\n");
                break;
            }

                // Assign policy to customer
            fptrCustomerPolicies = fopen("customer-policies.csv", "a");
            if (fptrCustomerPolicies != NULL) {
                fprintf(fptrCustomerPolicies, "Name: %s, Policy: %s, ID: %s\n", customers[customerIndex].name, policies[policyChoice - 1], customers[customerIndex].password);
                fclose(fptrCustomerPolicies);
                printf("Policy assigned successfully\n");
            } else {
                printf("Failed to open customer file for updating\n");
            }
                break;
            }
                break;
            case 2:
                // View Policies: Implement functionality to display information about existing policies
                fptrCustomerPolicies = fopen("customer-policies.csv", "r");
                if (fptrCustomerPolicies == NULL) {
                    printf("Failed to open customer file\n");
                    break;
                }
                while (fgets(storeCustomerName, sizeof(storeCustomerName), fptrCustomerPolicies) != NULL) {
                    printf("%s", storeCustomerName);
                }
                fclose(fptrCustomerPolicies);
                break;

            default:
                printf("Invalid choice\n");
                break;
        }
            break;

            case 3:
                 // View All claims
    fptrComments = fopen("customer-comments.csv", "r");

    if (fptrAgent == NULL) {
        printf("Failed to open agent data file for viewing\n");
        return 1;
    }

    printf("List of All Agents:\n");

    // Read and display each line (agent) in the file
    while (fgets(storeComments, sizeof(storeComments), fptrComments) != NULL) {
        printf("%s", storeComments);
    }

    fclose(fptrComments);
    break;

                break;

        default:
            printf("Invalid choice\n");
        }
        }while (userChoice != 0);
        break;

    case 2:
        printf("You entered as Agent\n");
        printf("As Agent You Only Can Edit Policies of Customers\n");
        printf("Sign in : 1\nLog in : 2\n");
        scanf("%d", &userChoice);

        switch (userChoice) {

        case 1:
            fptrAgent = fopen("agent-signin.csv", "a");
            fptrAgentID = fopen("agent-id.csv", "a");
            strcpy(Class, "Agent");
            getchar();
            // Agent inputs
            printf("Enter your name: ");
            fgets(agent[adminNum].name, sizeof(agent[adminNum].name), stdin);
            printf("Enter your ID: ");
            fgets(agent[adminNum].password, sizeof(agent[adminNum].password), stdin);
            // Remove newline characters
            agent[adminNum].name[strcspn(agent[adminNum].name, "\n")] = 0;
            agent[adminNum].password[strcspn(agent[adminNum].password, "\n")] = 0;
            fprintf(fptrAgent, "%s,%s\n", agent[adminNum].name, agent[adminNum].password);
            fprintf(fptrAgentID, "%s\n", agent[adminNum].password);

            fclose(fptrAgent);
            fclose(fptrAgentID);
            break;
        case 2:

            adminNum = 0;
            fptrAgentID = fopen("agent-id.csv", "r");
            if (fptrAgentID == NULL) {
                printf("Failed to open agent-id.csv\n");
                return 1;
            }

            // Read agent IDs from file
            while (fscanf(fptrAgentID, "%29s", agent[adminNum].password) != EOF) {
                adminNum++;
            }
            fclose(fptrAgentID);

            getchar();
            printf("Enter The ID: ");
            fgets(storeAgentPassword, sizeof(storeAgentPassword), stdin);
            storeAgentPassword[strcspn(storeAgentPassword, "\n")] = 0; // Remove newline character

            int loggedIn = 0;

            for (int i = 0; i < adminNum; i++) {
                if (strcmp(agent[i].password, storeAgentPassword) == 0) {
                    loggedIn = 1;
                    break;
                }
            }

            if (loggedIn) {
                printf("Successful login\n");
            } else {
                printf("Failed login\n");
                return 0;
            }

            break;
        default:
            printf("Invalid choice\n");
        }

        // Agent code

            char *policies[] = {
        "Auto Insurance",
        "Health Insurance",
        "Property Insurance",
        "Life Insurance",
        "Commercial Insurance",
        "Travel Insurance",
        "Pet Insurance",
        "Crop Insurance",
        "Marine Insurance",
        "Liability Insurance"
    };
    int numPolicies = sizeof(policies) / sizeof(policies[0]);
    int policyChoice;
    int customerIndex;

    // Display list of customers with IDs
    fptrCustomer = fopen("customer-signin.csv", "r");
    if (fptrCustomer == NULL) {
        printf("Failed to open customer file\n");
        break;
    }
    // Temporary storage for customers
    struct singin customers[500];
    int customerCount = 0;

    while (fgets(storeCustomerName, sizeof(storeCustomerName), fptrCustomer) != NULL) {
        char *token = strtok(storeCustomerName, ",");
        if (token) {
            strcpy(customers[customerCount].name, token);
            token = strtok(NULL, ",");
            if (token) {
                strcpy(customers[customerCount].password, token);
                customerCount++;
            }
        }
    }

    fclose(fptrCustomer);

    for (int i = 0; i < customerCount; i++) {
        printf("%d: %s\n", i, customers[i].name);
    }

    // Get customer choice
    printf("Enter customer number: ");
    scanf("%d", &customerIndex);
    if (customerIndex < 0 || customerIndex >= customerCount) {
        printf("Invalid customer number\n");
        break;
    }

    // Choose policy
    printf("Select a policy to assign:\n");
    for (int i = 0; i < numPolicies; i++) {
        printf("%d: %s\n", i + 1, policies[i]);
    }
    printf("Enter policy number: ");
    scanf("%d", &policyChoice);
    if (policyChoice < 1 || policyChoice > numPolicies) {
        printf("Invalid policy number\n");
        break;
    }

    // Assign policy to customer
    fptrCustomerPolicies = fopen("customer-policies.csv", "a");
    if (fptrCustomerPolicies != NULL) {
        fprintf(fptrCustomerPolicies, "Name: %s, Policy: %s, ID: %s\n", customers[customerIndex].name, policies[policyChoice - 1], customers[customerIndex].password);
        fclose(fptrCustomerPolicies);
        printf("Policy assigned successfully\n");
    } else {
        printf("Failed to open customer file for updating\n");
    }
    break;


        break;

    case 3:

        printf("You entered as Customer\n");
        printf("Sign in : 1\nLog in : 2\n");
        scanf("%d", &userChoice);

        switch (userChoice) {
        case 1:
            fptrCustomer = fopen("customer-signin.csv", "a");
            fptrCustomerID = fopen("customer-id.csv", "a");
            strcpy(Class, "Customer");
            getchar();
            // Customer inputs
            printf("Enter your name: ");
            fgets(customer[adminNum].name, sizeof(customer[adminNum].name), stdin);
            printf("Enter your ID: ");
            fgets(customer[adminNum].password, sizeof(customer[adminNum].password), stdin);
            // Remove newline characters
            customer[adminNum].name[strcspn(customer[adminNum].name, "\n")] = 0;
            customer[adminNum].password[strcspn(customer[adminNum].password, "\n")] = 0;
            fprintf(fptrCustomer, "%s,%s\n", customer[adminNum].name, customer[adminNum].password);
            fprintf(fptrCustomerID, "%s\n", customer[adminNum].password);

            fclose(fptrCustomer);
            fclose(fptrCustomerID);
            break;

        case 2:
            adminNum = 0;
            fptrCustomerID = fopen("customer-id.csv", "r");
            if (fptrCustomerID == NULL) {
                printf("Failed to open customer-id.csv\n");
                return 1;
            }

            // Read customer IDs from file
            while (fscanf(fptrCustomerID, "%29s", customer[adminNum].password) != EOF) {
                adminNum++;
            }
            fclose(fptrCustomerID);

            getchar();
            printf("Enter The ID: ");
            fgets(storeCustomerPassword, sizeof(storeCustomerPassword), stdin);
            storeCustomerPassword[strcspn(storeCustomerPassword, "\n")] = 0; // Remove newline character

            int loggedIn = 0;

            for (int i = 0; i < adminNum; i++) {
                if (strcmp(customer[i].password, storeCustomerPassword) == 0) {
                    loggedIn = 1;
                    break;
                }
            }

            if (loggedIn) {
                printf("Successful login\n");
            } else {
                printf("Failed login\n");
                return 0;
            }

            break;
        default:
            printf("Invalid choice\n");
        }

        // Customer code

        int customerOption;
    do {
        // Display customer menu options
        printf("Customer Menu:\n");
        printf("1. View Policy Details\n");
        printf("2. Add Claim\n");
        printf("3. End The Process\n");
        printf("4. Return Customer Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &customerOption);

        switch (customerOption) {
            case 1:
                // View Policy Details: Implement functionality to display the customer's policy details
                viewPolicyDetails(storeCustomerPassword);
                break;
            case 2:
                // Add Comment Or Request: Implement functionality for the customer to add requests
                addCommentOrRequest(storeCustomerPassword);
                break;
            case 3:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (customerOption != 4);
    break;

        break;

    default:
        printf("Invalid choice\n");
    }

    return 0;
}

void viewPolicyDetails(const char* customerID) {
    FILE *fptrCustomerPolicies;
    char line[100];
    int found = 0;

    fptrCustomerPolicies = fopen("customer-policies.csv", "r");
    if (fptrCustomerPolicies == NULL) {
        printf("Failed to open customer-policies.csv\n");
        return;
    }

    while (fgets(line, sizeof(line), fptrCustomerPolicies) != NULL) {
        // Check if the line contains the customer ID
        if (strstr(line, customerID) != NULL) {
            printf("Policy details for customer ID %s:\n", customerID);
            printf("%s", line); // Print the entire line
            found = 1;
        }
    }

    fclose(fptrCustomerPolicies);

    if (!found) {
        printf("No policies found for customer ID: %s\n", customerID);
    }
}

void addCommentOrRequest(const char* customerID) {
    FILE *fptrComments;
    char comment[100];

    printf("Enter your comment or request:\n");
    getchar(); // Clear input buffer
    fgets(comment, sizeof(comment), stdin);
    comment[strcspn(comment, "\n")] = '\0'; // Remove newline character

    // Open file to append comments/requests
    fptrComments = fopen("customer-comments.csv", "a");
    if (fptrComments == NULL) {
        printf("Failed to open customer-comments.csv\n");
        return;
    }

    // Write customer ID and comment/request to file
    fprintf(fptrComments, "Customer ID: %s ,Comment/Request: %s\n", customerID, comment);
    fclose(fptrComments);

    printf("Comment/Request added successfully.\n");
}


