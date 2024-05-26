#include <stdio.h>
#include <assert.h>  // For assertions

extern long count_digits(char *string); 

int main() {
    // Test Cases
    char *testStrings[] = {
        "",                // Empty string
        "12345",           // Only digits
        "abcde",           // No digits
        "Hello123World",   // Mixed digits and letters
        "1a2b3c4d5e",      // Digits with interspersed letters
        "!@#$%^&*()",     // Special characters
        "0987654321",      // Digits in reverse order
    };

    int expectedCounts[] = {0, 5, 0, 3, 5, 0, 10};

    // Iterate through test cases
    for (int i = 0; i < sizeof(testStrings) / sizeof(testStrings[0]); ++i) {
        long result = count_chars(testStrings[i]);
        printf("Test Case: '%s'\n", testStrings[i]);
        printf("Expected: %d, Actual: %ld\n", expectedCounts[i], result);

        // Assertion to check if result matches expected count
        assert(result == expectedCounts[i]); 

        printf("\n");
    }

    printf("All tests passed!\n");

    return 0;
}
