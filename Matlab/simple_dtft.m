function X = simple_dtft(x, N)
  if length(x) < N
    x = [x, zeros(1, N - length(x))];
  elseif length(x) > N 
    x = x(1:N);
  end
  X = zeros(1, N);

  for kk = 1:N
    exp_vec = exp((-j*2*pi*(kk-1).*[0:N-1])./N);
    X(kk) = sum(x.*exp_vec);
  end
end