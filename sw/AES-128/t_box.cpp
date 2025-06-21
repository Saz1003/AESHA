// #include <stdio.h>
// #include <stdint.h>
// #include <iostream>

// // S-box đầy đủ 256 phần tử
// uint8_t S[] = {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
//                0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
//                0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
//                0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
//                0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
//                0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
//                0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
//                0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
//                0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
//                0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
//                0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
//                0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
//                0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
//                0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
//                0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
//                0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};

// // T-box 32-bit
// uint32_t T0[256];
// uint32_t T1[256]; 
// uint32_t T2[256];
// uint32_t T3[256];

// // Hàm nhân với 2 trong GF(2^8)
// uint8_t nhan2(uint8_t a) {
//     return (a << 1) ^ (((a >> 7) & 1) * 0x1B);
// }

// // Hàm nhân với 3 trong GF(2^8) 
// uint8_t nhan3(uint8_t a) {
//     return nhan2(a) ^ a;
// }

// // Khởi tạo T-box
// void initTBox() {
//     for(int i = 0; i < 256; i++) {
//         uint8_t s = S[i];
//         uint8_t s2 = nhan2(s);
//         uint8_t s3 = nhan3(s);
        
//         // T0: [02*S[i], 01*S[i], 01*S[i], 03*S[i]]
//         T0[i] = (s2 << 24) | (s << 16) | (s << 8) | s3;
        
//         // T1: [03*S[i], 02*S[i], 01*S[i], 01*S[i]] 
//         T1[i] = (s3 << 24) | (s2 << 16) | (s << 8) | s;
        
//         // T2: [01*S[i], 03*S[i], 02*S[i], 01*S[i]]
//         T2[i] = (s << 24) | (s3 << 16) | (s2 << 8) | s;
        
//         // T3: [01*S[i], 01*S[i], 03*S[i], 02*S[i]]
//         T3[i] = (s << 24) | (s << 16) | (s3 << 8) | s2;
//     }
// }

// // In T-box theo định dạng 16x16 vào file
// void printTBoxToFile() {
//     FILE* file = fopen("t_box.txt", "w");
//     if(!file) {
//         printf("Không thể tạo file t_box.txt\n");
//         return;
//     }
    
//     fprintf(file, "=== AES T-BOX TABLES (32-bit) ===\n");
//     fprintf(file, "Generated from S-box with multiplication coefficients\n");
//     fprintf(file, "Format: [MSB -> LSB] for each 32-bit entry\n\n");
    
//     // T0 Table
//     fprintf(file, "T0 Table - Coefficients: [02, 01, 01, 03]\n");
//     fprintf(file, "     ");
//     for(int j = 0; j < 16; j++) {
//         fprintf(file, "      %X      ", j);
//     }
//     fprintf(file, "\n");
    
//     for(int i = 0; i < 16; i++) {
//         fprintf(file, " %X:  ", i);
//         for(int j = 0; j < 16; j++) {
//             int index = i * 16 + j;
//             fprintf(file, "0x%08x ", T0[index]);
//         }
//         fprintf(file, "\n");
//     }
    
//     // T1 Table
//     fprintf(file, "\nT1 Table - Coefficients: [03, 02, 01, 01]\n");
//     fprintf(file, "     ");
//     for(int j = 0; j < 16; j++) {
//         fprintf(file, "      %X      ", j);
//     }
//     fprintf(file, "\n");
    
//     for(int i = 0; i < 16; i++) {
//         fprintf(file, " %X:  ", i);
//         for(int j = 0; j < 16; j++) {
//             int index = i * 16 + j;
//             fprintf(file, "0x%08x ", T1[index]);
//         }
//         fprintf(file, "\n");
//     }
    
//     // T2 Table
//     fprintf(file, "\nT2 Table - Coefficients: [01, 03, 02, 01]\n");
//     fprintf(file, "     ");
//     for(int j = 0; j < 16; j++) {
//         fprintf(file, "      %X      ", j);
//     }
//     fprintf(file, "\n");
    
//     for(int i = 0; i < 16; i++) {
//         fprintf(file, " %X:  ", i);
//         for(int j = 0; j < 16; j++) {
//             int index = i * 16 + j;
//             fprintf(file, "0x%08x ", T2[index]);
//         }
//         fprintf(file, "\n");
//     }
    
