function Y = fft_from_matlab(y)

fprintf('Inside mat function\n');
assert(isa(y, 'double') && ~isreal(y) && all(size(y) == [64,1]))
Y = fft(y,64);
fprintf('Done FFT Inside mat function\n');

end