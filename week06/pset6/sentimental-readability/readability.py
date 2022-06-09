"""
Usage:
$ python readability.py


Description:
This function grade an input text based on the number of words, letters and sentences
within the text.
The grade is obtained based on the formula of Coleman-Liau:
 - index = 0.0588 * L - 0.296 * S - 15.8


Examples:
$ python readability.py
Text: One fish. Two fish. Red fish. Blue fish.
Before Grade 1

$ python readability.py
Text: Would you like them here or there? I would not like them here or there. I would not like them anywhere.
Grade 2
"""


def main():
    text = input("Text: ")

    # Count letters, words and sentences
    num_letters = count_letters(text)
    num_words = count_words(text)
    num_sentences = count_sentences(text)

    index = int(round(coleman_liau(num_letters, num_words, num_sentences)))

    grade_result = get_grade(index)

    print(grade_result)


# AUXILIAR FUNCTIONS
def count_letters(text):
    """(str)->(int)
    """
    counter = 0
    # only count letters
    for letter in text:
        if letter.isalpha():
            counter += 1

    return counter


def count_words(text):
    """(str)->int
    Every group of letters separated by a space
    count as a word
    """
    # get the length of the list of words in the text
    words = text.split()
    return len(words)


def count_sentences(text):
    """(str)->int
    Every group of words separated by a period,
    exclamation point or question mark indicates the end
    of a sentences.
    """
    sentences = (text.replace("?", ".").replace("!", ".")).split(".")
    return len(sentences) - 1


def coleman_liau(letters, words, sentences):
    """(int, int, int)->float
    """
    # average number of letter per 100 words in the text
    L = (100.0/words) * letters
    # average number of words per 100 words in the text
    S = (100.0/words) * sentences
    # Coleman-Liau index
    return 0.0588 * L - 0.296 * S - 15.8


def get_grade(index):
    """(int)->str
    """
    if index > 16:
        return "Grade 16+"
    elif index < 1:
        return "Before Grade 1"
    else:
        return "Grade " + str(index)


if __name__ == "__main__":
    main()