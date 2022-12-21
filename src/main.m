readChId = 0000000;
writeChId = 0000000;  % replace with your channel number

writeKey = '0000000000000000'; % Replace with your channel write key

% Read the field
uv = thingSpeakRead(readChId,'Fields',1);
fps = thingSpeakRead(readChId,'Fields',2);
remove = thingSpeakRead(readChId,'Fields',3);
number = thingSpeakRead(readChId,'Fields',4);

% Calculate average_uv
average_uv = mean(uv);

% Calculate initial_value
if remove == 0
    initial_value = (66 * 30) / (uv * uv);
    if initial_value > 120; initial_value = 120; end;
else
    initial_value = (66 * 30) / (uv * uv * 2);
    if initial_value > 80; initial_value = 80; end;
end

% Calculate lost_percentage
% lost_percentage = (initial_value - number) / initial_value;

% remain_percentage = 100;

% Calculate remain_percentage
% remain_percentage = remain_percentage - lost_percentage;

% Calculate remain_time
remain_time = initial_value - number;
    
% Write the field
thingSpeakWrite(writeChId,[initial_value],'Fields',[1],...
    'WriteKey',writeKey);
