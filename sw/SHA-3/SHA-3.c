#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define SHA3_L 6
#define SHA3_NR (12 + 2 * SHA3_L)
#define SHA3_B (25 << SHA3_L)
#define INPUT_SIZE 64  // 512 bits = 64 bytes
#define MAX_LINE_LENGTH 256
#define HEX_CHARS_PER_LINE 128  // 512 bits = 128 hex characters
#define MAX_LINES 10000  // Tăng từ 1000 lên 10000

char hex[] = "0123456789abcdef";

unsigned int sha3_rotConst[5][5] = {
    {0, 1, 190, 28, 91},
    {36, 300, 6, 55, 276},
    {3, 10, 171, 153, 231},
    {105, 45, 15, 21, 136},
    {210, 66, 253, 120, 78}};

unsigned long long sha3_roundConsts[SHA3_NR] = {
    0x0000000000000001,
    0x0000000000008082,
    0x800000000000808A,
    0x8000000080008000,
    0x000000000000808B,
    0x0000000080000001,
    0x8000000080008081,
    0x8000000000008009,
    0x000000000000008A,
    0x0000000000000088,
    0x0000000080008009,
    0x000000008000000A,
    0x000000008000808B,
    0x800000000000008B,
    0x8000000000008089,
    0x8000000000008003,
    0x8000000000008002,
    0x8000000000000080,
    0x000000000000800A,
    0x800000008000000A,
    0x8000000080008081,
    0x8000000000008080,
    0x0000000080000001,
    0x8000000080008008};

unsigned long long sha3_rotWord(unsigned long long w, unsigned int d)
{
    d = d & 0x3f; // d mod 64
    unsigned long long max = ~0L;

    unsigned long long wrapPortion = (max << (64 - d)) & w; // Get the d msb's
    unsigned long long shiftPortion = (max >> d) & w; // Get the (64 -d) lsb's

    // shift to put in place
    wrapPortion >>= 64 - d;
    shiftPortion <<= d;

    // return the addition
    return wrapPortion | shiftPortion;
}

void sha3_keccak_f(unsigned long long A[5][5])
{
    for (int i = 0; i < SHA3_NR; i++)
    {
        // THETA ===================
        unsigned long long C[5];
        unsigned long long D[5];

        // calculate C
        for (int x = 0; x < 5; x++)
        {
            C[x] = 0L;
            for (int y = 0; y < 5; y++)
            {
                C[x] ^= A[x][y];
            }
        }

        // calculate D
        for (int x = 0; x < 5; x++)
        {
            D[x] = C[(x + 4) % 5] ^ sha3_rotWord(C[(x + 1) % 5], 1);
        }

        // put result into A
        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 5; y++)
            {
                A[x][y] ^= D[x];
            }
        }

        // RHO, PI ===================
        unsigned long long B[5][5];
        memset(B, 0, 5 * 5 * sizeof(unsigned long long));

        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 5; y++)
            {
                B[y][(2 * x + 3 * y) % 5] = sha3_rotWord(A[x][y], sha3_rotConst[y][x]);
            }
        }

        // CHI ===================
        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 5; y++)
            {
                A[x][y] = B[x][y] ^ ((~B[(x + 1) % 5][y]) & B[(x + 2) % 5][y]);
            }
        }

        // IOTA ===================
        A[0][0] ^= sha3_roundConsts[i];
    }
}

int sha3_512_hash(unsigned char *in, unsigned char **out)
{
    // SHA3-512 parameters
    int r = 576 >> 3;  // 72 bytes (576 bits / 8)
    int ret_len = 64;  // 512 bits / 8 = 64 bytes

    // allocate output
    *out = (unsigned char *)malloc(ret_len * sizeof(unsigned char));

    // state variables
    unsigned long long A[5][5];
    memset(A, 0, 5 * 5 * sizeof(unsigned long long));

    int cursor = 0;           // cursor in the message
    int noBlocks = INPUT_SIZE / r + 1; // always pad

    // ABSORBING PHASE
    for (int i = 0; i < noBlocks; i++)
    {
        // Block variables
        int blockCursor = 0;                               // cursor in block
        int noBytesInBlock = fmin(r, fmax(INPUT_SIZE - cursor, 0)); // only take in between 0 and r bytes per block
        int noPadding = r - noBytesInBlock;                // number of bytes to padd to get complete block
        int padIdx = 0;                                    // current number of bytes already padded

        // XOR blocks into the state
        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
            {
                unsigned long long tmp = 0L;
                // write into tmp
                if (blockCursor < r) // have not written the complete block yet
                {
                    int noBytesInWord = fmin(8, fmax(noBytesInBlock - blockCursor, 0));
                    if (noBytesInWord)
                    {
                        // write byte from message
                        memcpy(&tmp, in + cursor + blockCursor, noBytesInWord);
                    }

                    // determine if need padding in this word
                    if (noBytesInWord != 8)
                    {
                        // must pad 01, then 1000*01
                        if (!padIdx)
                        {
                            // First padding byte, pad 01 instead of 06
                            tmp |= (unsigned long long)(0x01) << (noBytesInWord << 3); // noBytes to noBits
                        }
                        if (padIdx >= noPadding - 8)
                        {
                            // pad the last byte
                            tmp |= (unsigned long long)(0x01) << 0x3f; // 0b1000***0
                        }

                        // otherwise, leave as zeros
                        padIdx += 8 - noBytesInWord;
                    }
                }
                // xor tmp into the state
                A[x][y] ^= tmp;

                // advance block cursor
                blockCursor += 8;
            }
        }
        // advance message cursor
        cursor += noBytesInBlock;

        // Keccak-f
        sha3_keccak_f(A);
    }

    // SQUEEZING PHASE
    cursor = 0; // cursor for the output string

    while (cursor < ret_len)
    {
        // block variables
        int blockCursor = 0; // cursor in the block
        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
            {
                if (blockCursor < r && cursor + blockCursor < ret_len)
                {
                    // copy from state to the output
                    memcpy(*out + cursor + blockCursor, A[x] + y, sizeof(unsigned long long));

                    blockCursor += 8;
                }
                else
                {
                    break;
                }
            }
            if (blockCursor >= r || cursor + blockCursor >= ret_len)
            {
                // either completed block or the output
                break;
            }
        }
        cursor += r;
        sha3_keccak_f(A);
    }
    return ret_len;
}

