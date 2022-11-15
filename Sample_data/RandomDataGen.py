import random
import os
import csv




def main():
    print("Choose the type of data to generate")
    print("1: Random numbers")
    print("2: Random words")
    choice = int(input())
    if choice == 1:
        NumberGen()
    elif choice == 2:
        WordGen()
    else:
        print("Invalid choice")
        exit()

def NumberGen():
    #ask user to enter the name of the CSV file to create
    print("Enter the name of the CSV file to create")
    filename = input()+".csv"
    print("Enter the number of random numbers to generate")
    num = int(input())
    print("Enter the minimum value of the random numbers")
    min = int(input())
    print("Enter the maximum value of the random numbers")
    max = int(input())
    #set random seed as current time in seconds
    random.seed(os.times()[4])




    #create file and write data
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=',')
        for i in range(num):
            writer.writerow([random.randint(min, max)])


    #save the file and exit
    csvfile.close()
    print("File saved as " + filename)
    print("Press any key to exit")
    input()
    exit()

def WordGen():
    #ask user to enter the name of the CSV file to create and if it exists ask user to choose another name
    print("Enter the name of the CSV file to create")
    filename = input()+".csv"
    while os.path.isfile(filename):
        print("File already exists, enter a different name")
        filename = input()+".csv"
        

    print("Enter the number of random words to generate")
    num = int(input())
    print("Enter the minimum length of the random words")
    min = int(input())
    print("Enter the maximum length of the random words")
    max = int(input())
    #ask user to write all characters to exclude from the random words
    print("Use default czech characters to exclude? (y/n)")
    choice = input()
    if choice == "y":
        exclude = "áčďéěíňóřšťúůýžÁČĎÉĚÍŇÓŘŠŤÚŮÝŽćĆłŁńŃśŚźŹżŻ"
    else:
        print("Enter all characters to exclude from the random words")
        exclude = input()


    #set random seed as current time in seconds
    random.seed(os.times()[4])

    #look for dictionary file named "dictionary.txt" in the same directory as the script. if not found,list all files in current folder and let user choose the dictionary file¨
    print("\nLooking for dictionary file named \"dictionary.csv\" in the same directory as the script\n")

    if os.path.isfile("dictionary.csv"):
        dictfile = "dictionary.csv"
        print("Dictionary file found")
    else:
            print("Dictionary file not found")
            files = os.listdir()
            print("Choose the dictionary file from the list below")
            for i in range(len(files)):
             print(str(i) + ": " + files[i])
            dictfile = files[int(input())]

    #open dictionary file and read all lines into list
    with open(dictfile, "r", encoding="utf-8") as f:
        lines = f.readlines()

    #close dictionary file
    f.close()


    #remove all lines that are shorter than minimum length or longer than maximum length
    lines = [line for line in lines if len(line) >= min and len(line) <= max]

    #remove all lines that contain any of the excluded characters ignoring case
    lines = [line for line in lines if not any(c in line.lower() for c in exclude)]



    #write random lines from the list into buffer
    buffer = []
    for i in range(num):
        buffer.append(random.choice(lines))

    #select random lines from the buffer, delete them and replace missing lines by duplicating existing lines
    for i in range(num):
        if random.randint(0, 1) == 0:
            buffer.append(random.choice(buffer))
            buffer.remove(random.choice(buffer))



    #write all lines from the buffer into CSV file
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        for line in buffer:
            writer.writerow([line])
    f.close()

    #remove doublequotes from the file
    with open(filename, "r", newline="") as f:
        lines = f.readlines()  
    f.close()
    lines = [line.replace('"', '') for line in lines]

    #remove lines that dont contain any letters
    lines = [line for line in lines if any(c.isalpha() for c in line)]

    #write all lines back into the file

    with open(filename, "w", newline="") as f:
        f.writelines(lines)
        #print("number of lines: " + str(len(lines)))
    f.close()


    print("Done")
    #close CSV file and exit
    f.close()
    print("Press any key to exit")
    input()
    exit()

main()