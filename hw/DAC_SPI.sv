module dac_spi (
    input  logic clk,       
    input  logic rst,       
    
    // SPI Bus Interface 
    input  logic sclk,      
    input  logic cs_n,      
    input  logic mosi,      
    
    // Physical DAC Output
    output logic [11:0] dac_out 
);

    logic [11:0] shift_reg;
    logic sclk_prev;

    always_ff @(posedge clk) begin
        if (rst) begin
            dac_out <= 12'b0;
            shift_reg <= 12'b0;
            sclk_prev <= 1'b0;
        end else begin
            sclk_prev <= sclk; 

            if (cs_n == 1'b0) begin
                // Detect Rising Edge on SPI Clock
                if (sclk == 1'b1 && sclk_prev == 1'b0) begin
                    shift_reg <= {shift_reg[10:0], mosi}; 
                end
            end else begin
                // Latch output when Chip Select goes High
                dac_out <= shift_reg;
            end
        end
    end
endmodule