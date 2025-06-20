`ifndef SQUAD_I_TABLE
`define SQUAD_I_TABLE

module squad_lookup_table(input  logic          i_clk,
                          input  logic          i_reset,
                          input  logic          i_enc_or_dec, // enc = 0; dec = 1;
                          input  logic          i_t_or_s,     // t = 0; s = 1;
                          input  logic          i_genkey,
                          input  wire  [127:0]  i_data  [0:3],
                          output logic [31:0]   o_data  [0:3][0:3][0:3]
					      );

    logic [31:0] A_lut_in [0:3][0:3];
    logic [31:0] rotw;

    assign rotw = i_genkey ? {i_data[0][23:16], i_data[0][15:8], i_data[0][7:0], i_data[0][31:24]} : i_data[0];

	 assign A_lut_in[0][0] = i_data[0][127:96];
	 assign A_lut_in[0][1] = i_data[0][95:64];
	 assign A_lut_in[0][2] = i_data[0][63:32];
	 assign A_lut_in[0][3] = rotw;

	 assign A_lut_in[1][0] = i_data[1][127:96];
	 assign A_lut_in[1][1] = i_data[1][95:64];
	 assign A_lut_in[1][2] = i_data[1][63:32];
	 assign A_lut_in[1][3] = i_data[1][31:0];

	 assign A_lut_in[2][0] = i_data[2][127:96];
	 assign A_lut_in[2][1] = i_data[2][95:64];
	 assign A_lut_in[2][2] = i_data[2][63:32];
	 assign A_lut_in[2][3] = i_data[2][31:0];

	 assign A_lut_in[3][0] = i_data[3][127:96];
	 assign A_lut_in[3][1] = i_data[3][95:64];
	 assign A_lut_in[3][2] = i_data[3][63:32];
	 assign A_lut_in[3][3] = i_data[3][31:0];

    lookup_table lut0(.i_clk(i_clk),
                      .i_reset(i_reset),
                      .i_enc_or_dec(i_enc_or_dec),
                      .i_t_or_s(i_t_or_s),
                      .i_data(A_lut_in[0]),
                      .o_data(o_data[0])
                     );

    lookup_table lut1(.i_clk(i_clk),
                      .i_reset(i_reset),
                      .i_enc_or_dec(i_enc_or_dec),
                      .i_t_or_s(i_t_or_s),
                      .i_data(A_lut_in[1]),
                      .o_data(o_data[1])
                     );
                     
    lookup_table lut2(.i_clk(i_clk),
                      .i_reset(i_reset),
                      .i_enc_or_dec(i_enc_or_dec),
                      .i_t_or_s(i_t_or_s),
                      .i_data(A_lut_in[2]),
                      .o_data(o_data[2])
                      );

    lookup_table lut3(.i_clk(i_clk),
                      .i_reset(i_reset),
                      .i_enc_or_dec(i_enc_or_dec),
                      .i_t_or_s(i_t_or_s),
                      .i_data(A_lut_in[3]),
                      .o_data(o_data[3])
                      );
endmodule

`endif