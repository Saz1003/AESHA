`timescale 1ps/1ps
module tb_AESHA();

logic tb_i_clk, tb_reset, tb_i_aes_or_keccak, tb_i_enc_or_dec, tb_done;
logic [127:0] tb_i_key;
logic [511:0] tb_i_data;
logic [511:0] tb_o_data;

AESHA dut(.i_clk(tb_i_clk),
          .i_reset(tb_reset),
          .i_aes_or_keccak(tb_i_aes_or_keccak),
          .i_enc_or_dec(tb_i_enc_or_dec),
          .i_key(tb_i_key),
          .i_data(tb_i_data),
          .o_data(tb_o_data),
          .done(tb_done)
          );

initial begin
    tb_i_clk = 1'b0;
    forever begin
        tb_i_clk = #10 !tb_i_clk;
    end
end

initial begin
    tb_reset = 1'b0;
    tb_i_aes_or_keccak = 1'b0;
    tb_i_enc_or_dec = 1'b0;
    tb_i_data = 512'h0;
    tb_i_data = 512'h69c4e0d86a7b0430d8cdb78070b4c55a;

    tb_i_key = 128'h0;

    #10 tb_reset = 1'b1;
    // enc code
    // tb_i_aes_or_keccak = 1'b1;
    // tb_i_enc_or_dec = 1'b0;
    // tb_i_data = 512'h3243f6a8885a308d313198a2e0370734;
    // tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
    // @(posedge tb_done);

    tb_i_aes_or_keccak = 1'b0;
    // tb_i_data = 512'h69c4e0d86a7b0430d8cdb78070b4c55a;
    tb_i_key  = 128'h0;
    @(posedge tb_done);
    
    // repeat (2) begin
    //     tb_i_data = 512'h69c4e0d86a7b0430d8cdb78070b4c55a;
    //     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
    //     @(posedge tb_done);
    // end

    // tb_i_aes_or_keccak = 1'b1;
    // tb_i_enc_or_dec = 1'b1;
    // tb_i_data = 512'h7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f3925841d02dc09fbdc118597196a0b32;
    // tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
    // @(posedge tb_done);
    #20 $finish;
end

initial begin
    forever @(posedge tb_done) begin
        $display("[Time = %t] tb_i_aes_or_keccak %b Data in = %h, Data out = %h", $time, tb_i_aes_or_keccak, tb_i_data, tb_o_data);
    end
end

initial begin
    $dumpfile("tb_AESHA.vcd");
    $dumpvars(0, tb_AESHA);
end

endmodule