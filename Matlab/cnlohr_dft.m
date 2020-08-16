function X = cnlohr_dft(x, f)
  %% Based on Charles Lohr's DFT implementation for Colorchord. Only takes
  %% DFT samples at places indicated by the frequency vector f.

  X = zeros(1, length(f));
  q = 20; % quality parameter?
  speedup = 1000; %???

  for kk = 1:length(f)
    % Setup necessary variables
    ftq = f(kk)*q;
    skip = floor(ftq/speedup);
    if skip == 0
      skip = 1;
    end
    advance = 2*pi*f(kk)*skip;

    sample_idx = 1;
    phi = 0;
    real_sum = 0;
    imag_sum = 0;

    for nn = 0:skip:ftq
      sample = x(sample_idx);
      real_c = cos(phi) * sample;
      imag_c = sin(phi) * sample;
     
      real_sum = real_sum + real_c;
      imag_sum = imag_sum + imag_sum;

      phi = phi + advance;
      sample_idx = mod(sample_idx-1 + skip, length(x))+1;
    end
    amp = sqrt(real_sum * real_sum + imag_sum + imag_sum);
    X(kk) = amp;
  end
end 