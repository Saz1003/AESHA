`ifndef ROT_SV
`define ROT_SV

module rot(input  logic [63:0] i_lane,
           input  logic [5:0 ] i_r,
           output logic [63:0] o_lane
           );

    always_comb begin
        o_lane = (i_lane << i_r) | (i_lane >> (64 - i_r));
    end

endmodule

`endif // ROT_SV