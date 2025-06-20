`ifndef ROUND_COUNTER_A_SV
`define ROUND_COUNTER_A_SV

module round_counter_a(input  logic       i_clk, i_reset, i_aes_or_keccak,
                       output logic [4:0] o_round,
                       output logic       o_round_valid
                      );
    logic [1:0] count;
    always_ff @(posedge i_clk or negedge i_reset) begin
        if (!i_reset) begin
            o_round <= 0;
            count <= 0;
            o_round_valid <= 0;
        end
        else if (o_round == 10) begin
            o_round <= 0;
            count <= 0;
            o_round_valid <= 0;
        end
        else if (!i_aes_or_keccak) begin
            o_round <= 0;
            count <= 0;
            o_round_valid <= 0;
        end
        else begin
                count <= count + 1;
                o_round_valid <= 0;
                if(count == 1) begin
                    o_round <= o_round + 1;
                    count <= 0;
                    o_round_valid <= 1;
                end
            end
        end
endmodule
`endif // ROUND_COUNTER_A_SV
