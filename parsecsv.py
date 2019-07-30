#!/usr/bin/python
import csv


csv_file = raw_input('Enter the name of your input file: ')
txt_file = raw_input('Enter the name of your output file: ')

with open(txt_file, "w") as my_output_file:
    with open(csv_file, "r") as my_input_file:
        [ my_output_file.write(" ".join(row)+'\n') for row in csv.reader(my_input_file)]
    my_output_file.close()




# Delete specific columns from file, shell command line
#awk '{for(z=6;z<=14;z++)$z="";$0=$0;$1=$1}1' pseudo_facebook.txt  > tmp.txt 
#awk '!($1="")' tmp.txt > facebook_dataset.txt


#Delete the first row from txt file, shell comand line
#sed '1d' facebook_dataset2d.txt > tmpfile; mv tmpfile facebook_dataset2d.txt 



#delet space in the 3rd column
#awk '{$3=$3};3' facebook_dataset3d.txt > tmp.txt; mv tmp.txt facebook_dataset3d.txt