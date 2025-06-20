`ifndef ROUND_COUNTER_K_SV
`define ROUND_COUNTER_K_SV

module round_counter_k(input  logic       i_clk, i_reset, i_aes_or_keccak,
                       output logic [4:0] o_round
                      );
    always_ff @(posedge i_clk, negedge i_reset) begin
        if (!i_reset)              o_round <= 0;
        else if (o_round == 24)    o_round <= 0; 
        else if (i_aes_or_keccak)  o_round <= 0;
        else                       o_round <= o_round + 1; 
    end
endmodule

`endif // ROUND_COUNTER_K_SV