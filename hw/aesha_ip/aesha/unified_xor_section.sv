`ifndef UNIFIED_XOR_SECTION_SV
`define UNIFIED_XOR_SECTION_SV

module unified_xor_section(input  logic        i_aes_or_keccak,
                           input  wire  [31:0] i_A_1_state     [0:3][0:4],
                           input  wire  [31:0] i_A_2_state     [0:3][0:4],
                           input  wire  [31:0] i_K_state       [0:4][0:4],
                           input  wire  [31:0] i_C_shifted     [0:4],
                           output logic [31:0] o_C             [0:4],
                           output logic [63:0] o_A_state       [0:3],
                           output logic [31:0] D               [0:4]
                           );


logic [31:0] C          [0:4];
logic [31:0] o_data     [0:4];
logic [31:0] A_in_n_1   [0:3][0:4];
logic [31:0] A_in_n_2   [0:3][0:4];
logic [31:0] A_in_n_mid [0:4][0:4];

assign A_in_n_1 = (i_aes_or_keccak) ? i_A_1_state : i_K_state[0:3];

n n1(.A_in(A_in_n_1), .i_K_col_5(i_K_state[4]), .C(C[0:3]), .C_5(C[4]));

assign o_C[0] = C[0];
assign o_C[1] = C[1];
assign o_C[2] = C[2];
assign o_C[3] = C[3];
assign o_C[4] = C[4];

xor_padding xpad(.i_data(C[0:3]), .i_K_col_5(C[4]), .i_C_shifted(i_C_shifted), .o_data(A_in_n_mid[0:3]), .o_K_col_5(A_in_n_mid[4]));

assign A_in_n_2 = (i_aes_or_keccak) ? i_A_2_state : A_in_n_mid[0:3];

n n2(.A_in(A_in_n_2), .i_K_col_5(A_in_n_mid[4]), .C(o_data[0:3]), .C_5(o_data[4]));

   assign o_A_state[3] = (i_aes_or_keccak) ? {C[2]     , C[3]     } : 64'h0;
   assign o_A_state[2] = (i_aes_or_keccak) ? {C[0]     , C[1]     } : 64'h0;
   assign o_A_state[1] = (i_aes_or_keccak) ? {o_data[2], o_data[3]} : 64'h0;
   assign o_A_state[0] = (i_aes_or_keccak) ? {o_data[0], o_data[1]} : 64'h0;

   assign D[0] = (!i_aes_or_keccak) ? o_data[4] : 32'b0;
   assign D[1] = (!i_aes_or_keccak) ? o_data[0] : 32'b0;
   assign D[2] = (!i_aes_or_keccak) ? o_data[1] : 32'b0;
   assign D[3] = (!i_aes_or_keccak) ? o_data[2] : 32'b0;
   assign D[4] = (!i_aes_or_keccak) ? o_data[3] : 32'b0;

endmodule

`endif // UNIFIED_XOR_SECTION_SV