function x_samp = circ_downsample(x, n, N)
  x_samp = zeros(1, N);
  for ii = 1:N
    x_samp(ii) = x( mod((ii-1)*n+1, length(x)) );
  end
end