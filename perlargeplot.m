data4 = load('C:\Users\anima\Documents\School\CS170\Project_2\Part1\CS170_Spring_2023_Large_data__2.txt');

for i = 1: size(data4,1) 
    object1 = data4(i,2:end);
    label1  = data4(i,1);

end


subplot(1,2,1);

for i = 1: size(data4,1)
    if data4(i,1) == 1
        plot(data4(i,32),data4(i,22), 'ro');
         hold on;
         plot(data4(i,32),data4(i,22), 'ro');
         hold on;
    elseif data4(i,1) == 2
        plot(data4(i,32),data4(i,22), 'bo');
         hold on;
          plot(data4(i,32),data4(i,22), 'bo');
          hold on;
    end
end
xlabel('Feature 31');
ylabel('Feature 21');
title("Personal Large Best Feat.");

subplot(1,2,2);
for i = 1: size(data4,1)
    if data4(i,1) == 1
        plot(data4(i,38),data4(i,22), 'ro');
        hold on;
        plot(data4(i,38),data4(i,22), 'ro');
        hold on;
    elseif data4(i,1) == 2
        plot(data4(i,38),data4(i,22), 'bo');
         hold on;
        plot(data4(i,38),data4(i,22), 'bo');
        hold on;
    end
end
title("Personal Large Worst Feat.");
xlabel('Feature 37');
ylabel('Feature 21');
