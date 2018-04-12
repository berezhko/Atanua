module dflipflop (
    input wire data,
    input wire clk,
    input wire s,
    input wire r,
    output reg out,
    output reg invout
);

always_ff @(posedge clk, posedge s, posedge r)
begin
    if (r) begin
        out <= 0;
        invout <= 1;
    end else if (s) begin
        out <= 1;
        invout <= 0;
    end else begin
        out <= data;
        invout <= ~data;
    end
end

endmodule