//     // T3 Table
//     fprintf(file, "\nT3 Table - Coefficients: [01, 01, 03, 02]\n");
//     fprintf(file, "     ");
//     for(int j = 0; j < 16; j++) {
//         fprintf(file, "      %X      ", j);
//     }
//     fprintf(file, "\n");
    
//     for(int i = 0; i < 16; i++) {
//         fprintf(file, " %X:  ", i);
//         for(int j = 0; j < 16; j++) {
//             int index = i * 16 + j;
//             fprintf(file, "0x%08x ", T3[index]);
//         }
//         fprintf(file, "\n");
//     }
    
//     // Thêm thông tin chi tiết
//     fprintf(file, "\n=== DETAILED EXPLANATION ===\n");
//     fprintf(file, "Each T-box entry is a 32-bit word calculated as follows:\n");
//     fprintf(file, "T0[i] = [02*S[i], 01*S[i], 01*S[i], 03*S[i]]\n");
//     fprintf(file, "T1[i] = [03*S[i], 02*S[i], 01*S[i], 01*S[i]]\n");
//     fprintf(file, "T2[i] = [01*S[i], 03*S[i], 02*S[i], 01*S[i]]\n");
//     fprintf(file, "T3[i] = [01*S[i], 01*S[i], 03*S[i], 02*S[i]]\n\n");
    
//     fprintf(file, "Where:\n");
//     fprintf(file, "- S[i] is the AES S-box value at index i\n");
//     fprintf(file, "- Multiplication is performed in GF(2^8) with irreducible polynomial x^8 + x^4 + x^3 + x + 1\n");
//     fprintf(file, "- 02*x = (x << 1) XOR (0x1B if x >= 0x80)\n");
//     fprintf(file, "- 03*x = 02*x XOR x\n\n");
    
//     // Ví dụ chi tiết
//     fprintf(file, "=== EXAMPLES ===\n");
//     for(int i = 0; i < 5; i++) {
//         uint8_t s = S[i];
//         uint8_t s2 = nhan2(s);
//         uint8_t s3 = nhan3(s);
        
//         fprintf(file, "Index 0x%02X: S[0x%02X] = 0x%02X\n", i, i, s);
//         fprintf(file, "  02 * 0x%02X = 0x%02X\n", s, s2);
//         fprintf(file, "  03 * 0x%02X = 0x%02X\n", s, s3);
//         fprintf(file, "  T0[0x%02X] = 0x%08x = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n", 
//                 i, T0[i], s2, s, s, s3);
//         fprintf(file, "  T1[0x%02X] = 0x%08x = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n", 
//                 i, T1[i], s3, s2, s, s);
//         fprintf(file, "  T2[0x%02X] = 0x%08x = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n", 
//                 i, T2[i], s, s3, s2, s);
//         fprintf(file, "  T3[0x%02X] = 0x%08x = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n\n", 
//                 i, T3[i], s, s, s3, s2);
//     }
    
//     fclose(file);
//     printf("T-box đã được lưu vào file t_box.txt thành công!\n");
// }

// // In T-box lên console (rút gọn)
// void printTBoxToConsole() {
//     printf("=== AES T-BOX PREVIEW ===\n");
//     printf("T0 Table (first 3 rows):\n");
//     printf("     ");
//     for(int j = 0; j < 16; j++) {
//         printf("      %X      ", j);
//     }
//     printf("\n");
    
//     for(int i = 0; i < 3; i++) {
//         printf(" %X:  ", i);
//         for(int j = 0; j < 16; j++) {
//             int index = i * 16 + j;
//             printf("0x%08x ", T0[index]);
//         }
//         printf("\n");
//     }
//     printf("... (see t_box.txt for complete tables)\n\n");
// }

// int main(){
//     printf("=== AES T-Box Generator ===\n");
//     printf("Generating T-boxes from S-box...\n\n");
    
//     // Khởi tạo T-box
//     initTBox();
    
//     // Hiển thị một số giá trị mẫu
//     printf("Sample calculations:\n");
//     for(int i = 0; i < 3; i++) {
//         uint8_t s = S[i];
//         printf("S[0x%02X] = 0x%02X -> ", i, s);
//         printf("02*S = 0x%02X, 03*S = 0x%02X -> ", nhan2(s), nhan3(s));
//         printf("T0[0x%02X] = 0x%08x\n", i, T0[i]);
//     }
//     printf("\n");
    
//     // In preview lên console
//     printTBoxToConsole();
    
