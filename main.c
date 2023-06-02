//Ardian Graçi   Nadir Alan   Muhamed Ademi

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define MAX_HISTORY_SIZE 100


// Structure to hold BMI category information
typedef struct {
    float upperLimit;
    const char* label;
} BMICategory;


// Function to convert weight to kilograms
bool convertToKilograms(float weight, char unit, float* result) {
    if (unit == 'k' || unit == 'K') {
        *result = weight; // Already in kilograms
        return true;
    } else if (unit == 'p' || unit == 'P') {
        *result = weight * 0.453592; // Convert pounds to kilograms
        return true;
    } else {
        printf("Invalid weight unit. Please enter 'p' for pounds or 'k' for kilograms.\n");
        return false;
    }
}

// Function to convert height to meters
float convertToMeters(float height, char unit) {
    if (unit == 'm' || unit == 'M') {
        return height; // Already in meters
    } else if (unit == 'f' || unit == 'F') {
        return height * 0.3048; // Convert feet to meters
    } else {
        printf("Invalid height unit. Please enter 'f' for feet or 'm' for meters.\n");
        return -1;
    }
}

// Function to calculate BMI
float calculateBMI(float weight, float height) {
    if (height <= 0) {
        printf("Invalid input for height. Height must be a positive numeric value.\n");
        return -1;
    }

    return weight / (height * height);
}

// Function to print weight status category
void printWeightStatus(float bmi, BMICategory* categories, int numCategories) {
    if (bmi < 0) {
        return; // Error occurred in calculation, so weight status cannot be determined
    }

    int categoryIndex = -1;
    for (int i = 0; i < numCategories; i++) {
        if (bmi <= categories[i].upperLimit) {
            categoryIndex = i;
            break;
        }
    }

    if (categoryIndex != -1) {
        printf("Weight status: %s\n", categories[categoryIndex].label);
    } else {
        printf("Invalid BMI category\n");
    }
}

// Unit tests for the BMI calculation function
bool runBMITests() {
    float weight, height, bmi;

    // Test case 1: Normal weight calculation
    weight = 68.0;
    height = 1.75;
    bmi = calculateBMI(weight, height);
    if (fabs(bmi - 22.2) > 0.01) {
        printf("Test case 1 failed: Incorrect BMI calculation for normal weight\n");
        return false;
    }

    // Test case 2: Underweight calculation
    weight = 50.0;
    height = 1.65;
    bmi = calculateBMI(weight, height);
    if (fabs(bmi - 18.37) > 0.01) {
        printf("Test case 2 failed: Incorrect BMI calculation for underweight\n");
        return false;
    }

    // Test case 3: Overweight calculation
    weight = 90.0;
    height = 1.8;
    bmi = calculateBMI(weight, height);
    if (fabs(bmi - 27.78) > 0.01) {
        printf("Test case 3 failed: Incorrect BMI calculation for overweight\n");
        return false;
    }

    // Test case 4: Obese calculation
    weight = 110.0;
    height = 1.7;
    bmi = calculateBMI(weight, height);
    if (fabs(bmi - 38.07) > 0.01) {
        printf("Test case 4 failed: Incorrect BMI calculation for obese\n");
        return false;
    }

    return true;
}




// Function to pick custom BMI ranges and labels
void pickRangesAndLabels(BMICategory* categories, int numCategories) {
     printf("\n");
    printf("  ==================================\n");
    printf("  |   BMI Range   |  Category      |\n");
    printf("  ==================================\n");
    printf("  |   < 18.5      | 1. Underweight |\n");
    printf("  |--------------------------------|\n");
    printf("  |  18.5-24.9    | 2. Normal      |\n");
    printf("  |--------------------------------|\n");
    printf("  |  25.0-29.9    | 3. Overweight  |\n");
    printf("  |--------------------------------|\n");
    printf("  |   >= 30.0     | 4. Obese       |\n");
    printf("  ==================================\n");



    printf("\n");
    printf("\n");
    printf("  Enter custom BMI ranges and labels:\n");
    for (int i = 0; i < numCategories; i++) {
        printf("  Enter the upper limit for category %d: ", i + 1);
        scanf("%f", &(categories[i].upperLimit));
        printf("  Enter the label for category %d: ", i + 1);
        char label[100];
        scanf("%s", label);
        categories[i].label = strdup(label);
    }
}

// Function to store the BMI calculation result in a file
void storeResult(float bmi) {
    FILE* file = fopen("bmi_results.txt", "a+");
    if (file == NULL) {
        printf("Error! The file cannot be opened.\n");
        return;
    }

    fprintf(file, "%.2f\n", bmi);
    fclose(file);
}


BMICategory defaultCategories[] = {
    {18.5, "Underweight"},
    {24.9, "Normal weight"},
    {29.9, "Overweight"},
    {1000, "Obese"}
};



