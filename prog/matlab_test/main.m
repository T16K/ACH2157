readChId =  1901003;
writeChId = 1975950;  % Replace with your channel number

writeKey = '2HKHT6XPUGB6ZFCE'; % Replace with your channel write key

[uv, time] = thingSpeakRead(readChId,'Fields',1);
fps = thingSpeakRead(readChId,'Fields',2);
r = thingSpeakRead(readChId,'Fields',3);
n = thingSpeakRead(readChId,'Fields',4);

% t = (i * fps) / uv
% i = 66 / uv

% Compute remain time value
if r == 0
    t = (66 * fps) / (uv * uv);
    if t > 120 
        t = 120; 
    end
else
    t = (66 * fps) / (uv * uv * 2);
    if t > 80 
        t = 80; 
    end
end

% Compute percentage
p = (t - 5 * n) / t * 100;

thingSpeakWrite(writeChId,[uv,t,p],'Fields',[1,2,3],...
'TimeStamps',time,'WriteKey',writeKey);
