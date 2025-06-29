#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void Showword(unsigned int w){
    for (int i = 1; i <= 8; i++){
        unsigned int hex = (w >> 32 - 4*i) & 0xF;
        printf("%x", hex);
    }
}

unsigned int RotWord(unsigned int w){
    unsigned int temp1 = (w >> 24) & 0xFF;
    unsigned int temp234 = w & 0xFFFFFF;
    unsigned int rot = (temp234 << 8) | temp1;
    return rot;
}

unsigned int SubWord(unsigned int w){
    int S[] = {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 
               0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 
               0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15, 
               0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, 
               0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84, 
               0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF, 
               0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8, 
               0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 
               0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, 
               0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, 
               0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79, 
               0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08, 
               0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, 
               0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 
               0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, 
               0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16};
    
    unsigned int result = 0;
    for(int i = 1; i <= 4; i++){
        unsigned int byte = (w >> (32 - i*8)) & 0xFF;
        unsigned int subbyte = S[byte];
        result = (result << 8) | subbyte;
    }
    return result;
}

unsigned int XORRcon(unsigned int w, int j){
    int Rc[] = {
        0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
        0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39
    };
    unsigned int temp1 = (w >> 24) & 0xFF;
    unsigned int resultXOR = (temp1 ^ Rc[j]) & 0xFF;
    unsigned int temp234 = w & 0xFFFFFF;
    unsigned int result = (resultXOR << 24) | temp234;
    return result;
}

unsigned int G(unsigned int w, int j){
    unsigned int rot = RotWord(w);
    unsigned int sub = SubWord(rot);
    unsigned int result = XORRcon(sub, j);
    return result;
}

unsigned int* KeyExpansion(unsigned int key[4]){
    unsigned int *w = new unsigned int[44];
    w[0] = key[0];
    w[1] = key[1];
    w[2] = key[2];
    w[3] = key[3];
    for(int i = 4; i < 44; i++){
        if(i % 4 == 0){
            w[i] = G(w[i-1], i/4) ^ w[i - 4];
        } else {
            w[i] = w[i-1] ^ w[i-4];
        }
    }
    return w;
}

unsigned int* AddRoundKey(unsigned int state[4], unsigned int *K){
    unsigned int *result = new unsigned int[4];
    result[0] = state[0] ^ K[0];
    result[1] = state[1] ^ K[1];
    result[2] = state[2] ^ K[2];
    result[3] = state[3] ^ K[3];
    return result;
}

unsigned int* SubBytes(unsigned int state[4]){
    unsigned int *result = new unsigned int[4];
    for(int i = 0; i < 4; i++){
        result[i] = SubWord(state[i]);
    }
    return result;
} 

unsigned int* ShiftRows(unsigned int state[4]){
    unsigned int *result = new unsigned int[4];
    for(int i = 0; i < 4; i++){
        unsigned int temp1 = state[i] & 0xFF000000;
        unsigned int temp2 = state[(i + 1) % 4] & 0xFF0000;
        unsigned int temp3 = state[(i + 2) % 4] & 0xFF00;
        unsigned int temp4 = state[(i + 3) % 4] & 0xFF;
        result[i] = temp1 | temp2 | temp3 | temp4;
    }
    return result;
}

// Sửa lỗi hàm Nhan2
unsigned int Nhan2(unsigned int w){
    unsigned int result = w << 1;
    if(result >= 256){
        result = result ^ 0x1b;  // Sửa từ 0x11b thành 0x1b
    } 
    result = result & 0xFF;
    return result;
}

unsigned int Nhan3(unsigned int w){
    unsigned int result = w ^ Nhan2(w);
    result = result & 0xFF;
    return result;
}

unsigned int NhanCot(unsigned int w){
    unsigned int result;
    unsigned int temp1 = (w >> 24) & 0xFF;
    unsigned int temp2 = (w >> 16) & 0xFF;
    unsigned int temp3 = (w >> 8) & 0xFF;
    unsigned int temp4 = w & 0xFF;
    
    unsigned int resulttemp1 = Nhan2(temp1) ^ Nhan3(temp2) ^ temp3 ^ temp4; 
    unsigned int resulttemp2 = temp1 ^ Nhan2(temp2) ^ Nhan3(temp3) ^ temp4;
    unsigned int resulttemp3 = temp1 ^ temp2 ^ Nhan2(temp3) ^ Nhan3(temp4);
    unsigned int resulttemp4 = Nhan3(temp1) ^ temp2 ^ temp3 ^ Nhan2(temp4);
    
    result = (resulttemp1 << 24) | (resulttemp2 << 16) | (resulttemp3 << 8) | resulttemp4;
    return result;
}

