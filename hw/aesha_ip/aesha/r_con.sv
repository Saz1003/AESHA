`ifndef R_CON_SV
`define R_CON_SV

module r_con(input  logic       i_clk,
	         input  logic [4:0] t,
             output logic [31:0] rcon
            );

	always_ff @(posedge i_clk) begin
		case (t)
			5'b00000: rcon <= 32'h01000000;
			5'b00001: rcon <= 32'h02000000;
			5'b00010: rcon <= 32'h04000000;
			5'b00011: rcon <= 32'h08000000;
			5'b00100: rcon <= 32'h10000000;
			5'b00101: rcon <= 32'h20000000;
			5'b00110: rcon <= 32'h40000000;
			5'b00111: rcon <= 32'h80000000;
			5'b01000: rcon <= 32'h1b000000;
			5'b01001: rcon <= 32'h36000000;
			default: rcon <= 32'h0;
		endcase
	end

endmodule
`endif // R_CON_SV