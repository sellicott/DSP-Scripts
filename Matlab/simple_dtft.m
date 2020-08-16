function X = simple_dtft(x, N, k)
  exp_vec = exp((-j*2*pi*k.*[0:N-1])./N);
  X = sum(x.*exp_vec);
end