unsigned int* MixColumns(unsigned int state[4]){
    unsigned int *result = new unsigned int[4];
    for(int i = 0; i < 4; i++){
        result[i] = NhanCot(state[i]);
    }
    return result;
}

void showmatrix(unsigned int w[4]){
    for(int i = 0; i < 4; i++){
        printf("\n\t");
        Showword(w[i]);
    }
}

unsigned int* InvShiftRows(unsigned int state[4]){
    unsigned int *result = new unsigned int[4];
    for(int i = 0; i < 4; i++){
        unsigned int temp1 = state[i] & 0xFF000000;
        unsigned int temp2 = state[(i + 3) % 4] & 0xFF0000;
        unsigned int temp3 = state[(i + 2) % 4] & 0xFF00;
        unsigned int temp4 = state[(i + 1) % 4] & 0xFF;
        result[i] = temp1 | temp2 | temp3 | temp4;
    }
    return result;
}

unsigned int InvSubWord(unsigned int w){
    int InvS[] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };
    
    unsigned int result = 0;
    for(int i = 1; i <= 4; i++){
        unsigned int byte = (w >> (32 - i*8)) & 0xFF;
        unsigned int subbyte = InvS[byte];
        result = (result << 8) | subbyte;
    }
    return result;
}

unsigned int* InvSubBytes(unsigned int state[4]){
    unsigned int *result = new unsigned int[4];
    for (int i = 0; i < 4; i++){
        result[i] = InvSubWord(state[i]);
    }
    return result;
}

// Sửa lại các hàm nhân GF(2^8) cho InvMixColumns
unsigned int gf_mul(unsigned int a, unsigned int b) {
    unsigned int result = 0;
    unsigned int hi_bit_set;
    
    for (int i = 0; i < 8; i++) {
        if ((b & 1) == 1) {
            result ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80) {
            a ^= 0x1B;
        }
        b >>= 1;
    }
    return result & 0xFF;
}

unsigned int Nhan9(unsigned int w){
    return gf_mul(w, 0x09);
}

unsigned int NhanB(unsigned int w){
    return gf_mul(w, 0x0B);
}

unsigned int NhanD(unsigned int w){
    return gf_mul(w, 0x0D);
}

unsigned int NhanE(unsigned int w){
    return gf_mul(w, 0x0E);
}

unsigned int InvNhanCot(unsigned int w){
    unsigned int result;
    unsigned int temp1 = (w >> 24) & 0xFF;
    unsigned int temp2 = (w >> 16) & 0xFF;
    unsigned int temp3 = (w >> 8) & 0xFF;
    unsigned int temp4 = w & 0xFF;
    
    unsigned int resulttemp1 = NhanE(temp1) ^ NhanB(temp2) ^ NhanD(temp3) ^ Nhan9(temp4);
    unsigned int resulttemp2 = Nhan9(temp1) ^ NhanE(temp2) ^ NhanB(temp3) ^ NhanD(temp4);
    unsigned int resulttemp3 = NhanD(temp1) ^ Nhan9(temp2) ^ NhanE(temp3) ^ NhanB(temp4);
    unsigned int resulttemp4 = NhanB(temp1) ^ NhanD(temp2) ^ Nhan9(temp3) ^ NhanE(temp4);
    
    result = (resulttemp1 << 24) | (resulttemp2 << 16) | (resulttemp3 << 8) | resulttemp4;
    return result;
}

unsigned int* InvMixColumns(unsigned int state[4]){
    unsigned int *result = new unsigned int[4];
    for(int i = 0; i < 4; i++){
        result[i] = InvNhanCot(state[i]);
    }
    return result;
}

unsigned int* MahoaAES(unsigned int state[4], unsigned int Key[4]){
    unsigned int *w = KeyExpansion(Key);
    
    state = AddRoundKey(state, &w[0]);
    for(int i = 1; i <= 9; i++){
        state = SubBytes(state);
        state = ShiftRows(state);
        state = MixColumns(state);
        state = AddRoundKey(state, &w[4*i]);
    }

    state = SubBytes(state);
    state = ShiftRows(state);
    state = AddRoundKey(state, &w[40]);
    
    delete[] w;
    return state;
}

unsigned int* GiaimaAES(unsigned int C[4], unsigned int Key[4]){
    unsigned int *w = KeyExpansion(Key);
    
    unsigned int *state = AddRoundKey(C, &w[40]);
    for(int i = 1; i <= 9; i++){
        state = InvShiftRows(state);
        state = InvSubBytes(state);
        state = AddRoundKey(state, &w[40 - 4*i]);
        state = InvMixColumns(state);
    }
    
    state = InvShiftRows(state);
    state = InvSubBytes(state);
    state = AddRoundKey(state, &w[0]); 
    
    delete[] w;
    return state;
}

