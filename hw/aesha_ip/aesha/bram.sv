`ifndef BRAM_SV
`define BRAM_SV

module bram(input  logic        i_clk,
            input  logic        i_reset,
            input  logic        i_enc_or_dec, // enc = 0; dec = 1;
            input  logic        i_t_or_s,     // t = 0; s = 1;
            input  wire  [31:0] i_data,
            output logic [31:0] o_data [0:3]
            );

logic [31:0] dout_a[0:1];
logic [31:0] dout_b[0:1];
logic [31:0] dout_a_mid[0:1];
logic [31:0] dout_b_mid[0:1];
logic [9:0 ] address [0:3];
logic        control;

mem a(.i_clk(i_clk), .i_reset(i_reset), .address(address[0]), .o_data(dout_a[0])); // neg
mem b(.i_clk(i_clk), .i_reset(i_reset), .address(address[2]), .o_data(dout_a[1])); // pos 
mem c(.i_clk(i_clk), .i_reset(i_reset), .address(address[1]), .o_data(dout_b[0])); // neg
mem d(.i_clk(i_clk), .i_reset(i_reset), .address(address[3]), .o_data(dout_b[1])); // pos


always_ff @(i_clk ) begin //or negedge i_reset
	if(!i_reset) begin
		control <= 1'b0;
	end
	else begin
		control <= i_clk;
	end
end

always_ff @(control ) begin //or negedge i_reset
	if(!i_reset) begin
		address[0] = 10'b0;
		address[1] = 10'b0;
		address[2] = 10'b0;
		address[3] = 10'b0;
	end
	else if(control) begin
		address[2] = {i_enc_or_dec, i_t_or_s, i_data[15:8 ]};
		address[3] = {i_enc_or_dec, i_t_or_s, i_data[ 7:0 ]};
	end
	else if(!control) begin
		address[0] = {i_enc_or_dec, i_t_or_s, i_data[31:24]};
		address[1] = {i_enc_or_dec, i_t_or_s, i_data[23:16]};
	end
end

always_ff @(posedge control or negedge i_reset) begin
	if(!i_reset) begin
		o_data[0] <= 32'b0;
		o_data[1] <= 32'b0;
	end
	// else begin
	// 	if(i_enc_or_dec) begin
	// 		o_data[0] <= dout_a[0];
	// 	    o_data[1] <= dout_b[0];
	//     end
	    else begin
		    o_data[0] <= dout_a[0];
	        o_data[1] <= {dout_b[0][ 7:0 ], dout_b[0][31:24], dout_b[0][23:16], dout_b[0][15:8]};
		end
	// end
end

always_ff @(negedge control or negedge i_reset) begin
	if(!i_reset) begin
		o_data[2] <= 32'b0;
		o_data[3] <= 32'b0;
	end
	else begin
		// if(i_enc_or_dec) begin
		// 	o_data[2] <= dout_a[1];
		//     o_data[3] <= dout_b[1];
	    // end
	    // else begin
		    o_data[2] <= {dout_a[1][15:8 ], dout_a[1][ 7:0 ], dout_a[1][31:24], dout_a[1][23:16]};
		    o_data[3] <= {dout_b[1][23:16], dout_b[1][15:8 ], dout_b[1][ 7:0 ], dout_b[1][31:24]};
		// end
	end
end

endmodule 

`endif