% Configura la comunicación serie
close all
clear all
delete (instrfind({'Port'},{'COM3'}))
comport = 'COM3'; % Reemplaza 'COMx' con el nombre del puerto serie utilizado por tu ESP32
s = serialport(comport, 115200); % Ajusta la velocidad de baudios según la configuración en tu ESP32
% Abre el archivo CSV para escritura
archivoCSV = 'datos_temperatura11.csv';
fid = fopen(archivoCSV, 'w');

%fprintf(fid, 'Tiempo,Temperatura\n'); % Encabezado del archivo CSV
flush(s,"output")

for(i=1:9)
    data = readline(s)
end
tic;
% Lee y guarda los datos en el archivo CSV
for i=1:1600
    data = readline(s); % Lee una línea de datos desde el ESP32
    % Analiza la línea de datos (suponiendo que está en el formato "Tiempo,Temperatura")
    parts = strsplit(data, ',');
    %t(i)=toc;
    tiempo(i) = str2double(parts{1});
    vout(i) = str2double(parts{2});  %temperatura
    vin(i) = str2double(parts{3});   %on/off
    plot(tiempo(:),vout(:),tiempo(:),vin(:),'r');drawnow
    % Escribe los datos en el archivo CSV
    fprintf(fid, '%f,%f,%f\n', tiempo(i), vout(i), vin(i));
end
disp("fin de datos")
% Cierra la comunicación serie y el archivo CSV cuando hayas terminado
fclose(fid);
clear s;
