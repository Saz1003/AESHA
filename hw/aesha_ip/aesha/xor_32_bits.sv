`ifndef XOR_32_BITS_SV
`define XOR_32_BITS_SV

module xor_32_bits (
    input  wire  [31:0] i_data [0:4],
    output logic [31:0] o_data
);

    assign o_data[31:16] = i_data[0][31:16] ^ i_data[1][31:16] ^ i_data[2][31:16] ^ i_data[3][31:16] ^ i_data[4][31:16];
    assign o_data[15:0 ] = i_data[0][15:0 ] ^ i_data[1][15:0 ] ^ i_data[2][15:0 ] ^ i_data[3][15:0 ] ^ i_data[4][15:0 ];

endmodule

`endif // XOR_32_BITS_SV