// Function to print hex array to file
void printCharArrToFile(FILE *file, unsigned char *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        fprintf(file, "%c%c", hex[arr[i] >> 4], hex[arr[i] & 0x0f]);
    }
}

// Function to convert hex character to integer
int hexCharToInt(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1; // Invalid hex character
}

// Function to convert hex string to byte array
int hexStringToBytes(const char* hexStr, unsigned char* bytes, int maxBytes)
{
    int len = strlen(hexStr);
    int byteCount = 0;
    
    // Remove newline character if present
    if (len > 0 && (hexStr[len-1] == '\n' || hexStr[len-1] == '\r'))
        len--;
    
    // Each byte needs 2 hex characters
    if (len % 2 != 0) return -1; // Invalid hex string length
    
    for (int i = 0; i < len && byteCount < maxBytes; i += 2)
    {
        int high = hexCharToInt(hexStr[i]);
        int low = hexCharToInt(hexStr[i + 1]);
        
        if (high == -1 || low == -1) return -1; // Invalid hex character
        
        bytes[byteCount++] = (high << 4) | low;
    }
    
    return byteCount;
}

int main()
{
    printf("SHA3-512 Hash Calculator - Processing up to %d lines\n", MAX_LINES);
    printf("====================================================\n\n");

    // Open input file
    FILE *inputFile = fopen("data_in.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error: Cannot open data_in.txt file!\n");
        printf("Please make sure the file exists in the same directory.\n");
        getch();
        return 1;
    }

    // Open output file
    FILE *outputFile = fopen("data_out_sha3.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error: Cannot create data_out.txt file!\n");
        fclose(inputFile);
        getch();
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int successCount = 0;
    int errorCount = 0;
    unsigned char msg[INPUT_SIZE];
    unsigned char *hash = NULL;

    printf("Processing data from file...\n");
    printf("Progress: ");

    while (fgets(line, sizeof(line), inputFile) && lineNumber <= MAX_LINES)
    {
        // Skip empty lines
        if (strlen(line) <= 1) {
            lineNumber++;
            continue;
        }

        // Convert hex string to bytes
        int bytesRead = hexStringToBytes(line, msg, INPUT_SIZE);
        
        if (bytesRead != INPUT_SIZE)
        {
            printf("\nLine %d: Invalid data length (%d bytes, expected %d) - SKIPPED\n", 
                   lineNumber, bytesRead, INPUT_SIZE);
            errorCount++;
            lineNumber++;
            continue;
        }

        // Calculate SHA3-512 hash
        int len = sha3_512_hash(msg, &hash);

        // Show progress every 500 lines
        if (lineNumber % 500 == 0)
        {
            printf("%d ", lineNumber);
            fflush(stdout);
        }

        // Write only the hash result to output file (one line per hash)
        printCharArrToFile(outputFile, hash, len);
        fprintf(outputFile, "\n");

        // Free allocated memory
        free(hash);
        hash = NULL;
        
        successCount++;
        lineNumber++;
    }

    fclose(inputFile);
    fclose(outputFile);
    
    printf("\n\nProcessing completed!\n");
    printf("===================\n");
    printf("Total lines processed: %d\n", lineNumber - 1);
    printf("Successful hashes: %d\n", successCount);
    printf("Errors: %d\n", errorCount);
    printf("\nResults saved to data_out.txt\n");
    printf("Each line contains a 128-character SHA3-512 hash\n");
    printf("Press any key to exit...");
    getch();
    return 0;
}
