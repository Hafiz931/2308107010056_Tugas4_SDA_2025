#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * Generates random numbers and saves them to a file
 * @param filename: Name of the output file
 * @param count: Number of random numbers to generate
 * @param max_value: Maximum value for the random numbers (exclusive)
 */
void generate_random_numbers(const char *filename, int count, int max_value) {
    // Open file in write mode
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    
    // Seed the random number generator with current time
    srand((unsigned int)time(NULL));
    
    // Generate 'count' random numbers
    for (int i = 0; i < count; i++) {
        int number = rand() % max_value;  // Generate number between 0 and max_value-1
        fprintf(file, "%d\n", number);    // Write number to file
    }
    
    // Close the file and print success message
    fclose(file);
    printf("Successfully generated %d random numbers in %s\n", count, filename);
}

/**
 * Generates a single random word of specified length
 * @param word: Pointer to store the generated word
 * @param length: Desired length of the word
 */
void generate_random_word(char *word, int length) {
    const char letters[] = "abcdefghijklmnopqrstuvwxyz";  // Possible characters
    int letter_count = strlen(letters);                  // Total available letters

    // Generate each character of the word randomly
    for (int i = 0; i < length; i++) {
        int index = rand() % letter_count;  // Pick random index
        word[i] = letters[index];           // Assign corresponding letter
    }
    word[length] = '\0';  // Null-terminate the string
}

/**
 * Generates multiple random words and saves them to a file
 * @param filename: Name of the output file
 * @param count: Number of random words to generate
 * @param max_length: Maximum length for each word
 */
void generate_many_random_words(const char *filename, int count, int max_length) {
    // Open file in write mode
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    char word[100];  // Buffer to hold each word
    
    // Generate 'count' random words
    for (int i = 0; i < count; i++) {
        // Determine random length between 3 and max_length characters
        int length = (rand() % (max_length - 3)) + 3;
        generate_random_word(word, length);  // Generate the word
        fprintf(file, "%s\n", word);         // Write word to file
    }
    
    // Close the file and print success message
    fclose(file);
    printf("Successfully generated %d random words in %s\n", count, filename);
}

/**
 * Main function that coordinates the generation of random data
 */
int main() {
    // Generate 2,000,000 random numbers (0-1,999,999) in number_data.txt
    generate_random_numbers("number_data.txt", 2000000, 2000000);
    
    // Generate 2,000,000 random words (3-20 chars each) in word_data.txt
    generate_many_random_words("word_data.txt", 2000000, 20);
    
    return 0;
}
