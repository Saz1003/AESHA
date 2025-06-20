`ifndef LOOKUP_TABLE_SV
`define LOOKUP_TABLE_SV

module lookup_table(input  logic        i_clk,
                    input  logic        i_reset,
                    input  logic        i_enc_or_dec, // enc = 0; dec = 1;
                    input  logic        i_t_or_s,     // t = 0; s = 1;
                    input  wire  [31:0] i_data  [0:3],
                    output logic [31:0] o_data [0:3][0:3]
					);

bram bram1(.i_clk(i_clk), .i_reset(i_reset), .i_enc_or_dec(i_enc_or_dec), .i_t_or_s(i_t_or_s), .i_data(i_data[0]), .o_data(o_data[0]));
bram bram2(.i_clk(i_clk), .i_reset(i_reset), .i_enc_or_dec(i_enc_or_dec), .i_t_or_s(i_t_or_s), .i_data(i_data[1]), .o_data(o_data[1]));
bram bram3(.i_clk(i_clk), .i_reset(i_reset), .i_enc_or_dec(i_enc_or_dec), .i_t_or_s(i_t_or_s), .i_data(i_data[2]), .o_data(o_data[2]));
bram bram4(.i_clk(i_clk), .i_reset(i_reset), .i_enc_or_dec(i_enc_or_dec), .i_t_or_s(i_t_or_s), .i_data(i_data[3]), .o_data(o_data[3]));

endmodule

`endif // LOOKUP_TABLE_SV