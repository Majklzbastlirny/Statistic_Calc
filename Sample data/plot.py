#import list from csv file and make histogram
import csv
import matplotlib.pyplot as plt
import numpy as np
import os
import random

#list all files in current folder and let user choose the csv file
files = os.listdir()
print("Choose the source file from the list below")
for i in range(len(files)):
    print(str(i) + ": " + files[i])
dictfile = files[int(input())]

#read csv file and make the histogram of the words
with open(dictfile, 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for row in reader:

        plt.hist(row, bins=100)
        
plt.show()

#save the file and exit
csvfile.close()
print("Press any key to exit")
input()
exit()

