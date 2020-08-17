function X = sellicott_dft(x, f, Fs)
  %% Based on Charles Lohr's DFT implementation for Colorchord. Only takes
  %% DFT samples at places indicated by the frequency vector f.

  X = zeros(1, length(f));
  q = 20; % quality parameter?

  for kk = 1:length(f)
    % downsample the intput variable to be 2x the frequency of interest
    new_Fs = 2*f(kk);
    skip = floor(Fs/new_Fs);
    if skip == 0
      skip = 1;
    end
    advance = 2*pi*f(kk)/new_Fs;

    N_sum = 50;
    x_down = circ_downsample(x, skip, N_sum);

    phi = 0;
    real_sum = 0;
    imag_sum = 0;

    for nn = 1:N_sum 
      phi = 2*pi*f(kk)*(nn-1)/new_Fs;

      sample = x(nn);
      real_c = cos(phi) * sample;
      imag_c = sin(phi) * sample;
     
      real_sum = real_sum + real_c;
      imag_sum = imag_sum + imag_sum;

    end
    amp = sqrt(real_sum * real_sum + imag_sum * imag_sum);
    X(kk) = amp;
  end
end 