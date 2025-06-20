// module tb_AESHA_top();
// logic tb_i_clk, tb_i_reset, tb_i_aes_or_keccak, tb_i_enc_or_dec, tb_done;
// logic [127:0] tb_i_key;
// logic [511:0] tb_i_data;
// logic [511:0] tb_o_data;
// logic         tb_o_busy;

// AESHA_top dut(.i_clk(tb_i_clk),
//               .i_reset(tb_i_reset),
//               .i_aes_or_keccak(tb_i_aes_or_keccak),
//               .i_enc_or_dec(tb_i_enc_or_dec),
//               .i_key(tb_i_key),
//               .i_data(tb_i_data),
//               .o_data(tb_o_data),
//               .o_busy(tb_o_busy),
//               .o_done(tb_done)
// );

// initial begin
//     tb_i_clk = 1'b0;
//     forever #5 tb_i_clk = !tb_i_clk;
// end

// initial begin
//     tb_i_reset = 1'b0;
//     tb_i_aes_or_keccak = 1'b0;
//     tb_i_enc_or_dec = 1'b0;
//     tb_i_data = 512'h0;
//     tb_i_key = 128'h0;

//     #10 tb_i_reset = 1'b1;
//     $display("----------------------------------- SHA-3 --------------------------------------------");
//     @(posedge tb_done);

//     $display("----------------------------------- AES 128 ENC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b0;
//     tb_i_data = 512'h0;
//     tb_i_key  = 128'h0;
//     @(posedge tb_done);

//     $display("----------------------------------- AES 128 DEC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b1;
//     @(posedge tb_done);

//     $display("----------------------------------- AES 128 ENC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b0;
//     tb_i_data = 512'h3243f6a8885a308d313198a2e0370734;
//     tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
//     @(posedge tb_done);

//     $display("----------------------------------- AES 128 DEC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b1;
//     tb_i_data = 512'h7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f3925841d02dc09fbdc118597196a0b32;
//     tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
//     @(posedge tb_done);
    
//     $display("----------------------------------- SHA-3 --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b0;
//     tb_i_key  = 128'h0;
//     tb_i_data = 512'h69c4e0d86a7b0430d8cdb78070b4c55a;
//     @(posedge tb_done);

//     $display("----------------------------------- AES 128 ENC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b0;
//     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
//     tb_i_key  = {$random, $random, $random, $random};
//     @(posedge tb_done);

//     $display("----------------------------------- SHA-3 --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b0;
//     tb_i_key  = 128'h0;
//     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
//     @(posedge tb_done);    

//     $display("----------------------------------- SHA-3 --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b0;
//     tb_i_key  = 128'h0;
//     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
//     @(posedge tb_done);

//     $display("----------------------------------- AES 128 DEC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b1;
//     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
//     tb_i_key  = {$random, $random, $random, $random};
//     @(posedge tb_done);
    
//     // $display("----------------------------------- AES 128 ENC --------------------------------------------");
//     // tb_i_aes_or_keccak = 1'b1;
//     // tb_i_enc_or_dec = 1'b0;
//     // tb_i_data = 512'h3243f6a8885a308d313198a2e0370734;
//     // tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
//     // @(posedge tb_done);

//     $display("----------------------------------- AES 128 ENC --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b1;
//     tb_i_enc_or_dec = 1'b0;
//     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
//     tb_i_key  = {$random, $random, $random, $random};
//     @(posedge tb_done);

//     $display("----------------------------------- SHA-3 --------------------------------------------");
//     tb_i_aes_or_keccak = 1'b0;
//     tb_i_key  = 128'h0;
//     tb_i_data = {$random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random, $random};
//     @(posedge tb_done);

//     #20 tb_i_reset = 1'b0;
//     #100 $finish;
// end

// initial begin
//     forever @(posedge tb_done) begin
//         // $display("----------------------------------- %s %s --------------------------------------------", tb_i_aes_or_keccak ? "AES 128" : "SHA-3", tb_i_aes_or_keccak ? (tb_i_enc_or_dec) ? "DEC" : "ENC" : "");
//         $display("[TIME %t] Key = %h, Data in = %h, Data out = %h", $time, tb_i_key, tb_i_data, tb_o_data);
//     end
// end

// initial begin
//     $dumpfile("tb_AESHA_top.vcd");
//     $dumpvars(0, tb_AESHA_top);
// end

// endmodule

module tb_AESHA_top();
logic tb_i_clk, tb_i_reset, tb_i_aes_or_keccak, tb_i_enc_or_dec, tb_done;
logic [127:0] tb_i_key;
logic [511:0] tb_i_data;
logic [511:0] tb_o_data;
logic         tb_o_busy;

