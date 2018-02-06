#Skills Ordering 
import numpy as np
import pickle
import itertools
import csv
import operator 

def unique_file(input_filename, output_filename,input_file1,skill_file):
    input_file = open(input_filename, 'r')
    i_f = open(input_file1,'r')
    s_f = open(skill_file,'r')
    
    file_contents = input_file.read()
    year_contents = i_f.read()
    skills = s_f.read()

    input_file.close()
    i_f.close()
    s_f.close()

    duplicates = []
    
    word_list = file_contents.split()
    year_list = year_contents.split()
    skill = skills.split()
    
    dictionary = dict(zip(word_list,year_list))  
    
    file1 = open(output_filename, 'w')
    
    for i in range(len(dictionary)):

            file1.write(skill[i]+" ("+str(dictionary[skill[i]])+" Years)")
            file1.write("\n") 
    
    '''
    
    for word in word_list:
        if word not in duplicates:
             duplicates.append(word)    
             
    index = []
    for i in range(len(duplicates)):
        index.append(1)
    #index = np.zeros([len(duplicates)])
    dictionary = dict(itertools.izip(duplicates,index))  
    
    for word in word_list:
        if word  in duplicates:
             #dictionary.get(word)                
             dictionary[word] = dictionary[word]+1   
     
    sorted_x = sorted(dictionary.items(), key=operator.itemgetter(1))
    
    for i in range(len(dictionary)):
           file.write(sorted_x[len(dictionary)-1-i][0])
           file.write("\n")
    
    file.close()
    '''

unique_file('Java Developer.txt','F1.txt','Java Developer_Years.txt','JD.txt')

