#!/usr/bin/python

import sys

"""Chrisys Text Analyser - Python yeey"""

""" Variables """
count_arg = 0
max_arg = len(sys.argv)
count_words_of_each_file = 0
count_words_of_all_files = 0

words_of_each_file = {}
words_of_all_files = {}

"""(1) analyse arguments"""
""" here should also be the optional [i] thing """
if max_arg < 2:
	print("Provide one or more file(s) as argument!")
	sys.exit()

""" (2) read all the files """
while True:

	count_arg = count_arg + 1
	count_words_of_each_file = 0
	words_of_each_file = {}
	if max_arg <= count_arg:
		print("### TOTAL\n")
		print(count_words_of_all_files, "Words\n")
		equal = 30
		count = 0
		words_of_all_files = sorted(words_of_all_files.items(), key=lambda x: x[1], reverse=True)
		for word, word_key in words_of_all_files:
			percent = float((word_key / count_words_of_all_files) * 100)
			percent = round(percent, 4)
			percent = str(percent)
			quantity = str(word_key)
			print(word.ljust(20), quantity.rjust(10), "(,", percent.rjust(7), "%)", '=' * equal)
			equal = equal - (equal / 10)
			round(equal, 0)
			equal = int(equal)
			if count is 9:
				break
			count += 1
		break

	print("### FILE:", sys.argv[count_arg], "\n")
	try:
		f = open(sys.argv[count_arg],"r")
		for line in f:
			line = line.replace('\n', '')
			line = line.replace('.', '')
			line = line.replace(',', '')
			words = line.split(' ')
			for word in words:
				if word is not '':
					if word not in words_of_all_files:
						words_of_all_files[word] = 1
					else:
						words_of_all_files[word] += 1
					if word not in words_of_each_file:
						words_of_each_file[word] = 1

					else:
						words_of_each_file[word] += 1
					count_words_of_each_file += 1
		f.close
	except IOError:
		print("File not found.")
		sys.exit()

	print(count_words_of_each_file, "Words\n")
	count_words_of_all_files += count_words_of_each_file

	equal = 30
	count = 0
	words_of_each_file = sorted(words_of_each_file.items(), key=lambda x: x[1], reverse=True)
	for word, word_key in words_of_each_file[:10]:
		percent = float((word_key / count_words_of_each_file) * 100)
		percent = round(percent, 4)
		percent = str(percent)
		quantity = str(word_key)
		print(word.ljust(20), quantity.rjust(10), "(,", percent.rjust(7), "%)", '=' * equal)
		equal = equal - (equal / 10)
		round(equal, 0)
		equal = int(equal)
	print("\n\n")

