% Test for a dumb idea to use aliasing to fold audio frequency bins together

N = 5*10^4; 
Fs = 44100; % samples/sec
[y, Fs] = audioread('../inven_11.wav', [1, N]);


Ts = 1/Fs; 
delk = 1/(Ts*N); 
%f0 = 1*10^3; %freq of cosine in hertz

note_idx = 1:89;
notes = 2.^((note_idx - 48)/12) * 440;
f0 = 293; %freq of cosine in hertz
f1 = 43.65;
f3 = 3951;


notes_to_play = (61:1:73-1);
win_len = 440;
t = 0:Ts:Ts*(N-1);
k = 0:delk:delk*(N-1);
sigs = zeros(1, length(t));
for note_num = notes_to_play 
  sigs(1, :) = sigs(1, :) + cos(2*pi*notes(note_num)*t);
end
sig2 = cos(2*pi*f1*t);
% sig3 = cos(2*pi*f3*t);
x = sigs;
X = fft(x,N); 

%plot regular  
figure(1)
stem(k,abs(X))
xlabel('k freq')
ylabel('|X(\omega)|')
% set(gca, 'xscale', 'log');
xlim([0, Fs])

% we want to downsample so we only get the first octave [0, 55Hz]
% therefore we want to sample at twice that rate (110Hz)
lowA = notes(13);
% F_resample = 2*lowA; % 1/sec
F_resample = 2*notes(73)
samp_spacing = round(Fs / F_resample); % samples

% generate a windowing function
omega_s = 2*pi*(lowA + 5)/F_resample;
omega_c = 2*pi*(lowA - 5)/F_resample;
d_omega =  omega_s - omega_c;
% win_len = ceil(8*pi/d_omega);
win = hamming(win_len)';

fir_filt = [
0.05823042648162858
0.013776212102696573
-0.09134011567447117
0.03939770906403897
0.08537966720657984
-0.0011640352019618957
-0.32836864085725365
0.5250164863675381
-0.32836864085725365
-0.0011640352019618957
0.08537966720657984
0.03939770906403897
-0.09134011567447117
0.013776212102696573
0.05823042648162858
];

bins = win_len; 
samps = 1:samp_spacing:win_len*samp_spacing;


Xw = fft(win, bins);

x1 = x(samps);
x1_filt = conv(x1, fir_filt);

X1 = fft(x1,bins); 
T_resample = 1/F_resample; 
delk_resample = 1/(T_resample*bins); 

t1 = 0:T_resample:T_resample*(bins-1); 
k1 = 0:delk_resample:delk_resample*(bins-1); 

%plot regular  
figure(2)
stem(k1,abs(X1))
hold on
% stem(k1, abs(Xw));
xlabel('k freq')
ylabel('|X(\omega)|')
xlim([notes(1), F_resample])
set(gca, 'xscale', 'log');

a_notes = notes(1:12:89);
a_mags = 30 * ones(1, length(a_notes));
stem(a_notes, a_mags, 'color', 'r');

hold off



figure(3)
X2 = cnlohr_dft(sigs, notes);
stem(notes, abs(X2));
xlabel('k freq')
ylabel('|X(\omega)|')
xlim([notes(1), notes(length(notes))])
set(gca, 'xscale', 'log');

disp(note_num);
disp(notes(note_num));
% disp(delk_resample);