AESHA_top dut(.i_clk(tb_i_clk),
              .i_reset(tb_i_reset),
              .i_aes_or_keccak(tb_i_aes_or_keccak),
              .i_enc_or_dec(tb_i_enc_or_dec),
              .i_key(tb_i_key),
              .i_data(tb_i_data),
              .o_data(tb_o_data),
              .o_busy(tb_o_busy),
              .o_done(tb_done)
);

initial begin
    tb_i_clk = 1'b0;
    forever #5 tb_i_clk = !tb_i_clk;
end

initial begin
    tb_i_reset = 1'b0;
    tb_i_aes_or_keccak = 1'b0;
    tb_i_enc_or_dec = 1'b0;
    tb_i_data = 512'h0;
    tb_i_key = 128'h0;

    #10 tb_i_reset = 1'b1;
    $display("Test case 1: Input String: 512 bit 0");
    $display("----------------------------------- SHA-3 --------------------------------------------");
    tb_i_data = 512'h0;
    tb_i_key = 128'h0;
    @(posedge tb_done);
    assert (tb_o_data == 512'ha8620b2ebeca41fbc773bb837b5e724d6eb2de570d99858df0d7d97067fb8103b21757873b735097b35d3bea8fd1c359a9e8a63c1540c76c9784cf8d975e995c)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 2: Input String: 512 bit 0");
    $display("----------------------------------- AES 128 ENC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b0;
    tb_i_data = 512'h0;
    tb_i_key  = 128'h0;
    @(posedge tb_done);
    assert (tb_o_data == 512'h66e94bd4ef8a2c3b884cfa59ca342b2e66e94bd4ef8a2c3b884cfa59ca342b2e66e94bd4ef8a2c3b884cfa59ca342b2e66e94bd4ef8a2c3b884cfa59ca342b2e)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 3: Input String: 512 bit 0");
    $display("----------------------------------- AES 128 DEC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b1;
    @(posedge tb_done);
    assert (tb_o_data == 512'h140f0f1011b5223d79587717ffd9ec3a140f0f1011b5223d79587717ffd9ec3a140f0f1011b5223d79587717ffd9ec3a140f0f1011b5223d79587717ffd9ec3a)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 4: AES ENC Example");
    $display("----------------------------------- AES 128 ENC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b0;
    tb_i_data = 512'h3243f6a8885a308d313198a2e0370734;
    tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
    @(posedge tb_done);
    assert (tb_o_data == 512'h7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f3925841d02dc09fbdc118597196a0b32)
        $display("PASSED");
    else
        $display("FAILED");
    $display;


    $display("Test case 5: AES DEC Example");
    $display("----------------------------------- AES 128 DEC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b1;
    tb_i_data = 512'h7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f7df76b0c1ab899b33e42f047b91b546f3925841d02dc09fbdc118597196a0b32;
    tb_i_key  = 128'h2b7e151628aed2a6abf7158809cf4f3c;
    @(posedge tb_done);
    assert (tb_o_data == 512'h0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003243f6a8885a308d313198a2e0370734)
        $display("PASSED");
    else
        $display("FAILED");
    $display;
    
    $display("Test case 6: Random Values");
    $display("----------------------------------- SHA-3 --------------------------------------------");
    tb_i_aes_or_keccak = 1'b0;
    tb_i_key  = 128'h0;
    tb_i_data = 512'h69c4e0d86a7b0430d8cdb78070b4c55a;
    @(posedge tb_done);
    assert (tb_o_data == 512'h914fcd3ec67575c86d0327004a4a630170eef0b0931b342ee59d6de4247856e9a7466a3561853bedd79fa909fba8046f93127a9de6595179ed643b43f682fe8c)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 7: Random Values");
    $display("----------------------------------- AES 128 ENC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b0;
    tb_i_data = 512'he33724c67cfde9f9462df78c76d457ed1e8dcd3d3b23f17606d7cd0d00f3e30189375212b2c2846546df998d06b97b0db1f056638484d609c0895e8112153524;
    tb_i_key  = 128'hbbd2727772aff7e5d513d2aae2f784c5;
    @(posedge tb_done);
    assert (tb_o_data == 512'h0cdd96f7ab6c7b6e2e040c879aa775159282b1b5279fa418e3c4b7a7d5d2e9f8cd37f059a12631e2b8b0718caa1c62c8e71bcadcc82cbbcf8a9266ce124897b0)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 8: Random Values");
    $display("----------------------------------- SHA-3 --------------------------------------------");
    tb_i_aes_or_keccak = 1'b0;
    tb_i_key  = 128'h0;
    tb_i_data = 512'hcecccc9d557845aa10642120c03b22800573870ab1ef6263b2a7266596ab582dde8e28bd2e58495ce2ca4ec5f4007ae8e77696ce793069f247ecdb8f8932d612;
    @(posedge tb_done);  
    assert (tb_o_data == 512'h1f56e8bcb41a652984a26540f7626d9f01450e811b0b38d3df5190ae6c32334477ad95b7f1838462700927188c7cd41ef18b1d0829f8563cd35fce11800040ee)
        $display("PASSED");
    else
        $display("FAILED");  
    $display;

    $display("Test case 9: Random Values");
    $display("----------------------------------- SHA-3 --------------------------------------------");
    tb_i_aes_or_keccak = 1'b0;
    tb_i_key  = 128'h0;
    tb_i_data = 512'h452e618a7968bdf29e314c3ce5730aca0509650a11844923e7c572cf0effe91dd7563eae81174a02eaa62ad5359fdd6ba9a7d65386bc380d8983b813cb203e96;
    @(posedge tb_done);
    assert (tb_o_data == 512'h18a6d5e112741dbe663b3ec62d3ab03942bea8a22870feed8408a91546bec7e97330e15c080928fab0838581054dbcb2f7c89bf62f2fa248f03ebcbbbed8143f)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 10: Random Values");
    $display("----------------------------------- AES 128 DEC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b1;
    tb_i_data = 512'h1d06333a9dcc603b27f2554f42f24185b897be7185d79a0b150fdd2ade7502bc571513ae634bf9c65b0265b675c50debc48a12893c20f378ec4b34d820c4b341;
    tb_i_key  = 128'h6c9c4bd978d99bf10aaa4b15bf23327e;
    @(posedge tb_done);
    assert (tb_o_data == 512'he43e0699c411f736407d2c0e8e499a5fed9a6ce24994a0808eaf5abec2d0f58fd7e3e1b033049a63fba50a0750e20105b6f7e25d6f90994e2cc8f401a38aae0f)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 11: Random Values");
    $display("----------------------------------- AES 128 ENC --------------------------------------------");
    tb_i_aes_or_keccak = 1'b1;
    tb_i_enc_or_dec = 1'b0;
    tb_i_data = 512'h061d7f0c4b212f96a8c7fc51ebfec0d7e8233ed0a4ae324944de3789adcbc05bae7d945ccfc4569fdbcd60b77c6da9f847b9a18f4fa1559f2635fb4c31230762;
    tb_i_key  = 128'h1ef2ed3dbb825a776457edc8e12ccec2;
    @(posedge tb_done);
    assert (tb_o_data == 512'haf9a4efe3717aa32160dee0464702cc668ed872554d7b259b5fb936f17493bfdbeafbed9e8fdbfbc978d63039bb89e9da9befadaed470a626957b17e70505c59)
        $display("PASSED");
    else
        $display("FAILED");
    $display;

    $display("Test case 12: Random Values");
    $display("----------------------------------- SHA-3 --------------------------------------------");
    tb_i_aes_or_keccak = 1'b0;
    tb_i_key  = 128'h0;
    tb_i_data = 512'hce2ff29cc71a0c8ec33f38862c156358150caf2a9ff2ae3f248b4b492dda595bbc14887842d92f85e9ebf6d30fd28f1f1cd9e73936e5816dbf05007e090cdb12;
    @(posedge tb_done);
    assert (tb_o_data == 512'h96c676d5bf5a3c1debf7e9b845313c83e37929119e54bd5b35b5840f404f4aab9ad9ef4420bdaaff9d39384f84cc6df7eea04e9e1b8c93f727792fcbe6dc08bd)
        $display("PASSED");
    else
        $display("FAILED");
    $display;


    #20 tb_i_reset = 1'b0;
    #100 $finish;
end

initial begin
    // forever @(posedge tb_done) begin
    //     // $display("----------------------------------- %s %s --------------------------------------------", tb_i_aes_or_keccak ? "AES 128" : "SHA-3", tb_i_aes_or_keccak ? (tb_i_enc_or_dec) ? "DEC" : "ENC" : "");
    //     $display("[TIME %t] Key = %h, Data in = %h, Data out = %h", $time, tb_i_key, tb_i_data, tb_o_data);
    // end
end

initial begin
    $dumpfile("tb_AESHA_top.vcd");
    $dumpvars(0, tb_AESHA_top);
end

endmodule