data1 = load('C:\Users\anima\Documents\School\CS170\Project_2\Part1\small-test-dataset.txt');


for i = 1: size(data1,1) 
    object1 = data1(i,2:end);
    label1  = data1(i,1);

end


subplot(1,2,1);
for i = 1: size(data1,1)
    if data1(i,1) == 1
         cass1 =  plot(data1(i,4),data1(i,6), 'ro');
         plot(data1(i,4),data1(i,6), 'ro');
         hold on;
    elseif data1(i,1) == 2
         plot(data1(i,4),data1(i,6), 'bo');
          cass2 = plot(data1(i,4),data1(i,6), 'bo');
          hold on;
          
    end
end
xlabel('Feature 3');
ylabel('Feature 5');
hold on;
legend([cass1 cass2],{'Class 1', 'Class 2'});
title("General Small Best Feat.");

subplot(1,2,2);
for i = 1: size(data1,1)
    if data1(i,1) == 1
        plot(data1(i,10),data1(i,6), 'ro');
         cass1 =  plot(data1(i,10),data1(i,6), 'ro');
        hold on;
    elseif data1(i,1) == 2
         plot(data1(i,10),data1(i,5), 'bo');
        cass2 = plot(data1(i,10),data1(i,5), 'bo');
        hold on;
    end
end
title("General Small Worst Feat.");
xlabel('Feature 9');
ylabel('Feature 5');
legend([cass1 cass2],{'Class 1', 'Class 2'});
