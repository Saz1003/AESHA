`ifndef XOR_PADDING_SV
`define XOR_PADDING_SV

module xor_padding(input  wire  [31:0] i_data     [0:3],
                   input  wire  [31:0] i_K_col_5,
                   input  wire  [31:0] i_C_shifted[0:4],
                   output logic [31:0] o_data     [0:3][0:4],
                   output logic [31:0] o_K_col_5  [0:4]
                  );

    assign o_data[0][0] = i_data[0];
    assign o_data[0][1] = i_C_shifted[2];
    assign o_data[0][2] = 32'b0;
    assign o_data[0][3] = 32'b0;
    assign o_data[0][4] = 32'b0;

    assign o_data[1][0] = 32'b0;
    assign o_data[1][1] = 32'b0;
    assign o_data[1][2] = i_data[1];
    assign o_data[1][3] = i_C_shifted[3];
    assign o_data[1][4] = 32'b0;

    assign o_data[2][0] = 32'b0;
    assign o_data[2][1] = 32'b0;
    assign o_data[2][2] = 32'b0;
    assign o_data[2][3] = i_C_shifted[4];
    assign o_data[2][4] = i_data[2];

    assign o_data[3][0] = i_data[3];
    assign o_data[3][1] = i_C_shifted[0];
    assign o_data[3][2] = 32'b0;
    assign o_data[3][3] = 32'b0;
    assign o_data[3][4] = 32'b0;

    assign o_K_col_5[0] = i_C_shifted[1];
    assign o_K_col_5[1] = i_K_col_5;
    assign o_K_col_5[2] = 32'b0;
    assign o_K_col_5[3] = 32'b0;
    assign o_K_col_5[4] = 32'b0;
    
endmodule

`endif // XOR_PADDING_SV