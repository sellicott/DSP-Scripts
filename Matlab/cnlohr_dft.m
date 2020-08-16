function X = cnlohr_dft(x, f)
  %% Based on Charles Lohr's DFT implementation for Colorchord. Only takes
  %% DFT samples at places indicated by the frequency vector f.

  X = zeros(1, length(f));
  q = 20; % quality parameter?
  speedup = 1000; %???
  for kk = 1:length(f)
    ftq = f(kk)*q;
    skip = floor(ftq/speedup);
    if skip == 0
      skip = 1;
    end
    N = f(kk)/skip;
    x_down = circ_downsample(x, skip, floor(N));

    X(kk) = simple_dtft(x_down, N, kk);
    X(kk) = X(kk) / f(kk) / q * skip;
  end
end 