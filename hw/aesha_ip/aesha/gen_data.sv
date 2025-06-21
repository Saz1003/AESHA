module gen_data();

    // Khởi tạo dữ liệu random
    logic [511:0] data_rd;
    logic [511:0] data_out [0:9999];
    logic [127:0] key_out [0:9999];

    initial begin
        for(int i = 0; i < 10000; i++) begin
            data_out[i] = {$urandom(), $urandom(), $urandom(), $urandom(), 
                          $urandom(), $urandom(), $urandom(), $urandom(), 
                          $urandom(), $urandom(), $urandom(), $urandom(), 
                          $urandom(), $urandom(), $urandom(), $urandom()};
            key_out[i] = {$urandom(), $urandom(), $urandom(), $urandom()};
            for(int j = 1; j < i + 1; j++) begin
                if(data_out[i] == data_out[j]) begin
                    while (data_out[i] != data_out[j]) begin
                        data_out[i] = {$urandom(), $urandom(), $urandom(), $urandom(), 
                                       $urandom(), $urandom(), $urandom(), $urandom(), 
                                       $urandom(), $urandom(), $urandom(), $urandom(), 
                                       $urandom(), $urandom(), $urandom(), $urandom()};
                    end
                end
            end
        end

        for(int i = 0; i < 10000; i++) begin
            #1 $display("%h", key_out[i]);
        end
    end
endmodule