//     // Lưu toàn bộ vào file
//     printTBoxToFile();
    
//     printf("File t_box.txt chứa:\n");
//     printf("- 4 bảng T-box đầy đủ (T0, T1, T2, T3)\n");
//     printf("- Định dạng 16x16 như S-box\n");
//     printf("- Giải thích chi tiết và ví dụ\n");
//     printf("- Tổng cộng 1024 entries (256 x 4 tables)\n\n");
    
//     system("pause");
//     return 0;
// }

#include <stdio.h>
#include <stdint.h>
#include <iostream>

// S-box nghịch đảo đầy đủ 256 phần tử
uint8_t InvS[] = {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
                  0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
                  0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
                  0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
                  0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
                  0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
                  0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
                  0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
                  0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
                  0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
                  0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
                  0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
                  0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
                  0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
                  0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
                  0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D};

// T-box nghịch đảo 32-bit
uint32_t InvT0[256];
uint32_t InvT1[256]; 
uint32_t InvT2[256];
uint32_t InvT3[256];

// Hàm nhân trong GF(2^8) - tổng quát
uint8_t gf_mul(uint8_t a, uint8_t b) {
    uint8_t result = 0;
    uint8_t hi_bit_set;
    
    for (int i = 0; i < 8; i++) {
        if ((b & 1) == 1) {
            result ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80) {
            a ^= 0x1B; // x^8 + x^4 + x^3 + x + 1
        }
        b >>= 1;
    }
    return result;
}

// Các hàm nhân cụ thể cho InvMixColumns
uint8_t nhan0E(uint8_t a) { return gf_mul(a, 0x0E); }
uint8_t nhan09(uint8_t a) { return gf_mul(a, 0x09); }
uint8_t nhan0D(uint8_t a) { return gf_mul(a, 0x0D); }
uint8_t nhan0B(uint8_t a) { return gf_mul(a, 0x0B); }

// Khởi tạo Inverse T-box
void initInvTBox() {
    for(int i = 0; i < 256; i++) {
        uint8_t s = InvS[i];
        uint8_t s0E = nhan0E(s);
        uint8_t s09 = nhan09(s);
        uint8_t s0D = nhan0D(s);
        uint8_t s0B = nhan0B(s);
        
        // InvT0: [0E*InvS[i], 09*InvS[i], 0D*InvS[i], 0B*InvS[i]]
        InvT0[i] = (s0E << 24) | (s09 << 16) | (s0D << 8) | s0B;
        
        // InvT1: [0B*InvS[i], 0E*InvS[i], 09*InvS[i], 0D*InvS[i]] (xoay trái 1 byte)
        InvT1[i] = (s0B << 24) | (s0E << 16) | (s09 << 8) | s0D;
        
        // InvT2: [0D*InvS[i], 0B*InvS[i], 0E*InvS[i], 09*InvS[i]] (xoay trái 2 byte)
        InvT2[i] = (s0D << 24) | (s0B << 16) | (s0E << 8) | s09;
        
        // InvT3: [09*InvS[i], 0D*InvS[i], 0B*InvS[i], 0E*InvS[i]] (xoay trái 3 byte)
        InvT3[i] = (s09 << 24) | (s0D << 16) | (s0B << 8) | s0E;
    }
}

