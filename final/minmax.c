#include <stdio.h>
#include <assert.h>

extern void min_max(long *array, unsigned long len, long *min, long *max);

void printArray(long *arr, unsigned long len) {
    printf("[");
    for (unsigned long i = 0; i < len / 8; i++) {  // len/8 to get element count
        printf("%ld", arr[i]);
        if (i < len / 8 - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // Test Cases
    long testData1[] = {5, -3, 12, 0, 8, -15};
    long testData2[] = {-100, 50, 25, -75, 0};
    long testData3[] = {7};  // Single element array
    long testData4[] = {};   // Empty array

    long expectedMins[] = {-15, -100, 7, 0}; // Placeholder for empty array
    long expectedMaxs[] = {12, 50, 7, 0};  // Placeholder for empty array

    long *testArrays[] = {testData1, testData2, testData3, testData4};
    unsigned long testLengths[] = {sizeof(testData1), sizeof(testData2), sizeof(testData3), sizeof(testData4)};

    // Iterate through test cases
    for (int i = 0; i < sizeof(testArrays) / sizeof(testArrays[0]); ++i) {
        long minResult, maxResult;
        long *currentArray = testArrays[i];
        unsigned long currentLength = testLengths[i];

        printf("Test Case %d:\n", i + 1);
        printf("Input Array: ");
        printArray(currentArray, currentLength);

        min_max(currentArray, currentLength, &minResult, &maxResult);

        printf("Expected Min: %ld, Actual Min: %ld\n", expectedMins[i], minResult);
        printf("Expected Max: %ld, Actual Max: %ld\n", expectedMaxs[i], maxResult);
        
        // Assertions to check if results match expected values
        assert(minResult == expectedMins[i]);
        assert(maxResult == expectedMaxs[i]);

        printf("\n");
    }

    printf("All tests passed!\n");

    return 0;
}
