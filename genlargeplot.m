data2 = load('C:\Users\anima\Documents\School\CS170\Project_2\Part1\large-test-dataset-1.txt');

for i = 1: size(data2,1) 
    object1 = data2(i,2:end);
    label1  = data2(i,1);

end

subplot(1,2,1);

for i = 1: size(data2,1)
    if data2(i,1) == 1
          plot(data2(i,2),data2(i,28), 'ro');
        cass1 =   plot(data2(i,2),data2(i,28), 'ro');
         hold on;
    elseif data2(i,1) == 2
         plot(data2(i,2),data2(i,28), 'bo');
          cass2 = plot(data2(i,2),data2(i,28), 'bo');
          hold on;
    end
end
xlabel('Feature 1');
ylabel('Feature 27');
title("General Large Best Feat.");
legend([cass1 cass2],{'Class 1', 'Class 2'});

subplot(1,2,2);
for i = 1: size(data2,1)
    if data2(i,1) == 1
        plot(data2(i,25),data2(i,28), 'ro');
       cass1 =   plot(data2(i,25),data2(i,28), 'ro');
        hold on;
    elseif data2(i,1) == 2
        plot(data2(i,25),data2(i,28), 'bo');
       cass2 = plot(data2(i,25),data2(i,28), 'bo');
        hold on;
    end
end
title("General Large Worst Feat.");
xlabel('Feature 24');
ylabel('Feature 27');
legend([cass1 cass2],{'Class 1', 'Class 2'});