// In Inverse T-box theo định dạng 16x16 vào file
void printInvTBoxToFile() {
    FILE* file = fopen("inv_t_box.txt", "w");
    if(!file) {
        printf("Không thể tạo file inv_t_box.txt\n");
        return;
    }
    
    fprintf(file, "=== AES INVERSE T-BOX TABLES (32-bit) ===\n");
    fprintf(file, "Generated from Inverse S-box with multiplication coefficients\n");
    fprintf(file, "InvMixColumns matrix: [0E 0B 0D 09]\n");
    fprintf(file, "                      [09 0E 0B 0D]\n");
    fprintf(file, "                      [0D 09 0E 0B]\n");
    fprintf(file, "                      [0B 0D 09 0E]\n");
    fprintf(file, "Format: [MSB -> LSB] for each 32-bit entry\n\n");
    
    // InvT0 Table
    fprintf(file, "InvT0 Table - Coefficients: [0E, 09, 0D, 0B]\n");
    fprintf(file, "     ");
    for(int j = 0; j < 16; j++) {
        fprintf(file, "      %X      ", j);
    }
    fprintf(file, "\n");
    
    for(int i = 0; i < 16; i++) {
        fprintf(file, " %X:  ", i);
        for(int j = 0; j < 16; j++) {
            int index = i * 16 + j;
            fprintf(file, "0x%08X ", InvT0[index]);
        }
        fprintf(file, "\n");
    }
    
    // InvT1 Table
    fprintf(file, "\nInvT1 Table - Coefficients: [0B, 0E, 09, 0D]\n");
    fprintf(file, "     ");
    for(int j = 0; j < 16; j++) {
        fprintf(file, "      %X      ", j);
    }
    fprintf(file, "\n");
    
    for(int i = 0; i < 16; i++) {
        fprintf(file, " %X:  ", i);
        for(int j = 0; j < 16; j++) {
            int index = i * 16 + j;
            fprintf(file, "0x%08X ", InvT1[index]);
        }
        fprintf(file, "\n");
    }
    
    // InvT2 Table
    fprintf(file, "\nInvT2 Table - Coefficients: [0D, 0B, 0E, 09]\n");
    fprintf(file, "     ");
    for(int j = 0; j < 16; j++) {
        fprintf(file, "      %X      ", j);
    }
    fprintf(file, "\n");
    
    for(int i = 0; i < 16; i++) {
        fprintf(file, " %X:  ", i);
        for(int j = 0; j < 16; j++) {
            int index = i * 16 + j;
            fprintf(file, "0x%08X ", InvT2[index]);
        }
        fprintf(file, "\n");
    }
    
    // InvT3 Table
    fprintf(file, "\nInvT3 Table - Coefficients: [09, 0D, 0B, 0E]\n");
    fprintf(file, "     ");
    for(int j = 0; j < 16; j++) {
        fprintf(file, "      %X      ", j);
    }
    fprintf(file, "\n");
    
    for(int i = 0; i < 16; i++) {
        fprintf(file, " %X:  ", i);
        for(int j = 0; j < 16; j++) {
            int index = i * 16 + j;
            fprintf(file, "0x%08X ", InvT3[index]);
        }
        fprintf(file, "\n");
    }
    
    // Thêm thông tin chi tiết
    fprintf(file, "\n=== DETAILED EXPLANATION ===\n");
    fprintf(file, "Each Inverse T-box entry is a 32-bit word calculated as follows:\n");
    fprintf(file, "InvT0[i] = [0E*InvS[i], 09*InvS[i], 0D*InvS[i], 0B*InvS[i]]\n");
    fprintf(file, "InvT1[i] = [0B*InvS[i], 0E*InvS[i], 09*InvS[i], 0D*InvS[i]]\n");
    fprintf(file, "InvT2[i] = [0D*InvS[i], 0B*InvS[i], 0E*InvS[i], 09*InvS[i]]\n");
    fprintf(file, "InvT3[i] = [09*InvS[i], 0D*InvS[i], 0B*InvS[i], 0E*InvS[i]]\n\n");
    
    fprintf(file, "Where:\n");
    fprintf(file, "- InvS[i] is the AES Inverse S-box value at index i\n");
    fprintf(file, "- Multiplication is performed in GF(2^8) with irreducible polynomial x^8 + x^4 + x^3 + x + 1\n");
    fprintf(file, "- These coefficients are used in the InvMixColumns transformation\n\n");
    
    // Ví dụ chi tiết
    fprintf(file, "=== EXAMPLES ===\n");
    for(int i = 0; i < 5; i++) {
        uint8_t s = InvS[i];
        uint8_t s0E = nhan0E(s);
        uint8_t s09 = nhan09(s);
        uint8_t s0D = nhan0D(s);
        uint8_t s0B = nhan0B(s);
        
        fprintf(file, "Index 0x%02X: InvS[0x%02X] = 0x%02X\n", i, i, s);
        fprintf(file, "  0E * 0x%02X = 0x%02X\n", s, s0E);
        fprintf(file, "  09 * 0x%02X = 0x%02X\n", s, s09);
        fprintf(file, "  0D * 0x%02X = 0x%02X\n", s, s0D);
        fprintf(file, "  0B * 0x%02X = 0x%02X\n", s, s0B);
        fprintf(file, "  InvT0[0x%02X] = 0x%08X = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n", 
                i, InvT0[i], s0E, s09, s0D, s0B);
        fprintf(file, "  InvT1[0x%02X] = 0x%08X = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n", 
                i, InvT1[i], s0B, s0E, s09, s0D);
        fprintf(file, "  InvT2[0x%02X] = 0x%08X = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n", 
                i, InvT2[i], s0D, s0B, s0E, s09);
        fprintf(file, "  InvT3[0x%02X] = 0x%08X = [0x%02X, 0x%02X, 0x%02X, 0x%02X]\n\n", 
                i, InvT3[i], s09, s0D, s0B, s0E);
    }
    
    // Bảng tra cứu GF multiplication
    fprintf(file, "=== GF(2^8) MULTIPLICATION TABLE (Sample) ===\n");
    fprintf(file, "x    | 0E*x | 09*x | 0D*x | 0B*x\n");
    fprintf(file, "-----|------|------|------|------\n");
    for(int i = 0; i < 16; i++) {
        fprintf(file, "0x%02X | 0x%02X | 0x%02X | 0x%02X | 0x%02X\n", 
                i, nhan0E(i), nhan09(i), nhan0D(i), nhan0B(i));
    }
    
    fclose(file);
    printf("Inverse T-box đã được lưu vào file inv_t_box.txt thành công!\n");
}