// Function to read and display previous results from a file
void displayPreviousResults() {
    FILE* file = fopen("bmi_results.txt", "r");
    if (file == NULL) {
        printf("\n");
        printf("  No previous results found.\n");
        return;
    }


    printf("\n");
    printf("\n");
    printf("  ===========================================\n");
    printf("  |     PREVIOUS BMI    |       Category    |\n");
    printf("  ===========================================\n");

    float result;
    while (fscanf(file, "%f", &result) != EOF) {
        int categoryIndex = -1;
        for (int i = 0; i < 4; i++) {
            if (result <= defaultCategories[i].upperLimit) {
                categoryIndex = i;
                break;
            }
        }

        if (categoryIndex != -1) {
            printf("  |    %.2f            | %-18s|\n", result, defaultCategories[categoryIndex].label);
        } else {
            printf("  |    %.2f     |   Invalid category  |\n", result);
        }
    }

    printf("  ===========================================\n");

    fclose(file);
}


int main() {


    int option;
    // Run unit tests
    if (!runBMITests()) {
        printf("Unit tests failed. Exiting program.\n");
        return 1;
    }

    // Default BMI categories and labels
    BMICategory defaultCategories[] = {
        {18.5, "Underweight"},
        {24.9, "Normal weight"},
        {29.9, "Overweight"},
        {1000, "Obese"}
    };

    BMICategory customCategories[4];


    printf("\n");
    printf("\n");


    printf("          ________  ________   ____  __  _______   _________    __    ________  ____    ___  __________  ____ \n");
    printf("         /_  __/ / / / ____/  / __ )/  |/  /  _/  / ____/   |  / /   / ____/ / / / /   /   |/_  __/ __ \\/ __ \\\n");
    printf("          / / / /_/ / __/    / __  / /|_/ // /   / /   / /| | / /   / /   / / / / /   / /| | / / / / / / /_/ /\n");
    printf("         / / / __  / /___   / /_/ / /  / // /   / /___/ ___ |/ /___/ /___/ /_/ / /___/ ___ |/ / / /_/ / _, _/ \n");
    printf("        /_/ /_/ /_/_____/  /_____/_/  /_/___/   \\____/_/  |_/_____/\\____/\\____/_____/_/  |_/_/  \\____/_/ |_|  \n");

    printf("\n");
    printf("\n");
    printf("  ==========================================\n");
    printf("  |               PICK OPTION              |\n");
    printf("  ==========================================\n");
    printf("  | 1. Find BMI                            |\n");
    printf("  | 2. Check previous results              |\n");
    printf("  ==========================================\n");

    printf("\n  Choose option: ");
    scanf("%d", &option);
    system("cls");

    switch (option) {
        case 1: {
            char weightUnit, heightUnit;
            float weight, height, bmi;
            bool customRanges = false;


            printf("\n");
            printf("\n");
            printf("  ==========================================\n");
            printf("  |               FIND BMI                 |\n");
            printf("  ==========================================\n");
            printf("  | 1. Use default BMI ranges/labels       |\n");
            printf("  | 2. Create custom BMI ranges/labels     |\n");
            printf("  ==========================================\n");

            printf("\n  Choose option: ");
            scanf("%d", &option);
            system("cls");

            if (option == 2) {
                customRanges = true;
                pickRangesAndLabels(customCategories, 4);
            }


            printf("\n");
            printf("\n");
            printf("  ==========================================\n");
            printf("  |        CALCULATE BMI - OPTIONS         |\n");
            printf("  ==========================================\n");
            printf("  | 1. Metric System (kg, m)               |\n");
            printf("  | 2. Imperial System (lb, ft)            |\n");
            printf("  ==========================================\n");

            printf("\n  Choose option: ");
            scanf("%d", &option);
            system("cls");

            if (option == 1) {
                weightUnit = 'k';
                heightUnit = 'm';
            } else if (option == 2) {
                weightUnit = 'p';
                heightUnit = 'f';
            } else {
                printf("\n");
                printf("\n");
                printf("  Invalid option. Please choose option 1 or 2.\n");
                return 0;
            }
            printf("\n");
            printf("\n");
            printf("  Enter weight: ");
            scanf("%f", &weight);

            float weightInKg;
            if (!convertToKilograms(weight, weightUnit, &weightInKg)) {
                return 0;
            }
            printf("\n");
            printf("\n");
            printf("  Enter height: ");
            scanf("%f", &height);

            float heightInMeters = convertToMeters(height, heightUnit);
            if (heightInMeters == -1) {
                return 0;
            }

            bmi = calculateBMI(weightInKg, heightInMeters);

            printf("\n");
            printf("\n");
            printf("BMI: %.2f\n", bmi);

            if (customRanges) {
                printWeightStatus(bmi, customCategories, 4);
            } else {
                printWeightStatus(bmi, defaultCategories, 4);
            }

            // Store the BMI calculation result
            storeResult(bmi);

            break;
        }
        case 2: {

            // Read and display previous results from a file
            displayPreviousResults();
            break;
        }
        default:
            printf("Invalid option. Please choose option 1 or 2.\n");
            break;
    }

    return 0;
}
