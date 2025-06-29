module AESHA_wrapper(input 		     [3:0]		KEY,
	                 input 		     [9:0]		SW,
	                 output		     [9:0]		LEDR,
	                 output		     [6:0]		HEX0,
	                 output		     [6:0]		HEX1,
	                 output		     [6:0]		HEX2,
	                 output		     [6:0]		HEX3,
	                 output		     [6:0]		HEX4,
	                 output		     [6:0]		HEX5
                    );

	logic [511:0] o_data;
	logic [23:0] msb, lsb, disp;
	
	assign msb  = o_data[511:488];
	assign lsb  = o_data[23:0];
	assign disp = (SW[0]) ? lsb : msb;

	AESHA_top TOP(.i_clk(KEY[0]),
	              .i_reset(SW[9]),
				  .i_aes_or_keccak(SW[0]),
				  .i_enc_or_dec(SW[1]),
				  .i_key(128'h0),
				  .i_data(512'h0),
				  .o_data(o_data),
				  .o_busy(LEDR[0]),
				  .o_done(LEDR[1])
				  );

	binto7seg disp0 (.bits(disp[3:0]),   .segs(HEX0));
	binto7seg disp1 (.bits(disp[7:4]),   .segs(HEX1));
	binto7seg disp2 (.bits(disp[11:8]),  .segs(HEX2));
	binto7seg disp3 (.bits(disp[15:12]), .segs(HEX3));
	binto7seg disp4 (.bits(disp[19:16]), .segs(HEX4));
	binto7seg disp5 (.bits(disp[23:20]), .segs(HEX5));

endmodule