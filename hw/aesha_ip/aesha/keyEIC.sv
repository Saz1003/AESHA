`ifndef KEIC_SV
`define KEIC_SV

module keyEIC(input  wire  [31:0] A_in [0:3],
              output logic [31:0] A_out[0:3]
             );

	logic [7:0 ]  A_in_mid  [0:3];
   logic [7:0 ]  A_out_mid [0:3][0:3];
	logic [15:0]  A_mid_tmp [0:3][0:3];
	logic [7:0 ]  A_out_tmp [0:3];
		
	always_comb begin
		for (int i = 0; i < 4; i++) begin
		    A_in_mid[0] = A_in[i][31:24];
            A_in_mid[1] = A_in[i][23:16];
            A_in_mid[2] = A_in[i][15:8 ];
            A_in_mid[3] = A_in[i][ 7:0 ];
			for (int j = 0; j < 4; j++) begin // lưu kết quả theo e 9 d b

				//nhan e
				A_mid_tmp[j][0] = (A_in_mid[j] << 3) ^ (A_in_mid[j] << 2) ^ (A_in_mid[j] << 1); 
				if (A_mid_tmp[j][0] >= ('h100 << 2)) begin
					A_mid_tmp[j][0] = A_mid_tmp[j][0] ^ (16'h11B << 2);
				end
				if (A_mid_tmp[j][0] >= ('h100 << 1)) begin
					A_mid_tmp[j][0] = A_mid_tmp[j][0] ^ (16'h11B << 1);
				end
				if (A_mid_tmp[j][0] >= 'h100 ) begin
					A_mid_tmp[j][0] = A_mid_tmp[j][0] ^ 16'h11B;
				end
				
				A_out_mid[j][0] = A_mid_tmp[j][0][7:0];//cột j hàng 0 
				
				//nhan9
				A_mid_tmp[j][1] = (A_in_mid[j] << 3) ^ A_in_mid[j]; 
				if (A_mid_tmp[j][1] >= ('h100 << 2)) begin
					A_mid_tmp[j][1] = A_mid_tmp[j][1] ^ (16'h11B << 2);
				end
				if (A_mid_tmp[j][1] >= ('h100 << 1)) begin
					A_mid_tmp[j][1] = A_mid_tmp[j][1] ^ (16'h11B << 1);
				end
				if (A_mid_tmp[j][1] >= 'h100) begin
					A_mid_tmp[j][1] = A_mid_tmp[j][1] ^ 16'h11B;
				end
				
				A_out_mid[j][1] = A_mid_tmp[j][1][7:0];//cột j hàng 1 
				
				//nhanD
				A_mid_tmp[j][2] = (A_in_mid[j] << 3) ^ (A_in_mid[j] << 2) ^ A_in_mid[j]; 
				if (A_mid_tmp[j][2] >= ('h100 << 2)) begin
					A_mid_tmp[j][2] = A_mid_tmp[j][2] ^ (16'h11B << 2);
				end
				if (A_mid_tmp[j][2] >= ('h100 << 1)) begin
					A_mid_tmp[j][2] = A_mid_tmp[j][2] ^ (16'h11B << 1);
				end
				if (A_mid_tmp[j][2] >= 'h100 ) begin
					A_mid_tmp[j][2] = A_mid_tmp[j][2] ^ 16'h11B;
				end
				
				A_out_mid[j][2] = A_mid_tmp[j][2][7:0];//cột j hàng 2
				
				//nhanB
				A_mid_tmp[j][3] = (A_in_mid[j] << 3) ^ (A_in_mid[j] << 1) ^ A_in_mid[j]; 
				if (A_mid_tmp[j][3] >= ('h100 << 2)) begin
					A_mid_tmp[j][3] = A_mid_tmp[j][3] ^ (16'h11B << 2);
				end
				if (A_mid_tmp[j][3] >= ('h100 << 1)) begin
					A_mid_tmp[j][3] = A_mid_tmp[j][3] ^ (16'h11B << 1);
				end
				if (A_mid_tmp[j][3] >= 'h100 ) begin
					A_mid_tmp[j][3] = A_mid_tmp[j][3] ^ 16'h11B;
				end
				
				A_out_mid[j][3] = A_mid_tmp[j][3][7:0];//cột j hàng 3
			end
				
			A_out_tmp[0] = A_out_mid[0][0] ^ A_out_mid[1][3] ^ A_out_mid[2][2] ^ A_out_mid[3][1]; // e(A_out_mid[0]) b(A_out_mid[1]) d(A_out_mid[2]) 9(A_out_mid[3])
			A_out_tmp[1] = A_out_mid[0][1] ^ A_out_mid[1][0] ^ A_out_mid[2][3] ^ A_out_mid[3][2]; // 9(A_out_mid[0]) e(A_out_mid[1]) b(A_out_mid[2]) d(A_out_mid[3])
			A_out_tmp[2] = A_out_mid[0][2] ^ A_out_mid[1][1] ^ A_out_mid[2][0] ^ A_out_mid[3][3]; // d(A_out_mid[0]) 9(A_out_mid[1]) e(A_out_mid[2]) b(A_out_mid[3])
			A_out_tmp[3] = A_out_mid[0][3] ^ A_out_mid[1][2] ^ A_out_mid[2][1] ^ A_out_mid[3][0]; // b(A_out_mid[0]) d(A_out_mid[1]) 9(A_out_mid[2]) e(A_out_mid[3])	
			

			A_out[i] = {A_out_tmp[0], A_out_tmp[1], A_out_tmp[2], A_out_tmp[3]};
				
		end
	end

endmodule


`endif