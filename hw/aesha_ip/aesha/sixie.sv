`ifndef SIXIE_SV
`define SIXIE_SV

module sixie (
  input  wire  [63:0] A_in  [0:4][0:4],
  input  wire  [63:0] D     [0:4],
  input  wire  [63:0] rc,
  output logic [63:0] A_out [0:4][0:4]
);
                                              
logic [5:0] rot_constants [0:4][0:4] = '{'{ 0, 36, 3,  41, 18 },
                                         '{ 1, 44, 10, 45,  2 },
                                         '{62,  6, 43, 15, 61 },
                                         '{28, 55, 25, 21, 56 },
                                         '{27, 20, 39, 8, 14 }
                                        };

genvar x, y;
generate
  for(x = 0; x < 5; x++) begin : gen_x
      for(y = 0; y < 5; y++) begin : gen_y
          logic [63:0] theta_3_0, theta_3_1, theta_3_2;
          logic [63:0] o_rot_0, o_rot_1, o_rot_2;
          
          assign theta_3_0 = A_in[(x + 3 * y) % 5][x] ^ D[(x + 3 * y) % 5];
          assign theta_3_1 = A_in[((x + 1) + 3 * y) % 5][(x + 1) % 5] ^ D[((x + 1) + 3 * y) % 5];
          assign theta_3_2 = A_in[((x + 2) + 3 * y) % 5][(x + 2) % 5] ^ D[((x + 2) + 3 * y) % 5];

          wire [5:0] rot_cons_0 = rot_constants[(x + 3 * y) % 5][x];
          wire [5:0] rot_cons_1 = rot_constants[((x + 1) + 3 * y) % 5][(x + 1) % 5];
          wire [5:0] rot_cons_2 = rot_constants[((x + 2) + 3 * y) % 5][(x + 2) % 5];

          rot rot0_ins(.i_lane(theta_3_0), .i_r(rot_cons_0), .o_lane(o_rot_0));
          rot rot1_ins(.i_lane(theta_3_1), .i_r(rot_cons_1), .o_lane(o_rot_1));
          rot rot2_ins(.i_lane(theta_3_2), .i_r(rot_cons_2), .o_lane(o_rot_2));

          wire [63:0] sixie_result = o_rot_0 ^ ((~o_rot_1) & o_rot_2);

          always_comb begin
              if (x == 0 && y == 0) 
                  A_out[x][y] = sixie_result ^ rc;
              else
                  A_out[x][y] = sixie_result;
          end 
      end
  end
endgenerate

endmodule

`endif // SIXIE_SV