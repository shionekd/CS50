from cs50 import get_string

text = get_string("Text: ").upper()
count_words = 0
count_sentences = 0
count_letters = 0

if (len(text) > 0):
    count_words += 1
    for i in range(len(text)):
        if 'A' <= text[i] <= 'Z':
            count_letters += 1
        elif text[i] == ' ':
            count_words += 1
        elif (text[i] == '!') or (text[i] == '.') or (text[i] == '?'):
            count_sentences += 1

L = count_letters / count_words * 100
S = count_sentences / count_words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 0:
    print("Grade: Before Grade 1")
elif index > 16:
    print("Grade: Grade 16+")
else:
    print("Grade ", index)
