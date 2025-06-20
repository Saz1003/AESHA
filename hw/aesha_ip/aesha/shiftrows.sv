`ifndef SR_SV
`define SR_SV

module shiftrows (input  logic        i_reset,
                  input  logic        i_enc_or_dec,     
			      input  wire  [127:0] A_in,      
				  output logic [127:0] A_out      
				  );

    logic [31:0] A_in_mid [0:3];
    assign A_in_mid[0] = A_in[127:96];
    assign A_in_mid[1] = A_in[ 96:64];
    assign A_in_mid[2] = A_in[ 63:32];
    assign A_in_mid[3] = A_in[ 31: 0];

    logic [7:0]  state_in    [0:3][0:3];  
    logic [7:0]  state_sr    [0:3][0:3]; 
    logic [7:0]  state_in_sr [0:3][0:3]; 
    logic [31:0] A_out_SR    [0:3];
    logic [31:0] A_out_inSR  [0:3];

    always_comb begin
        if(!i_reset) begin
            for(int i = 0; i < 4; i++) begin
                A_out_SR[i]=  0;
                A_out_inSR[i] = 0;
            end
        end
        else begin
            for (int c = 0; c < 4; c++) begin
                state_in[0][c] = A_in_mid[c][31:24];
                state_in[1][c] = A_in_mid[c][23:16];
                state_in[2][c] = A_in_mid[c][15:8];
                state_in[3][c] = A_in_mid[c][7:0];
            end
    
            for (int r = 0; r < 4; r++) begin
                for (int c = 0; c < 4; c++) begin
                    state_sr[r][c] = state_in[r][(c + r) % 4];
                end
            end
    
            for (int r = 0; r < 4; r++) begin
                for (int c = 0; c < 4; c++) begin
                    state_in_sr[r][c] = state_in[r][(c - r + 4) % 4];
                end
            end
    
            for (int c = 0; c < 4; c++) begin
                A_out_SR[c] = {
                    state_sr[0][c],
                    state_sr[1][c],
                    state_sr[2][c],
                    state_sr[3][c]
                };
    
                A_out_inSR[c] = {
                    state_in_sr[0][c],
                    state_in_sr[1][c],
                    state_in_sr[2][c],
                    state_in_sr[3][c]
                };
            end
        end
    end
	 
    assign A_out = (!i_enc_or_dec) ? {A_out_SR[0], A_out_SR[1], A_out_SR[2], A_out_SR[3]} : {A_out_inSR[0], A_out_inSR[1], A_out_inSR[2], A_out_inSR[3]};

endmodule

`endif