`ifndef N_SV
`define N_SV

module n (
    input  wire  [31:0] A_in      [0:3][0:4],
    input  wire  [31:0] i_K_col_5 [0:4],
    output logic [31:0] C         [0:3],
    output logic [31:0] C_5
);

    xor_32_bits xor1(.i_data(A_in[0]),    .o_data(C[0]));
    xor_32_bits xor2(.i_data(A_in[1]),    .o_data(C[1]));
    xor_32_bits xor3(.i_data(A_in[2]),    .o_data(C[2]));
    xor_32_bits xor4(.i_data(A_in[3]),    .o_data(C[3]));
    xor_32_bits xor5(.i_data(i_K_col_5),  .o_data(C_5));

endmodule

`endif // N_SV