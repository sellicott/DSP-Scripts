%DSP class 9-10-18

%% bigger example
N = 1*10^3; 
Fs = 8000; 
Ts = 1/Fs; 
delk = 1/(Ts*N); 
%f0 = 1*10^3; %freq of cosine in hertz
f0 = 300; %freq of cosine in hertz

t = 0:Ts:Ts*(N-1); 
k = 0:delk:delk*(N-1); 
x = cos(2*pi*f0*t); 
X = fft(x,N); 

%plot regular  
figure(1)
stem(k,abs(X))
xlabel('k freq')
ylabel('|X(\omega)|')
xlim([0, Fs/2])

% figure(2)
% k = 0:delk*2*pi:delk*(N-1)*2*pi; 
% stem(k,abs(X))
% xlabel('k radian freq')

% %plot it centered at zero
% figure(3)
% k = -pi:2*pi*delk:(pi-delk); 
% stem(k,fftshift(abs(X)))
% xlabel('k radian freq')
