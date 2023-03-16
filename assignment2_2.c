#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constant for the maximum length of each line of input
#define MAX_LINE_LEN 100

// Constant for the maximum length of each word
#define MAX_WORD_LEN 30

// Structure to store a word and its count
typedef struct WordCount
{
    char *word;
    int count;
} WordCount;

// Compare function for use with qsort
int cmpFunc(const void *a, const void *b)
{
    // Convert the void pointers to WordCount pointers
    const WordCount *wordCountA = (WordCount *)a;
    const WordCount *wordCountB = (WordCount *)b;

    // Use strcmp to compare the words stored in the WordCount structures
    return strcmp(wordCountA->word, wordCountB->word);
}

int main()
{
    // Allocate memory for the word count array
    WordCount *wordArray = (WordCount *)malloc(sizeof(WordCount));

    // Initialize the size of the word count array
    int arraySize = 1;

    // Initialize the number of words in the word count array
    int numWords = 0;

    // Read input line by line
    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, stdin))
    {
        // Parse words from the line
        char *currWord = strtok(line, " .,\n");
        while (currWord != NULL)
        {
            // Convert word to lowercase
            for (int i = 0; i < strlen(currWord); i++)
            {
                currWord[i] = tolower(currWord[i]);
            }

            // Remove non-alphabetic characters from the word
            int newLen = 0;
            for (int i = 0; i < strlen(currWord); i++)
            {
                if (isalpha(currWord[i]))
                {
                    currWord[newLen++] = currWord[i];
                }
            }
            currWord[newLen] = '\0';
            // If the word is not empty, add it to the word count array
            if (strlen(currWord) > 0)
            {
                int found = 0;
                for (int i = 0; i < numWords; i++)
                {
                    // If the word already exists in the array, increment its count
                    if (strcmp(wordArray[i].word, currWord) == 0)
                    {
                        wordArray[i].count++;
                        found = 1;
                        break;
                    }
                }
                // If the word does not exist in the array, add it
                if (!found)
                {
                    if (numWords == arraySize)
                    {
                        arraySize *= 2;
                        wordArray = (WordCount *)realloc(wordArray, arraySize * sizeof(WordCount));
                    }
                    wordArray[numWords].word = strdup(currWord);
                    wordArray[numWords].count = 1;
                    numWords++;
                }
            }
            currWord = strtok(NULL, " .,\n");
        }
    }

    // Sort the word count array alphabetically
    qsort(wordArray, numWords, sizeof(WordCount), cmpFunc);

    // Print the words and their counts
    for (int i = 0; i < numWords; i++)
    {
        printf("%s => %d\n", wordArray[i].word, wordArray[i].count);
    }

    // Free memory from the array of words
    for (int i = 0; i < numWords; i++)
    {
        free(wordArray[i].word);
    }
    free(wordArray);

    return 0;
}