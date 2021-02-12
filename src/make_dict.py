# Script that will open the words_alpha.txt and
# filter out all the words smaller than 4 letters long.
#
# Output will be saved as spelling_bee_dict.txt
#
#
#
# Code for opening the relative file path taken from:
# https://stackoverflow.com/questions/40416072/reading-file-using-relative-path-in-python-project
#

import os.path

my_path = os.path.abspath(os.path.dirname(__file__))
path = os.path.join(my_path, "../data/words_alpha.txt")
with open(path) as f:
    # Save the github dictionary as a string that we need to pare down
    dictionary = f.read()

    # The new dictionary we will construct for the spelling bee solver
    new_path = os.path.join(my_path, "../data/spelling_bee_dict.txt")
    new_dict = open(new_path, "w")

    d_list = dictionary.split()
    ret_list = list()

    for word in d_list :
        if len(word) >= 4:
            ret_list.append(word)

    dictionary = '\n'.join(ret_list)

    new_dict.write(dictionary)