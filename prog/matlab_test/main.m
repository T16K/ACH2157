readChId =  1901003;
writeChId = 1975950;  % replace with your channel number

writeKey = '2HKHT6XPUGB6ZFCE'; % Replace with your channel write key

% Read the field
uv = thingSpeakRead(readChId,'Fields',1,'NumPoints',10);
[fps, time] = thingSpeakRead(readChId,'Fields',2);
remove = thingSpeakRead(readChId,'Fields',3);
number = thingSpeakRead(readChId,'Fields',4);

% Calculate average_uv
average_uv = mean(uv);

% Calculate initial_value
if remove == 0
    initial_value = (66 * fps) / (average_uv * average_uv);
    if initial_value > 120; initial_value = 120; end;
else
    initial_value = (66 * fps) / (average_uv * average_uv * 2);
    if initial_value > 80; initial_value = 80; end;
end
    
% Calculate the percentage decrease in 5 minute
percentage_decrease = 5 * number / initial_value;

% Calculate the percentage the remaining percentage
remaining_percentage = 100 * (1 - percentage_decrease);
    
% Write the field
thingSpeakWrite(writeChId,[remaining_percentage],'Fields',[1],...
    'TimeStamps',time,'WriteKey',writeKey);
