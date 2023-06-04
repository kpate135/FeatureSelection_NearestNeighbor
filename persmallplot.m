data3 = load('C:\Users\anima\Documents\School\CS170\Project_2\Part1\CS170_Spring_2023_Small_data__2.txt');

for i = 1: size(data3,1) 
    object1 = data3(i,2:end);
    label1  = data3(i,1);

end

subplot(1,2,1);

for i = 1: size(data3,1)
    if data3(i,1) == 1
        plot(data3(i,4),data3(i,10), 'ro');
         hold on;
         plot(data3(i,4),data3(i,10), 'ro');
         hold on;
    elseif data3(i,1) == 2
        plot(data3(i,4),data3(i,10), 'bo');
         hold on;
          plot(data3(i,4),data3(i,10), 'bo');
          hold on;
    end
end
xlabel('Feature 3');
ylabel('Feature 9');
title("Personal Small Best Feat.");

subplot(1,2,2);
for i = 1: size(data3,1)
    if data3(i,1) == 1
        plot(data3(i,6),data3(i,10), 'ro');
        hold on;
        plot(data3(i,6),data3(i,10), 'ro');
        hold on;
    elseif data3(i,1) == 2
        plot(data3(i,6),data3(i,10), 'bo');
         hold on;
        plot(data3(i,6),data3(i,10), 'bo');
        hold on;
    end
end
title("Personal Small Worst Feat.");
xlabel('Feature 5');
ylabel('Feature 9');
