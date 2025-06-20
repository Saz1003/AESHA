`ifndef CU_SV
`define CU_SV

module control_unit (input  logic         i_clk,
                     input  logic         i_reset,
                     input  logic         i_aes_or_keccak,
                     input  logic         i_enc_or_dec,
                     input  wire  [127:0] i_key,
                     input  wire  [511:0] i_data,
                     output logic         busy,
                     output logic         aclr,
                     output logic         aes_or_keccak,
                     output logic         enc_or_dec,
                     output logic [127:0] key,
                     output logic [511:0] data,
                     output logic         genkey
                    );

logic         busy_reg, aclr_reg, aes_or_keccak_reg, enc_or_dec_reg, genkey_reg;
logic [127:0] key_reg;
logic [511:0] data_reg;
logic [4:0]   round_a, round_k;
logic [1:0]   counter;
logic [1:0]   cu_state;

assign busy          = busy_reg;
assign aclr          = aclr_reg;
assign aes_or_keccak = aes_or_keccak_reg;
assign enc_or_dec    = enc_or_dec_reg;
assign genkey        = genkey_reg;
assign key           = key_reg;
assign data          = data_reg;

localparam INIT = 2'd0, READY = 2'd1, RUN = 2'd2;

    always_ff @(posedge i_clk or negedge i_reset) begin
        if(!i_reset) begin
            round_a              = 5'd0;
            round_k              = 5'd0;
            counter              = 2'd0;
            aes_or_keccak_reg    = 1'd0;
            enc_or_dec_reg       = 1'd0;
            busy_reg             = 1'd0;
            aclr_reg             = 1'd0;
            genkey_reg           = 1'd1;
            cu_state             = INIT;
        end
        else if(cu_state == INIT) begin
            key_reg = i_key;
            data_reg = i_data;
            round_a              = 5'd0;
            round_k              = 5'd0;
            aclr_reg             = 1'd0;
            genkey_reg           = 1'd1;
            cu_state = READY;
        end
        else if(cu_state == READY) begin
            aes_or_keccak_reg = i_aes_or_keccak;
            enc_or_dec_reg = i_enc_or_dec;
            busy_reg = 1'd1;
            aclr_reg = 1'd1;
            cu_state = RUN;
        end
        else if (cu_state == RUN) begin
            if(aes_or_keccak_reg == 1'd0) begin
                if(round_k < 5'd23) begin
                    round_k = round_k + 1'd1;
                end
                else begin
                    round_k = round_k + 1'd1;
                    cu_state = INIT;
                end
            end
            else if(aes_or_keccak_reg == 1'd1) begin
                if(round_a < 5'd10) begin
                    if(counter == 1) begin
                        round_a = round_a + 1'd1;
                        counter = 2'd0;
                    end
                    else begin
                        counter = counter + 1'd1;
                    end
                end
                else begin
                    if(genkey_reg == 1'd1) begin
                        round_a = 5'd0;
                        genkey_reg = 1'd0;
                    end
                    else begin
                        cu_state = INIT;
                    end
                end
            end
        end
    end
endmodule

`endif 