int main(){
    srand((unsigned int)time(NULL));

    FILE *fkey = fopen("key_in.txt", "r");
    if (fkey == NULL) {
        perror("Không thể mở file key_in.txt");
        return 1;
    }

    FILE *fin = fopen("data_in.txt", "r");
    if (fin == NULL) {
        perror("Không thể mở file data_in.txt");
        fclose(fkey);
        return 1;
    }
    
    FILE *fenc = fopen("outenc.txt", "w");
    if (fenc == NULL) {
        perror("Không thể mở file outenc.txt");
        fclose(fkey);
        fclose(fin);
        return 1;
    }
    
    FILE *fdec = fopen("outdec.txt", "w");
    if (fdec == NULL) {
        perror("Không thể mở file outdec.txt");
        fclose(fkey);
        fclose(fin);
        fclose(fenc);
        return 1;
    }

    char hexkey[64];  // Tăng buffer size để an toàn
    char hexblock[256]; // Tăng buffer size để an toàn

    printf("Đang xử lý 10000 dòng dữ liệu...\n");

    for (int i = 1; i <= 10000; i++) {
        // Hiển thị tiến trình
        if (i % 1000 == 0) {
            printf("Đã xử lý: %d/10000 dòng\n", i);
        }

        // Đọc key
        if (fgets(hexkey, sizeof(hexkey), fkey) == NULL) {
            fprintf(stderr, "Không đủ key trong file key_in.txt tại dòng %d\n", i);
            break;
        }

        // Loại bỏ ký tự newline
        hexkey[strcspn(hexkey, "\r\n")] = 0;

        // Parse key
        unsigned int w0, w1, w2, w3;
        if (sscanf(hexkey, "%8x%8x%8x%8x", &w0, &w1, &w2, &w3) != 4) {
            fprintf(stderr, "Lỗi parse key tại dòng %d: %s\n", i, hexkey);
            continue;
        }
        unsigned int Key[] = {w0, w1, w2, w3};

        // Đọc input block
        if (!fgets(hexblock, sizeof(hexblock), fin)) {
            fprintf(stderr, "Không đủ input trong file data_in.txt tại dòng %d\n", i);
            break;
        }

        // Loại bỏ ký tự newline
        hexblock[strcspn(hexblock, "\r\n")] = 0;

        // Kiểm tra độ dài dữ liệu (phải có ít nhất 128 ký tự hex cho 4 block)
        if (strlen(hexblock) < 128) {
            fprintf(stderr, "Dữ liệu không đủ tại dòng %d: %s\n", i, hexblock);
            continue;
        }

        // Xử lý 4 block 128-bit từ 1 dòng 512-bit
        for(int j = 0; j < 4; j++){
            unsigned int state[4];
            char subblock[33] = {0};

            // Lấy 32 ký tự hex (128 bit)
            strncpy(subblock, hexblock + j * 32, 32);
            subblock[32] = '\0';

            // Parse hex string thành 4 words
            if (sscanf(subblock, "%8x%8x%8x%8x", &state[0], &state[1], &state[2], &state[3]) != 4) {
                fprintf(stderr, "Lỗi parse data tại dòng %d, block %d: %s\n", i, j, subblock);
                continue;
            }

            // Mã hóa
            unsigned int *C = MahoaAES(state, Key);
            
            // Ghi kết quả mã hóa với %08x
            for (int k = 0; k < 4; k++) {
                fprintf(fenc, "%08x", C[k]);
            }

            // Giải mã từ kết quả mã hóa
            unsigned int *M = GiaimaAES(C, Key);
            
            // Ghi kết quả giải mã với %08x
            for (int k = 0; k < 4; k++) {
                fprintf(fdec, "%08x", M[k]);
            }

            // Giải phóng bộ nhớ
            delete[] C;
            delete[] M;
        }
        
        // Xuống dòng sau mỗi dòng dữ liệu
        fprintf(fenc, "\n");
        fprintf(fdec, "\n");
        
        // Flush để đảm bảo dữ liệu được ghi ngay
        fflush(fenc);
        fflush(fdec);
    }
    
    fclose(fkey);
    fclose(fin);
    fclose(fenc);
    fclose(fdec);
    
    printf("Hoàn thành! Đã xử lý xong 10000 dòng.\n");
    printf("Kết quả được lưu trong outenc.txt và outdec.txt\n");
    
    system("pause");
    return 0;
}
