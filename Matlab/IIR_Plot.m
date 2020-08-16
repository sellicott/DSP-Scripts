%clear; clc;

M = 1000;
T_s = 0.001;
step = 2*pi/M;
omega = step:step:step*M;
z = exp(1j*omega);
a = 0.9;
H_z = (1-a).*z./(z-a);

figure(1)
subplot(2, 1, 1)
plot(omega, 20*log10(abs(H_z)), 'linewidth', 2);
ylabel("Magnitude (dB)");
xlabel("Normalized Frequency (rad/sample)")
title('H(z)')
hold on
subplot(2, 1, 2)
plot(omega, angle(H_z), 'linewidth', 2, '--')
ylabel("Phase")
xlabel("Normalized Frequency (rad/sample)")
hold on

