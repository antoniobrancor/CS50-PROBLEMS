from cs50 import get_string

letters = 0
words = 1
sentences = 0

#get text
text = get_string ("Text: ")

#count letters
for letter in text:
  if letter.isalpha():
     letters += 1

#count words
for space in text:
    if space.isspace():
        words += 1

#count sentences
sentences = text.count("!") + text.count(".") + text.count("?")

#calculate score
score = (round(0.0588 * ((letters * 100) / words) - 0.296 * ((sentences * 100) / words) - 15.8))

if (score < 1):
    print("Before Grade 1")

if (score > 15):
    print("Grade 16+")

else:
    print(f"Grade {score}")