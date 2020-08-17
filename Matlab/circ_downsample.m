function x_samp = circ_downsample(x, n, N)
  samp_points = 1:n:n*N;
  if length(samp_points) > length(x)
    error('Trying to take more samples than are in input vector');
  end
  x_samp = x(samp_points);
end