`ifndef TOP_SV
`define TOP_SV

module AESHA_top(input  logic         i_clk,
                 input  logic         i_reset,
                 input  logic         i_aes_or_keccak,
                 input  logic         i_enc_or_dec,
                 input  logic [127:0] i_key,
                 input  wire  [511:0] i_data,
                 output logic [511:0] o_data,
                 output logic         o_busy,
                 output logic         o_done
                );

logic       aclr_reg, aes_or_keccak_reg, enc_or_dec_reg, genkey_reg;
logic [127:0] key_reg;
logic [511:0] data_reg;

control_unit cu(.i_clk(i_clk),
                .i_reset(i_reset),
                .i_aes_or_keccak(i_aes_or_keccak),
                .i_enc_or_dec(i_enc_or_dec),
                .i_key(i_key),
                .i_data(i_data),
                .busy(o_busy),
                .aclr(aclr_reg),
                .aes_or_keccak(aes_or_keccak_reg),
                .enc_or_dec(enc_or_dec_reg),
                .key(key_reg),
                .data(data_reg),
                .genkey(genkey_reg)
                );

AESHA core(.i_clk(i_clk),
           .i_reset(aclr_reg),
           .i_aes_or_keccak(aes_or_keccak_reg),
           .i_enc_or_dec(enc_or_dec_reg),
           .genkey(genkey_reg),
           .i_key(key_reg),
           .i_data(data_reg),
           .o_data(o_data),
           .done(o_done)
           );

endmodule

`endif