// In Inverse T-box lên console (rút gọn)
void printInvTBoxToConsole() {
    printf("=== AES INVERSE T-BOX PREVIEW ===\n");
    printf("InvT0 Table (first 3 rows) - Coefficients [0E, 09, 0D, 0B]:\n");
    printf("     ");
    for(int j = 0; j < 16; j++) {
        printf("      %X      ", j);
    }
    printf("\n");
    
    for(int i = 0; i < 3; i++) {
        printf(" %X:  ", i);
        for(int j = 0; j < 16; j++) {
            int index = i * 16 + j;
            printf("0x%08X ", InvT0[index]);
        }
        printf("\n");
    }
    printf("... (see inv_t_box.txt for complete tables)\n\n");
}

// Demo sử dụng Inverse T-box trong InvMixColumns
uint32_t invMixColumnsWord(uint32_t word) {
    uint8_t a0 = (word >> 24) & 0xFF;
    uint8_t a1 = (word >> 16) & 0xFF;
    uint8_t a2 = (word >> 8) & 0xFF;
    uint8_t a3 = word & 0xFF;
    
    // Sử dụng Inverse T-box
    return InvT0[a0] ^ InvT1[a1] ^ InvT2[a2] ^ InvT3[a3];
}

int main(){
    printf("=== AES Inverse T-Box Generator ===\n");
    printf("Generating Inverse T-boxes from Inverse S-box...\n");
    printf("Coefficients: 0E, 09, 0D, 0B (InvMixColumns)\n\n");
    
    // Khởi tạo Inverse T-box
    initInvTBox();
    
    // Hiển thị một số giá trị mẫu
    printf("Sample calculations:\n");
    for(int i = 0; i < 3; i++) {
        uint8_t s = InvS[i];
        printf("InvS[0x%02X] = 0x%02X -> ", i, s);
        printf("0E*InvS = 0x%02X, 09*InvS = 0x%02X, 0D*InvS = 0x%02X, 0B*InvS = 0x%02X\n", 
               nhan0E(s), nhan09(s), nhan0D(s), nhan0B(s));
        printf("InvT0[0x%02X] = 0x%08X\n\n", i, InvT0[i]);
    }
    
    // In preview lên console
    printInvTBoxToConsole();
    
    // Test InvMixColumns với Inverse T-box
    uint32_t testWord = 0x8A84EB01; // Ví dụ
    printf("Test InvMixColumns:\n");
    printf("Input:  0x%08X\n", testWord);
    printf("Output: 0x%08X\n\n", invMixColumnsWord(testWord));
    
    // Lưu toàn bộ vào file
    printInvTBoxToFile();
    
    printf("File inv_t_box.txt chứa:\n");
    printf("- 4 bảng Inverse T-box đầy đủ (InvT0, InvT1, InvT2, InvT3)\n");
    printf("- Định dạng 16x16 như S-box\n");
    printf("- Hệ số nhân: 0E, 09, 0D, 0B\n");
    printf("- Giải thích chi tiết và ví dụ\n");
    printf("- Bảng tra cứu GF multiplication\n");
    printf("- Tổng cộng 1024 entries (256 x 4 tables)\n\n");
    
    system("pause");
    return 0;
}
